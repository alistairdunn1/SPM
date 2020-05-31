//============================================================================
// Name        : CProportionsAtLengthObservation.cpp
// Author      : A. Dunn
// Date        : 02/12/2019
// Copyright   : 
// Description :
// $Date$
//============================================================================

// Global Headers
#include <iostream>
#include <boost/lexical_cast.hpp>

// Local Headers
#include "CProportionsAtLengthObservation.h"
#include "../../Helpers/CComparer.h"
#include "../../Helpers/CConvertor.h"
#include "../../Helpers/CCompoundCategories.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../AgeSize/CAgeSizeManager.h"

// Using
using std::cout;
using std::endl;

//**********************************************************************
// CProportionsAtLengthObservation::CProportionsAtLengthObservation()
// Default Constructor
//**********************************************************************
CProportionsAtLengthObservation::CProportionsAtLengthObservation() {

  // Default Values
  pLengthResults      = 0;
  iNBins              = 0;
  bRescale            = false;
  pCategories         = 0;

  // Register estimables
  registerEstimable(PARAM_PROCESS_ERROR, &dProcessError);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_OBS); 
  pParameterList->registerAllowed(PARAM_LENGTH_BINS);
  pParameterList->registerAllowed(PARAM_TOLERANCE);  
  pParameterList->registerAllowed(PARAM_DELTA);
  pParameterList->registerAllowed(PARAM_ERROR_VALUE);
  pParameterList->registerAllowed(PARAM_PROCESS_ERROR);
}

