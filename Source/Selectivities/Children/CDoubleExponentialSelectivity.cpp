//============================================================================
// Name        : CDoubleExponentialSelectivity.cpp
// Author      : S.Rasmussen
// Date        : 20/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CDoubleExponentialSelectivity.h"

#include "../../Helpers/CComparer.h"
#include "../../Helpers/CError.h"

//**********************************************************************
// CDoubleExponentialSelectivity::CDoubleExponentialSelectivity()
// Default constructor
//**********************************************************************
CDoubleExponentialSelectivity::CDoubleExponentialSelectivity() {
  // Register estimables
  registerEstimable(PARAM_X0, &dX0);
  registerEstimable(PARAM_Y0, &dY0);
  registerEstimable(PARAM_Y1, &dY1);
  registerEstimable(PARAM_Y2, &dY2);
  registerEstimable(PARAM_ALPHA, &dAlpha);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_X0);
  pParameterList->registerAllowed(PARAM_X1);
  pParameterList->registerAllowed(PARAM_X2);
  pParameterList->registerAllowed(PARAM_Y0);
  pParameterList->registerAllowed(PARAM_Y1);
  pParameterList->registerAllowed(PARAM_Y2);
  pParameterList->registerAllowed(PARAM_ALPHA);
}

//**********************************************************************
// void CDoubleExponentialSelectivity::validate()
// Validate the selectivity
//**********************************************************************
void CDoubleExponentialSelectivity::validate() {
  try {
    // Populate our parameters
    dX0    = pParameterList->getDouble(PARAM_X0);
    dX1    = pParameterList->getDouble(PARAM_X1);
    dX2    = pParameterList->getDouble(PARAM_X2);
    dY0    = pParameterList->getDouble(PARAM_Y0);
    dY1    = pParameterList->getDouble(PARAM_Y1);
    dY2    = pParameterList->getDouble(PARAM_Y2);
    dAlpha = pParameterList->getDouble(PARAM_ALPHA, true, 1.0);

    // Validate parent
    CSelectivity::validate();

    // Local validation
    if (dAlpha <= 0)
      CError::errorLessThanEqualTo(PARAM_ALPHA, PARAM_ZERO);
    if (!CComparer::isBetween(dX0, dX1, dX2))
      CError::errorNotBetween(PARAM_X0, PARAM_X1, PARAM_X2);
    if (dY0 < 0)
      CError::errorLessThan(PARAM_Y0, PARAM_ZERO);
    if (dY1 < 0)
      CError::errorLessThan(PARAM_Y1, PARAM_ZERO);
    if (dY2 < 0)
      CError::errorLessThan(PARAM_Y2, PARAM_ZERO);
  } catch (string& Ex) {
    Ex = "CDoubleExponentialSelectivity.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CDoubleExponentialSelectivity::getResult(int Index)
// Get the result from our selectivity
//**********************************************************************
double CDoubleExponentialSelectivity::calculateResult(int Age) {
#ifndef OPTIMIZE
  try {
#endif

    double dRet = 0.0;

    if (Age <= dX0)
      dRet = dAlpha * dY0 * pow((dY1 / dY0), ((double)Age - dX0) / (dX1 - dX0));
    else
      dRet = dAlpha * dY0 * pow((dY2 / dY0), ((double)Age - dX0) / (dX2 - dX0));

    return dRet;

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CDoubleExponentialSelectivity.calculateResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
  return 0.0;
#endif
}

//**********************************************************************
// CDoubleExponentialSelectivity::~CDoubleExponentialSelectivity()
// Destructor
//**********************************************************************
CDoubleExponentialSelectivity::~CDoubleExponentialSelectivity() {}
