//============================================================================
// Name        : C1x1_Fixture.h
// Author      : S.Rasmussen
// Date        : 20/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description : This class is a basic 1x1 World Setup for our Unit Tests
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST
#ifndef C1X1_FIXTURE_H_
#define C1X1_FIXTURE_H_

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
class C1x1_Fixture
{
public:
  // Functions
  C1x1_Fixture();
  virtual ~C1x1_Fixture();
  void addToConfiguration(string value);
  void addToEstimateValueConfiguation(string value);
  void addToTimeStep(string process);
  void loadEnvironment();
  void loadAndRunEnvironment();
  CWorldSquare *getSquare();

protected:
  vector<string> vConfiguration;
  vector<string> vEstimateValueConfiguration;
  CConfigurationLoader *pConfigLoader;
  string sTimeStep;
};

#endif /* C1X1_FIXTURE_H_ */
#endif /* TEST */
