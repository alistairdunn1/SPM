//============================================================================
// Name        : CHollingMortalityRateProcess.cpp
// Author      : S.Rasmussen
// Date        : 15/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CHollingMortalityRateProcess.h"

#include "../../Helpers/CComparer.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/ForEach.h"
#include "../../Penalties/CPenalty.h"
#include "../../Penalties/CPenaltyManager.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Selectivities/CSelectivityManager.h"
#include "../../TimeSteps/CTimeStepManager.h"

//**********************************************************************
// CHollingMortalityRateProcess::CHollingMortalityRateProcess()
// Default Constructor
//**********************************************************************
CHollingMortalityRateProcess::CHollingMortalityRateProcess() {
  // Variables
  sType    = PARAM_HOLLING_MORTALITY_RATE;
  pPenalty = 0;

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_IS_ABUNDANCE);
  pParameterList->registerAllowed(PARAM_A);
  pParameterList->registerAllowed(PARAM_B);
  pParameterList->registerAllowed(PARAM_X);
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_SELECTIVITIES);
  pParameterList->registerAllowed(PARAM_PREDATOR_CATEGORIES);
  pParameterList->registerAllowed(PARAM_PREDATOR_SELECTIVITIES);
  pParameterList->registerAllowed(PARAM_U_MAX);
  pParameterList->registerAllowed(PARAM_PENALTY);
}

