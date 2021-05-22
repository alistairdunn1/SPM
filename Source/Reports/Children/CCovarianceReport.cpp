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
#include "../../Estimates/CEstimateManager.h"
#include "../../Estimates/CEstimate.h"
#include "../../Helpers/ForEach.h"

//**********************************************************************
// CCovarianceReport::CCovarianceReport()
// Default Constructor
//**********************************************************************
CCovarianceReport::CCovarianceReport()
{
  // Variables
  eExecutionState = STATE_FINALIZATION;
}

//**********************************************************************
// void CCovarianceReport::execute()
// Execute
//**********************************************************************
void CCovarianceReport::execute()
{

  try
  {
    // Check for correct state
    if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
      if (pRuntimeController->getRunMode() != RUN_MODE_PROFILE)
        return;

    // Get our Minimizer
    CMinimizerManager *pManager = CMinimizerManager::Instance();
    CMinimizer *pMinimizer = pManager->getMinimizer();
    if (pMinimizer == 0)
      return;

    if (!(pMinimizer->getBuildCovariance()))
      return;

    this->start();

    // Write The Report
    cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
    cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";

    int iCount = pMinimizer->getEstimateCount();
    vector<CEstimate *> vEstimates;
    CEstimateManager::Instance()->fillVector(vEstimates);
    cout << PARAM_PARAMETER << CONFIG_RATIO_SEPARATOR << " ";
    for (int i = 0; i < (int)vEstimates.size(); ++i)
    {
      //foreach(CEstimate *Estimate, vEstimates) {
      cout << vEstimates[i]->getParameter() << (i < ((int)vEstimates.size() - 1) ? CONFIG_SPACE_SEPARATOR : "\n");
      ;
    }
    cout << "Hessian:\n";
    for (int i = 0; i < iCount; ++i)
    {
      for (int j = 0; j < iCount; ++j)
      {
        cout << pMinimizer->getHessianValue(i, j) << (j < (iCount - 1) ? CONFIG_SPACE_SEPARATOR : "\n");
      }
    }

    cout << "Covariance:\n";
    if (pMinimizer->getCovarianceError())
    {
      cout << "Covariance creation failed. Hessian was not invertable\n";
    }
    else
    {
      for (int i = 0; i < iCount; ++i)
      {
        for (int j = 0; j < iCount; ++j)
        {
          cout << pMinimizer->getCovarianceValue(i, j) << (j < (iCount - 1) ? CONFIG_SPACE_SEPARATOR : "\n");
        }
      }
      cout << "Correlation:\n";
      for (int i = 0; i < iCount; ++i)
      {
        for (int j = 0; j < iCount; ++j)
        {
          cout << pMinimizer->getCorrelationValue(i, j) << (j < (iCount - 1) ? CONFIG_SPACE_SEPARATOR : "\n");
        }
      }
    }

    cout << CONFIG_END_REPORT << "\n"
         << endl;

    this->end();
  }
  catch (string &Ex)
  {
    Ex = "CCovarianceReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CCovarianceReport::~CCovarianceReport()
// Destructor
//**********************************************************************
CCovarianceReport::~CCovarianceReport()
{
}
