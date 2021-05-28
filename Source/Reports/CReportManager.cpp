//============================================================================
// Name        : CReportManager.cpp
// Author      : S.Rasmussen
// Date        : 30/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global Headers
#include <iostream>

// Local headers
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"
#include "CReport.h"
#include "CReportManager.h"

// Using
using std::cout;
using std::endl;

// Single Static variable
boost::thread_specific_ptr<CReportManager> CReportManager::clInstance;

//**********************************************************************
// CReportManager::CReportManager()
// Default Constructor
//**********************************************************************
CReportManager::CReportManager() {
  // Variables
  sReportSuffix   = "";
  bDisableReports = false;
}

//**********************************************************************
// CReportManager* CReportManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CReportManager* CReportManager::Instance() {
  if (clInstance.get() == 0)
    clInstance.reset(new CReportManager());
  return clInstance.get();
}

//**********************************************************************
// void CReportManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CReportManager::Destroy() {
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// void CReportManager::addReporter(CReport *value)
// Add a Reporter to our vector
//**********************************************************************
void CReportManager::addReporter(CReport* value) {
  vReporters.push_back(value);
}

//**********************************************************************
// void CReportManager::clone(CReportManager *Manager)
// Clone our reporters
//**********************************************************************
void CReportManager::clone(CReportManager* Manager) {
  foreach (CReport* report, Manager->vReporters) { vReporters.push_back(report->clone()); }
}

//**********************************************************************
// void CReportManager::validate()
// Validate our Reporters
//**********************************************************************
void CReportManager::validate() {
  try {
    // Vars
    bDisableReports = pConfig->getDisableReports();

    foreach (CReport* Reporter, vReporters) { Reporter->validate(); }

    // Look for Duplicate Labels
    map<string, int> mLabelList;
    foreach (CReport* Reporter, vReporters) {
      // Increase Count for this label
      mLabelList[Reporter->getLabel()] += 1;

      // Check if we have more than 1
      if (mLabelList[Reporter->getLabel()] > 1)
        CError::errorDuplicate(PARAM_REPORT, Reporter->getLabel());
    }
  } catch (string& Ex) {
    Ex = "ReportManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CReportManager::build()
// Build our Reporters
//**********************************************************************
void CReportManager::build() {
  try {
    foreach (CReport* Reporter, vReporters) { Reporter->build(); }

    // Populate our other vectors
    foreach (CReport* Reporter, vReporters) {
      switch (Reporter->getExecutionState()) {
        case STATE_MODELLING:
          vModellingReporters.push_back(Reporter);
          break;
        default:
          break;
      }
    }
  } catch (string& Ex) {
    Ex = "CReportManager.build()" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CReportManager::execute()
// Execute Reporters
//**********************************************************************
void CReportManager::execute() {
  if (bDisableReports)
    return;
  // Check for correct modes
  if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
    return;
  // Check for correct state
  if (pRuntimeController->getCurrentState() != STATE_MODELLING)
    return;

  // Execute Modelling Reporters
  // Reporter will check Year/TimeStep itself
  // This is because some will run across multiple-timesteps
  foreach (CReport* Reporter, vModellingReporters) { Reporter->execute(); }
}

//**********************************************************************
// void CReportManager::execute(EState state)
// Execute State-Based reporters
//**********************************************************************
void CReportManager::execute(EState state) {
  if (bDisableReports)
    return;

  foreach (CReport* Reporter, vReporters) {
    if (Reporter->getExecutionState() == state)
      Reporter->execute();
  }
}

//**********************************************************************
// CReportManager::~CReportManager()
// Destructor
//**********************************************************************
CReportManager::~CReportManager() {
  foreach (CReport* Reporter, vReporters) { delete Reporter; }
}