//**********************************************************************
// void CHollingMortalityRateProcess::validate()
// Validate our process
//**********************************************************************
void CHollingMortalityRateProcess::validate() {
  try {
    // Get our parameters
    bIsAbundance = pParameterList->getBool(PARAM_IS_ABUNDANCE);
    dA           = pParameterList->getDouble(PARAM_A);
    dB           = pParameterList->getDouble(PARAM_B);
    dX           = pParameterList->getDouble(PARAM_X, true, 2.0);
    dUMax        = pParameterList->getDouble(PARAM_U_MAX, true, 0.99);
    sPenalty     = pParameterList->getString(PARAM_PENALTY, true, "");

    pParameterList->fillVector(vCategoryList, PARAM_CATEGORIES);
    pParameterList->fillVector(vSelectivityList, PARAM_SELECTIVITIES);
    pParameterList->fillVector(vPredatorCategoryList, PARAM_PREDATOR_CATEGORIES);
    pParameterList->fillVector(vPredatorSelectivityList, PARAM_PREDATOR_SELECTIVITIES);

    // Base Validation
    CProcess::validate();

    // Register Estimables
    registerEstimable(PARAM_A, &dA);
    registerEstimable(PARAM_B, &dB);
    registerEstimable(PARAM_X, &dX);

    // Local Validation
    if (getCategoryCount() != getSelectivityCount())
      CError::errorListSameSize(PARAM_CATEGORY, PARAM_SELECTIVITY);

    if (getPredatorCategoryCount() != getPredatorSelectivityCount())
      CError::errorListSameSize(PARAM_PREDATOR_CATEGORIES, PARAM_PREDATOR_SELECTIVITIES);

    if (dUMax >= ONE)
      CError::errorGreaterThanEqualTo(PARAM_U_MAX, PARAM_ONE);
    if (dUMax <= TRUE_ZERO)
      CError::errorLessThanEqualTo(PARAM_U_MAX, PARAM_ZERO);

    if (dA < ZERO)
      CError::errorLessThanEqualTo(PARAM_A, PARAM_ZERO);

    if (dB < ZERO)
      CError::errorLessThanEqualTo(PARAM_B, PARAM_ZERO);

    if (dX < ONE)
      CError::errorLessThanEqualTo(PARAM_X, PARAM_ONE);

  } catch (string& Ex) {
    Ex = "CHollingMortalityRateProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CHollingMortalityRateProcess::build()
// Build our process
//**********************************************************************
void CHollingMortalityRateProcess::build() {
  try {
    // Base Build
    CProcess::build();

    CSelectivityManager* pSelectivityManager = CSelectivityManager::Instance();
    foreach (string Name, vPredatorSelectivityList) { vPredatorSelectivityIndex.push_back(pSelectivityManager->getSelectivity(Name)); }

    foreach (string Name, vPredatorCategoryList) { vPredatorCategoryIndex.push_back(pWorld->getCategoryIndexForName(Name)); }

    // Build Refs
    pTimeStepManager = CTimeStepManager::Instance();

    // Build Penalty
    if (sPenalty != "")
      pPenalty = CPenaltyManager::Instance()->getPenalty(sPenalty);

    // Rebuild
    rebuild();
  } catch (string& Ex) {
    Ex = "CHollingMortalityRateProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CHollingMortalityProcess::rebuild()
// Rebuild
//**********************************************************************
void CHollingMortalityRateProcess::rebuild() {
#ifndef OPTIMIZE
  try {
#endif

    vMortalityRate.resize(0);
    vMortalityN.resize(0);
    vMortalityBiomass.resize(0);
    vMortalityYears.resize(0);
    vPredatorBiomass.resize(0);

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CHollingMortalityRateProcess.rebuild(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CHollingMortalityRateProcess::execute()
// Execute our process
//**********************************************************************
void CHollingMortalityRateProcess::execute() {
#ifndef OPTIMIZE
  try {
#endif
    // Base execute
    CProcess::execute();

    double dSumMortality        = 0;
    double dSumAbundance        = 0;
    double dSumMortalityBiomass = 0;

    // Loop Through The World Grid (i,j)
    for (int i = 0; i < iWorldHeight; ++i) {
      for (int j = 0; j < iWorldWidth; ++j) {
        // Get Current Square
        pBaseSquare = pWorld->getBaseSquare(i, j);
        if (!pBaseSquare->getEnabled())
          continue;

        pDiff = pWorld->getDifferenceSquare(i, j);

        // Clear our Vulnerable Amount
        dVulnerable         = 0.0;
        dPredatorVulnerable = 0.0;

        // Loop Through Categories & Work out Vulnerable Stock in abundance or biomass
        for (int k = 0; k < (int)vCategoryIndex.size(); ++k) {
          for (int l = 0; l < iBaseColCount; ++l) {
            // get current prey abundance in age/category
            dCurrent = pBaseSquare->getValue(vCategoryIndex[k], l) * vSelectivityIndex[k]->getResult(l);
            if (dCurrent < 0.0)
              dCurrent = 0.0;
            // Increase Vulnerable biomass
            if (bIsAbundance) {
              dVulnerable += dCurrent;
            } else {
              dVulnerable += dCurrent * pWorld->getMeanWeight(l, vCategoryIndex[k]);
            }
          }
        }

        // Loop Through Categories & Work out Predator Stock in abundance or biomass
        for (int k = 0; k < (int)vPredatorCategoryIndex.size(); ++k) {
          for (int l = 0; l < iBaseColCount; ++l) {
            // get current prey abundance in age/category
            dPredatorCurrent = pBaseSquare->getValue(vPredatorCategoryIndex[k], l) * vPredatorSelectivityIndex[k]->getResult(l);
            if (dPredatorCurrent < 0.0)
              dPredatorCurrent = 0.0;
            // Increase Predator biomass
            if (bIsAbundance) {
              dPredatorVulnerable += dPredatorCurrent;
            } else {
              dPredatorVulnerable += dPredatorCurrent * pWorld->getMeanWeight(l, vPredatorCategoryIndex[k]);
            }
          }
        }

        // Holling function type 2 (x=1) or 3 (x=2), or generalised (Michaelis Menten)
        dMortality = dPredatorVulnerable * (dA * pow(dVulnerable, (dX - 1.0))) / (dB + pow(dVulnerable, (dX - 1.0)));

        // Work out exploitation rate to remove (catch/vulnerableBiomass)
        dExploitation = dMortality / CMath::zeroFun(dVulnerable, ZERO);
        if (dExploitation > dUMax) {
          dExploitation = dUMax;
          if (pPenalty != 0) {  // Throw Penalty
            pPenalty->trigger(sLabel, dMortality, (dVulnerable * dUMax));
          }
        } else if (dExploitation < ZERO) {
          dExploitation = 0.0;
          continue;
        }

        // Loop Through Categories & remove number based on calcuated exploitation rate
        for (int k = 0; k < (int)vCategoryIndex.size(); ++k) {
          for (int l = 0; l < iBaseColCount; ++l) {
            // Get Amount to remove
            dCurrent = pBaseSquare->getValue(vCategoryIndex[k], l) * vSelectivityIndex[k]->getResult(l) * dExploitation;

            // If is Zero, Cont
            if (dCurrent <= 0.0)
              continue;

            // Subtract These
            pDiff->subValue(vCategoryIndex[k], l, dCurrent);
            dSumMortality += dCurrent;
            dSumAbundance += pBaseSquare->getValue(vCategoryIndex[k], l);
            if (!bIsAbundance)
              dSumMortalityBiomass += dCurrent * pWorld->getMeanWeight(l, vCategoryIndex[k]);
          }
        }
      }
    }
    if (pRuntimeController->getCurrentState() != STATE_INITIALIZATION) {
      vMortalityYears.push_back(pTimeStepManager->getCurrentYear());
      vMortalityRate.push_back(dSumMortality / dSumAbundance);
      vMortalityN.push_back(dSumMortality);
      if (!bIsAbundance)
        vMortalityBiomass.push_back(dSumMortalityBiomass);
      vPredatorBiomass.push_back(dPredatorVulnerable);
    }

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CHollingMortalityRateProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CHollingMortalityRateProcess::~CHollingMortalityRateProcess()
// Destructor
//**********************************************************************
CHollingMortalityRateProcess::~CHollingMortalityRateProcess() {}
