//============================================================================
// Name        : CPreferenceFunction.cpp
// Author      : S.Rasmussen
// Date        : 16/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CPreferenceFunction.h"

#include "../Helpers/CError.h"
#include "../Layers/CLayerManager.h"
#include "../Layers/Numeric/Base/CNumericLayer.h"

//**********************************************************************
// CPreferenceFunction::CPreferenceFunction()
// Default Constructor
//**********************************************************************
CPreferenceFunction::CPreferenceFunction() {
  // Initialise
  sType  = "";
  pLayer = 0;

  // Register our Estimables
  registerEstimable(PARAM_ALPHA, &dAlpha);

  // Register User Allowed Parameters
  pParameterList->registerAllowed(PARAM_ALPHA);
}

//**********************************************************************
// void CPreferenceFunction::validate()
// Validate
//**********************************************************************
void CPreferenceFunction::validate() {
  try {
    // Base Validation
    CBaseBuild::validate();

    // Populate our Parameters.
    dAlpha = pParameterList->getDouble(PARAM_ALPHA, true, 1.0);
  } catch (string& Ex) {
    Ex = "CPreferenceFunction.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPreferenceFunction::build()
// Build our Object
//**********************************************************************
void CPreferenceFunction::build() {
  try {
  } catch (string& Ex) {
    Ex = "CPreferenceFunction.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CPreferenceFunction::getIsStatic()
// getIsStatic
//**********************************************************************
bool CPreferenceFunction::getIsStatic() {
  if (pLayer == 0)
    return false;

  return pLayer->getIsStatic();
}

//**********************************************************************
// CPreferenceFunction::~CPreferenceFunction()
// Destructor
//**********************************************************************
CPreferenceFunction::~CPreferenceFunction() {}
