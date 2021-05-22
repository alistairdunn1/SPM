//============================================================================
// Name        : CNormalByStdevEstimate.cpp
// Author      : S.Rasmussen
// Date        : 8/09/2014
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
// Description :
//============================================================================

// headers
#include "CNormalByStdevEstimate.h"
#include "../../Helpers/CError.h"

/**
 * Default constructor
 */
CNormalByStdevEstimate::CNormalByStdevEstimate()
{
  // Register estimables
  registerEstimable(PARAM_MU, &dMu);
  registerEstimable(PARAM_SIGMA, &dSigma);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_MU);
  pParameterList->registerAllowed(PARAM_SIGMA);
}

/**
 * Validate the Prior/Estimate
 */
void CNormalByStdevEstimate::validate()
{
  CEstimate::validate();

  try
  {
    // Assign parameters
    dMu = pParameterList->getDouble(PARAM_MU);
    dSigma = pParameterList->getDouble(PARAM_SIGMA);

    // Local validation
    if (dSigma <= 0.0)
      CError::errorLessThanEqualTo(PARAM_SIGMA, PARAM_ZERO);
  }
  catch (string &Ex)
  {
    Ex = "CNormalByStdevPrior.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

/**
 * Get our score
 */
double CNormalByStdevEstimate::getScore()
{
  return 0.5 * ((getValue() - dMu) / dSigma) * ((getValue() - dMu) / dSigma);
}
