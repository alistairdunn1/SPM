//============================================================================
// Name        : CEstimateValueReport.cpp
// Author      : S.Rasmussen
// Date        : 4/03/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global Headers
#include <sys/stat.h>

// Local Headers
#include "../../Estimates/CEstimate.h"
#include "../../Estimates/CEstimateManager.h"
#include "../../Helpers/CError.h"
#include "CEstimateValueReport.h"

//**********************************************************************
// CEstimateValueReport::CEstimateValueReport()
// Default Constructor
//**********************************************************************
CEstimateValueReport::CEstimateValueReport() {
  eExecutionState = STATE_FINALIZATION;
  bWrittenHeader  = false;
  bStandardHeader = false;

  // Register allowed
  pParameterList->registerAllowed(PARAM_HEADER);
}

//**********************************************************************
// void CEstimateValueReport::validate()
// Validate our selectivity
//**********************************************************************
void CEstimateValueReport::validate() {
  try {
    // Validate parent
    CFileReport::validate();

    // Local validation
    bStandardHeader = pParameterList->getBool(PARAM_HEADER, true, sFileName == "" ? true : false);
  } catch (string& ex) {
    ex = "CEstimateValueReport.validate(" + getLabel() + ")->" + ex;
    throw ex;
  }
}

//**********************************************************************
//
//
//**********************************************************************
void CEstimateValueReport::execute() {
  try {
    // Check for correct state
    if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
      if (pRuntimeController->getRunMode() != RUN_MODE_PROFILE)
        return;

    // Check if File Already Exists for overwrite
    // If file already exists, and we not overwriting we don't
    // want to re-write the original header
    if ((sFileName != "") && (!bOverwrite)) {
      struct stat stFileInfo;
      int         intStat = stat(sFileName.c_str(), &stFileInfo);

      if (intStat == 0)         // File Exists
        bWrittenHeader = true;  // Don't write the header
    }
    // Start IO
    this->start();

    // Variables
    CEstimateManager* pEstimateManager = CEstimateManager::Instance();
    int               iCount           = pEstimateManager->getEstimateCount();

    if (bStandardHeader) {
      cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
      cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";
      cout << PARAM_PARAMETER << CONFIG_RATIO_SEPARATOR << " ";
    }

    if (!bWrittenHeader) {
      bWrittenHeader = true;

      // Output Header
      for (int i = 0; i < iCount; ++i) {
        CEstimate* pEstimate = pEstimateManager->getEstimate(i);
        cout << pEstimate->getParameter();

        if ((i + 1) < iCount)
          cout << CONFIG_SPACE_SEPARATOR;
      }
      cout << "\n";
    }

    for (int i = 0; i < iCount; ++i) {
      CEstimate* pEstimate = pEstimateManager->getEstimate(i);
      cout << pEstimate->getValue();
      if ((i + 1) < iCount)
        cout << CONFIG_SPACE_SEPARATOR;
    }
    cout << endl;

    if (bStandardHeader)
      cout << CONFIG_END_REPORT << "\n" << endl;

    // End IO
    this->end();
  } catch (string& Ex) {
    Ex = "CEstimateValueReport.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CEstimateValueReport::~CEstimateValueReport()
// Destructor
//**********************************************************************
CEstimateValueReport::~CEstimateValueReport() {}
