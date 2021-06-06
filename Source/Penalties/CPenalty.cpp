//============================================================================
// Name        : CPenalty.cpp
// Author      : S.Rasmussen
// Date        : 16/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
//============================================================================

// Local Headers
#include "CPenalty.h"

#include "../Helpers/CComparer.h"
#include "../Helpers/CError.h"
#include "../Helpers/CMath.h"
#include "../Processes/CProcessManager.h"
#include "CPenaltyManager.h"

//**********************************************************************
// CPenalty::CPenalty()
// Default Constructor
//**********************************************************************
CPenalty::CPenalty() {
  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_MULTIPLIER);
  pParameterList->registerAllowed(PARAM_LOG_SCALE);
}

//**********************************************************************
// void CPenalty::validate()
// validate
//**********************************************************************
void CPenalty::validate() {
  try {
    // Base
    CBaseValidate::validate();

    // Get local Parameters
    dMultiplier = pParameterList->getDouble(PARAM_MULTIPLIER, true, 1.0);
    bLogScale   = pParameterList->getBool(PARAM_LOG_SCALE, true, false);
  } catch (string& Ex) {
    Ex = "CPenalty.validate(" + sLabel + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPenalty::triggerNull(string Label)
// trigger The penalty with a zero
//**********************************************************************
void CPenalty::triggerZero(string Label) {
#ifndef OPTIMIZE
  try {
#endif
    // Assign Variables
    string sFullLabel = sLabel + "(" + Label + ")";

    // Flag Penalty Manager
    CPenaltyManager* pPenaltyManager = CPenaltyManager::Instance();
    pPenaltyManager->flagPenalty(sFullLabel, 0.0);

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CPenalty.triggerZero(" + sLabel + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CPenalty::trigger(string Label, double Value1, double Value2)
// trigger The penalty
//**********************************************************************
void CPenalty::trigger(string Label, double Value1, double Value2) {
#ifndef OPTIMIZE
  try {
#endif
    // Assign Variables
    string sFullLabel = sLabel + "(" + Label + ")";
    double dValue     = 0.0;

    if (bLogScale) {
      // Ensure values are not zero
      dValue = (log(CMath::zeroFun(Value1, DELTA)) - log(CMath::zeroFun(Value2, DELTA))) * (log(CMath::zeroFun(Value1, DELTA)) - log(CMath::zeroFun(Value2, DELTA))) * dMultiplier;
    } else {
      dValue = (Value1 - Value2) * (Value1 - Value2) * dMultiplier;
    }

    // Flag Penalty Manager
    CPenaltyManager* pPenaltyManager = CPenaltyManager::Instance();
    pPenaltyManager->flagPenalty(sFullLabel, dValue);

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CPenalty.trigger(" + sLabel + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CPenalty::~CPenalty()
// Default De-Constructor
//**********************************************************************
CPenalty::~CPenalty() {}
