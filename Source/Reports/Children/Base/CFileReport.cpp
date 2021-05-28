//============================================================================
// Name        : CFileReport.cpp
// Author      : S.Rasmussen
// Date        : 29/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CFileReport.h"

#include "../../CReportManager.h"

//**********************************************************************
// CFileReport::CFileReport()
// Default constructor
//**********************************************************************
CFileReport::CFileReport() {
  // Default Values
  sFileName     = "";
  sFullFileName = "";
  bOverwrite    = true;
  bStartedWrite = false;
  fFile         = 0;

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_FILE_NAME);
  pParameterList->registerAllowed(PARAM_OVERWRITE);
}

//**********************************************************************
// void CFileReport::validate()
// Validate file reporter
//**********************************************************************
void CFileReport::validate() {
  try {
    // Base
    CReport::validate();

    // Assign variables
    sFileName  = pParameterList->getString(PARAM_FILE_NAME, true, "");
    bOverwrite = pParameterList->getBool(PARAM_OVERWRITE, true, true);

    fFile = new ofstream();
  } catch (string& Ex) {
    Ex = "CFileReport.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CFileReport::start()
// Start the Reporting
//**********************************************************************
void CFileReport::start() {
  if (sFileName != "") {
    /**
     * Check if our suffix has changed. If it has we need to reset
     * our overwrite variable otherwise all reports after the
     * first one will append.
     */
    string sSuffix = CReportManager::Instance()->getReportSuffix();
    if (sSuffix != sLastSuffix) {
      bOverwrite = pParameterList->getBool(PARAM_OVERWRITE, true, true);
    }
    sLastSuffix = sSuffix;

    // This variable allows us to print out to different suffixed files
    // based on different iterations etc
    sFullFileName = sFileName + sSuffix;

    // Variables
    sCoutBackup = cout.rdbuf();

    // Set our Open Flag
    ios_base::openmode mode = ios_base::out;
    if (!bOverwrite)
      mode = ios_base::app;

    // Try to Open our File
    fFile->open(sFullFileName.c_str(), mode);
    if (!(*fFile))
      throw string(ERROR_OPEN_FILE + sFullFileName);

    // Redirect Standard Output
    cout.rdbuf(fFile->rdbuf());
  }

  // Now we want to Append
  bOverwrite = false;
}

//**********************************************************************
// void CFileReport::end()
// End the Reporting
//**********************************************************************
void CFileReport::end() {
  cout.flush();

  if (sFileName != "") {
    fFile->close();
    cout.rdbuf(sCoutBackup);
  }
}

//**********************************************************************
// CFileReport::~CFileReport()
// Destructor
//**********************************************************************
CFileReport::~CFileReport() {
  if (fFile != 0)
    delete fFile;
}
