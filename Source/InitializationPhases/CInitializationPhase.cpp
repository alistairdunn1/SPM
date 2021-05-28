//============================================================================
// Name        : CInitializationPhase.cpp
// Author      : S.Rasmussen
// Date        : 13/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global headers
#include <boost/lexical_cast.hpp>
#include <iostream>

// Local headers
#include "../DerivedQuantities/CDerivedQuantityManager.h"
#include "../DerivedQuantitiesByCell/CDerivedQuantityByCellManager.h"
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"
#include "../TimeSteps/CTimeStep.h"
#include "../TimeSteps/CTimeStepManager.h"
#include "CInitializationPhase.h"

// Using
using std::cout;
using std::endl;

//**********************************************************************
// CInitializationPhase::CInitializationPhase()
// Default constructor
//**********************************************************************
CInitializationPhase::CInitializationPhase() {
  // Vars
  iYears            = 0;
  iCurrentTimeStep  = 0;
  dLambda           = 0;
  dTotalLambda      = 0.0;
  dDiffLambda       = 0.0;
  bConvergenceCheck = false;

  // Register parameters
  pParameterList->registerAllowed(PARAM_YEARS);
  pParameterList->registerAllowed(PARAM_TIME_STEPS);
  pParameterList->registerAllowed(PARAM_LAMBDA);
  pParameterList->registerAllowed(PARAM_LAMBDA_YEARS);
}

