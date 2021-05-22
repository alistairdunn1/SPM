//============================================================================
// Name        : CProportionsAtLengthByCategoryObservation.cpp
// Author      :
// Date        :
// Copyright   :
// Description :
//============================================================================

// Global Headers
#include <iostream>
#include <limits>
#include <boost/lexical_cast.hpp>

// Local Headers
#include "CProportionsAtLengthByCategoryObservation.h"
#include "../../Helpers/CComparer.h"
#include "../../Helpers/CConvertor.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/ForEach.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Selectivities/CSelectivityManager.h"

// Using
using std::cout;
using std::endl;
using std::numeric_limits;

//**********************************************************************
// CProportionsAtLengthByCategoryObservation::CProportionsAtLengthByCategoryObservation()
// Default Constructor
//**********************************************************************
CProportionsAtLengthByCategoryObservation::CProportionsAtLengthByCategoryObservation()
{
  // Variables
  pLengthResults = 0;
  pCombinedLengthResults = 0;
  dDetectionProbability = 1.0;

  // Register estimables
  registerEstimable(PARAM_PROCESS_ERROR, &dProcessError);
  registerEstimable(PARAM_DETECTION_PROBABILITY, &dDetectionProbability);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_OBS);
  pParameterList->registerAllowed(PARAM_LENGTH_BINS);
  pParameterList->registerAllowed(PARAM_ERROR_VALUE);
  pParameterList->registerAllowed(PARAM_TARGET_CATEGORIES);
  pParameterList->registerAllowed(PARAM_TARGET_SELECTIVITIES);
  pParameterList->registerAllowed(PARAM_DELTA);
  pParameterList->registerAllowed(PARAM_PROCESS_ERROR);
  pParameterList->registerAllowed(PARAM_DETECTION_PROBABILITY);
}

