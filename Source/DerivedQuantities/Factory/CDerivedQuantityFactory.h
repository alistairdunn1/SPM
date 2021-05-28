//============================================================================
// Name        : CDerivedQuantityFactory.h
// Author      : S.Rasmussen
// Date        : 23/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CDERIVEDQUANTITYFACTORY_H_
#define CDERIVEDQUANTITYFACTORY_H_

// Global Includes
#include <string>

// Local includes
#include "../CDerivedQuantity.h"

// Using
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CDerivedQuantityFactory {
public:
  static CDerivedQuantity* buildDerivedQuantity(string type, bool registerWithManager = true);

private:
  // Functions
  CDerivedQuantityFactory(){};
  virtual ~CDerivedQuantityFactory(){};
};

#endif /* CDERIVEDQUANTITYFACTORY_H_ */
