//============================================================================
// Name        : CCovarianceReport.cpp
// Author      : S.Rasmussen
// Date        : 6/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CCovarianceReport.h"
#include "../../Minimizers/CMinimizerManager.h"
#include "../../Minimizers/CMinimizer.h"

//**********************************************************************
// CCovarianceReport::CCovarianceReport()
// Default Constructor
//**********************************************************************
CCovarianceReport::CCovarianceReport() {
  // Variables
  eExecutionState   = STATE_FINALIZATION;
}

//**********************************************************************
// void CCovarianceReport::execute()
// Execute
//**********************************************************************
void CCovarianceReport::execute() {
  // Check for correct state
  if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
    if (pRuntimeController->getRunMode() != RUN_MODE_PROFILE)
      return;

  // Get our Minimizer
  CMinimizerManager *pManager = CMinimizerManager::Instance();
  CMinimizer *pMinimizer = pManager->getMinimizer();
  if (pMinimizer == 0)
    return;

  this->start();

  // TODO: Add Observation Writing Stuff Cout
  cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
  cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";
  int iCount = pMinimizer->getEstimateCount();

  cout << "Hessian:\n";
  for (int i = 0; i < iCount; ++i) {
      for (int j = 0; j < iCount; ++j) {
        cout << pMinimizer->getHessianValue(i, j) << " ";
      }
      cout << "\n";
    }

  cout << "Covariance:\n";
  for (int i = 0; i < iCount; ++i) {
    for (int j = 0; j < iCount; ++j) {
      cout << pMinimizer->getCovarianceValue(i, j) << " ";
    }
    cout << "\n";
  }

  cout << "*end\n" << endl;

  this->end();
}

//**********************************************************************
// CCovarianceReport::~CCovarianceReport()
// Destructor
//**********************************************************************
CCovarianceReport::~CCovarianceReport() {
}