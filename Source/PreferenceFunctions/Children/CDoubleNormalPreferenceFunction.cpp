//============================================================================
// Name        : CDoubleNormalPreferenceFunction.cpp
// Author      : S.Rasmussen
// Date        : 16/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CDoubleNormalPreferenceFunction.h"

#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"

//**********************************************************************
// CDoubleNormalPreferenceFunction::CDoubleNormalPreferenceFunction()
// Default Constructor
//**********************************************************************
CDoubleNormalPreferenceFunction::CDoubleNormalPreferenceFunction() {
  sType = PARAM_DOUBLE_NORMAL;

  // Register our Estimables
  registerEstimable(PARAM_SIGMA_L, &dSigmaL);
  registerEstimable(PARAM_SIGMA_R, &dSigmaR);
  registerEstimable(PARAM_MU, &dMu);

  // Register User Allowed Parameters
  pParameterList->registerAllowed(PARAM_SIGMA_L);
  pParameterList->registerAllowed(PARAM_SIGMA_R);
  pParameterList->registerAllowed(PARAM_MU);
  pParameterList->registerAllowed(PARAM_LAYER);
}

//**********************************************************************
// void CDoubleNormalPreferenceFunction::validate()
// Validate
//**********************************************************************
void CDoubleNormalPreferenceFunction::validate() {
  try {
    // Assign our Variables
    dSigmaL    = pParameterList->getDouble(PARAM_SIGMA_L);
    dSigmaR    = pParameterList->getDouble(PARAM_SIGMA_R);
    dMu        = pParameterList->getDouble(PARAM_MU);
    sLayerName = pParameterList->getString(PARAM_LAYER);

    // Validate parent
    CPreferenceFunction::validate();

    // Local validation
    if (dSigmaL <= 0.0)
      CError::errorLessThanEqualTo(PARAM_SIGMA_L, PARAM_ZERO);
    if (dSigmaR <= 0.0)
      CError::errorLessThanEqualTo(PARAM_SIGMA_R, PARAM_ZERO);
  } catch (string& Ex) {
    Ex = "CDoubleNormalPreferenceFunction.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CDoubleNormalPreferenceFunction::build()
// Build our Object
//**********************************************************************
void CDoubleNormalPreferenceFunction::build() {
  try {
    // Get our Layer
    CLayerManager* pLayerManager = CLayerManager::Instance();
    pLayer                       = pLayerManager->getNumericLayer(sLayerName);
  } catch (string& Ex) {
    Ex = "CDoubleNormalPreferenceFunction.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CDoubleNormalPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
// Get Result
//**********************************************************************
double CDoubleNormalPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex) {
  dRet = 0.0;
#ifndef OPTIMIZE
  try {
#endif

    dLayerValue = pLayer->getValue(TRIndex, TCIndex, RIndex, CIndex);
    if (dLayerValue < dMu)
      dRet = pow(2.0, -((dLayerValue - dMu) / dSigmaL * (dLayerValue - dMu) / dSigmaL));
    else
      dRet = pow(2.0, -((dLayerValue - dMu) / dSigmaR * (dLayerValue - dMu) / dSigmaR));

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CDoubleNormalPreferenceFunction.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return CMath::zeroFun(pow(dRet, dAlpha), ZERO);
}

//**********************************************************************
// CDoubleNormalPreferenceFunction::~CDoubleNormalPreferenceFunction()
// Default De-Constructor
//**********************************************************************
CDoubleNormalPreferenceFunction::~CDoubleNormalPreferenceFunction() {}
