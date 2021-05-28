//============================================================================
// Name        : CProfileManager.cpp
// Author      : S.Rasmussen
// Date        : 2/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description : << See CProfileManager.h >>
// $Date$
//============================================================================

// Local Headers
#include "CProfileManager.h"

#include "../CRuntimeController.h"
#include "../Estimates/CEstimate.h"
#include "../Estimates/CEstimateManager.h"
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"
#include "../Minimizers/CMinimizerManager.h"
#include "../Reports/CReportManager.h"
#include "CProfile.h"

// Singleton Var
boost::thread_specific_ptr<CProfileManager> CProfileManager::clInstance;

//**********************************************************************
// CProfileManager::CProfileManager()
// Default Constructor
//**********************************************************************
CProfileManager::CProfileManager() {}

//**********************************************************************
// CProfileManager* CProfileManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CProfileManager* CProfileManager::Instance() {
  if (clInstance.get() == 0)
    clInstance.reset(new CProfileManager());
  return clInstance.get();
}

//**********************************************************************
// void CProfileManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CProfileManager::Destroy() {
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// void CProfileManager::addProfile(CProfile *Profile)
// add Profile to our List
//**********************************************************************
void CProfileManager::addProfile(CProfile* Profile) {
  vProfileList.push_back(Profile);
}

//**********************************************************************
// CProfile* CProfileManager::getProfile(int index)
// Get profile from our vector @ index
//**********************************************************************
CProfile* CProfileManager::getProfile(int index) {
  try {
    if (index >= (int)vProfileList.size())
      CError::errorGreaterThan(PARAM_INDEX, PARAM_PROFILES);
    if (index < 0)
      CError::errorLessThan(PARAM_INDEX, PARAM_ZERO);
  } catch (string& Ex) {
    Ex = "CProfileManager.getProfile()->" + Ex;
    throw Ex;
  }

  return vProfileList[index];
}

//**********************************************************************
// void CProfileManager::clone(CProfileManager *Manager)
// Clone the CProfileManager with param
//**********************************************************************
void CProfileManager::clone(CProfileManager* Manager) {
  try {
    for (int i = 0; i < Manager->getProfileCount(); ++i) {
      CProfile* pProfile = Manager->getProfile(i);
      vProfileList.push_back(pProfile->clone());
    }
  } catch (string& Ex) {
    Ex = "CProfileManager.clone()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProfileManager::validate()
// Validate our Profiles
//**********************************************************************
void CProfileManager::validate() {
  try {
    // Variables
    map<string, int> mParameterList;
    ERunMode         eRunMode = CRuntimeController::Instance()->getRunMode();

    // Check Run Mode
    if (eRunMode == RUN_MODE_PROFILE)
      if ((int)vProfileList.size() == 0)
        CError::errorMissing(PARAM_PROFILES);

    // Check For Duplicates
    foreach (CProfile* Profile, vProfileList) {
      mParameterList[Profile->getParameter()] += 1;

      if (mParameterList[Profile->getParameter()] > 1)
        CError::errorDuplicate(PARAM_PARAMETER, Profile->getParameter());
    }

    // Validate The Parameters
    foreach (CProfile* Profile, vProfileList) { Profile->validate(); }
  } catch (string& Ex) {
    Ex = "CProfileManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProfileManager::build()
// build
//**********************************************************************
void CProfileManager::build() {
#ifndef OPTIMIZE
  try {
#endif

    // Build profiles
    foreach (CProfile* Profile, vProfileList) { Profile->build(); }

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CProfileManager.build()->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CProfileManager::execute()
// execute
//**********************************************************************
void CProfileManager::execute() {
  try {
    // Variables
    CMinimizerManager* pMinimizer = CMinimizerManager::Instance();
    CReportManager*    pReporter  = CReportManager::Instance();

    // Save our Current State
    saveState();
    resetState();

    // Loop Through Profiles
    foreach (CProfile* Profile, vProfileList) {
      Profile->setEnabled(true);

      // Loop through the number of steps
      while (Profile->doStep()) {
        // minimize
        pMinimizer->execute();

        pReporter->execute(STATE_FINALIZATION);

        // Reset state back to initial world.
        resetState();
      }

      Profile->setEnabled(false);
      resetState();
    }
  } catch (string& Ex) {
    Ex = "CProfileManager.execute()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProfileManager::saveState()
// Save Current State of the World
//**********************************************************************
void CProfileManager::saveState() {
  try {
    CEstimateManager* pEstimateManager = CEstimateManager::Instance();
    int               iCount           = pEstimateManager->getEstimateCount();

    for (int i = 0; i < iCount; ++i) vCurrentState.push_back(pEstimateManager->getEstimate(i)->getValue());
  } catch (string& Ex) {
    Ex = "CProfileManager.saveState()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProfileManager::resetState()
// Reset Current State();
//**********************************************************************
void CProfileManager::resetState() {
  try {
    CEstimateManager* pEstimateManager = CEstimateManager::Instance();
    CWorld*           pWorld           = CWorld::Instance();

    // Clear our World
    pWorld->zeroGrid();

    int iCount = (int)vCurrentState.size();
    // Reset our Variables back from the Saved State
    for (int i = 0; i < iCount; ++i) {
      if (pEstimateManager->getEstimate(i)->getEnabled())
        pEstimateManager->getEstimate(i)->setValue(vCurrentState[i]);
    }
  } catch (string& Ex) {
    Ex = "CProfileManager.resetState()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CProfileManager::~CProfileManager()
// Default De-Constructor
//**********************************************************************
CProfileManager::~CProfileManager() {
  // De-Allocate our Memory
  foreach (CProfile* Profile, vProfileList) { delete Profile; }
  vProfileList.clear();
}
