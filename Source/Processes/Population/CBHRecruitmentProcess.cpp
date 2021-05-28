//============================================================================
// Name        : CBHRecruitmentProcess.cpp
// Author      : S.Rasmussen
// Date        : 13/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
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
#include "CBHRecruitmentProcess.h"

// Using
using std::cout;
using std::endl;
using std::numeric_limits;

//**********************************************************************
// CBHRecruitmentProcess::CBHRecruitmentProcess()
// Default constructor
//**********************************************************************
CBHRecruitmentProcess::CBHRecruitmentProcess() {
  pTimeStepManager            = CTimeStepManager::Instance();
  pInitializationPhaseManager = CInitializationPhaseManager::Instance();

  // Default Vars
  pLayer         = 0;
  sType          = PARAM_BH_RECRUITMENT2;
  bRequiresMerge = false;

  // Register allowed estimables
  registerEstimable(PARAM_R0, &dR0);
  registerEstimable(PARAM_STEEPNESS, &dSteepness);
  // registerEstimable(PARAM_SIGMA_R, &dSigmaR);
  // registerEstimable(PARAM_RHO, &dRho);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_R0);
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_PROPORTIONS);
  pParameterList->registerAllowed(PARAM_AGE);
  pParameterList->registerAllowed(PARAM_STEEPNESS);
  // pParameterList->registerAllowed(PARAM_SIGMA_R);
  // pParameterList->registerAllowed(PARAM_RHO);
  pParameterList->registerAllowed(PARAM_SSB);
  pParameterList->registerAllowed(PARAM_B0);
  pParameterList->registerAllowed(PARAM_SSB_OFFSET);
  pParameterList->registerAllowed(PARAM_YCS_VALUES);
  pParameterList->registerAllowed(PARAM_STANDARDISE_YCS_YEARS);
  pParameterList->registerAllowed(PARAM_LAYER);
}

