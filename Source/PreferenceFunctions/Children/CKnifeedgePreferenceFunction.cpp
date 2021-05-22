//============================================================================
// Name        : CKnifeedgePreferenceFunction.cpp
// Author      :
// Date        :
// Copyright   :
// Description :
//============================================================================

// Global Headers
#include <iostream>

// Local Headers
#include "CKnifeedgePreferenceFunction.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/CComparer.h"
#include "../../Helpers/CError.h"
#include "../../Layers/CLayerManager.h"

// Using
using std::cout;
using std::endl;

//**********************************************************************
// CKnifeedgePreferenceFunction::CKnifeedgePreferenceFunction()
// Default Constructor
//**********************************************************************
CKnifeedgePreferenceFunction::CKnifeedgePreferenceFunction()
{

  sType = PARAM_KNIFE_EDGE;

  // Register our Estimables
  registerEstimable(PARAM_C, &dC);

  // Register User Allowed Parameters
  pParameterList->registerAllowed(PARAM_C);
  pParameterList->registerAllowed(PARAM_LAYER);
}

//**********************************************************************
// void CKnifeedgePreferenceFunction::validate()
// Validate
//**********************************************************************
void CKnifeedgePreferenceFunction::validate()
{
  try
  {

    dC = pParameterList->getDouble(PARAM_C, true, 1.0);
    sLayerName = pParameterList->getString(PARAM_LAYER);

    // Validate parent
    CPreferenceFunction::validate();

    // Local validations
    //Local validation
    if (dC <= 0.0)
      CError::errorLessThanEqualTo(PARAM_C, PARAM_ZERO);
  }
  catch (string &Ex)
  {
    Ex = "CKnifeedgePreferenceFunction.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CKnifeedgePreferenceFunction::build()
// Build our Object
//**********************************************************************
void CKnifeedgePreferenceFunction::build()
{
  try
  {
    // Get our Layer
    CLayerManager *pLayerManager = CLayerManager::Instance();
    pLayer = pLayerManager->getNumericLayer(sLayerName);
  }
  catch (string &Ex)
  {
    Ex = "CKnifeedgePreferenceFunction.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CKnifeedgePreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
// Get Result
//**********************************************************************
double CKnifeedgePreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
{
#ifndef OPTIMIZE
  try
  {
#endif

    dRet = 0.0;

    if (pLayer->getValue(TRIndex, TCIndex, RIndex, CIndex) < dC)
      dRet = 1.0;

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CKnifeedgePreferenceFunction.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return CMath::zeroFun(pow(dRet, dAlpha), ZERO);
}

//**********************************************************************
// CKnifeedgePreferenceFunction::~CKnifeedgePreferenceFunction()
// Default De-Constructor
//**********************************************************************
CKnifeedgePreferenceFunction::~CKnifeedgePreferenceFunction()
{
}
