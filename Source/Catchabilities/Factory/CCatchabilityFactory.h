//============================================================================
// Name        : CCatchabilityFactory.h
// Author      : S.Rasmussen
// Date        : 26/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CCATCHABILITYFACTORY_H_
#define CCATCHABILITYFACTORY_H_

// Global headers
#include <string>

// Local headers
#include "../CCatchability.h"

// Using
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CCatchabilityFactory {
public:
  // Functions
  static CCatchability* buildCatchability(string type, bool registerWithManager = true);

private:
  // Functions
  CCatchabilityFactory() {}
  virtual ~CCatchabilityFactory(){};
};

#endif /* CCATCHABILITYFACTORY_H_ */