//**********************************************************************
// void CBHRecruitmentProcess::validate()
// Validate the process
//**********************************************************************
void CBHRecruitmentProcess::validate() {
  try {
    // Assign our variables
    dR0        = pParameterList->getDouble(PARAM_R0);
    iAge       = pParameterList->getInt(PARAM_AGE, true, pWorld->getMinAge());
    dSteepness = pParameterList->getDouble(PARAM_STEEPNESS, true, 1.0);
    sSSB       = pParameterList->getString(PARAM_SSB);
    sB0        = pParameterList->getString(PARAM_B0, true, "");
    iSSBOffset = pParameterList->getInt(PARAM_SSB_OFFSET);
    sLayer     = pParameterList->getString(PARAM_LAYER, true, "");
    // dSigmaR       = pParameterList->getDouble(PARAM_SIGMA_R,true,1.0);
    // dRho          = pParameterList->getDouble(PARAM_RHO,true,0.0);

    pParameterList->fillVector(vProportions, PARAM_PROPORTIONS);
    pParameterList->fillVector(vYCSValues, PARAM_YCS_VALUES);
    pParameterList->fillVector(vStandardiseYCSYears, PARAM_STANDARDISE_YCS_YEARS, true);
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
    // Check that a value of YCSValues supplied for each YCSYear
    if ((int)vYCSValues.size() != (pWorld->getCurrentYear() - pWorld->getInitialYear() + 1))
      CError::errorListSameSize(PARAM_YCS_VALUES, string("model years"));

    // Register our YCS as Estimable
    for (int i = 0; i < (int)vYCSValues.size(); ++i) registerEstimable(PARAM_YCS_VALUES, i, &vYCSValues[i]);

    // Loop Through YCS. Make Sure They Are > 0.0
    foreach (double dValue, vYCSValues) {
      if (!CComparer::isPositive(dValue))
        CError::errorLessThanEqualTo(PARAM_YCS_VALUES, PARAM_ZERO);
    }
  } catch (string& Ex) {
    Ex = "CBHRecruitment.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CBHRecruitmentProcess::build()
// Build the process
//**********************************************************************
void CBHRecruitmentProcess::build() {
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

    // Figure out the when SSB is calcuated w.r.t. recruitment, and then the default iActualOffset
    pTimeStepManager = CTimeStepManager::Instance();

    if (pTimeStepManager->getTimeStepIndexForProcess(sLabel) <= pDerivedQuantity->getTimeStep()) {
      iActualOffset = iSSBOffset - 1;
      if (iActualOffset < 0) {
        CError::errorLessThan(PARAM_YEAR_OFFSET, PARAM_ONE);
      }
    } else {
      iActualOffset = iSSBOffset;
    }

    // Build the Standardise YCS Year Range
    if (vStandardiseYCSYears.size() == 0) {
      for (int i = pWorld->getInitialYear(); i < (pWorld->getCurrentYear() + 1); ++i) {
        vStandardiseYCSYears.push_back(i - iSSBOffset);
      }
    } else if (vStandardiseYCSYears.size() > 1) {
      for (int i = 1; i < (int)vStandardiseYCSYears.size(); ++i) {
        if (vStandardiseYCSYears[i - 1] >= vStandardiseYCSYears[i])
          CError::error(PARAM_YCS_YEARS + string(" is not in numeric order"));
      }
    }

    if (vStandardiseYCSYears[0] < (pWorld->getInitialYear() - iSSBOffset))
      CError::errorLessThan(PARAM_STANDARDISE_YCS_YEARS, PARAM_INITIAL_YEAR);
    if (vStandardiseYCSYears[vStandardiseYCSYears.size() - 1] > (pWorld->getCurrentYear() - iSSBOffset))
      CError::errorGreaterThan(PARAM_STANDARDISE_YCS_YEARS, PARAM_CURRENT_YEAR);

    // rebuild
    rebuild();
  } catch (string& Ex) {
    Ex = "CBHRecruitment.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CBHRecruitmentProcess::rebuild()
// Build the process
//**********************************************************************
void CBHRecruitmentProcess::rebuild() {
#ifndef OPTIMIZE
  try {
#endif

    // Base rebuild
    CProcess::rebuild();

    // reset values
    vSSBValues.resize(0);
    vYCSYears.resize(0);
    vTrueYCSValues.resize(0);
    vRecruitmentValues.resize(0);

    // Create vector of YCS years
    for (int i = pWorld->getInitialYear(); i <= pWorld->getCurrentYear(); ++i) {
      vYCSYears.push_back(i - iSSBOffset);
    }

    // Rescale vYCSValues to get the standardised YCS values over years defined by vStandardiseYCSYears
    double dMeanYCS = 0;
    for (int i = 0; i < (int)vYCSYears.size(); ++i) {
      for (int j = 0; j < (int)vStandardiseYCSYears.size(); ++j) {
        if (vYCSYears[i] == vStandardiseYCSYears[j]) {
          dMeanYCS += vYCSValues[i];
          break;
        }
      }
    }
    dMeanYCS /= vStandardiseYCSYears.size();

    for (int i = 0; i < (int)vYCSYears.size(); ++i) {
      for (int j = 0; j < (int)vStandardiseYCSYears.size(); ++j) {
        if (vYCSYears[i] == vStandardiseYCSYears[j]) {
          // rescale
          vYCSValues[i] = vYCSValues[i] / dMeanYCS;
          break;
        }
      }
    }

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CBHRecruitmentProcess.rebuild(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CBHRecruitmentProcess::execute()
// Execute this process
//**********************************************************************
void CBHRecruitmentProcess::execute() {
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
      double dYCS = vYCSValues[pTimeStepManager->getCurrentYear() - pWorld->getInitialYear()];
      // Get SSB (and SSB:B0 ratio)
      dB0              = pDerivedQuantity->getInitialisationValue(iPhaseB0, (pDerivedQuantity->getInitialisationValuesSize(iPhaseB0)) - 1);
      double dSSBRatio = pDerivedQuantity->getValue(iActualOffset) / dB0;
      // Calculate the Stock-recruit relationship
      double dTrueYCS = dYCS * dSSBRatio / (1 - ((5 * dSteepness - 1) / (4 * dSteepness)) * (1 - dSSBRatio));
      // And apply to calculate this events recruitment
      dAmountPer = dR0 * dTrueYCS;
      // Retain these for later reporting
      vTrueYCSValues.push_back(dTrueYCS);
      vRecruitmentValues.push_back(dAmountPer);
      vSSBValues.push_back(pDerivedQuantity->getValue(iActualOffset));
    }

    // Allocate our recruitment across the cells
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
    Ex = "CBHRecruitment.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CBHRecruitmentProcess::~CBHRecruitmentProcess()
// Destructor
//**********************************************************************
CBHRecruitmentProcess::~CBHRecruitmentProcess() {
  vProportions.clear();
}
