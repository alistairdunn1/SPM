//============================================================================
// Name        : CLogNormalEstimate.cpp
// Author      : S.Rasmussen
// Date        : 8/09/2014
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
// Description :
//============================================================================

// headers
#include "CLogNormalEstimate.h"
#include "../../Helpers/CError.h"

/**
 * Default constructor
 */
CLogNormalEstimate::CLogNormalEstimate()
{
  // Register estimables
  registerEstimable(PARAM_MU, &dMu);
  registerEstimable(PARAM_CV, &dCv);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_MU);
  pParameterList->registerAllowed(PARAM_CV);
}

/**
 * Validate our Prior/Estimate
 */
void CLogNormalEstimate::validate()
{
  CEstimate::validate();

  try
  {

    // Populate our variables
    dMu = pParameterList->getDouble(PARAM_MU);
    dCv = pParameterList->getDouble(PARAM_CV);

    // Local validation
    if (dMu <= 0.0)
      CError::errorLessThanEqualTo(PARAM_MU, PARAM_ZERO);
    if (dCv <= 0.0)
      CError::errorLessThanEqualTo(PARAM_CV, PARAM_ZERO);
  }
  catch (string &Ex)
  {
    Ex = "CLogNormalPrior.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

/**
 *
 */
double CLogNormalEstimate::getScore()
{
  double dRet = 0.0;
  dSigma = sqrt(log(1 + dCv * dCv));
  dRet = log(getValue()) + 0.5 * pow(log(getValue() / dMu) / dSigma + dSigma * 0.5, 2);
  return dRet;
}
