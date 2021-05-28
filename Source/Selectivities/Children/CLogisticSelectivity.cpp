//============================================================================
// Name        : CLogisticSelectivity.cpp
// Author      : S.Rasmussen
// Date        : 6/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CLogisticSelectivity.h"

#include "../../Helpers/CError.h"

//**********************************************************************
// CLogisticSelectivity::CLogisticSelectivity()
// Default constructor
//**********************************************************************
CLogisticSelectivity::CLogisticSelectivity() {
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
// void CLogisticSelectivity::validate()
// validate
//**********************************************************************
void CLogisticSelectivity::validate() {
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
    Ex = "CLogisticSelectivity.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CLogisticSelectivity::calculateResult(int Age)
// Calculate a result for our Vector
//**********************************************************************
double CLogisticSelectivity::calculateResult(int Age) {
#ifndef OPTIMIZE
  try {
#endif

    double dRet  = 0.0;
    double dTemp = (dA50 - Age) / dAto95;

    if (dTemp > 5.0)
      dRet = 0.0;
    else if (dTemp < -5.0)
      dRet = dAlpha;
    else
      dRet = dAlpha / (1.0 + pow(19.0, dTemp));

    return dRet;

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CLogisticSelectivity.calculateResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
  return 0.0;
#endif
}

//**********************************************************************
// CLogisticSelectivity::~CLogisticSelectivity()
// Default De-Constructor
//**********************************************************************
CLogisticSelectivity::~CLogisticSelectivity() {}
