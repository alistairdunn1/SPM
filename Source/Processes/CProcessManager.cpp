//============================================================================
// Name        : CProcessManager.cpp
// Author      : S.Rasmussen
// Date        : 12/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description : << See CProcessManager.h >>
// $Date$
//============================================================================

// Global headers
#include <iostream>

// Local Headers
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"
#include "CProcess.h"
#include "CProcessManager.h"

// Using
using std::cout;
using std::endl;

// Single Static variable
boost::thread_specific_ptr<CProcessManager> CProcessManager::clInstance;

//**********************************************************************
// CProcessManager::CProcessManager()
// Default Constructor
//**********************************************************************
CProcessManager::CProcessManager() {}

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
#ifndef OPTIMIZE
  try {
#endif

    // Loop for Match
    foreach (CProcess* Process, vProcessList) {
      if (Process->getLabel() == Label)
        return Process;
    }

    CError::errorUnknown(PARAM_PROCESS, Label);

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CProcessManager.getProcess()->" + Ex;
    throw Ex;
  }
#endif

  return 0;
}

//**********************************************************************
// void CProcessManager::fillVector(vector<CProcess*> list, vector<string> &labels)
// Fill vector with Processes with Labels
//**********************************************************************
void CProcessManager::fillVector(vector<CProcess*>& list, vector<string>& labels) {
  list.clear();

  foreach (string Label, labels) { list.push_back(getProcess(Label)); }
}

//**********************************************************************
// void CProcessManager::clone(CProcessManager *Manager)
// Clone the manager passed in as a parameter
//**********************************************************************
void CProcessManager::clone(CProcessManager* Manager) {
  foreach (CProcess* process, Manager->vProcessList) { vProcessList.push_back(process->clone()); }
}

//**********************************************************************
// void CProcessManager::validate()
// Validate Our Processes Against Bad Input Data
//**********************************************************************
void CProcessManager::validate() {
  try {
    // Validate Processes
    foreach (CProcess* Process, vProcessList) { Process->validate(); }

    // Check For Duplicate Labels
    map<string, int> mLabelList;
    foreach (CProcess* Process, vProcessList) {
      mLabelList[Process->getLabel()] += 1;
      if (mLabelList[Process->getLabel()] > 1)
        CError::errorDuplicate(PARAM_LABEL, Process->getLabel());
    }

  } catch (string& Ex) {
    Ex = "CProcessManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProcessManager::build()
// Build Our Processes, And Relationships.
//**********************************************************************
void CProcessManager::build() {
#ifndef OPTIMIZE
  try {
#endif

    // Loop n Build
    foreach (CProcess* Process, vProcessList) { Process->build(); }

#ifndef OPTIMIZE
  } catch (string& Ex) {
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
#ifndef OPTIMIZE
  try {
#endif

    // Loop n Build
    foreach (CProcess* Process, vProcessList) { Process->rebuild(); }

#ifndef OPTIMIZE
  } catch (string& Ex) {
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
  foreach (CProcess* Process, vProcessList) { delete Process; }

  vProcessList.clear();
}
