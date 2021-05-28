//============================================================================
// Name        : C1x1EmptyFixture.cpp
// Author      : S.Rasmussen
// Date        : 11/09/2014
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
// Description :
//============================================================================
#ifdef TEST

// headers
#include "C1x1_Empty_Fixture.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim_all.hpp>

#include "../CRuntimeController.h"
#include "../ConfigurationLoaders/CConfigurationLoader.h"
#include "../Helpers/CConvertor.h"

/**
 * Default constructor
 */
C1x1_Empty_Fixture::C1x1_Empty_Fixture() {
  pConfigLoader = new CConfigurationLoader();

  const char* argv[] = {"C:\\Temp\\spm.exe", "-e", "-q"};
  CRuntimeController::Instance()->parseCommandLine(3, argv);
}

/**
 * Destructor
 */
C1x1_Empty_Fixture::~C1x1_Empty_Fixture() {
  delete pConfigLoader;
  CRuntimeController::Destroy();
}

/**
 *
 */
void C1x1_Empty_Fixture::addToConfiguration(std::string value) {
  vector<string> lines;
  boost::split(lines, value, boost::is_any_of("\n"));

  vConfiguration.insert(vConfiguration.end(), lines.begin(), lines.end());
}

/**
 *
 */
void C1x1_Empty_Fixture::loadAndRunEnvironment() {
  pConfigLoader->loadIntoCache(vConfiguration);
  pConfigLoader->loadConfigFile(true);

  CRuntimeController::Instance()->run();
}

#endif /* TEST */
