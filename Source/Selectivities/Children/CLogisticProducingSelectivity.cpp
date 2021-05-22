//============================================================================
// Name        : CLogisticproducingSelectivity.cpp
// Author      : A. Dunn
// Date        : 7/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CLogisticProducingSelectivity.h"
#include "../../Helpers/CError.h"

//**********************************************************************
// CLogisticproducingSelectivity::CLogisticProducingSelectivity()
// Default Constructor
//**********************************************************************
CLogisticProducingSelectivity::CLogisticProducingSelectivity()
{
  // Register estimables
  registerEstimable(PARAM_A50, &dA50);
  registerEstimable(PARAM_ATO95, &dAto95);
  registerEstimable(PARAM_ALPHA, &dAlpha);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_L);
  pParameterList->registerAllowed(PARAM_H);
  pParameterList->registerAllowed(PARAM_A50);
  pParameterList->registerAllowed(PARAM_ATO95);
  pParameterList->registerAllowed(PARAM_ALPHA);
}

//**********************************************************************
// void CLogisticProducingSelectivity::validate()
// validate
//**********************************************************************
void CLogisticProducingSelectivity::validate()
{
  try
  {

    // Populate our variables
    iL = pParameterList->getInt(PARAM_L);
    iH = pParameterList->getInt(PARAM_H);
    dA50 = pParameterList->getDouble(PARAM_A50);
    dAto95 = pParameterList->getDouble(PARAM_ATO95);
    dAlpha = pParameterList->getDouble(PARAM_ALPHA, true, 1.0);

    // Validate parent
    CSelectivity::validate();

    // Local validation
    if (dAlpha <= 0)
      CError::errorLessThanEqualTo(PARAM_ALPHA, PARAM_ZERO);
    if (dAto95 <= 0)
      CError::errorLessThanEqualTo(PARAM_ATO95, PARAM_ZERO);
  }
  catch (string &Ex)
  {
    Ex = "CLogisticProducingSelectivity.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CLogisticProducingSelectivity::calculateResult(int Age)
// Calculate Our Result
//**********************************************************************
double CLogisticProducingSelectivity::calculateResult(int Age)
{
#ifndef OPTIMIZE
  try
  {
    // Do our logistic producing Function
#endif

    double dRet = 0.0;

    if (Age < iL)
      dRet = 0.0;
    else if (Age >= iH)
      dRet = dAlpha;
    else if (Age == iL)
    {
      dRet = 1.0 / (1.0 + pow(19.0, (dA50 - Age) / dAto95)) * dAlpha;
    }
    else
    {
      double lambda2 = 1.0 / (1.0 + pow(19.0, (dA50 - (Age - 1)) / dAto95));
      if (lambda2 > 0.9999)
      {
        dRet = dAlpha;
      }
      else
      {
        double lambda1 = 1.0 / (1.0 + pow(19.0, (dA50 - Age) / dAto95));
        dRet = (lambda1 - lambda2) / (1 - lambda2) * dAlpha;
      }
    }
    return dRet;

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CLogisticProducingSelectivity.calculateResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
  return 0.0;
#endif
}

//**********************************************************************
// CLogisticProducingSelectivity::~CLogisticProducingSelectivity()
// Default De-Constructor
//**********************************************************************
CLogisticProducingSelectivity::~CLogisticProducingSelectivity()
{
}
