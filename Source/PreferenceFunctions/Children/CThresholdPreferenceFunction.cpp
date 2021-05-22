//============================================================================
// Name        : CThresholdPreferenceFunction.cpp
// Author      : S.Rasmussen
// Date        : 16/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CThresholdPreferenceFunction.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/CError.h"
#include "../../Layers/CLayerManager.h"

//**********************************************************************
// CThresholdPreferenceFunction::CThresholdPreferenceFunction()
// Default Constructor
//**********************************************************************
CThresholdPreferenceFunction::CThresholdPreferenceFunction()
{

  sType = PARAM_THRESHOLD;

  // Register estimables
  registerEstimable(PARAM_N, &dN);
  registerEstimable(PARAM_LAMBDA, &dLambda);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_N);
  pParameterList->registerAllowed(PARAM_LAMBDA);
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_SELECTIVITIES);
  pParameterList->registerAllowed(PARAM_LAYER);
}

//**********************************************************************
// void CThresholdPreferenceFunction::validate()
// Validate
//**********************************************************************
void CThresholdPreferenceFunction::validate()
{
  try
  {

    // Assign local variables
    dN = pParameterList->getDouble(PARAM_N);
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
    Ex = "CThresholdPreferenceFunction.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CThresholdPreferenceFunction::build()
// Build our Object
//**********************************************************************
void CThresholdPreferenceFunction::build()
{
  try
  {

    // Build parent
    CPreferenceFunction::build();

    // Get our Layer
    CLayerManager *pLayerManager = CLayerManager::Instance();
    pLayer = pLayerManager->getNumericLayer(sLayerName);
  }
  catch (string &Ex)
  {
    Ex = "CThreshholdPreferenceFunction.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CThresholdPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
// Get Result
//**********************************************************************
double CThresholdPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
{

  dRet = 0.0;

#ifndef OPTIMIZE
  try
  {
#endif

    dLayerValue = pLayer->getValue(TRIndex, TCIndex, RIndex, CIndex);
    if (dLayerValue > dN)
      dRet = 1.0 / (pow(dLayerValue / dN, dLambda));
    else
      dRet = 1.0;

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CThresholdPreferenceFunction.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return CMath::zeroFun(pow(dRet, dAlpha), ZERO);
}
//**********************************************************************
// CThresholdPreferenceFunction::~CThresholdPreferenceFunction()
// Default De-Constructor
//**********************************************************************
CThresholdPreferenceFunction::~CThresholdPreferenceFunction()
{
}
