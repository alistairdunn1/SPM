//============================================================================
// Name        : CProcessManager.cpp
// Author      : S.Rasmussen
// Date        : 12/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description : << See CProcessManager.h >>
// $Date$
//============================================================================

// Local Headers
#include "CProcessManager.h"
#include "CProcess.h"
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"

// Single Static variable
boost::thread_specific_ptr<CProcessManager> CProcessManager::clInstance;

//**********************************************************************
// CProcessManager::CProcessManager()
// Default Constructor
//**********************************************************************
CProcessManager::CProcessManager() {
}

//**********************************************************************
// CProcessManager* CProcessManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CProcessManager* CProcessManager::Instance() {
  if (clInstance.get() == 0)
    clInstance.reset(new CProcessManager());
  return clInstance.get();
}

//**********************************************************************
// void CProcessManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CProcessManager::Destroy() {
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// void CProcessManager::addProcess(CProcess *Process)
// Add A Process To Our List
//**********************************************************************
void CProcessManager::addProcess(CProcess* value) {
  vProcessList.push_back(value);
}

//**********************************************************************
// CProcess* CProcessManager::getProcess(string Label)
// Return Link To Our process
//**********************************************************************
CProcess* CProcessManager::getProcess(string Label) {
#ifndef OPTIMISE
  try {
#endif

    // Loop for Match
    foreach(CProcess *Process, vProcessList) {
      if (Process->getLabel() == Label)
        return Process;
    }

    throw string(ERROR_UNKNOWN_PROCESS + Label);

#ifndef OPTIMISE
  } catch(string Ex) {
    Ex = "CProcessManager.getProcess()->" + Ex;
    throw Ex;
  }
  return 0;
#endif
}

//**********************************************************************
// CProcess* CProcessManager::getProcess(int index)
// Get the process from our vector @ index
//**********************************************************************
CProcess* CProcessManager::getProcess(int index) {
  try {
    if (index >= (int)vProcessList.size())
      CError::errorGreaterThanEqualTo(PARAM_INDEX, PARAM_PROCESSES);
    if (index < 0)
      CError::errorLessThan(PARAM_INDEX, PARAM_ZERO);

    return vProcessList[index];

  } catch (string Ex) {
    Ex = "CProcessManager.getProcess()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProcessManager::clone(CProcessManager *Manager)
// Clone the manager passed in as a parameter
//**********************************************************************
void CProcessManager::clone(CProcessManager *Manager) {
  try {

    for (int i = 0; i < Manager->getProcessCount(); ++i) {
      CProcess *pProcess = Manager->getProcess(i);
      vProcessList.push_back(pProcess->clone());
    }

  } catch (string Ex) {
    Ex = "CProcessManager.clone()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProcessManager::validate()
// Validate Our Processes Against Bad Input Data
//**********************************************************************
void CProcessManager::validate() {
  try {
    // Variables
    map<string, int>              mLabelList;

    // Check For Duplicate Labels
    foreach(CProcess *Process, vProcessList) {
      mLabelList[Process->getLabel()] += 1;
      if (mLabelList[Process->getLabel()] > 1)
        throw string(ERROR_DUPLICATE_LABEL + Process->getLabel());
    }

    // Validate Processes
    foreach(CProcess *Process, vProcessList) {
      Process->validate();
    }
  } catch(string Ex) {
    Ex = "CProcessManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProcessManager::build()
// Build Our Processes, And Relationships.
//**********************************************************************
void CProcessManager::build() {
#ifndef OPTIMISE
  try {
#endif

    // Loop n Build
    foreach(CProcess *Process, vProcessList) {
      Process->build();
    }

#ifndef OPTIMISE
  } catch(string Ex) {
    Ex = "CProcessManager.buildProcesses()->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CProcessManager::rebuild()
// Rebuild our Processes
//**********************************************************************
void CProcessManager::rebuild() {
#ifndef OPTIMISE
  try {
#endif

    // Loop n Build
    foreach(CProcess *Process, vProcessList) {
      Process->rebuild();
    }

#ifndef OPTIMISE
  } catch(string Ex) {
    Ex = "CProcessManager.buildProcesses()->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CProcessManager::~CProcessManager()
// Default De-Constructor
//**********************************************************************
CProcessManager::~CProcessManager() {
  // Loop n Delete
  foreach(CProcess *Process, vProcessList) {
    delete Process;
  }

  vProcessList.clear();
}