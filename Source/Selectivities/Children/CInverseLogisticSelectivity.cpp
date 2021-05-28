//============================================================================
// Name        : CInverseLogisticSelectivity.cpp
// Author      : S.Rasmussen
// Date        : 6/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CInverseLogisticSelectivity.h"

#include "../../Helpers/CError.h"

//**********************************************************************
// CInverseLogisticSelectivity::CInverseLogisticSelectivity()
// Default constructor
//**********************************************************************
CInverseLogisticSelectivity::CInverseLogisticSelectivity() {
  // Register Estimables
  registerEstimable(PARAM_A50, &dA50);
  registerEstimable(PARAM_ATO95, &dAto95);
  registerEstimable(PARAM_ALPHA, &dAlpha);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_A50);
  pParameterList->registerAllowed(PARAM_ATO95);
  pParameterList->registerAllowed(PARAM_ALPHA);
}

//**********************************************************************
// void CInverseLogisticSelectivity::validate()
// validate
//**********************************************************************
void CInverseLogisticSelectivity::validate() {
  try {
    // Populate our variables
    dA50   = pParameterList->getDouble(PARAM_A50);
    dAto95 = pParameterList->getDouble(PARAM_ATO95);
    dAlpha = pParameterList->getDouble(PARAM_ALPHA, true, 1.0);

    // Validate parent
    CSelectivity::validate();

    // Local validation
    if (dAlpha <= 0)
      CError::errorLessThanEqualTo(PARAM_ALPHA, PARAM_ZERO);
    if (dAto95 <= 0)
      CError::errorLessThanEqualTo(PARAM_ATO95, PARAM_ZERO);
  } catch (string& Ex) {
    Ex = "CInverseLogisticSelectivity.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CInverseLogisticSelectivity::calculateResult(int Age)
// Calculate a result for our Vector
//**********************************************************************
double CInverseLogisticSelectivity::calculateResult(int Age) {
#ifndef OPTIMIZE
  try {
#endif

    double dRet  = 0.0;
    double dTemp = (dA50 - Age) / dAto95;

    if (dTemp > 5.0)
      dRet = dAlpha;
    else if (dTemp < -5.0)
      dRet = 0.0;
    else
      dRet = dAlpha - (dAlpha / (1.0 + pow(19.0, dTemp)));

    return dRet;

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CInverseLogisticSelectivity.calculateResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
  return 0.0;
#endif
}

//**********************************************************************
// CInverseLogisticSelectivity::~CInverseLogisticSelectivity()
// Default De-Constructor
//**********************************************************************
CInverseLogisticSelectivity::~CInverseLogisticSelectivity() {}
