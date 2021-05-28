//============================================================================
// Name        : C3x3_Fixture.h
// Author      : S.Rasmussen
// Date        : 27/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST
#ifndef C3X3_FIXTURE_H_
#define C3X3_FIXTURE_H_

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
class C3x3_Fixture {
public:
  C3x3_Fixture();
  virtual ~C3x3_Fixture();
  void          addToConfiguration(string value);
  void          addToTimeStep(string process);
  void          loadEnvironment(string runMode = "-r");
  void          loadAndRunEnvironment(string runMode = "-r");
  CWorldSquare* getSquare(int row, int col);

protected:
  vector<string>        vConfiguration;
  CConfigurationLoader* pConfigLoader;
  string                sTimeStep;
};

#endif /* C3X3_FIXTURE_H_ */
#endif
