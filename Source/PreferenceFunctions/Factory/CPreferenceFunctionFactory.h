//============================================================================
// Name        : CPreferenceFunctionFactory.h
// Author      : S.Rasmussen
// Date        : 7/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CPREFERENCEFUNCTIONFACTORY_H_
#define CPREFERENCEFUNCTIONFACTORY_H_

// Global Includes
#include <string>

// Local headers
#include "../CPreferenceFunction.h"

// Using
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CPreferenceFunctionFactory
{
public:
  // Functions
  static CPreferenceFunction *buildPreferenceFunction(string type, bool registerWithManager = true);

private:
  // Functions
  CPreferenceFunctionFactory() {}
  virtual ~CPreferenceFunctionFactory() {}
};

#endif /* CPREFERENCEFUNCTIONFACTORY_H_ */
