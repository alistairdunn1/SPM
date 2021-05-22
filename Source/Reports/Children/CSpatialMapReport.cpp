//============================================================================
// Name        : CSpatialMapReport.cpp
// Author      : S.Rasmussen
// Date        : 15/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CSpatialMapReport.h"

//**********************************************************************
// CSpatialMapReport::CSpatialMapReport()
// Default constructor
//**********************************************************************
CSpatialMapReport::CSpatialMapReport()
{
  // Variables
  eExecutionState = STATE_FINALIZATION;
}

//**********************************************************************
// void CSpatialMapReport::execute()
// Execute
//**********************************************************************
void CSpatialMapReport::execute()
{
  try
  {

    // Check for correct state
    if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
      return;

    this->start();

    // Print
    cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
    cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR << pParameterList->getString(PARAM_TYPE) << "\n";

    for (int i = 0; i < pWorld->getHeight(); ++i)
    {
      for (int j = 0; j < pWorld->getWidth(); ++j)
      {
        cout << "r" << (i + 1) << "-c" << (j + 1) << CONFIG_SPACE_SEPARATOR;
      }
      cout << "\n";
    }

    cout << CONFIG_END_REPORT << "\n"
         << endl;
    this->end();
  }
  catch (string &Ex)
  {
    Ex = "CSpatialMapReport.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CSpatialMapReport::~CSpatialMapReport()
// Destructor
//**********************************************************************
CSpatialMapReport::~CSpatialMapReport()
{
}
