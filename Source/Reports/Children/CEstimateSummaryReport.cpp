//============================================================================
// Name        : CEstimateSummaryReport.cpp
// Author      : S.Rasmussen
// Date        : 30/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CEstimateSummaryReport.h"
#include "../../Estimates/CEstimateManager.h"
#include "../../Estimates/CEstimate.h"
#include "../../Helpers/ForEach.h"

//**********************************************************************
// CEstimateSummaryReport::CEstimateSummaryReport()
// Default Constructor
//**********************************************************************
CEstimateSummaryReport::CEstimateSummaryReport()
{
  eExecutionState = STATE_FINALIZATION;
}

//**********************************************************************
// void CEstimateSummaryReport::execute()
// Execute print state
//**********************************************************************
void CEstimateSummaryReport::execute()
{

  try
  {
    // Check Run-Mode
    // Check for correct state
    if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
      if (pRuntimeController->getRunMode() != RUN_MODE_PROFILE)
        return;

    // Start IO
    this->start();

    // Get Estimates
    vector<CEstimate *> vEstimates;
    CEstimateManager::Instance()->fillVector(vEstimates);

    if (vEstimates.size() > 0)
    {

      cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
      cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";

      foreach (CEstimate *Estimate, vEstimates)
      {
        cout << PARAM_PARAMETER << ": " << Estimate->getParameter() << "\n";
        cout << PARAM_LOWER_BOUND << ": " << Estimate->getLowerBound() << "\n";
        cout << PARAM_UPPER_BOUND << ": " << Estimate->getUpperBound() << "\n";
        cout << PARAM_PRIOR << ": " << Estimate->getType() << "\n";
        cout << PARAM_VALUE << ": " << Estimate->getValue() << "\n\n";
      }

      cout << CONFIG_END_REPORT << "\n"
           << endl;
    }

    // End IO
    this->end();
  }
  catch (string &Ex)
  {
    Ex = "CEstimateSummaryReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CEstimateSummaryReport::~CEstimateSummaryReport()
// Destructor
//**********************************************************************
CEstimateSummaryReport::~CEstimateSummaryReport()
{
}
