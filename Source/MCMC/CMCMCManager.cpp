//============================================================================
// Name        : CMCMCManager.cpp
// Author      : S.Rasmussen
// Date        : 11/01/2020
// Copyright   : Copyright NIWA Science �2020 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Headers
#include "CMCMCManager.h"

#include <boost/lexical_cast.hpp>

#include "../CRuntimeController.h"
#include "../Estimates/CEstimate.h"
#include "../Estimates/CEstimateManager.h"
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"
#include "../Reports/CReportManager.h"
#include "../RuntimeThread/CRuntimeThread.h"
#include "CMCMC.h"

// Singleton Variable
CMCMCManager* CMCMCManager::clInstance = 0;

//**********************************************************************
// CMinimizerManager::CMinimizerManager()
// Default Constructor
//**********************************************************************
CMCMCManager::CMCMCManager() {
  // Set Vars
  pMCMC = 0;
  sMCMC = "";

  // Register
  pParameterList->registerAllowed(PARAM_MINIMIZER);
  pParameterList->registerAllowed(PARAM_MCMC);
}

//**********************************************************************
// CMCMCManager* CMCMCManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CMCMCManager* CMCMCManager::Instance() {
  if (clInstance == 0)
    clInstance = new CMCMCManager();
  return clInstance;
}

//**********************************************************************
// void CMCMCManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CMCMCManager::Destroy() {
  if (clInstance != 0) {
    delete clInstance;
    clInstance = 0;
  }
}

//**********************************************************************
// void CMinimizerManager::addMinimizer(CMinimizer *value)
// Add A Minimizer to our List
//**********************************************************************
void CMCMCManager::addMCMC(CMCMC* value) {
  vMCMCList.push_back(value);
}

//**********************************************************************
// void CMinimizer::validate()
// Validate our MinizerManager
//**********************************************************************
void CMCMCManager::validate() {
  try {
    if (CRuntimeController::Instance()->getRunMode() != RUN_MODE_MONTE_CARLO_MARKOV_CHAIN)
      return;

    pParameterList->checkInvalidParameters();

    // Validate our Minimizers
    foreach (CMCMC* MCMC, vMCMCList) { MCMC->validate(); }

    // Look for Duplicate Labels
    map<string, int> mLabelList;
    foreach (CMCMC* mcmc, vMCMCList) {
      // Increase Count for this label
      mLabelList[mcmc->getLabel()] += 1;

      // Check if we have more than 1
      if (mLabelList[mcmc->getLabel()] > 1)
        CError::errorDuplicate(PARAM_MCMC, mcmc->getLabel());
    }

    // Reset Variable
    pMCMC = 0;

    if (vMCMCList.size() == 1) {
      pMCMC = vMCMCList[0];
    } else {
      throw std::string("Doesn't support multiple MCMCs yet");
    }

    // See if we have a valid minimizer defined
    if (pMCMC == 0)
      CError::errorUnknown(PARAM_MCMC, sMCMC);
  } catch (string& Ex) {
    Ex = "CMCMCManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMCMCManager::build()
// Build our Minimizer
//**********************************************************************
void CMCMCManager::build() {
  try {
    if (CRuntimeController::Instance()->getRunMode() != RUN_MODE_MONTE_CARLO_MARKOV_CHAIN)
      return;

    pMCMC->build();
  } catch (string& Ex) {
    Ex = "CMCMCManager.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMCMCManager::execute()
// Execute Our Minimisation
//**********************************************************************
void CMCMCManager::execute() {
  try {
    if (pMCMC == 0)
      throw string(ERROR_INVALID_TARGET_NULL);

    pMCMC->execute();
  } catch (string& Ex) {
    Ex = "CMCMCManager.execute()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CMCMCManager::~CMCMCManager()
// Default De-Constructor
//**********************************************************************
CMCMCManager::~CMCMCManager() {}
