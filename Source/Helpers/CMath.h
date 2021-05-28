//============================================================================
// Name        : CMath.h
// Author      : S.Rasmussen
// Date        : 6/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
//============================================================================
#ifndef CMATH_H_
#define CMATH_H_

// Local Headers
#include "DefinedValues.h"

//**********************************************************************
//
//
//**********************************************************************
class CMath {
public:
  // Functions
  static double lnGamma(double t);
  static double lnFactorial(double t);
  static double zeroFun(double x, double delta);

private:
  // Functions
  CMath() {}
  virtual ~CMath() {}
};

#endif /* CMATH_H_ */
