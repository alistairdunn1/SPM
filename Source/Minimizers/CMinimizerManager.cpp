//============================================================================
// Name        : CMinimizerManager.cpp
// Author      : S.Rasmussen
// Date        : 2/05/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Headers
#include "CMinimizerManager.h"

#include <boost/lexical_cast.hpp>

#include "../CRuntimeController.h"
#include "../Estimates/CEstimate.h"
#include "../Estimates/CEstimateManager.h"
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"
#include "../Reports/CReportManager.h"
#include "../RuntimeThread/CRuntimeThread.h"
#include "CMinimizer.h"

// Singleton Variable
CMinimizerManager* CMinimizerManager::clInstance = 0;

//**********************************************************************
// CMinimizerManager::CMinimizerManager()
// Default Constructor
//**********************************************************************
CMinimizerManager::CMinimizerManager() {
  // Set Vars
  pMinimizer = 0;
  sMinimizer = "";

  // Register
  pParameterList->registerAllowed(PARAM_MINIMIZER);
  pParameterList->registerAllowed(PARAM_MCMC);
}

//**********************************************************************
// CMinimizerManager* CMinimizerManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CMinimizerManager* CMinimizerManager::Instance() {
  if (clInstance == 0)
    clInstance = new CMinimizerManager();
  return clInstance;
}

//**********************************************************************
// void CMinimizerManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CMinimizerManager::Destroy() {
  if (clInstance != 0) {
    delete clInstance;
    clInstance = 0;
  }
}

//**********************************************************************
// void CMinimizerManager::addMinimizer(CMinimizer *value)
// Add A Minimizer to our List
//**********************************************************************
void CMinimizerManager::addMinimizer(CMinimizer* value) {
  vMinimizerList.push_back(value);
}

//**********************************************************************
// void CMinimizerManager::addThread(CRuntimeThread *Thread)
// Add Thread to our Pool
//**********************************************************************
void CMinimizerManager::addThread(CRuntimeThread* Thread) {
  lock lk(mutThread);
  vThreadList.push_back(Thread);
}

//**********************************************************************
// void CMinimizer::validate()
// Validate our MinizerManager
//**********************************************************************
void CMinimizerManager::validate() {
  try {
    if ((CRuntimeController::Instance()->getRunMode() == RUN_MODE_BASIC) || (CRuntimeController::Instance()->getRunMode() == RUN_MODE_SIMULATION))
      return;

    pParameterList->checkInvalidParameters();

    sMinimizer = pParameterList->getString(PARAM_MINIMIZER);
    sMCMC      = pParameterList->getString(PARAM_MCMC, true, "");

    // Validate our Minimizers
    foreach (CMinimizer* Minimizer, vMinimizerList) { Minimizer->validate(); }

    // Look for Duplicate Labels
    map<string, int> mLabelList;
    foreach (CMinimizer* Minimizer, vMinimizerList) {
      // Increase Count for this label
      mLabelList[Minimizer->getLabel()] += 1;

      // Check if we have more than 1
      if (mLabelList[Minimizer->getLabel()] > 1)
        CError::errorDuplicate(PARAM_MINIMIZER, Minimizer->getLabel());
    }

    // Reset Variable
    pMinimizer = 0;

    // Find and Assign
    foreach (CMinimizer* Minimizer, vMinimizerList) {
      if (Minimizer->getLabel() == sMinimizer)
        pMinimizer = Minimizer;
    }

    // See if we have a valid minimizer defined
    if (pMinimizer == 0)
      CError::errorUnknown(PARAM_MINIMIZER, sMinimizer);
  } catch (string& Ex) {
    Ex = "CMinimizerManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMinimizerManager::build()
// Build our Minimizer
//**********************************************************************
void CMinimizerManager::build() {
  try {
    if ((CRuntimeController::Instance()->getRunMode() == RUN_MODE_BASIC) || (CRuntimeController::Instance()->getRunMode() == RUN_MODE_SIMULATION))
      return;

    pMinimizer->build();
  } catch (string& Ex) {
    Ex = "CMinimizerManager.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMinimizer::initialise()
// Initialise Our Minimisation
//**********************************************************************
void CMinimizerManager::initialise() {
  try {
    if (pMinimizer == 0)
      throw string(ERROR_INVALID_TARGET_NULL);

    CEstimateManager* pEstimateManager = CEstimateManager::Instance();

    /* We need to go through each of the estimates now and check out what phases
     * that have been given. This will allow us to determine how many minimisation
     * phases we need to run.
     */
    ERunMode runMode = CRuntimeController::Instance()->getRunMode();

    vEstimationPhases.resize(0);
    vEstimationPhases.push_back(1);

    if (runMode == RUN_MODE_ESTIMATION) {
      int enabledEstimates = pEstimateManager->getEnabledEstimateCount();
      for (int i = 0; i < enabledEstimates; ++i) {
        int estimationPhase = pEstimateManager->getEnabledEstimate(i)->getEstimationPhase();
        vEstimationPhases.push_back(estimationPhase);
      }
      sort(vEstimationPhases.begin(), vEstimationPhases.end());
      vEstimationPhases.erase(unique(vEstimationPhases.begin(), vEstimationPhases.end()), vEstimationPhases.end());
    }
  } catch (string& Ex) {
    Ex = "CMinimizerManager.initialise()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMinimizer::execute(int estimationPhase)
// Execute Our Minimisation
//**********************************************************************
void CMinimizerManager::execute(int estimationPhase) {
  try {
    if (pMinimizer == 0)
      throw string(ERROR_INVALID_TARGET_NULL);

    CEstimateManager* pEstimateManager = CEstimateManager::Instance();
    ERunMode          runMode          = CRuntimeController::Instance()->getRunMode();

    if (runMode == RUN_MODE_ESTIMATION)
      pEstimateManager->setCurrentPhase(estimationPhase);

    pMinimizer->runEstimation();
    if (pMinimizer->getBuildCovariance())
      pMinimizer->buildCovarianceMatrix();
  } catch (string& Ex) {
    Ex = "CMinimizerManager.execute(int)->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMinimizer::execute()
// Execute Our Minimisation
//**********************************************************************
void CMinimizerManager::execute() {
  try {
    if (pMinimizer == 0)
      throw string(ERROR_INVALID_TARGET_NULL);

    pMinimizer->runEstimation();
    if (pMinimizer->getBuildCovariance())
      pMinimizer->buildCovarianceMatrix();
  } catch (string& Ex) {
    Ex = "CMinimizerManager.execute()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CMinimizerManager::~CMinimizerManager()
// Default De-Constructor
//**********************************************************************
CMinimizerManager::~CMinimizerManager() {}
