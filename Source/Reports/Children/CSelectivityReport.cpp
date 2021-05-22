//============================================================================
// Name        : CSelectivityReport.cpp
// Author      : S.Rasmussen
// Date        : 26/03/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CSelectivityReport.h"
#include "../../Selectivities/CSelectivityManager.h"
#include "../../Selectivities/CSelectivity.h"

//**********************************************************************
// CSelectivityReport::CSelectivityReport()
// Constructor
//**********************************************************************
CSelectivityReport::CSelectivityReport()
{
  // Variables
  eExecutionState = STATE_FINALIZATION;
  pSelectivity = 0;

  // Register allowed
  pParameterList->registerAllowed(PARAM_SELECTIVITY);
}

//**********************************************************************
// void CSelectivityReport::validate()
// Validate our selectivity
//**********************************************************************
void CSelectivityReport::validate()
{
  try
  {

    sSelectivity = pParameterList->getString(PARAM_SELECTIVITY);

    // Validate parent
    CFileReport::validate();

    // Local validation
  }
  catch (string &Ex)
  {
    Ex = "CSelectivityReport.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CSelectivityReport::build()
// Build our Report
//**********************************************************************
void CSelectivityReport::build()
{
  try
  {
    // Parent
    CFileReport::build();

    // Get our selectivity
    CSelectivityManager *pManager = CSelectivityManager::Instance();
    pSelectivity = pManager->getSelectivity(sSelectivity);
  }
  catch (string &Ex)
  {
    Ex = "CSelectivityReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CSelectivityReport::execute()
// Execute
//**********************************************************************
void CSelectivityReport::execute()
{

  try
  {
    // Check for correct state
    if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
      if (pRuntimeController->getRunMode() != RUN_MODE_PROFILE)
        return;

    this->start();

    // Work our how many viable ages we have.
    int iSpread = (pWorld->getMaxAge() - pWorld->getMinAge()) + 1;
    int iMinAge = pWorld->getMinAge();

    // Output Header
    cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
    cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";
    cout << PARAM_LABEL << CONFIG_RATIO_SEPARATOR << " " << sSelectivity << "\n";

    cout << PARAM_AGES << CONFIG_RATIO_SEPARATOR << " " << iMinAge;
    for (int i = 1; i < iSpread; ++i)
      cout << CONFIG_SPACE_SEPARATOR << (i + iMinAge);
    cout << "\n";

    cout << PARAM_VALUES << CONFIG_RATIO_SEPARATOR << " ";
    cout << pSelectivity->getResult(0);
    for (int i = 1; i < iSpread; ++i)
      cout << CONFIG_SPACE_SEPARATOR << pSelectivity->getResult(i);
    cout << "\n";
    cout << CONFIG_END_REPORT << "\n"
         << endl;

    this->end();
  }
  catch (string &Ex)
  {
    Ex = "CSelectivityReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CSelectivityReport::~CSelectivityReport()
// Destuctor
//**********************************************************************
CSelectivityReport::~CSelectivityReport()
{
}
