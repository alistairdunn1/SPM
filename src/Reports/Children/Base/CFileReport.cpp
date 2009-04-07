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

//**********************************************************************
// CFileReport::CFileReport()
// Default constructor
//**********************************************************************
CFileReport::CFileReport() {
  // Default Values
  sFileName           = "";
  bOverwrite          = true;
  bStartedWrite       = false;
  fFile               = 0;

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
    sFileName   = pParameterList->getString(PARAM_FILE_NAME, true, "");
    bOverwrite  = pParameterList->getBool(PARAM_OVERWRITE, true, true);

    fFile = new ofstream();
  } catch (string Ex) {
    Ex = "CFileReporter.validate(" + getLabel() + ")->" + Ex;

  }
}

//**********************************************************************
// void CFileReport::start()
// Start the Reporting
//**********************************************************************
void CFileReport::start() {
  if (sFileName != "") {
    // Variables
    sCoutBackup     = cout.rdbuf();

    // Set our Open Flag
    ios_base::openmode mode = ios_base::out;
    if (!bOverwrite)
      mode = ios_base::app;

    // Try to Open our File
    fFile->open(sFileName.c_str(), mode);
    if (!(*fFile))
      throw string(ERROR_OPEN_FILE + sFileName);

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