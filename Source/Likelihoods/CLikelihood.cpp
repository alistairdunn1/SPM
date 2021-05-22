//============================================================================
// Name        : CLikelihood.cpp
// Author      : S.Rasmussen
// Date        : 14/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CLikelihood.h"

//**********************************************************************
// CLikelihood::CLikelihood()
// Default Constructor
//**********************************************************************
CLikelihood::CLikelihood()
{
}

double CLikelihood::adjustLikelihoodValue(const double LikelihoodMultiplier, const double Likelihood)
{
  // adjust likelihood
  if ((LikelihoodMultiplier > 0.0))
    return (LikelihoodMultiplier * Likelihood);

  return 0.0;
}

//**********************************************************************
// CLikelihood::~CLikelihood()
// Destructor
//**********************************************************************
CLikelihood::~CLikelihood()
{
}
