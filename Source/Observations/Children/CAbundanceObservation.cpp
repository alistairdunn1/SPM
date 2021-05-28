//============================================================================
// Name        : CAbundanceObservation.cpp
// Author      : S.Rasmussen
// Date        : 4/04/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Headers
#include "CAbundanceObservation.h"

#include <boost/lexical_cast.hpp>

#include "../../Catchabilities/CCatchability.h"
#include "../../Catchabilities/CCatchabilityManager.h"
#include "../../Helpers/CConvertor.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "../../Selectivities/CSelectivity.h"

//**********************************************************************
// CAbundanceObservation::CAbundanceObservation()
// Default Constructor
//**********************************************************************
CAbundanceObservation::CAbundanceObservation() {
  // Variables
  sCatchability = "";
  pCatchability = 0;

  // Register estimables
  registerEstimable(PARAM_PROCESS_ERROR, &dProcessError);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_CATCHABILITY);
  pParameterList->registerAllowed(PARAM_OBS);
  pParameterList->registerAllowed(PARAM_ERROR_VALUE);
  pParameterList->registerAllowed(PARAM_DELTA);
  pParameterList->registerAllowed(PARAM_PROCESS_ERROR);
}

//**********************************************************************
// void CAbundanceObservation::validate()
// validate
//**********************************************************************
void CAbundanceObservation::validate() {
  try {
    // Base Validate
    CObservation::validate();

    // Check length of categories and selectivites are equal
    unsigned iCategoryNamesSize    = vCategoryNames.size();
    unsigned iSelectivityNamesSize = vSelectivityNames.size();

    if (iCategoryNamesSize != iSelectivityNamesSize)
      CError::errorListSameSize(PARAM_CATEGORIES, PARAM_SELECTIVITIES);

    // Get our Parameters
    sCatchability = pParameterList->getString(PARAM_CATCHABILITY);
    dDelta        = pParameterList->getDouble(PARAM_DELTA, true, DELTA);
    dProcessError = pParameterList->getDouble(PARAM_PROCESS_ERROR, true, 0);

    if (dDelta < 0)
      CError::errorLessThan(PARAM_DELTA, PARAM_ZERO);

    // Get our OBS
    vector<string> vOBS;
    pParameterList->fillVector(vOBS, PARAM_OBS);

    if ((vOBS.size() % 2) != 0)
      CError::errorPairs(PARAM_OBS);

    for (int i = 0; i < (int)vOBS.size(); i += 2) {
      try {
        mProportionMatrix[vOBS[i]] = boost::lexical_cast<double>(vOBS[i + 1]);
      } catch (boost::bad_lexical_cast&) {
        string Ex = string("Non-numeric value in ") + PARAM_OBS + string(" for ") + PARAM_OBSERVATION + string(" ") + getLabel();
        throw Ex;
      }

      // Check for non-positive values in our observation values (for all likelihoods except normal)
      //       or negative values in the normal likelihood
      if (sLikelihood == PARAM_NORMAL) {
        if (mProportionMatrix[vOBS[i]] < 0.0)
          CError::errorLessThanEqualTo(PARAM_OBS, PARAM_ZERO);
      } else {
        if (mProportionMatrix[vOBS[i]] <= 0.0)
          CError::errorLessThanEqualTo(PARAM_OBS, PARAM_ZERO);
      }
    }

    if (dProcessError < 0)
      CError::errorLessThan(PARAM_PROCESS_ERROR, PARAM_ZERO);

    // Get our ErrorValues
    vector<string> vErrorValues;
    pParameterList->fillVector(vErrorValues, PARAM_ERROR_VALUE);

    if ((vErrorValues.size() % 2) != 0)
      CError::errorPairs(PARAM_ERROR_VALUE);

    for (int i = 0; i < (int)vErrorValues.size(); i += 2) {
      try {
        mErrorValue[vErrorValues[i]] = boost::lexical_cast<double>(vErrorValues[i + 1]);
      } catch (boost::bad_lexical_cast&) {
        string Ex = string("Non-numeric value in ") + PARAM_ERROR_VALUE + string(" for ") + PARAM_OBSERVATION + string(" ") + getLabel();
        throw Ex;
      }

      // Check for non-positive values in our error values (for all likihoods)
      if (mErrorValue[vErrorValues[i]] <= 0.0)
        CError::errorLessThanEqualTo(PARAM_ERROR_VALUE, PARAM_ZERO);
    }

    // Validate our vErrorValues's to make sure we have the right amount for our
    // Observations
    bool                          bMatch         = false;
    map<string, double>::iterator mErrorValuePtr = mErrorValue.begin();
    map<string, double>::iterator mPropPtr       = mProportionMatrix.begin();

    while (mErrorValuePtr != mErrorValue.end()) {
      // Reset Vars
      bMatch   = false;
      mPropPtr = mProportionMatrix.begin();

      while (mPropPtr != mProportionMatrix.end()) {
        if ((*mPropPtr).first == (*mErrorValuePtr).first) {
          bMatch = true;
          break;
        }
        mPropPtr++;
      }

      if (!bMatch)
        CError::errorNoMatch(PARAM_ERROR_VALUE, (*mErrorValuePtr).first, PARAM_OBS);

      mErrorValuePtr++;
    }
  } catch (string& Ex) {
    Ex = "CAbundanceObservation.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAbundanceObservation::build()
// build
//**********************************************************************
void CAbundanceObservation::build() {
  try {
    // Base build
    CObservation::build();

    // Get Categories
    pWorld->fillCategoryVector(vCategories, vCategoryNames);

    // Build relationships
    CCatchabilityManager* pCatchabilityManager = CCatchabilityManager::Instance();
    pCatchability                              = pCatchabilityManager->getCatchability(sCatchability);
  } catch (string& Ex) {
    Ex = "CAbundanceObservation.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAbundanceObservation::execute()
// Execute
//**********************************************************************
void CAbundanceObservation::execute() {
#ifndef OPTIMIZE
  try {
#endif
    // Variables
    dScore                        = 0.0;
    double         dExpectedTotal = 0.0;
    vector<string> vKeys;
    vector<double> vExpected;
    vector<double> vObserved;
    vector<double> vProcessError;
    vector<double> vErrorValue;
    vector<double> vScores;

    // Base
    CObservation::execute();

    pWorldView->execute();

    // Loop Through Obs
    map<string, double>::iterator mPropPtr = mProportionMatrix.begin();
    while (mPropPtr != mProportionMatrix.end()) {
      // Reset Vars
      dExpectedTotal = 0.0;

      CWorldSquare* pStartSquare = pStartWorldView->getSquare((*mPropPtr).first);
      CWorldSquare* pSquare      = pWorldView->getSquare((*mPropPtr).first);

      for (int i = 0; i < (int)vCategories.size(); ++i) {
        for (int j = 0; j < pSquare->getWidth(); ++j) {
          double dSelectResult = vSelectivities[i]->getResult(j);

          double dStartValue = pStartSquare->getAbundanceInCategoryForAge(j, vCategories[i]);
          double dEndValue   = pSquare->getAbundanceInCategoryForAge(j, vCategories[i]);
          double dFinalValue = 0.0;
          if (sProportionMethod == PARAM_MEAN) {
            dFinalValue = dStartValue + ((dEndValue - dStartValue) * dProportionTimeStep);
          } else {
            dFinalValue = std::abs(dStartValue - dEndValue) * dProportionTimeStep;
          }
          dExpectedTotal += dSelectResult * dFinalValue;
        }
      }

      // Note: dExpectedTotal is total number of fish the model has for that
      // Proportion Label across all squares in that layer where that
      // label is used.
      dExpectedTotal *= pCatchability->getQ();
      double dErrorValue = mErrorValue[(*mPropPtr).first];

      // Store our Values
      vKeys.push_back((*mPropPtr).first);
      vExpected.push_back(dExpectedTotal);
      vObserved.push_back((*mPropPtr).second);
      vErrorValue.push_back(dErrorValue);
      vProcessError.push_back(dProcessError);

      mPropPtr++;
    }

    // Simulate or Generate Result?
    if (pRuntimeController->getRunMode() == RUN_MODE_SIMULATION) {
      // Simulate our values, then save them
      pLikelihood->simulateObserved(vKeys, vObserved, vExpected, vErrorValue, vProcessError, dDelta);
      for (int i = 0; i < (int)vObserved.size(); ++i)
        saveComparison(vKeys[i], vExpected[i], vObserved[i], vErrorValue[i], vProcessError[i], pLikelihood->adjustErrorValue(vProcessError[i], vErrorValue[i]), 1.0, 0.0);
    } else {  // Generate Score
      dScore = 0.0;

      // Generate Results and save them
      pLikelihood->getResult(vScores, vExpected, vObserved, vErrorValue, vProcessError, dDelta);
      for (int i = 0; i < (int)vScores.size(); ++i) {
        dScore += (vScores[i] * dMultiplier);
        saveComparison(vKeys[i], vExpected[i], vObserved[i], vErrorValue[i], vProcessError[i], pLikelihood->adjustErrorValue(vProcessError[i], vErrorValue[i]), dMultiplier,
                       vScores[i]);
      }
    }

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CAbundanceObservation.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CAbundanceObservation::getCatchability()
// Get catchabilty
//**********************************************************************
double CAbundanceObservation::getCatchability() {
  double Q = pCatchability->getQ();
  return (Q);
}

//**********************************************************************
// CAbundanceObservation::~CAbundanceObservation()
// Default De-Constructor
//**********************************************************************
CAbundanceObservation::~CAbundanceObservation() {}
