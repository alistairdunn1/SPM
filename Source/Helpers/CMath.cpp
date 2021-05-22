//============================================================================
// Name        : CMath.cpp
// Author      : S.Rasmussen
// Date        : 6/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
//============================================================================

// Global Headers
#include <cmath>

// Local Headers
#include "CMath.h"

//**********************************************************************
// double CMath::lnGamma(double t)
// LN Gamma Function
//**********************************************************************
double CMath::lnGamma(double t)
{
  int j;
  double x, y, tmp, ser;
  double cof[6] = {76.18009172947146, -86.50532032941677, 24.01409824083091, -1.231739572450155, 0.1208650973866179e-2, -0.5395239384953e-5};
  y = x = t;
  tmp = x + 5.5 - (x + 0.5) * log(x + 5.5);
  ser = 1.000000000190015;
  for (j = 0; j <= 5; j++)
    ser += (cof[j] / ++y);
  return (log(2.5066282746310005 * ser / x) - tmp);
}

//**********************************************************************
// double CMath::lnFactorial(double t)
// LN Factorial Function
//**********************************************************************
double CMath::lnFactorial(double t)
{
  return (CMath::lnGamma(t + 1.0));
}

//**********************************************************************
// double CMath::zeroFun(double x, double delta)
// ZeroFun Function
//**********************************************************************
double CMath::zeroFun(double x, double delta)
{
  if (x >= delta)
  {
    return x;
  }
  else
  {
    return delta / (2 - (x / delta));
  }
}
