//============================================================================
// Name        : CSelectivityFactory.h
// Author      : S.Rasmussen
// Date        : 9/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CSELECTIVITYFACTORY_H_
#define CSELECTIVITYFACTORY_H_

// Global headers
#include <string>

// Local headers
#include "../CSelectivity.h"

// Using
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CSelectivityFactory {
public:
  // Functions
  static CSelectivity* buildSelectivity(string type, bool registerWithManager = true);

private:
  // Functions
  CSelectivityFactory();
  virtual ~CSelectivityFactory();
};

#endif /* CSELECTIVITYFACTORY_H_ */
