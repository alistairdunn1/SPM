//============================================================================
// Name        : CBHRecruitmentProcess2.cpp
// Author      : A.Dunn
// Date        : 23/05/2021
// Copyright   :
// Description : This is a Beverton-Holt stock recruitment, parametersed with absolute annual recruitment
//============================================================================

// Global headers
#include <iostream>
#include <limits>

// Local headers
#include "../../DerivedQuantities/CDerivedQuantity.h"
#include "../../Helpers/CComparer.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"
#include "../../InitializationPhases/CInitializationPhaseManager.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../TimeSteps/CTimeStepManager.h"
#include "CBHRecruitmentProcess2.h"

// Using
using std::cout;
using std::endl;
using std::numeric_limits;

//**********************************************************************
// CBHRecruitmentProcess2::CBHRecruitmentProcess2()
// Default constructor
//**********************************************************************
CBHRecruitmentProcess2::CBHRecruitmentProcess2() {
  pTimeStepManager            = CTimeStepManager::Instance();
  pInitializationPhaseManager = CInitializationPhaseManager::Instance();

  // Default Vars
  pLayer         = 0;
  sType          = PARAM_BH_RECRUITMENT2;
  bRequiresMerge = false;

  // Register allowed estimables
  registerEstimable(PARAM_STEEPNESS, &dSteepness);
  //  registerEstimable(PARAM_SIGMA_R, &dSigmaR);
  //  registerEstimable(PARAM_RHO, &dRho);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_VALUES);
  pParameterList->registerAllowed(PARAM_YEARS);
  pParameterList->registerAllowed(PARAM_STANDARDISE_RECRUITMENT_YEARS);
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_PROPORTIONS);
  pParameterList->registerAllowed(PARAM_AGE);
  pParameterList->registerAllowed(PARAM_STEEPNESS);
  // pParameterList->registerAllowed(PARAM_SIGMA_R);
  // pParameterList->registerAllowed(PARAM_RHO);
  pParameterList->registerAllowed(PARAM_SSB);
  pParameterList->registerAllowed(PARAM_B0);
  pParameterList->registerAllowed(PARAM_SSB_OFFSET);
  pParameterList->registerAllowed(PARAM_LAYER);
}

