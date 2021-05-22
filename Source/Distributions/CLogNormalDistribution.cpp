//============================================================================
// Name        : CNormalDistribution.cpp
// Author      : S.Rasmussen
// Date        : 7/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global Headers
#include <boost/math/distributions/lognormal.hpp>

// Local Headers
#include "CLogNormalDistribution.h"

// Namespace
using boost::math::lognormal;

//**********************************************************************
// double CNormalDistribution::getCDF(double x, double mu, double sigma)
// Get a a value from the normal CDF
//**********************************************************************
double CLogNormalDistribution::getCDF(double x, double mu, double sigma)
{

  if (sigma <= 0)
  {
    if (x < mu)
      return 0;
    else if (x >= mu)
      return 1;
  }

  lognormal s(mu, sigma);
  return cdf(s, x);
}

//**********************************************************************
// double CLogNormalDistribution::getQuantile(double x, double mu, double sigma)
// Get a a value from the normal as quantiles
//**********************************************************************
double CLogNormalDistribution::getQuantile(double x, double mu, double sigma)
{

  if (sigma <= 0)
  {
    if (x < mu)
      return 0;
    else if (x >= mu)
      return 1;
  }

  lognormal s(mu, sigma);
  return quantile(s, x);
}