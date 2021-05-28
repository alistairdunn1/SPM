//============================================================================
// Name        : C3x3_Fixture.cpp
// Author      : S.Rasmussen
// Date        : 27/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Local headers
#include "C3x3_Fixture.h"

#include "../CRuntimeController.h"
#include "../ConfigurationLoaders/CConfigurationLoader.h"
#include "../Helpers/CConvertor.h"

// Configuration Files
#include "ConfigurationFiles/Basic_3x3.h"

//**********************************************************************
// C3x3_Fixture::C3x3_Fixture()
// Default Constructor
//**********************************************************************
C3x3_Fixture::C3x3_Fixture() {
  // Load our Configuration Loader
  pConfigLoader = new CConfigurationLoader();

  CConvertor::stringToVectorByNewline(basic_3x3, vConfiguration);

  sTimeStep = "@time_step step_one\n";
  sTimeStep += "processes ";
}

//**********************************************************************
//
//
//**********************************************************************
void C3x3_Fixture::addToConfiguration(string value) {
  CConvertor::stringToVectorByNewline(value, vConfiguration);
}

//**********************************************************************
//
//
//**********************************************************************
void C3x3_Fixture::addToTimeStep(string process) {
  sTimeStep += process + " ";
}

//**********************************************************************
//
//
//**********************************************************************
void C3x3_Fixture::loadEnvironment(string runMode) {
  if (runMode == "-s") {
    const char* argv[] = {"C:\\Temp\\spm.exe", "-s", "1", "-g", "656"};
    CRuntimeController::Instance()->parseCommandLine(5, argv);
  } else {
    const char* argv[] = {"C:\\Temp\\spm.exe", (char*)runMode.c_str()};
    CRuntimeController::Instance()->parseCommandLine(2, argv);
  }

  sTimeStep += "\n";
  addToConfiguration(sTimeStep);

  pConfigLoader->loadIntoCache(vConfiguration);
  pConfigLoader->loadConfigFile(true);
}

//**********************************************************************
//
//
//**********************************************************************
void C3x3_Fixture::loadAndRunEnvironment(string runMode) {
  loadEnvironment(runMode);
  CRuntimeController::Instance()->run();
}

//**********************************************************************
//
//
//**********************************************************************
CWorldSquare* C3x3_Fixture::getSquare(int row, int col) {
  return CWorld::Instance()->getBaseSquare(row, col);
}

//**********************************************************************
// C3x3_Fixture::~C3x3_Fixture()
// Destructor
//**********************************************************************
C3x3_Fixture::~C3x3_Fixture() {
  delete pConfigLoader;

  CRuntimeController::Destroy();
}

#endif /* TEST */
