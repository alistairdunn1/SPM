//============================================================================
// Name        : CSizeWeightReport.cpp
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CSizeWeightReport.h"
#include "../../AgeSize/CAgeSizeManager.h"
#include "../../AgeSize/CAgeSize.h"
#include "../../Helpers/CError.h"

//**********************************************************************
// CSizeWeightReport::CSizeWeightReport()
// Constructor
//**********************************************************************
CSizeWeightReport::CSizeWeightReport()
{
  // Variables
  eExecutionState = STATE_FINALIZATION;
  pAgeSize = 0;

  // Register allowed
  pParameterList->registerAllowed(PARAM_AGE_SIZE);
  pParameterList->registerAllowed(PARAM_SIZES);
}

//**********************************************************************
// void CSizeWeightReport::validate()
// Validate our selectivity
//**********************************************************************
void CSizeWeightReport::validate()
{
  try
  {

    sAgeSize = pParameterList->getString(PARAM_AGE_SIZE);
    // Get our list of sizes to evaluate
    pParameterList->fillVector(vSizeList, PARAM_SIZES);

    // Validate parent
    CFileReport::validate();

    // Local validation
    for (int i = 0; i < (int)vSizeList.size(); ++i)
    {
      if (vSizeList[i] < 0)
        CError::errorLessThan(PARAM_SIZES, PARAM_ZERO);
    }
  }
  catch (string &Ex)
  {
    Ex = "CSizeWeightReport.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CSizeWeightReport::build()
// Build our Report
//**********************************************************************
void CSizeWeightReport::build()
{
  try
  {
    // Parent
    CFileReport::build();

    // Get our relationship
    CAgeSizeManager *pManager = CAgeSizeManager::Instance();
    pAgeSize = pManager->getAgeSize(sAgeSize);

    bByLength = pAgeSize->getByLength();
    if (!bByLength)
    {
      CError::error((string)PARAM_AGE_SIZE + "." + (string)PARAM_BY_LENGTH + (string) " = false is not supported for " + (string)PARAM_SIZE_WEIGHT + (string) " reports.");
    }
  }
  catch (string &Ex)
  {
    Ex = "CSizeWeightReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CSizeWeightReport::execute()
// Execute
//**********************************************************************
void CSizeWeightReport::execute()
{
  try
  {

    // Check for correct state
    if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
      return;

    this->start();

    // Output Header
    cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
    cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR << pParameterList->getString(PARAM_TYPE) << "\n";
    cout << PARAM_LABEL << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR << sAgeSize << "\n";

    cout << PARAM_SIZES << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
    for (int i = 0; i < ((int)vSizeList.size() - 1); ++i)
    {
      cout << vSizeList[i] << CONFIG_SPACE_SEPARATOR;
    }
    cout << vSizeList[vSizeList.size() - 1] << "\n";

    cout << PARAM_WEIGHTS << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
    for (int i = 0; i < ((int)vSizeList.size() - 1); ++i)
    {
      dCV = pAgeSize->getCVFromSize(vSizeList[i]);
      cout << pAgeSize->getMeanWeightFromSize(vSizeList[i], dCV) << CONFIG_SPACE_SEPARATOR;
    }
    dCV = pAgeSize->getCVFromSize(vSizeList[vSizeList.size() - 1]);
    cout << pAgeSize->getMeanWeightFromSize(vSizeList[vSizeList.size() - 1], dCV) << "\n";
    cout << CONFIG_END_REPORT << "\n"
         << endl;

    this->end();
  }
  catch (string &Ex)
  {
    Ex = "CSizeWeightReport.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CSizeWeightReport::~CSizeWeightReport()
// Destuctor
//**********************************************************************
CSizeWeightReport::~CSizeWeightReport()
{
}
