//============================================================================
// Name        : CProfileFactory.h
// Author      : S.Rasmussen
// Date        : 12/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CPROFILEFACTORY_H_
#define CPROFILEFACTORY_H_

// Global headers
#include <string>

// Local headers
#include "../CProfile.h"

// Using
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CProfileFactory {
public:
  // Functions
  static CProfile* buildProfile(string type, bool registerWithManager = true);

private:
  // Functions
  CProfileFactory();
  virtual ~CProfileFactory();
};

#endif /* CPROFILEFACTORY_H_ */
