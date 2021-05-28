//============================================================================
// Name        : CDESolverCallback.cpp
// Author      : S.Rasmussen
// Date        : 2/05/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global Headers
#include <iostream>

// Local Headers
#include "../../Estimates/CEstimate.h"
#include "../../Estimates/CEstimateManager.h"
#include "../../ObjectiveFunction/CObjectiveFunction.h"
#include "../../RuntimeThread/CRuntimeThread.h"
#include "CDESolverCallback.h"

//**********************************************************************
// CDESolverCallback::CDESolverCallback()
// Default Constructor
//**********************************************************************
CDESolverCallback::CDESolverCallback(int vectorsize, int populationsize, double tolerance) : DESolverEngine(vectorsize, populationsize, tolerance) {
  // Vars
  pEstimateManager = CEstimateManager::Instance();
}

//**********************************************************************
// double CDESolverCallback::EnergyFunction(double trial[],bool &bAtSolution)
// Our CallBack Function. Returns our Score
//**********************************************************************
double CDESolverCallback::EnergyFunction(vector<double> vTrialValues) {
  // Update our Components with the New Parameters
  int iCount = pEstimateManager->getEnabledEstimateCount();
  for (int i = 0; i < iCount; ++i) {
    pEstimateManager->getEnabledEstimate(i)->setValue(vTrialValues[i]);
  }

  CObjectiveFunction* pObjectiveFunction = CObjectiveFunction::Instance();

  try {
    // Rebuild and Run
    CRuntimeThread* pThread = pRuntimeController->getCurrentThread();
    pThread->rebuild();
    pThread->startModel();

    // Workout our Objective Score
    pObjectiveFunction->execute();
  } catch (string& Ex) {
    Ex = "CDESolverCallback.EnergyFunction()->" + Ex;
    throw Ex;
  }

  //  std::cout << "total_score: " << pObjectiveFunction->getScore() << std::endl;

  return pObjectiveFunction->getScore();
}

//**********************************************************************
// CDESolverCallback::~CDESolverCallback()
// Default De-Constructor
//**********************************************************************
CDESolverCallback::~CDESolverCallback() {}
