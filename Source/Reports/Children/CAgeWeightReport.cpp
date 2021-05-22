//============================================================================
// Name        : CAgeWeightReport.cpp
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CAgeWeightReport.h"
#include "../../AgeSize/CAgeSizeManager.h"
#include "../../AgeSize/CAgeSize.h"
#include "../../SizeWeight/CSizeWeightManager.h"
#include "../../SizeWeight/CSizeWeight.h"

//**********************************************************************
// CAgeWeightReport::CAgeWeightReport()
// Constructor
//**********************************************************************
CAgeWeightReport::CAgeWeightReport()
{
  // Variables
  eExecutionState = STATE_FINALIZATION;
  pAgeSize = 0;

  // Register allowed
  pParameterList->registerAllowed(PARAM_AGE_SIZE);
}

//**********************************************************************
// void CAgeWeightReport::validate()
// Validate our selectivity
//**********************************************************************
void CAgeWeightReport::validate()
{
  try
  {

    sAgeSize = pParameterList->getString(PARAM_AGE_SIZE);

    // Validate parent
    CFileReport::validate();

    // Local validation
    // Get our list of ages to evaluate
    for (int i = pWorld->getMinAge(); i <= pWorld->getMaxAge(); ++i)
    {
      vAgeList.push_back(i);
    }
  }
  catch (string &Ex)
  {
    Ex = "CAgeWeightReport.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAgeWeightReport::build()
// Build our Report
//**********************************************************************
void CAgeWeightReport::build()
{
  try
  {
    // Parent
    CFileReport::build();

    // Get our selectivity
    CAgeSizeManager *pManager = CAgeSizeManager::Instance();
    pAgeSize = pManager->getAgeSize(sAgeSize);
  }
  catch (string &ex)
  {
    ex = "CAgeWeightReport.build(" + getLabel() + ")->" + ex;
    throw ex;
  }
}

//**********************************************************************
// void CAgeWeightReport::execute()
// Execute
//**********************************************************************
void CAgeWeightReport::execute()
{

  try
  {
    // Check for correct state
    if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
      return;

    this->start();

    // Output Header
    cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
    cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";
    cout << PARAM_LABEL << CONFIG_RATIO_SEPARATOR << " " << sAgeSize << "\n";

    // Output list of ages
    cout << PARAM_AGES << CONFIG_RATIO_SEPARATOR << " ";
    for (int i = 0; i < ((int)vAgeList.size() - 1); ++i)
    {
      cout << vAgeList[i] << CONFIG_SPACE_SEPARATOR;
    }
    cout << vAgeList[vAgeList.size() - 1] << "\n";

    // Output list of weights corrsponding to list of sizes
    cout << PARAM_WEIGHTS << CONFIG_RATIO_SEPARATOR << " ";
    for (int i = 0; i < ((int)vAgeList.size() - 1); ++i)
    {
      cout << pAgeSize->getMeanWeight(vAgeList[i]) << CONFIG_SPACE_SEPARATOR;
    }
    cout << pAgeSize->getMeanWeight(vAgeList[vAgeList.size() - 1]) << "\n";

    // Ouptut end of report
    cout << CONFIG_END_REPORT << "\n"
         << endl;

    this->end();
  }
  catch (string &Ex)
  {
    Ex = "CAgeWeightReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CAgeWeightReport::~CAgeWeightReport()
// Destuctor
//**********************************************************************
CAgeWeightReport::~CAgeWeightReport()
{
}
