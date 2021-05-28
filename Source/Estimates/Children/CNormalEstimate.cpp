//============================================================================
// Name        : CNormalEstimate.cpp
// Author      : S.Rasmussen
// Date        : 8/09/2014
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
// Description :
//============================================================================

// headers
#include "CNormalEstimate.h"

#include "../../Helpers/CError.h"

/**
 * Constructor
 */
CNormalEstimate::CNormalEstimate() {
  // Register estimables
  registerEstimable(PARAM_MU, &dMu);
  registerEstimable(PARAM_CV, &dCv);

  // Register allowed parameters
  pParameterList->registerAllowed(PARAM_MU);
  pParameterList->registerAllowed(PARAM_CV);
}

/**
 * Validate the Prior/Estimate
 */
void CNormalEstimate::validate() {
  CEstimate::validate();

  try {
    // Assign parameters
    dMu = pParameterList->getDouble(PARAM_MU);
    dCv = pParameterList->getDouble(PARAM_CV);

    // Local validation
    if (dCv <= 0.0)
      CError::errorLessThanEqualTo(PARAM_CV, PARAM_ZERO);
  } catch (string& Ex) {
    Ex = "CNormalPrior.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

/**
 * get the score
 */
double CNormalEstimate::getScore() {
  return 0.5 * ((getValue() - dMu) / (dCv * dMu)) * ((getValue() - dMu) / (dCv * dMu));
}
