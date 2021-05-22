//============================================================================
// Name        : CRandomNumberSeedReport.cpp
// Author      : S.Rasmussen
// Date        : 26/03/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CRandomNumberSeedReport.h"
#include "../../CConfiguration.h"

//**********************************************************************
// CRandomNumberSeedReport::CRandomNumberSeedReport()
// Constructor
//**********************************************************************
CRandomNumberSeedReport::CRandomNumberSeedReport()
{
  // Variables
  eExecutionState = STATE_FINALIZATION;
}

//**********************************************************************
// void CRandomNumberSeedReport::execute()
// Execute the Report
//**********************************************************************
void CRandomNumberSeedReport::execute()
{

  try
  {
    // Check for correct state
    if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
      if (pRuntimeController->getRunMode() != RUN_MODE_PROFILE)
        return;

    this->start();

    // Output
    cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
    cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";
    cout << PARAM_RANDOM_NUMBER_SEED << CONFIG_RATIO_SEPARATOR << " " << pConfig->getRandomSeed() << "\n";
    cout << CONFIG_END_REPORT << "\n"
         << endl;

    this->end();
  }
  catch (string &Ex)
  {
    Ex = "CRandomNumberSeedReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CRandomNumberSeedReport::~CRandomNumberSeedReport()
// Destructor
//**********************************************************************
CRandomNumberSeedReport::~CRandomNumberSeedReport()
{
}
