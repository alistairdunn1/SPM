//============================================================================
// Name        : CDoubleNormalSelectivity.cpp
// Author      : A. Dunn
// Date        : 7/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CDoubleNormalSelectivity.h"

//**********************************************************************
// CDoubleNormalSelectivity::CDoubleNormalSelectivity()
// Default constructor
//**********************************************************************
CDoubleNormalSelectivity::CDoubleNormalSelectivity() {
  // Register estimables
  registerEstimable(PARAM_MU, &dMu);
  registerEstimable(PARAM_SIGMA_L, &dSigmaL);
  registerEstimable(PARAM_SIGMA_R, &dSigmaR);
  registerEstimable(PARAM_ALPHA, &dAlpha);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_MU);
  pParameterList->registerAllowed(PARAM_SIGMA_L);
  pParameterList->registerAllowed(PARAM_SIGMA_R);
  pParameterList->registerAllowed(PARAM_ALPHA);
}

//**********************************************************************
// void CDoubleNormalSelectivity::validate()
// validate
//**********************************************************************
void CDoubleNormalSelectivity::validate() {
  try {
    // Base
    CSelectivity::validate();

    // Populate our variables
    dMu     = pParameterList->getDouble(PARAM_MU);
    dSigmaL = pParameterList->getDouble(PARAM_SIGMA_L);
    dSigmaR = pParameterList->getDouble(PARAM_SIGMA_R);
    dAlpha  = pParameterList->getDouble(PARAM_ALPHA,true,1.0);

    if (dAlpha <= 0)
      throw("Alpha must be positive"); // TODO: better error messages
    if ((dSigmaL <= 0) || (dSigmaR <= 0 ))
      throw("Non-positive values for sigma_l or sigma_r are not allowed");  // TODO: better phrased error message

  } catch (string Ex) {
    Ex = "CDoublenormalSelectivity.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CDoubleNormalSelectivity::calculateResult(int Age)
// calculate the results for our Vector
//**********************************************************************
double CDoubleNormalSelectivity::calculateResult(int Age) {
#ifndef OPTIMIZE
  try {
#endif

    double dRet = 0.0;
    // Do our double normal Function
    if (Age < dMu)
      dRet = pow(2.0,-((Age-dMu)/dSigmaL * (Age-dMu)/dSigmaL)) * dAlpha;
    else
      dRet = pow(2.0,-((Age-dMu)/dSigmaR * (Age-dMu)/dSigmaR)) * dAlpha;

    return dRet;

#ifndef OPTIMIZE
  } catch (string Ex) {
    Ex = "CDoubleNormalSelectivity.calculateResult()->" + Ex;
    throw Ex;
  }
  return 0.0;
#endif
}

//**********************************************************************
// CDoubleNormalSelectivity::~CDoubleNormalSelectivity()
// Default De-Constructor
//**********************************************************************
CDoubleNormalSelectivity::~CDoubleNormalSelectivity() {
}