//**********************************************************************
// void CBHRecruitmentProcess2::validate()
// Validate the process
//**********************************************************************
void CBHRecruitmentProcess2::validate() {
  try {
    // Assign our variables
    iAge       = pParameterList->getInt(PARAM_AGE, true, pWorld->getMinAge());
    dSteepness = pParameterList->getDouble(PARAM_STEEPNESS, true, 1.0);
    sSSB       = pParameterList->getString(PARAM_SSB);
    sB0        = pParameterList->getString(PARAM_B0, true, "");
    iSSBOffset = pParameterList->getInt(PARAM_SSB_OFFSET);
    sLayer     = pParameterList->getString(PARAM_LAYER, true, "");
    // dSigmaR = pParameterList->getDouble(PARAM_SIGMA_R,true,1.0);
    // dRho = pParameterList->getDouble(PARAM_RHO,true,0.0);
    pParameterList->fillVector(vProportions, PARAM_PROPORTIONS);
    pParameterList->fillVector(vRecruitmentValues, PARAM_VALUES);
    pParameterList->fillVector(vStandardiseRecruitmentYears, PARAM_STANDARDISE_RECRUITMENT_YEARS);
    pParameterList->fillVector(vRecruitmentYears, PARAM_YEARS);
    pParameterList->fillVector(vCategoryList, PARAM_CATEGORIES);

    // Validate parent
    CProcess::validate();

    // local validation
    // iAge must be a valid age
    if (iAge < pWorld->getMinAge())
      CError::errorLessThan(PARAM_AGE, PARAM_MIN_AGE);
    if (iAge > pWorld->getMaxAge())
      CError::errorGreaterThan(PARAM_AGE, PARAM_MAX_AGE);

    // The 2 Vectors must be same size
    if (getCategoryCount() != (int)vProportions.size())
      CError::errorListSameSize(PARAM_CATEGORIES, PARAM_PROPORTIONS);

    // Register our Proportions as Estimable
    for (int i = 0; i < (int)vProportions.size(); ++i) registerEstimable(PARAM_PROPORTIONS, i, &vProportions[i]);

    // Loop Through Proportions. Make Sure They Equal 1.0
    double dRunningTotal = 0.0;
    foreach (double Prop, vProportions) {
      dRunningTotal += Prop;
      if (Prop < TRUE_ZERO)
        CError::errorLessThan(PARAM_PROPORTIONS, PARAM_ZERO);
    }
    // See If It is close enough to 1.0
    if (!CComparer::isEqual(dRunningTotal, 1.0))
      CError::errorNotEqual(PARAM_PROPORTIONS, PARAM_ONE);

    // Check iSSBOffset is a non-negative int
    if (iSSBOffset < 0)
      CError::errorLessThan(PARAM_SSB_OFFSET, PARAM_ZERO);

    //***************************************************
    // Check that a value of RecruitmentValues supplied for each RecruitmentYear in
    if ((int)vRecruitmentValues.size() != (int)vRecruitmentYears.size())
      CError::errorListSameSize(PARAM_YEARS, PARAM_VALUES);

    // Register our RecruitmentValues as Estimable
    for (int i = 0; i < (int)vRecruitmentValues.size(); ++i) registerEstimable(PARAM_VALUES, i, &vRecruitmentValues[i]);

    // Loop Through RecruitmentValues. Make Sure They Are > 0.0
    foreach (double dValue, vRecruitmentValues) {
      if (!CComparer::isPositive(dValue))
        CError::errorLessThanEqualTo(PARAM_VALUES, PARAM_ZERO);
    }
  } catch (string& Ex) {
    Ex = "CBHRecruitment2.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CBHRecruitmentProcess2::build()
// Build the process
//**********************************************************************
void CBHRecruitmentProcess2::build() {
  try {
    // Base Build
    CProcess::build();

    // Get our Layer
    if (sLayer != "")
      pLayer = CLayerManager::Instance()->getNumericLayer(sLayer);

    // Get our derived quantity (SSB)
    pDerivedQuantity = CDerivedQuantityManager::Instance()->getDerivedQuantity(sSSB);

    // Get B0 phase
    if (sB0 == "") {
      iPhaseB0 = pInitializationPhaseManager->getNumberInitializationPhases() - 1;
    } else {
      iPhaseB0 = pInitializationPhaseManager->getInitializationPhaseOrderIndex(sB0);
    }

    // Populate Our Ages Index
    iAgeIndex = pWorld->getColIndexForAge(iAge);

    // Validate our Vectors are all same size
    if (getCategoryCount() != (int)vProportions.size())
      CError::errorListSameSize(PARAM_CATEGORIES, PARAM_PROPORTIONS);

    // Figure out the when SSB is calculated w.r.t. recruitment, and then the default iActualOffset
    pTimeStepManager = CTimeStepManager::Instance();

    if (pTimeStepManager->getTimeStepIndexForProcess(sLabel) <= pDerivedQuantity->getTimeStep()) {
      iActualOffset = iSSBOffset - 1;
      if (iActualOffset < 0) {
        CError::errorLessThan(PARAM_YEAR_OFFSET, PARAM_ONE);
      }
    } else {
      iActualOffset = iSSBOffset;
    }

    // Check the Year Range
    if (vRecruitmentYears.size() > 1) {
      for (int i = 1; i < (int)vRecruitmentYears.size(); ++i) {
        if (vRecruitmentYears[i - 1] >= vRecruitmentYears[i])
          CError::error(PARAM_YEARS + string(" is not in numeric order"));
      }
    }

    if (vRecruitmentYears[0] < (pWorld->getInitialYear() - iSSBOffset))
      CError::errorLessThan(PARAM_YEARS, PARAM_INITIAL_YEAR);
    if (vRecruitmentYears[vRecruitmentYears.size() - 1] > (pWorld->getCurrentYear() - iSSBOffset))
      CError::errorGreaterThan(PARAM_YEARS, PARAM_CURRENT_YEAR);

    // Check the Year Range for standardising
    if (vStandardiseRecruitmentYears.size() > 1) {
      for (int i = 1; i < (int)vStandardiseRecruitmentYears.size(); ++i) {
        if (vStandardiseRecruitmentYears[i - 1] >= vStandardiseRecruitmentYears[i])
          CError::error(PARAM_STANDARDISE_RECRUITMENT_YEARS + string(" is not in numeric order"));
      }
    }

    if (vStandardiseRecruitmentYears[0] < vRecruitmentYears[0])
      CError::errorLessThan(PARAM_STANDARDISE_RECRUITMENT_YEARS, PARAM_YEARS);
    if (vStandardiseRecruitmentYears[vStandardiseRecruitmentYears.size() - 1] > vRecruitmentYears[vRecruitmentYears.size() - 1])
      CError::errorGreaterThan(PARAM_STANDARDISE_RECRUITMENT_YEARS, PARAM_YEARS);

    // rebuild
    rebuild();
  } catch (string& Ex) {
    Ex = "CBHRecruitment2.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CBHRecruitmentProcess2::rebuild()
// Build the process
//**********************************************************************
void CBHRecruitmentProcess2::rebuild() {
#ifndef OPTIMIZE
  try {
#endif

    // Base rebuild
    CProcess::rebuild();

    // reset values
    vSSBValues.resize(0);
    vYCSValues.resize(0);
    vTrueYCSValues.resize(0);
    vAllRecruitmentValues.resize(0);
    vTrueRecruitmentValues.resize(0);
    vAllRecruitmentYears.resize(0);

    // Create R0
    dR0 = 0.0;
    for (int i = 0; i < (int)vRecruitmentYears.size(); ++i) {
      for (int j = 0; j < (int)vStandardiseRecruitmentYears.size(); ++j) {
        if (vRecruitmentYears[i] == vStandardiseRecruitmentYears[j]) {
          dR0 += vRecruitmentValues[i];
          break;
        }
      }
    }
    dR0 = dR0 / (double)vStandardiseRecruitmentYears.size();

    // Create vector of AllRecruitment years, values, and YCS
    for (int i = pWorld->getInitialYear(); i <= pWorld->getCurrentYear(); ++i) {
      vAllRecruitmentYears.push_back(i - iSSBOffset);
      vAllRecruitmentValues.push_back(-1);
    }
    for (int i = 0; i < (int)vAllRecruitmentYears.size(); ++i) {
      vAllRecruitmentValues[i] = dR0;
      for (int j = 0; j < (int)vRecruitmentYears.size(); ++j) {
        if (vAllRecruitmentYears[i] == vRecruitmentYears[j]) {
          vAllRecruitmentValues[i] = vRecruitmentValues[j];
          break;
        }
      }
      vYCSValues.push_back(vAllRecruitmentValues[i] / dR0);
    }

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CBHRecruitmentProcess2.rebuild(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CBHRecruitmentProcess2::execute()
// Execute this process
//**********************************************************************
void CBHRecruitmentProcess2::execute() {
#ifndef OPTIMIZE
  try {
#endif
    // Base Execute
    CProcess::execute();

    if (pRuntimeController->getCurrentState() == STATE_INITIALIZATION) {
      // We are in an initialisation phase
      if (pInitializationPhaseManager->getLastExecutedInitializationPhase() <= iPhaseB0) {
        // If in a phase before we have defined B0, then just assume a constant recruitment of dR0
        dAmountPer = dR0;
      } else {
        // Get our B0 (assumed to be the LAST value in the defined initialisation)
        dB0 = pDerivedQuantity->getInitialisationValue(iPhaseB0, (pDerivedQuantity->getInitialisationValuesSize(iPhaseB0)) - 1);
        // if dB0 is zero, then error out
        if (dB0 <= 0) {
          CError::error("The calculated value of " + string(PARAM_B0)
                        + " is not positive (i.e., <=0). Hence the SSB/B0 ratio cannot be calculated. Check the initialisation phase when " + string(PARAM_B0) + " is defined.");
        } else {
          double dSSBRatio = pDerivedQuantity->getValue(iActualOffset) / dB0;
          // Calculate the Stock-recruit relationship
          double dTrueYCS = 1.0 * dSSBRatio / (1 - ((5 * dSteepness - 1) / (4 * dSteepness)) * (1 - dSSBRatio));
          // And apply to calculate this events recruitment
          dAmountPer = dR0 * dTrueYCS;
        }
      }
    } else {
      // We are not in an initialisation phase
      // Setup Our Variables
      double dRecruitment = vAllRecruitmentValues[pTimeStepManager->getCurrentYear() - pWorld->getInitialYear()];
      // Get SSB (and SSB:B0 ratio)
      dB0              = pDerivedQuantity->getInitialisationValue(iPhaseB0, (pDerivedQuantity->getInitialisationValuesSize(iPhaseB0)) - 1);
      double dSSBRatio = pDerivedQuantity->getValue(iActualOffset) / dB0;
      // Calculate the Stock-recruit relationship
      double dTrueYCS = (dRecruitment / dR0) * dSSBRatio / (1 - ((5 * dSteepness - 1) / (4 * dSteepness)) * (1 - dSSBRatio));
      // And apply to calculate this events recruitment
      dAmountPer = dR0 * dTrueYCS;
      // Retain these for later reporting
      vTrueYCSValues.push_back(dTrueYCS);
      vTrueRecruitmentValues.push_back(dAmountPer);
      vSSBValues.push_back(pDerivedQuantity->getValue(iActualOffset));
    }

    // Allocate recruitment across the cells
    if (pLayer != 0) {
      double dTotal = 0.0;

      for (int i = 0; i < iWorldHeight; ++i) {
        for (int j = 0; j < iWorldWidth; ++j) {
          pBaseSquare = pWorld->getBaseSquare(i, j);
          if (pBaseSquare->getEnabled()) {
            dTotal += pLayer->getValue(i, j);
          }
        }
      }

      if (CComparer::isPositive(dTotal)) {
        dAmountPer /= dTotal;
      } else {
        CError::errorLessThanEqualTo(PARAM_LAYER, PARAM_ZERO);
      }
    } else
      dAmountPer /= pWorld->getEnabledSquareCount();

    // Loop Through The World Grid (i,j)
    for (int i = 0; i < iWorldHeight; ++i) {
      for (int j = 0; j < iWorldWidth; ++j) {
        // Get Current Square, and Difference Equal
        pBaseSquare = pWorld->getBaseSquare(i, j);
        // Check if this square is enabled or not.
        if (!pBaseSquare->getEnabled())
          continue;

        double value = dAmountPer;
        if (pLayer != 0)
          value *= pLayer->getValue(i, j);

        // Loop Through the Categories and Ages we have and Recruit
        for (int k = 0; k < getCategoryCount(); ++k) pBaseSquare->addValue(vCategoryIndex[k], iAgeIndex, (value * vProportions[k]));
      }
    }

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CBHRecruitment2.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CBHRecruitmentProcess2::~CBHRecruitmentProcess2()
// Destructor
//**********************************************************************
CBHRecruitmentProcess2::~CBHRecruitmentProcess2() {
  vProportions.clear();
}
