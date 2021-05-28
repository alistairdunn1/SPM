//============================================================================
// Name        : CBetaEstimate.cpp
// Author      : S.Rasmussen
// Date        : 8/09/2014
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
// Description :
//============================================================================

// headers
#include "CBetaEstimate.h"

#include <iostream>

#include "../../Helpers/CError.h"

// namespaces
using std::cout;
using std::endl;

/**
 * Default constructor
 */
CBetaEstimate::CBetaEstimate() {
  // Register estimables
  registerEstimable(PARAM_MU, &dMu);
  registerEstimable(PARAM_SIGMA, &dSigma);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_MU);
  pParameterList->registerAllowed(PARAM_SIGMA);
  pParameterList->registerAllowed(PARAM_A);
  pParameterList->registerAllowed(PARAM_B);
}

/**
 * Validate our Beta prior/estimate
 */
void CBetaEstimate::validate() {
  CEstimate::validate();

  try {
    // Assign our parameters
    dMu    = pParameterList->getDouble(PARAM_MU);
    dSigma = pParameterList->getDouble(PARAM_SIGMA);
    dA     = pParameterList->getDouble(PARAM_A);
    dB     = pParameterList->getDouble(PARAM_B);

    // Local validation
    if (dSigma <= 0.0)
      CError::errorLessThanEqualTo(PARAM_SIGMA, PARAM_ZERO);
    if (dA >= dB)
      CError::errorGreaterThanEqualTo(PARAM_A, PARAM_B);
    if (((((dMu - dA) * (dB - dMu)) / (dSigma * dSigma)) - 1) <= 0)
      CError::error(PARAM_SIGMA + string(" is too large"));
  } catch (string& Ex) {
    Ex = "CBetaEstimate.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

/**
 *
 */
double CBetaEstimate::getScore() {
  double dRet = 0.0;

  dV   = (dMu - dA) / (dB - dA);
  dT   = (((dMu - dA) * (dB - dMu)) / (dSigma * dSigma)) - 1.0;
  dM   = dT * dV;
  dN   = dT * (1.0 - dV);
  dRet = ((1.0 - dM) * log(getValue() - dA)) + ((1.0 - dN) * log(dB - getValue()));

  return dRet;
}
