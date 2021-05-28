//============================================================================
// Name        : CProportionsByCategoryObservation.cpp
// Author      : S.Rasmussen
// Date        : 1/05/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global Headers
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <limits>

// Local Headers
#include "../../Helpers/CComparer.h"
#include "../../Helpers/CConvertor.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/ForEach.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Selectivities/CSelectivityManager.h"
#include "CProportionsByCategoryObservation.h"

// Using
using std::cout;
using std::endl;
using std::numeric_limits;

//**********************************************************************
// CProportionsByCategoryObservation::CProportionsByCategoryObservation()
// Default Constructor
//**********************************************************************
CProportionsByCategoryObservation::CProportionsByCategoryObservation() {
  // Variables
  pAgeResults           = 0;
  pCombinedAgeResults   = 0;
  iMinAge               = -1;
  iMaxAge               = -1;
  bAgePlus              = false;
  dDetectionProbability = 1.0;

  // Register estimables
  registerEstimable(PARAM_PROCESS_ERROR, &dProcessError);
  registerEstimable(PARAM_DETECTION_PROBABILITY, &dDetectionProbability);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_MIN_AGE);
  pParameterList->registerAllowed(PARAM_MAX_AGE);
  pParameterList->registerAllowed(PARAM_AGE_PLUS_GROUP);
  pParameterList->registerAllowed(PARAM_OBS);
  pParameterList->registerAllowed(PARAM_ERROR_VALUE);
  pParameterList->registerAllowed(PARAM_TARGET_CATEGORIES);
  pParameterList->registerAllowed(PARAM_TARGET_SELECTIVITIES);
  pParameterList->registerAllowed(PARAM_DELTA);
  pParameterList->registerAllowed(PARAM_PROCESS_ERROR);
  pParameterList->registerAllowed(PARAM_DETECTION_PROBABILITY);
}

