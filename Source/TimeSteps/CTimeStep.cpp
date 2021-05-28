//============================================================================
// Name        : CTimeStep.cpp
// Author      : S.Rasmussen
// Date        : 13/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// $Date$
//============================================================================

// Global headers
#include <iostream>

// Local Headers
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"
#include "../Processes/CProcess.h"
#include "../Processes/CProcessManager.h"
#include "CTimeStep.h"

// Using
using std::cout;
using std::endl;

//**********************************************************************
// CTimeStep::CTimeStep()
// Default Constructor
//**********************************************************************
CTimeStep::CTimeStep() {
  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_PROCESSES);
  pParameterList->registerAllowed(PARAM_GROWTH_PROPORTION);
}

//**********************************************************************
// void CTimeStep::validate()
// Validate Time Step
//**********************************************************************
void CTimeStep::validate() {
  try {
    // Base
    CBaseExecute::validate();

    // Populate our parameters
    dGrowthProportion = pParameterList->getDouble(PARAM_GROWTH_PROPORTION, true, 0.0);
    pParameterList->fillVector(vProcessNames, PARAM_PROCESSES);

    // Check growth proportion
    if (dGrowthProportion < 0.0)
      CError::errorNotBetween(PARAM_GROWTH_PROPORTION, "0.0", "1.0");
    if (dGrowthProportion > 1.0)
      CError::errorNotBetween(PARAM_GROWTH_PROPORTION, "0.0", "1.0");
  } catch (string& Ex) {
    Ex = "CTimeStep.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CTimeStep::build()
//
//**********************************************************************
void CTimeStep::build() {
  try {
    // Now Lets Build Our Relationships
    CProcessManager* pProcessManager = CProcessManager::Instance();
    pProcessManager->fillVector(vProcesses, vProcessNames);
  } catch (string& Ex) {
    Ex = "CTimeStep.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CTimeStep::execute()
// Execute This TimeStep
//**********************************************************************
void CTimeStep::execute() {
#ifndef OPTIMIZE
  try {
#endif
    // Loop Through and Execute
    foreach (CProcess* Process, vProcesses) {
      Process->execute();
      if (Process->getRequiresMerge())
        pWorld->mergeDifferenceGrid();
    }

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CTimeStep.execute()->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CTimeStep::~CTimeStep()
// Default De-Constructor
//**********************************************************************
CTimeStep::~CTimeStep() {}