//**********************************************************************
// void CProportionsAtLengthObservation::Validate()
// Validate
//**********************************************************************
void CProportionsAtLengthObservation::validate() {
  try {
    // Base

    CObservation::validate();

    // Populate our Parameters
    dDelta              = pParameterList->getDouble(PARAM_DELTA,true,DELTA);
    dTolerance          = pParameterList->getDouble(PARAM_TOLERANCE,true,0.001);
    dProcessError       = pParameterList->getDouble(PARAM_PROCESS_ERROR,true,0);

    // Read in categories, and construct the vector<vector> of categories and selectivities
    // rows = sets of proportions: columns are the categories to aggregate
    pCategories = new CCompoundCategories;
    pCategories->setCategories(vCategoryNames,getLabel());

    // Validate
    //Check length of categories and selectivities are equal
    unsigned iCategoryNamesSize = pCategories->getNCategories();
    unsigned iSelectivityNamesSize = vSelectivityNames.size();
    if (iCategoryNamesSize != iSelectivityNamesSize)
      CError::errorListSameSize(PARAM_CATEGORIES, PARAM_SELECTIVITIES);

    if (dDelta < 0)
      CError::errorLessThan(PARAM_DELTA, PARAM_ZERO);

    if (dProcessError < 0)
      CError::errorLessThan(PARAM_PROCESS_ERROR, PARAM_ZERO);
    if(sLikelihood == PARAM_DIRICHLET && dProcessError > 1)
      CError::errorGreaterThan(PARAM_PROCESS_ERROR, PARAM_ONE);

    int iNGroups = pCategories->getNRows();

    // Get our length bins
    pParameterList->fillVector(vLengthBins, PARAM_LENGTH_BINS);

    // Check LENGTH_BINS are monotonically increasing
    for (int i = 0; i < ((int)vLengthBins.size()-1); ++i) {
      if(vLengthBins[i] >= vLengthBins[i+1]) {
        CError::errorNotIncreasing(PARAM_LENGTH_BINS);
      }
    }

    // Get our OBS
    vector<string> vOBS;
    pParameterList->fillVector(vOBS, PARAM_OBS);

    // Check nBins is the same as the number of observations per row
    iNBins =  vLengthBins.size() -1;
    if ((vOBS.size() % (iNGroups * iNBins + 1)) !=0)
      CError::errorListNotSize(PARAM_OBS, iNBins * iNGroups);

      // Check at least 2 length bins
    if (iNBins < 2)
      CError::errorNotEnough(PARAM_LENGTH_BINS);

    // Fill in the matrix of observations
    for (int i = 0; i < (int)vOBS.size(); i+=(iNGroups * iNBins + 1)) {
      for (int j = 0; j < (iNGroups * iNBins); ++j) {
        try {
          mvObservationMatrix[vOBS[i]].push_back(boost::lexical_cast<double>(vOBS[i+j+1]));
        } catch (boost::bad_lexical_cast&) {
          string Ex = string("Non-numeric value in ") + PARAM_OBS + string(" for ") + PARAM_OBSERVATION + string(" ") + getLabel();
          throw Ex;
        }

        // Check for non-positive or negative values in our observations  - depends on likelihood
        if(sLikelihood == PARAM_LOGNORMAL) {
          if ((*mvObservationMatrix[vOBS[i]].rbegin()) <= 0.0 ) {
            CError::errorLessThanEqualTo(PARAM_OBS, PARAM_ZERO);
          }
        } else if(sLikelihood == PARAM_MULTINOMIAL || sLikelihood == PARAM_DIRICHLET ) {
          if(boost::lexical_cast<double>(vOBS[i+j+1]) < 0.0) {
            CError::errorLessThan(PARAM_OBS, PARAM_ZERO);
          }
        }
      }
    }

    if (dProcessError < 0)
      CError::errorLessThan(PARAM_PROCESS_ERROR, PARAM_ZERO);

    // Get our Error Value
    vector<string> vErrorValues;
    pParameterList->fillVector(vErrorValues, PARAM_ERROR_VALUE);

    string sThisLikelihood = sLikelihood;
    if(sLikelihood == PARAM_PSEUDO) {
      sThisLikelihood = pParameterList->getString(PARAM_SIMULATION_LIKELIHOOD);
    }

    if(sThisLikelihood == PARAM_LOGNORMAL) {
      if ((vErrorValues.size() % (iNGroups * iNBins + 1)) !=0)
        CError::errorListNotSize(PARAM_ERROR_VALUE, iNBins * iNGroups);
      for (int i = 0; i < (int)vErrorValues.size(); i+=(iNGroups * iNBins + 1)) {
        for (int j = 0; j < (iNGroups * iNBins); ++j) {
          try {
            mvErrorMatrix[vErrorValues[i]].push_back(boost::lexical_cast<double>(vErrorValues[i+j+1]));
          } catch (boost::bad_lexical_cast&) {
            string Ex = string("Non-numeric value in ") + PARAM_ERROR_VALUE + string(" for ") + PARAM_OBSERVATION + string(" ") + getLabel();
            throw Ex;
          }
          // Check for non-positive or negative values in the error - depends on likelihood
          if (boost::lexical_cast<double>(vErrorValues[i+j+1]) <= 0.0 ) {
            CError::errorLessThanEqualTo(PARAM_ERROR_VALUE, PARAM_ZERO);
          }
        }
      }
    } else if(sThisLikelihood == PARAM_MULTINOMIAL || sThisLikelihood == PARAM_DIRICHLET) {
      if ((vErrorValues.size() % 2) != 0)
        throw string(PARAM_ERROR_VALUE + string(ERROR_NOT_CONTAIN_EVEN_ELEMENTS));
      for (int i = 0; i < (int)vErrorValues.size(); i+=2) {
        for (int j = 0; j < (iNGroups * iNBins); ++j) {
          try {
            mvErrorMatrix[vErrorValues[i]].push_back(boost::lexical_cast<double>(vErrorValues[i+1]));
          } catch (boost::bad_lexical_cast&) {
            string Ex = string("Non-numeric value in ") + PARAM_ERROR_VALUE + string(" for ") + PARAM_OBSERVATION + string(" ") + getLabel();
            throw Ex;
          }
          // Check for non-positive or negative values in the error - depends on likelihood
          if (boost::lexical_cast<double>(vErrorValues[i+1]) < 0.0 ) {
            CError::errorLessThan(PARAM_ERROR_VALUE, PARAM_ZERO);
          }
        }
      }
    }

    // Declare maps for later use
    map<string, vector<double> >::iterator vObsPtr = mvObservationMatrix.begin();
    map<string, vector<double> >::iterator vErrPtr = mvErrorMatrix.begin();

    // Loop Through our Partitions
    while (vObsPtr != mvObservationMatrix.end()) {
      // Validate Sizes
      if ((iNBins * iNGroups) > (int)((*vObsPtr).second).size())
        throw string(ERROR_QTY_LESS_PROPORTIONS + (*vObsPtr).first);
      if ((iNBins * iNGroups) < (int)((*vObsPtr).second).size())
        throw string(ERROR_QTY_MORE_PROPORTIONS + (*vObsPtr).first);

      // Rescale if Tolerance is exceeded
      double dRunningTotal = 0.0;
      vector<double>::iterator vPtr3 = ((*vObsPtr).second).begin();
      while (vPtr3 != ((*vObsPtr).second).end()) {
        dRunningTotal += (*vPtr3);
        vPtr3++;
      }

      if (fabs(1.0-dRunningTotal) > dTolerance) {
        vector<double>::iterator vPtr4 = ((*vObsPtr).second).begin();
        while (vPtr4 != ((*vObsPtr).second).end()) {
          (*vPtr4) /= dRunningTotal;
          vPtr4++;
        }
      }
      vObsPtr++;
    }

    // Number of N's must be equal to number of Proportions
    if (mvErrorMatrix.size() != mvObservationMatrix.size()) {
      CError::errorListSameSize(PARAM_N, PARAM_OBS);
    }

    // Validate our N's against the OBS
    // They have to have a 1-to-1 relationship
    bool bMatch = false;

    while (vErrPtr != mvErrorMatrix.end()) {
      bMatch = false;
      // Loop Props Looking For Match;
      vObsPtr = mvObservationMatrix.begin();
      while (vObsPtr != mvObservationMatrix.end()) {
        if ((*vObsPtr).first == (*vErrPtr).first) {
          bMatch = true;
          break;
        }
        vObsPtr++;
      }
      
      if (!bMatch)
        throw string(ERROR_MISSING_N_OBS + (*vErrPtr).first);
  
      vErrPtr++;
    }
  } catch (string &Ex) {
    Ex = "CProportionsAtLengthObservation.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProportionsAtLengthObservation::build()
// Build
//**********************************************************************
void CProportionsAtLengthObservation::build() {
  try {
    // Base Build
    CObservation::build();
  
    // Create Array of Length Results
    if (pLengthResults == 0)
      pLengthResults = new double[iNBins * pCategories->getNRows()];
    for (int i = 0; i < (iNBins * pCategories->getNRows()); ++i)
      pLengthResults[i] = 0.0;
  
  } catch (string &Ex) {
    Ex = "CProportionsAtLengthObservation.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProportionsAtLengthObservation::execute()
// Execute
//**********************************************************************
void CProportionsAtLengthObservation::execute() {
#ifndef OPTIMIZE
  try {
#endif
  // Variables
                      dScore             = 0.0;
  double              dRunningTotal      = 0.0;
  double              dCurrentProp       = 0.0;
  vector<string>      vKeys;
  vector<int>         vBin;
  vector<double>      vLengths;
  vector<string>      vGroup;
  vector<double>      vObserved;
  vector<double>      vExpected;
  vector<double>      vProcessError;
  vector<double>      vErrorValue;
  vector<double>      vScores;

  // Base
  CObservation::execute();
  pWorldView->execute();

  // Loop Through Observations
  map<string, vector<double> >::iterator mvObsPtr = mvObservationMatrix.begin();
  map<string, vector<double> >::iterator mvErrPtr = mvErrorMatrix.begin();

  while (mvObsPtr != mvObservationMatrix.end()) {
    // Get Square for this Area
    CWorldSquare *pStartSquare = pStartWorldView->getSquare((*mvObsPtr).first);
    CWorldSquare *pSquare      = pWorldView->getSquare((*mvObsPtr).first);

    //calculate proportion time_step
    vector<double> vTemp(pSquare->getWidth(),0);
    for (int i = 0; i < (int)pSquare->getHeight(); ++i) {
      for (int j = 0; j < (int)pSquare->getWidth(); ++j) {
        double dStartValue  = pStartSquare->getValue(i, j);
        double dEndValue    = pSquare->getValue(i, j);
        if(sProportionMethod == PARAM_MEAN) {
          vTemp[j] = std::abs(dStartValue + ((dEndValue - dStartValue) * dProportionTimeStep));
        } else {
          vTemp[j] = std::abs((dStartValue - dEndValue) * dProportionTimeStep);
        }
      }
      for (int j = 0; j < (int)pSquare->getWidth(); ++j) {
        pSquare->setValue(i,j,vTemp[j]);
      }
    }
    
    // Loop Through Category Groups
    for (int j = 0; j < pCategories->getNRows(); ++j) {
      vector<double> vLengthFrequency(iNBins);
      // loop Through category elements
      for (int k = 0; k < pCategories->getNElements(j); ++k) {
        // Loop Through Ages in that square and do the length conversion
        for (int i = 0; i < (int)pSquare->getWidth(); ++i) {			  
          double dSelectResult = vSelectivities[pCategories->getIndex(j,k)]->getResult(i);
          double dNumberAtAge = dSelectResult * pSquare->getAbundanceInCategoryForAge(i, pCategories->getCategoryIndex(j,k));
          vector<double> vLengthProportions = pWorld->getLengthFrequency(i ,pCategories->getCategoryIndex(j,k), vLengthBins);
          for(int l = 0; l < (int)vLengthProportions.size(); ++l) {
            vLengthFrequency[l] += dNumberAtAge * vLengthProportions[l];
          }
        }
      }
      for(int m = 0; m < (int)vLengthFrequency.size(); ++m) {
        pLengthResults[m + (j * iNBins)] = vLengthFrequency[m];
      }
    }
    // Populate our Running Total
    dRunningTotal = 0.0;

    for (int i = 0; i < (iNBins * pCategories->getNRows()); ++i)
      dRunningTotal += pLengthResults[i];

    for (int i = 0; i < (pCategories->getNRows()); ++i) {
      for (int j = 0; j < iNBins; ++j) {
        // Get our Proportion
        if(!CComparer::isZero(dRunningTotal))
          dCurrentProp = pLengthResults[(iNBins * i) + j] / dRunningTotal;
        else
          dCurrentProp = 0.0;

        // Store the items we want to calculate scores for
        vKeys.push_back((*mvObsPtr).first);
        vGroup.push_back(pCategories->getGroup(i));
        vBin.push_back(j+1);
        vExpected.push_back(dCurrentProp);
        vObserved.push_back(((*mvObsPtr).second)[(iNBins * i) + j]);
        vProcessError.push_back(dProcessError);
        //identify the correct row of error values and extract the correct error value
        while (mvErrPtr != mvErrorMatrix.end()) {
          if ((*mvErrPtr).first == (*mvObsPtr).first) {
            vErrorValue.push_back(((*mvErrPtr).second)[(iNBins * i) + j]);
            break;
          }
          mvErrPtr++;
        }
      }
    }

    // Clear Our Length Results
    for (int i = 0; i < (iNBins * pCategories->getNRows()); ++i)
      pLengthResults[i] = 0.0;

    mvObsPtr++;
  }

  // Simulate or Generate Result?
  if (pRuntimeController->getRunMode() == RUN_MODE_SIMULATION) {
    // Simulate our values, then save them
    pLikelihood->simulateObserved(vKeys, vObserved, vExpected, vErrorValue, vProcessError, dDelta);
    for (int i = 0; i < (int)vObserved.size(); ++i)
      saveComparison(vKeys[i], vBin[i], vGroup[i], vExpected[i], vObserved[i], vErrorValue[i], vProcessError[i], pLikelihood->adjustErrorValue(vProcessError[i], vErrorValue[i]), 1.0, 0.0);

  } else { // Generate Score
    dScore = pLikelihood->getInitialScore(vKeys, vExpected, vObserved, vProcessError, vErrorValue, dDelta);

    // Generate Results and save them
    pLikelihood->getResult(vScores, vExpected, vObserved, vErrorValue, vProcessError, dDelta);
    for (int i = 0; i < (int)vScores.size(); ++i) {
      dScore += (vScores[i] * dMultiplier);
      saveComparison(vKeys[i], vBin[i], vGroup[i], vExpected[i], vObserved[i], vErrorValue[i], vProcessError[i], pLikelihood->adjustErrorValue(vProcessError[i], vErrorValue[i]), dMultiplier, vScores[i]);
    }
  }

#ifndef OPTIMIZE
  } catch (string &Ex) {
    Ex = "CProportionsAtLengthObservation.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CProportionsAtLengthObservation::~CProportionsAtLengthObservation()
// Default De-Constructor
//**********************************************************************
CProportionsAtLengthObservation::~CProportionsAtLengthObservation() {
  // Clear Length Results
  if (pLengthResults != 0)
    delete [] pLengthResults;
}
