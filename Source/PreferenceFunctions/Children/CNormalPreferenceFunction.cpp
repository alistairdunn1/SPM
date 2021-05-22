//============================================================================
// Name        : CNormalPreferenceFunction.cpp
// Author      : S.Rasmussen
// Date        : 16/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CNormalPreferenceFunction.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "../../Layers/CLayerManager.h"

//**********************************************************************
// CNormalPreferenceFunction::CNormalPreferenceFunction()
// Default Constructor
//**********************************************************************
CNormalPreferenceFunction::CNormalPreferenceFunction()
{

  sType = PARAM_NORMAL;

  // Register Estimables
  registerEstimable(PARAM_MU, &dMu);
  registerEstimable(PARAM_SIGMA, &dSigma);

  // Register user allowed variables
  pParameterList->registerAllowed(PARAM_MU);
  pParameterList->registerAllowed(PARAM_SIGMA);
  pParameterList->registerAllowed(PARAM_LAYER);
}

//**********************************************************************
// void CNormalPreferenceFunction::validate()
// Validate
//**********************************************************************
void CNormalPreferenceFunction::validate()
{
  try
  {

    // Assign our variables
    dMu = pParameterList->getDouble(PARAM_MU);
    dSigma = pParameterList->getDouble(PARAM_SIGMA);
    sLayerName = pParameterList->getString(PARAM_LAYER);

    // Validate parent
    CPreferenceFunction::validate();

    //Local validation
    if (dSigma <= 0.0)
      CError::errorLessThanEqualTo(PARAM_SIGMA, PARAM_ZERO);
  }
  catch (string &Ex)
  {
    Ex = "CNormalPreferenceFunction.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CNormalPreferenceFunction::build()
// Build our Object
//**********************************************************************
void CNormalPreferenceFunction::build()
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
    Ex = "CNormalPreferenceFunction.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CNormalPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
// get Result
//**********************************************************************
double CNormalPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
{

  dRet = 0.0;

#ifndef OPTIMIZE
  try
  {
#endif

    dLayerValue = pLayer->getValue(TRIndex, TCIndex, RIndex, CIndex);
    dRet = pow(2.0, -((dLayerValue - dMu) / dSigma * (dLayerValue - dMu) / dSigma));

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CNormalPreferenceFunction.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return CMath::zeroFun(pow(dRet, dAlpha), ZERO);
}
//**********************************************************************
// CNormalPreferenceFunction::~CNormalPreferenceFunction()
// Default De-Constructor
//**********************************************************************
CNormalPreferenceFunction::~CNormalPreferenceFunction()
{
}