//**********************************************************************
// void CProportionsByCategoryObservation::validate()
// Validate the Observation Parameters
//**********************************************************************
void CProportionsByCategoryObservation::validate() {
  try {
    // Base Validation
    CObservation::validate();

    // Get our Variables from ParameterList
    dDelta                = pParameterList->getDouble(PARAM_DELTA, true, DELTA);
    iMinAge               = pParameterList->getInt(PARAM_MIN_AGE);
    iMaxAge               = pParameterList->getInt(PARAM_MAX_AGE);
    bAgePlus              = pParameterList->getBool(PARAM_AGE_PLUS_GROUP, true, true);
    dProcessError         = pParameterList->getDouble(PARAM_PROCESS_ERROR, true, 0);
    dDetectionProbability = pParameterList->getDouble(PARAM_DETECTION_PROBABILITY, true, 1.0);
    pParameterList->fillVector(vTargetCategoryNames, PARAM_TARGET_CATEGORIES);
    pParameterList->fillVector(vTargetSelectivityNames, PARAM_TARGET_SELECTIVITIES);

    // Check length of categories and selectivities are equal
    unsigned iCategoryNamesSize    = vCategoryNames.size();
    unsigned iSelectivityNamesSize = vSelectivityNames.size();
    if (iCategoryNamesSize != iSelectivityNamesSize)
      CError::errorListSameSize(PARAM_CATEGORIES, PARAM_SELECTIVITIES);

    unsigned iTargetCategoryNamesSize    = vTargetCategoryNames.size();
    unsigned iTargetSelectivityNamesSize = vTargetSelectivityNames.size();
    if (iTargetCategoryNamesSize != iTargetSelectivityNamesSize)
      CError::errorListSameSize(PARAM_TARGET_CATEGORIES, PARAM_TARGET_SELECTIVITIES);

    // Check no duplicates
    for (int i = 0; i < (int)iCategoryNamesSize; ++i) {
      for (int j = 0; j < (int)iTargetCategoryNamesSize; ++j) {
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

    // Find out the Spread in Ages
    int iAgeSpread = (iMaxAge + 1) - iMinAge;

    if (iMinAge < pWorld->getMinAge())
      CError::errorLessThan(PARAM_MIN_AGE, PARAM_MIN_AGE);
    if (iMaxAge > pWorld->getMaxAge())
      CError::errorGreaterThan(PARAM_MAX_AGE, PARAM_MAX_AGE);
    if (dProcessError < 0)
      CError::errorLessThan(PARAM_PROCESS_ERROR, PARAM_ZERO);

    // Get our OBS
    vector<string> vOBS;
    pParameterList->fillVector(vOBS, PARAM_OBS);

    if ((vOBS.size() % (iAgeSpread + 1)) != 0)
      throw string("OBS not right amount");

    for (int i = 0; i < (int)vOBS.size(); i += (iAgeSpread + 1)) {
      for (int j = 0; j < iAgeSpread; ++j) {
        try {
          mvProportionMatrix[vOBS[i]].push_back(boost::lexical_cast<double>(vOBS[i + j + 1]));
        } catch (boost::bad_lexical_cast&) {
          string Ex = string("Non-numeric value in ") + PARAM_OBS + string(" for ") + PARAM_OBSERVATION + string(" ") + getLabel();
          throw Ex;
        }
      }
    }

    // Get our Error Value
    vector<string> vErrorValues;
    pParameterList->fillVector(vErrorValues, PARAM_ERROR_VALUE);

    if (vErrorValues.size() != vOBS.size()) {
      CError::errorListSameSize(PARAM_OBS, PARAM_ERROR_VALUE);
    }

    for (int i = 0; i < (int)vErrorValues.size(); i += (iAgeSpread + 1)) {
      for (int j = 0; j < iAgeSpread; ++j) {
        try {
          mvErrorValue[vErrorValues[i]].push_back(boost::lexical_cast<double>(vErrorValues[i + j + 1]));
        } catch (boost::bad_lexical_cast&) {
          string Ex = string("Non-numeric value in ") + PARAM_ERROR_VALUE + string(" for ") + PARAM_OBSERVATION + string(" ") + getLabel();
          throw Ex;
        }

        // Check for negative values
        if (boost::lexical_cast<double>(vErrorValues[i + j + 1]) < 0.0)
          CError::errorLessThan(PARAM_ERROR_VALUE, PARAM_ZERO);
      }
    }
  } catch (string& Ex) {
    Ex = "CProportionsByCategoryObservation.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProportionsByCategoryObservation::build()
// Build our Observation Objects and Relationships
//**********************************************************************
void CProportionsByCategoryObservation::build() {
  try {
    // Base Build
    CObservation::build();

    pWorld->fillCategoryVector(vCategories, vCategoryNames);
    pWorld->fillCategoryVector(vTargetCategories, vTargetCategoryNames);
    CSelectivityManager* pSelectivityManager = CSelectivityManager::Instance();
    pSelectivityManager->fillVector(vTargetSelectivities, vTargetSelectivityNames);

    // Create Array of Age Results
    iAgeSpread = (iMaxAge + 1) - iMinAge;

    if (pAgeResults == 0)
      pAgeResults = new double[iAgeSpread];
    for (int i = 0; i < iAgeSpread; ++i) pAgeResults[i] = 0.0;

    if (pCombinedAgeResults == 0)
      pCombinedAgeResults = new double[iAgeSpread];
    for (int i = 0; i < iAgeSpread; ++i) pCombinedAgeResults[i] = 0.0;

    // Validate our N's against the OBS
    // They have to have a 1-to-1 relationship
    bool                                  bMatch   = false;
    map<string, vector<double>>::iterator vNPtr    = mvErrorValue.begin();
    map<string, vector<double>>::iterator vPropPtr = mvProportionMatrix.begin();

    while (vNPtr != mvErrorValue.end()) {
      bMatch = false;
      // Loop Props Looking For Match;
      vPropPtr = mvProportionMatrix.begin();
      while (vPropPtr != mvProportionMatrix.end()) {
        if ((*vPropPtr).first == (*vNPtr).first) {
          bMatch = true;
          break;
        }
        vPropPtr++;
      }

      if (!bMatch)
        throw string(ERROR_MISSING_N_OBS + (*vNPtr).first);

      vNPtr++;
    }
  } catch (string& Ex) {
    Ex = "CProportionsByCategoryObservation.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProportionsByCategoryObservation::execute()
// Execute our Observation to generate a score
//**********************************************************************
void CProportionsByCategoryObservation::execute() {
  // Variables
  int            iSquareAgeOffset = iMinAge - pWorld->getMinAge();
  vector<string> vKeys;
  vector<int>    vAges;
  vector<double> vExpected;
  vector<double> vObserved;
  vector<double> vProcessError;
  vector<double> vErrorValue;
  vector<double> vScores;
  dScore = 0.0;

  // Base
  CObservation::execute();
  // Execute the World View to get a Snapshot
  pWorldView->execute();

  // Loop through our proportions
  map<string, vector<double>>::iterator mvPropPtr = mvProportionMatrix.begin();
  while (mvPropPtr != mvProportionMatrix.end()) {
    // Get Square for this Area
    CWorldSquare* pStartSquare = pStartWorldView->getSquare((*mvPropPtr).first);
    CWorldSquare* pSquare      = pWorldView->getSquare((*mvPropPtr).first);

    // Build our 2 Age Result arrays so we can compare them to get the
    // proportion to match against our observation.
    for (int i = 0; i < iAgeSpread; ++i) {
      // Loop Through Categories
      for (int j = 0; j < (int)vCategories.size(); ++j) {
        double dSelectResult    = vSelectivities[j]->getResult(i);
        double dStartValue      = pStartSquare->getAbundanceInCategoryForAge((i + iSquareAgeOffset), vCategories[j]);
        double dEndValue        = pSquare->getAbundanceInCategoryForAge((i + iSquareAgeOffset), vCategories[j]);
        double dProportionValue = 0.0;
        if (sProportionMethod == PARAM_MEAN) {
          dProportionValue = dStartValue + ((dEndValue - dStartValue) * dProportionTimeStep);
        } else {
          dProportionValue = std::abs(dStartValue - dEndValue) * dProportionTimeStep;
        }
        pAgeResults[i] += dSelectResult * dProportionValue;
      }
      for (int j = 0; j < (int)vTargetCategories.size(); ++j) {
        double dSelectResult    = vTargetSelectivities[j]->getResult(i);
        double dStartValue      = pStartSquare->getAbundanceInCategoryForAge((i + iSquareAgeOffset), vTargetCategories[j]);
        double dEndValue        = pSquare->getAbundanceInCategoryForAge((i + iSquareAgeOffset), vTargetCategories[j]);
        double dProportionValue = 0.0;
        if (sProportionMethod == PARAM_MEAN) {
          dProportionValue = dStartValue + ((dEndValue - dStartValue) * dProportionTimeStep);
        } else {
          dProportionValue = std::abs(dStartValue - dEndValue) * dProportionTimeStep;
        }
        pCombinedAgeResults[i] += (dSelectResult * dProportionValue * dDetectionProbability);
      }
    }

    // If we have an age_plus_group we wanna add all + ages to the highest specified
    if (bAgePlus) {
      // Loop Through Plus Group Ages in that square and add them to count for the Plus group
      for (int i = iAgeSpread + iSquareAgeOffset; i < pWorld->getAgeSpread(); ++i) {
        // Loop Through Categories
        for (int j = 0; j < (int)vCategories.size(); ++j) {
          double dSelectResult    = vSelectivities[j]->getResult(i);
          double dStartValue      = pStartSquare->getAbundanceInCategoryForAge(i, vCategories[j]);
          double dEndValue        = pSquare->getAbundanceInCategoryForAge(i, vCategories[j]);
          double dProportionValue = 0.0;
          if (sProportionMethod == PARAM_MEAN) {
            dProportionValue = dStartValue + ((dEndValue - dStartValue) * dProportionTimeStep);
          } else {
            dProportionValue = std::abs(dStartValue - dEndValue) * dProportionTimeStep;
          }
          pAgeResults[iAgeSpread - 1] += dSelectResult * dProportionValue;
        }
        for (int j = 0; j < (int)vTargetCategories.size(); ++j) {
          double dSelectResult    = vTargetSelectivities[j]->getResult(i);
          double dStartValue      = pStartSquare->getAbundanceInCategoryForAge(i, vTargetCategories[j]);
          double dEndValue        = pSquare->getAbundanceInCategoryForAge(i, vTargetCategories[j]);
          double dProportionValue = 0.0;
          if (sProportionMethod == PARAM_MEAN) {
            dProportionValue = dStartValue + ((dEndValue - dStartValue) * dProportionTimeStep);
          } else {
            dProportionValue = std::abs(dStartValue - dEndValue) * dProportionTimeStep;
          }
          pCombinedAgeResults[iAgeSpread - 1] += (dSelectResult * dProportionValue * dDetectionProbability);
        }
      }
    }

    // Do our Comparison
    for (int i = 0; i < iAgeSpread; ++i) {
      double dExpected = 0.0;
      if (!CComparer::isZero(pAgeResults[i] + pCombinedAgeResults[i]))
        dExpected = pAgeResults[i] / (pAgeResults[i] + pCombinedAgeResults[i]);

      // Store the items we want to calculate scores for
      vKeys.push_back((*mvPropPtr).first);
      vAges.push_back(i + iMinAge);
      vExpected.push_back(dExpected);
      vObserved.push_back((*mvPropPtr).second[i]);
      vProcessError.push_back(dProcessError);
      vErrorValue.push_back(mvErrorValue[(*mvPropPtr).first][i]);
    }

    // Clear Our Age Results
    for (int i = 0; i < iAgeSpread; ++i) {
      pAgeResults[i]         = 0.0;
      pCombinedAgeResults[i] = 0.0;
    }
    mvPropPtr++;
  }

  // Simulate or Generate Result?
  if (pRuntimeController->getRunMode() == RUN_MODE_SIMULATION) {
    // Simulate our values, then save them
    vector<double> vAdjustedObserved;
    for (int i = 0; i < (int)vObserved.size(); ++i) vAdjustedObserved.push_back(vObserved[i] * dDetectionProbability);
    pLikelihood->simulateObserved(vKeys, vAdjustedObserved, vExpected, vErrorValue, vProcessError, dDelta);
    for (int i = 0; i < (int)vObserved.size(); ++i)
      saveComparison(vKeys[i], vAges[i], std::string(""), vExpected[i], vAdjustedObserved[i], vErrorValue[i], vProcessError[i],
                     pLikelihood->adjustErrorValue(vProcessError[i], vErrorValue[i]), 1.0, 0.0);
  } else {  // Generate Score
    dScore = 0.0;

    // Generate Results and save them
    pLikelihood->getResult(vScores, vExpected, vObserved, vErrorValue, vProcessError, dDelta);
    for (int i = 0; i < (int)vScores.size(); ++i) {
      dScore += (vScores[i] * dMultiplier);
      saveComparison(vKeys[i], vAges[i], std::string(""), vExpected[i], vObserved[i], vErrorValue[i], vProcessError[i],
                     pLikelihood->adjustErrorValue(vProcessError[i], vErrorValue[i]), dMultiplier, vScores[i]);
    }
  }
}

//**********************************************************************
// CProportionsByCategoryObservation::~CProportionsByCategoryObservation()
// Default De-Constructor
//**********************************************************************
CProportionsByCategoryObservation::~CProportionsByCategoryObservation() {
  if (pAgeResults != 0)
    delete[] pAgeResults;
  if (pCombinedAgeResults != 0)
    delete[] pCombinedAgeResults;
}
