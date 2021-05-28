//============================================================================
// Name        : C1x1_Initialisation_Fixture.cpp
// Author      : S.Rasmussen A.Dunn
// Date        : 19/07/2013
// Copyright   : Copyright NIWA Science �2013 - www.niwa.co.nz
//============================================================================
#ifdef TEST

// Local headers
#include "C1x1_Initialisation_Fixture.h"

#include "../CRuntimeController.h"
#include "../ConfigurationLoaders/CConfigurationLoader.h"
#include "../Helpers/CConvertor.h"

// Configuration Files
#include "ConfigurationFiles/Basic_initialisation_1x1.h"

//**********************************************************************
// C1x1_Fixture::C1x1_Fixture()
// Default Constructor
//**********************************************************************
C1x1_Initialisation_Fixture::C1x1_Initialisation_Fixture() {
  // Load our Configuration Loader
  pConfigLoader = new CConfigurationLoader();

  CConvertor::stringToVectorByNewline(basic_initialisation_1x1, vConfiguration);

  const char* argv[] = {"C:\\Temp\\spm.exe", "-r"};
  CRuntimeController::Instance()->parseCommandLine(2, argv);

  sTimeStep = "@time_step step_one\n";
  sTimeStep += "processes ";
}

//**********************************************************************
// void C1x1_Fixture::addToConfiguration(string value)
// Add a value to our Configuration
//**********************************************************************
void C1x1_Initialisation_Fixture::addToConfiguration(string value) {
  CConvertor::stringToVectorByNewline(value, vConfiguration);
}

//**********************************************************************
// void C1x1_Fixture::addToEstimateValueConfiguration(string value)
// Add values to our Estimate Value configuration
//**********************************************************************
void C1x1_Initialisation_Fixture::addToEstimateValueConfiguation(string value) {
  CConvertor::stringToVectorByNewline(value, vEstimateValueConfiguration);
}

//**********************************************************************
// void C1x1_Fixture::addToTimeStep(string process)
// Add processes to our time step
//**********************************************************************
void C1x1_Initialisation_Fixture::addToTimeStep(string process) {
  sTimeStep += process + " ";
}

//**********************************************************************
// void C1x1_Fixture::loadEnvironment()
// Load Environment
//**********************************************************************
void C1x1_Initialisation_Fixture::loadEnvironment() {
  sTimeStep += "\n";
  addToConfiguration(sTimeStep);

  pConfigLoader->loadIntoCache(vConfiguration);
  pConfigLoader->loadConfigFile(true);

  if (vEstimateValueConfiguration.size() > 0) {
    pConfigLoader->loadIntoCache(vEstimateValueConfiguration);
    pConfigLoader->loadEstimateValuesFile(true);
  }
}

//**********************************************************************
// void C1x1_Fixture::loadAndRunEnvironment()
// Load our Environment and Run the World
//**********************************************************************
void C1x1_Initialisation_Fixture::loadAndRunEnvironment() {
  loadEnvironment();
  CRuntimeController::Instance()->run();
}

//**********************************************************************
// CWorldSquare* C1x1_Fixture::getSquare()
// Get our World Square
//**********************************************************************
CWorldSquare* C1x1_Initialisation_Fixture::getSquare() {
  return CWorld::Instance()->getBaseSquare(0, 0);
}

//**********************************************************************
// C1x1_Fixture::~C1x1_Fixture()
// Destructor
//**********************************************************************
C1x1_Initialisation_Fixture::~C1x1_Initialisation_Fixture() {
  delete pConfigLoader;

  CRuntimeController::Destroy();
}

#endif
