//============================================================================
// Name        : CConstantPreferenceFunction.cpp
// Author      : A.Dunn
// Date        : 15/04/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global Headers
#include <iostream>

// Local Headers
#include "../../Helpers/CComparer.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "CConstantPreferenceFunction.h"

// Using
using std::cout;
using std::endl;

//**********************************************************************
// CConstantPreferenceFunction::CConstantPreferenceFunction()
// Default Constructor
//**********************************************************************
CConstantPreferenceFunction::CConstantPreferenceFunction() {
  sType = PARAM_CONSTANT;

  // Register our Estimables
  registerEstimable(PARAM_C, &dC);

  // Register User Allowed Parameters
  pParameterList->registerAllowed(PARAM_C);
  pParameterList->registerAllowed(PARAM_LAYER);
}

//**********************************************************************
// void CConstantPreferenceFunction::validate()
// Validate
//**********************************************************************
void CConstantPreferenceFunction::validate() {
  try {
    dC         = pParameterList->getDouble(PARAM_C, true, 1.0);
    sLayerName = pParameterList->getString(PARAM_LAYER);

    // Validate parent
    CPreferenceFunction::validate();

    // Local validations
    // Local validation
    if (dC <= 0.0)
      CError::errorLessThanEqualTo(PARAM_C, PARAM_ZERO);
  } catch (string& Ex) {
    Ex = "CConstantPreferenceFunction.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CConstantPreferenceFunction::build()
// Build our Object
//**********************************************************************
void CConstantPreferenceFunction::build() {
  try {
    // Get our Layer
    CLayerManager* pLayerManager = CLayerManager::Instance();
    pLayer                       = pLayerManager->getNumericLayer(sLayerName);
  } catch (string& Ex) {
    Ex = "CConstantPreferenceFunction.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CConstantPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
// Get Result
//**********************************************************************
double CConstantPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex) {
#ifndef OPTIMIZE
  try {
#endif

    dRet = pLayer->getValue(TRIndex, TCIndex, RIndex, CIndex) * dC;

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CConstantPreferenceFunction.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return CMath::zeroFun(pow(dRet, dAlpha), ZERO);
}

//**********************************************************************
// CConstantPreferenceFunction::~CConstantPreferenceFunction()
// Default De-Constructor
//**********************************************************************
CConstantPreferenceFunction::~CConstantPreferenceFunction() {}
