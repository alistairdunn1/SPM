//============================================================================
// Name        : CExponentialPreferenceFunction.cpp
// Author      : S.Rasmussen
// Date        : 16/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

#include <iostream>

// Local Headers
#include "CExponentialPreferenceFunction.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/CError.h"
#include "../../Layers/CLayerManager.h"

// Using
using std::cout;
using std::endl;

//**********************************************************************
// CExponentialPreferenceFunction::CExponentialPreferenceFunction()
// Default Constructor
//**********************************************************************
CExponentialPreferenceFunction::CExponentialPreferenceFunction()
{

  sType = PARAM_EXPONENTIAL;
  dLambda = -1.0;

  // Register Estimable
  registerEstimable(PARAM_LAMBDA, &dLambda);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_LAMBDA);
  pParameterList->registerAllowed(PARAM_LAYER);
}

//**********************************************************************
// void CExponentialPreferenceFunction::validate()
// Validate
//**********************************************************************
void CExponentialPreferenceFunction::validate()
{
  try
  {

    // Assign Variables
    dLambda = pParameterList->getDouble(PARAM_LAMBDA);
    sLayerName = pParameterList->getString(PARAM_LAYER);

    // Validate parent
    CPreferenceFunction::validate();

    //Local validation
    if (dLambda <= 0.0)
      CError::errorLessThanEqualTo(PARAM_LAMBDA, PARAM_ZERO);
  }
  catch (string &Ex)
  {
    Ex = "CExponentialPreferenceFunction.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CExponentialPreferenceFunction::build()
// Build our Object
//**********************************************************************
void CExponentialPreferenceFunction::build()
{
  try
  {
    // Get our Layer
    CLayerManager *pLayerManager = CLayerManager::Instance();
    pLayer = pLayerManager->getNumericLayer(sLayerName);
  }
  catch (string &Ex)
  {
    Ex = "CExponentialPreferenceFunction.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CExponentialPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
// get Result
//**********************************************************************
double CExponentialPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
{
#ifndef OPTIMIZE
  try
  {
#endif

    return CMath::zeroFun(pow(exp(-dLambda * pLayer->getValue(TRIndex, TCIndex, RIndex, CIndex)), dAlpha), ZERO);

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CExponentialPreferenceFunction.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

  return 0.0;
#endif
}
//**********************************************************************
// CExponentialPreferenceFunction::~CExponentialPreferenceFunction()
// Default De-Constructor
//**********************************************************************
CExponentialPreferenceFunction::~CExponentialPreferenceFunction()
{
}