//**********************************************************************
// void CInitializationPhase::validate()
// Validate our Initialization Phase
//**********************************************************************
void CInitializationPhase::validate() {
  try {
    // Base
    CBaseExecute::validate();

    // Fill our Variables
    iYears = pParameterList->getInt(PARAM_YEARS);
    pParameterList->fillVector(vTimeStepNames, PARAM_TIME_STEPS);
    if (pParameterList->hasParameter(PARAM_LAMBDA) || pParameterList->hasParameter(PARAM_LAMBDA_YEARS)) {
      bConvergenceCheck = true;
      dLambda           = pParameterList->getDouble(PARAM_LAMBDA, true, 0.0);
      if (pParameterList->hasParameter(PARAM_LAMBDA_YEARS)) {
        pParameterList->fillVector(vLambdaYears, PARAM_LAMBDA_YEARS);
      } else {
        vLambdaYears.resize(0);
        vLambdaYears.push_back(iYears);
      }
    }

    // Validate
    if (iYears < 1)
      CError::errorLessThan(PARAM_YEARS, PARAM_ONE);

    if (bConvergenceCheck) {
      if (dLambda < 0)
        CError::errorLessThan(PARAM_LAMBDA, PARAM_ZERO);
      if (dLambda >= 1)
        CError::errorGreaterThan(PARAM_LAMBDA, PARAM_ONE);
      for (int i = 0; i < (int)vLambdaYears.size(); ++i) {
        if (vLambdaYears[i] < 1)
          CError::errorLessThan(PARAM_LAMBDA_YEARS, PARAM_ONE);
        if (vLambdaYears[i] > iYears)
          CError::errorGreaterThan(PARAM_LAMBDA_YEARS, PARAM_YEARS);
        if ((i > 0) & (vLambdaYears[i] == vLambdaYears[i - 1]))
          CError::errorDuplicate(PARAM_LAMBDA_YEARS, boost::lexical_cast<string>(vLambdaYears[i]));
      }
    }
  } catch (string& Ex) {
    Ex = "CInitializationPhase.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CInitializationPhase::build()
// Build this Initilization phase
//**********************************************************************
void CInitializationPhase::build() {
  try {
    // Now Lets Build Our Relationships
    CTimeStepManager* pTimeStepManager = CTimeStepManager::Instance();
    pTimeStepManager->fillVector(vTimeStepNames, vTimeSteps);

    // TimeStep Validation
    for (int i = 0; i < (int)vTimeStepNames.size(); ++i) {
      bool bValid = false;
      foreach (CTimeStep* TimeStep, vTimeSteps) {
        if (TimeStep->getLabel() == vTimeStepNames[i]) {
          bValid = true;
        }
      }
      if (bValid == false) {
        CError::errorUnknown(PARAM_TIME_STEP, vTimeStepNames[i]);
      }
    }

    if (bConvergenceCheck) {
      vvWorldCopy.resize(pWorld->getHeight());
      for (int i = 0; i < pWorld->getHeight(); ++i) {
        vvWorldCopy[i].resize(pWorld->getWidth());
        for (int j = 0; j < (int)pWorld->getWidth(); ++j) {
          vvWorldCopy[i][j].resize(pWorld->getCategoryCount());
          for (int k = 0; k < pWorld->getCategoryCount(); ++k) {
            vvWorldCopy[i][j][k].resize(pWorld->getAgeSpread());
          }
        }
      }
    }
  } catch (string& Ex) {
    Ex = "CInitializationPhase.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CInitializationPhase::rebuild()
// Rebuild this Initialisation phase
//**********************************************************************
void CInitializationPhase::rebuild() {
#ifndef OPTIMIZE
  try {
#endif

    // reset holding container for lambda
    vLambdaHat.resize(0);
    vLambdaHatYears.resize(0);

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CInitializationPhase.rebuild(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CInitializationPhase::execute()
// Execute the TimeSteps for this initialisation phase
//**********************************************************************
void CInitializationPhase::execute() {
  CDerivedQuantityByCellManager* pDerivedQuantityByCellManager = CDerivedQuantityByCellManager::Instance();
  CDerivedQuantityManager*       pDerivedQuantityManager       = CDerivedQuantityManager::Instance();

  iActualYears = iYears;
  // Loop Through and Execute
  for (int i = 0; i < iYears; ++i) {
    for (int j = 0; j < (int)vTimeSteps.size(); ++j) {
      iCurrentTimeStep = j;
      vTimeSteps[j]->execute();
      pDerivedQuantityByCellManager->calculate(iExecutionOrderIndex);
      pDerivedQuantityManager->calculate(iExecutionOrderIndex);
    }

    if (bConvergenceCheck) {
      // If convergence checks are enabled, then...

      bool bExit = false;
      for (int k = 0; k < (int)vLambdaYears.size(); ++k) {
        if ((i + 1) == (vLambdaYears[k] - 1)) {
          // record state from previous year

          for (int i2 = 0; i2 < pWorld->getHeight(); ++i2) {
            for (int j2 = 0; j2 < pWorld->getWidth(); ++j2) {
              pPreviousSquare = pWorld->getBaseSquare(i2, j2);
              for (int i3 = 0; i3 < pWorld->getCategoryCount(); ++i3) {
                for (int j3 = 0; j3 < pWorld->getAgeSpread(); ++j3) {
                  vvWorldCopy[i2][j2][i3][j3] = pPreviousSquare->getValue(i3, j3);
                }
              }
            }
          }
        } else if ((i + 1) == vLambdaYears[k]) {
          // record state in this year and compare
          dDiffLambda  = 0.0;
          dTotalLambda = 0.0;

          for (int i2 = 0; i2 < pWorld->getHeight(); ++i2) {
            for (int j2 = 0; j2 < pWorld->getWidth(); ++j2) {
              pBaseSquare = pWorld->getBaseSquare(i2, j2);
              if (!pBaseSquare->getEnabled())
                continue;
              for (int k = 0; k < pBaseSquare->getHeight(); ++k) {
                for (int l = 0; l < pBaseSquare->getWidth(); ++l) {
                  dTotalLambda += pBaseSquare->getValue(k, l);
                  dDiffLambda += fabs(pBaseSquare->getValue(k, l) - vvWorldCopy[i2][j2][k][l]);
                }
              }
            }
          }
          vLambdaHat.push_back(dDiffLambda / dTotalLambda);
          vLambdaHatYears.push_back(i + 1);
          // Compare with  dPreviousLambdaValue and exit loop if converged
          if ((dDiffLambda / dTotalLambda) < dLambda) {
            iActualYears = i + 1;
            bExit        = true;
          }
        }
      }
      if (bExit)
        break;
    }
  }
}

//**********************************************************************
// CInitializationPhase::~CInitializationPhase()
// Destructor
//**********************************************************************
CInitializationPhase::~CInitializationPhase() {}
