//============================================================================
// Name        : C1x1_Initialisation_Fixture.h
// Author      : S.Rasmussen A.Dunn
// Date        : 19/07/2013
// Copyright   : Copyright NIWA Science �2013 - www.niwa.co.nz
//============================================================================
#ifdef TEST
#ifndef C1X1_INITIALISATION_FIXTURE_H_
#define C1X1_INITIALISATION_FIXTURE_H_

// Global headers
#include <string>
#include <vector>

// Local
#include "../ConfigurationLoaders/CConfigurationLoader.h"
#include "../World/CWorld.h"
#include "../World/CWorldSquare.h"

// Using
using namespace std;

//**********************************************************************
//
//
//**********************************************************************
class C1x1_Initialisation_Fixture {
public:
  // Functions
  C1x1_Initialisation_Fixture();
  virtual ~C1x1_Initialisation_Fixture();
  void          addToConfiguration(string value);
  void          addToEstimateValueConfiguation(string value);
  void          addToTimeStep(string process);
  void          loadEnvironment();
  void          loadAndRunEnvironment();
  CWorldSquare* getSquare();

protected:
  vector<string>        vConfiguration;
  vector<string>        vEstimateValueConfiguration;
  CConfigurationLoader* pConfigLoader;
  string                sTimeStep;
};

#endif /* C1X1_INITIALISATION_FIXTURE_H_ */
#endif /* TEST */
