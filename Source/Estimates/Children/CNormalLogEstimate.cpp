//============================================================================
// Name        : CNormalLogEstimate.cpp
// Author      : S.Rasmussen
// Date        : 8/09/2014
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
// Description :
//============================================================================

// headers
#include "CNormalLogEstimate.h"

#include "../../Helpers/CError.h"

/**
 * Constructor
 */
CNormalLogEstimate::CNormalLogEstimate() {
  // Register estimables
  registerEstimable(PARAM_MU, &dMu);
  registerEstimable(PARAM_SIGMA, &dSigma);

  // Register parameters
  pParameterList->registerAllowed(PARAM_MU);
  pParameterList->registerAllowed(PARAM_SIGMA);
}

/**
 * Validate the Prior/Estimate
 */
void CNormalLogEstimate::validate() {
  CEstimate::validate();

  try {
    // Assign parameters
    dMu    = pParameterList->getDouble(PARAM_MU);
    dSigma = pParameterList->getDouble(PARAM_SIGMA);

    // Local validation
    if (dSigma <= 0.0)
      CError::errorLessThanEqualTo(PARAM_SIGMA, PARAM_ZERO);
  } catch (string& Ex) {
    Ex = "CNormalLogPrior.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

/**
 * Get the score
 */
double CNormalLogEstimate::getScore() {
  double dRet = 0.0;
  dRet        = log(getValue()) + 0.5 * pow((log(getValue()) - dMu) / dSigma, 2);
  return dRet;
}
