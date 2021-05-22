//============================================================================
// Name        : C1x1EmptyFixture.h
// Author      : S.Rasmussen
// Date        : 11/09/2014
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
// Description :
//============================================================================
#ifdef TEST
#ifndef C1X1EMPTYFIXTURE_H_
#define C1X1EMPTYFIXTURE_H_

// headers
#include <string>
#include <vector>

#include "../ConfigurationLoaders/CConfigurationLoader.h"
#include "../World/CWorld.h"
#include "../World/CWorldSquare.h"

// namespaces
using namespace std;

/**
 * Class definition
 */
class C1x1_Empty_Fixture
{
public:
  C1x1_Empty_Fixture();
  virtual ~C1x1_Empty_Fixture();
  void addToConfiguration(std::string value);
  void loadAndRunEnvironment();

protected:
  vector<string> vConfiguration;
  CConfigurationLoader *pConfigLoader;
};

#endif /* C1X1EMPTYFIXTURE_H_ */
#endif