//**********************************************************************
// void CProportionsAtLengthByCategoryObservation::validate()
// Validate the Observation Parameters
//**********************************************************************
void CProportionsAtLengthByCategoryObservation::validate()
{
  try
  {
    // Base Validation
    CObservation::validate();

    // Populate our Parameters
    dProcessError = pParameterList->getDouble(PARAM_PROCESS_ERROR, true, 0);
    dDelta = pParameterList->getDouble(PARAM_DELTA, true, DELTA);
    dDetectionProbability = pParameterList->getDouble(PARAM_DETECTION_PROBABILITY, true, 1.0);
    pParameterList->fillVector(vTargetCategoryNames, PARAM_TARGET_CATEGORIES);
    pParameterList->fillVector(vTargetSelectivityNames, PARAM_TARGET_SELECTIVITIES);

    //Check length of categories and selectivities are equal
    unsigned iCategoryNamesSize = vCategoryNames.size();
    unsigned iSelectivityNamesSize = vSelectivityNames.size();
    if (iCategoryNamesSize != iSelectivityNamesSize)
      CError::errorListSameSize(PARAM_CATEGORIES, PARAM_SELECTIVITIES);

    unsigned iTargetCategoryNamesSize = vTargetCategoryNames.size();
    unsigned iTargetSelectivityNamesSize = vTargetSelectivityNames.size();
    if (iTargetCategoryNamesSize != iTargetSelectivityNamesSize)
      CError::errorListSameSize(PARAM_TARGET_CATEGORIES, PARAM_TARGET_SELECTIVITIES);

    // Check no duplicates
    for (int i = 0; i < (int)iCategoryNamesSize; ++i)
    {
      for (int j = 0; j < (int)iTargetCategoryNamesSize; ++j)
      {
        if (vTargetCategoryNames[j] == vCategoryNames[i])
          CError::errorDuplicate(PARAM_TARGET_CATEGORIES, PARAM_CATEGORIES);
      }
    }

    if (dDelta < 0)
      CError::errorLessThan(PARAM_DELTA, PARAM_ZERO);

    if (dProcessError < 0)
      CError::errorLessThan(PARAM_PROCESS_ERROR, PARAM_ZERO);

    if (dDetectionProbability <= 0)
      CError::errorLessThanEqualTo(PARAM_DETECTION_PROBABILITY, PARAM_ZERO);

    // Get our length bins
    pParameterList->fillVector(vLengthBins, PARAM_LENGTH_BINS);

    // Check LENGTH_BINS are monotonically increasing
    for (int i = 0; i < ((int)vLengthBins.size() - 1); ++i)
    {
      if (vLengthBins[i] >= vLengthBins[i + 1])
      {
        CError::errorNotIncreasing(PARAM_LENGTH_BINS);
      }
    }

    // Get our OBS
    vector<string> vOBS;
    pParameterList->fillVector(vOBS, PARAM_OBS);

    // Check nBins is the same as the number of observations per row
    iNBins = vLengthBins.size() - 1;
    if ((vOBS.size() % (iNBins + 1)) != 0)
      CError::errorListNotSize(PARAM_OBS, iNBins);

    // Check at least 2 length bins
    if (iNBins < 2)
      CError::errorNotEnough(PARAM_LENGTH_BINS);

    for (int i = 0; i < (int)vOBS.size(); i += (iNBins + 1))
    {
      for (int j = 0; j < iNBins; ++j)
      {
        try
        {
          mvObservationMatrix[vOBS[i]].push_back(boost::lexical_cast<double>(vOBS[i + j + 1]));
        }
        catch (boost::bad_lexical_cast &)
        {
          string Ex = string("Non-numeric value in ") + PARAM_OBS + string(" for ") + PARAM_OBSERVATION + string(" ") + getLabel();
          throw Ex;
        }
      }
    }

    // Get our Error Value
    vector<string> vErrorValues;
    pParameterList->fillVector(vErrorValues, PARAM_ERROR_VALUE);

    if (vErrorValues.size() != vOBS.size())
    {
      CError::errorListSameSize(PARAM_OBS, PARAM_ERROR_VALUE);
    }

    for (int i = 0; i < (int)vErrorValues.size(); i += (iNBins + 1))
    {
      for (int j = 0; j < iNBins; ++j)
      {
        try
        {
          mvErrorMatrix[vErrorValues[i]].push_back(boost::lexical_cast<double>(vErrorValues[i + j + 1]));
        }
        catch (boost::bad_lexical_cast &)
        {
          string Ex = string("Non-numeric value in ") + PARAM_ERROR_VALUE + string(" for ") + PARAM_OBSERVATION + string(" ") + getLabel();
          throw Ex;
        }

        // Check for negative values
        if (boost::lexical_cast<double>(vErrorValues[i + j + 1]) < 0.0)
          CError::errorLessThan(PARAM_ERROR_VALUE, PARAM_ZERO);
      }
    }
  }
  catch (string &Ex)
  {
    Ex = "CProportionsAtLengthByCategoryObservation.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProportionsAtLengthByCategoryObservation::build()
// Build our Observation Objects and Relationships
//**********************************************************************
void CProportionsAtLengthByCategoryObservation::build()
{
  try
  {

    // Base Build
    CObservation::build();

    pWorld->fillCategoryVector(vCategories, vCategoryNames);
    pWorld->fillCategoryVector(vTargetCategories, vTargetCategoryNames);
    CSelectivityManager *pSelectivityManager = CSelectivityManager::Instance();
    pSelectivityManager->fillVector(vTargetSelectivities, vTargetSelectivityNames);

    // Create Array of Length Results
    if (pLengthResults == 0)
      pLengthResults = new double[iNBins];
    if (pCombinedLengthResults == 0)
      pCombinedLengthResults = new double[iNBins];

    for (int i = 0; i < iNBins; ++i)
    {
      pLengthResults[i] = 0.0;
      pCombinedLengthResults[i] = 0.0;
    }

    // Validate our N's against the OBS
    // They have to have a 1-to-1 relationship
    bool bMatch = false;
    map<string, vector<double>>::iterator vNPtr = mvErrorMatrix.begin();
    map<string, vector<double>>::iterator vPropPtr = mvObservationMatrix.begin();

    while (vNPtr != mvErrorMatrix.end())
    {
      bMatch = false;
      // Loop Props Looking For Match;
      vPropPtr = mvObservationMatrix.begin();
      while (vPropPtr != mvObservationMatrix.end())
      {
        if ((*vPropPtr).first == (*vNPtr).first)
        {
          bMatch = true;
          break;
        }
        vPropPtr++;
      }

      if (!bMatch)
        throw string(ERROR_MISSING_N_OBS + (*vNPtr).first);

      vNPtr++;
    }
  }
  catch (string &Ex)
  {
    Ex = "CProportionsAtLengthByCategoryObservation.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProportionsAtLengthByCategoryObservation::execute()
// Execute our Observation to generate a score
//**********************************************************************
void CProportionsAtLengthByCategoryObservation::execute()
{
#ifndef OPTIMIZE
  try
  {
#endif

    // Variables
    dScore = 0.0;
    vector<string> vKeys;
    vector<int> vBin;
    vector<int> vLengths;
    vector<string> vGroup;
    vector<double> vExpected;
    vector<double> vObserved;
    vector<double> vProcessError;
    vector<double> vErrorValue;
    vector<double> vScores;

    // Base
    CObservation::execute();
    // Execute the World View to get a Snapshot
    pWorldView->execute();

    // Loop Through Observations
    map<string, vector<double>>::iterator mvObsPtr = mvObservationMatrix.begin();

    // Loop through our proportions
    while (mvObsPtr != mvObservationMatrix.end())
    {
      // Get Square for this Area
      CWorldSquare *pStartSquare = pStartWorldView->getSquare((*mvObsPtr).first);
      CWorldSquare *pSquare = pWorldView->getSquare((*mvObsPtr).first);

      //calculate proportion time_step
      vector<double> vTemp(pSquare->getWidth(), 0);
      for (int i = 0; i < (int)pSquare->getHeight(); ++i)
      {
        for (int j = 0; j < (int)pSquare->getWidth(); ++j)
        {
          double dStartValue = pStartSquare->getValue(i, j);
          double dEndValue = pSquare->getValue(i, j);
          if (sProportionMethod == PARAM_MEAN)
          {
            vTemp[j] = dStartValue + ((dEndValue - dStartValue) * dProportionTimeStep);
          }
          else
          {
            vTemp[j] = std::abs(dStartValue - dEndValue) * dProportionTimeStep;
          }
        }
        for (int j = 0; j < (int)pSquare->getWidth(); ++j)
        {
          pSquare->setValue(i, j, vTemp[j]);
        }
      }

      // Build our 2 length Result arrays so we can compare them to get the proportion to match against our observation.
      for (int i = 0; i < iNBins; ++i)
      {
        // Loop Through Categories
        for (int j = 0; j < (int)vCategories.size(); ++j)
        {
          // Loop Through Ages in that square and do the length conversion
          for (int i = 0; i < (int)pSquare->getWidth(); ++i)
          {
            double dSelectResult = vSelectivities[j]->getResult(i);
            double dNumberAtAge = dSelectResult * pSquare->getAbundanceInCategoryForAge(i, j);
            vector<double> vLengthProportions = pWorld->getLengthFrequency(i, j, vLengthBins);
            for (int l = 0; l < (int)vLengthProportions.size(); ++l)
            {
              pLengthResults[l] += dNumberAtAge * vLengthProportions[l];
            }
          }
        }
        for (int j = 0; j < (int)vTargetCategories.size(); ++j)
        {
          // Loop Through Ages in that square and do the length conversion
          for (int i = 0; i < (int)pSquare->getWidth(); ++i)
          {
            double dSelectResult = vSelectivities[j]->getResult(i);
            double dNumberAtAge = dSelectResult * pSquare->getAbundanceInCategoryForAge(i, j);
            vector<double> vLengthProportions = pWorld->getLengthFrequency(i, j, vLengthBins);
            for (int l = 0; l < (int)vLengthProportions.size(); ++l)
            {
              pCombinedLengthResults[l] += (dNumberAtAge * vLengthProportions[l] * dDetectionProbability);
            }
          }
        }
      }

      // Do our Comparison
      for (int i = 0; i < iNBins; ++i)
      {
        double dExpected = 0.0;
        if (!CComparer::isZero(pLengthResults[i] + pCombinedLengthResults[i]))
          dExpected = pLengthResults[i] / (pLengthResults[i] + pCombinedLengthResults[i]);

        // Store the items we want to calculate scores for
        vKeys.push_back((*mvObsPtr).first);
        vBin
            .push_back(i + 1);
        vExpected.push_back(dExpected);
        vObserved.push_back((*mvObsPtr).second[i]);
        vProcessError.push_back(dProcessError);
        vErrorValue.push_back(mvErrorMatrix[(*mvObsPtr).first][i]);
      }

      // Clear Our Age Results
      for (int i = 0; i < iNBins; ++i)
      {
        pLengthResults[i] = 0.0;
        pCombinedLengthResults[i] = 0.0;
      }
      mvObsPtr++;
    }

    // Simulate or Generate Result?
    if (pRuntimeController->getRunMode() == RUN_MODE_SIMULATION)
    {
      // Simulate our values, then save them
      vector<double> vAdjustedObserved;
      for (int i = 0; i < (int)vObserved.size(); ++i)
        vAdjustedObserved.push_back(vObserved[i] * dDetectionProbability);
      pLikelihood->simulateObserved(vKeys, vAdjustedObserved, vExpected, vErrorValue, vProcessError, dDelta);
      for (int i = 0; i < (int)vObserved.size(); ++i)
        saveComparison(vKeys[i], vBin[i], std::string(""), vExpected[i], vAdjustedObserved[i], vErrorValue[i], vProcessError[i], pLikelihood->adjustErrorValue(vProcessError[i], vErrorValue[i]), 1.0, 0.0);
    }
    else
    { // Generate Score
      dScore = 0.0;

      // Generate Results and save them
      pLikelihood->getResult(vScores, vExpected, vObserved, vErrorValue, vProcessError, dDelta);

      for (int i = 0; i < (int)vScores.size(); ++i)
      {
        dScore += (vScores[i] * dMultiplier);
        saveComparison(vKeys[i], vBin[i], std::string(""), vExpected[i], vObserved[i], vErrorValue[i], vProcessError[i], pLikelihood->adjustErrorValue(vProcessError[i], vErrorValue[i]), dMultiplier, vScores[i]);
      }
    }

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CProportionsAtLengthObservation.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CProportionsAtLengthByCategoryObservation::~CProportionsAtLengthByCategoryObservation()
// Default De-Constructor
//**********************************************************************
CProportionsAtLengthByCategoryObservation::~CProportionsAtLengthByCategoryObservation()
{
  if (pLengthResults != 0)
    delete[] pLengthResults;
  if (pCombinedLengthResults != 0)
    delete[] pCombinedLengthResults;
}
