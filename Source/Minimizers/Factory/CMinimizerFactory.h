//============================================================================
// Name        : CMinimizerFactory.h
// Author      : S.Rasmussen
// Date        : 12/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CMINIMIZERFACTORY_H_
#define CMINIMIZERFACTORY_H_

// Global headers
#include <string>

// Local Includes
#include "../CMinimizer.h"

// Using
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CMinimizerFactory {
public:
  // Functions
  static CMinimizer* buildMinimizer(string type, bool registerWithManager = true);

private:
  // Functions
  CMinimizerFactory();
  virtual ~CMinimizerFactory();
};

#endif /* CMINIMIZERFACTORY_H_ */
