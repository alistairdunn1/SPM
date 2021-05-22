//============================================================================
// Name        : CUniformLogEstimate.cpp
// Author      : S.Rasmussen
// Date        : 8/09/2014
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
// Description :
//============================================================================

// headers
#include "CUniformLogEstimate.h"

/**
 * Constructor
 */
CUniformLogEstimate::CUniformLogEstimate()
{
}

/**
 * Get our score
 */
double CUniformLogEstimate::getScore()
{
  double dRet = log(getValue());
  return dRet;
}
