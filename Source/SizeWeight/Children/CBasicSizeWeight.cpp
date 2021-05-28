//============================================================================
// Name        : CBasicSizeWeight.cpp
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CBasicSizeWeight.h"

#include "../../Helpers/CError.h"

//**********************************************************************
// CBasicSizeWeight::CBasicSizeWeight()
// Default Constructor
//**********************************************************************
CBasicSizeWeight::CBasicSizeWeight() {
  sType = PARAM_BASIC;

  // Register estimables
  registerEstimable(PARAM_A, &dA);
  registerEstimable(PARAM_B, &dB);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_A);
  pParameterList->registerAllowed(PARAM_B);
}

//**********************************************************************
// voidCBasicSizeWeight::validate()
// Validate the size-weight relationship
//**********************************************************************
void CBasicSizeWeight::validate() {
  try {
    // Get our variables
    dA = pParameterList->getDouble(PARAM_A);
    dB = pParameterList->getDouble(PARAM_B);

    // Validate parent
    CSizeWeight::validate();

    // Local validations
    if (dA <= 0)
      CError::errorLessThanEqualTo(PARAM_A, PARAM_ZERO);
    if (dB < 0)
      CError::errorLessThan(PARAM_B, PARAM_ZERO);
  } catch (string& Ex) {
    Ex = "CBasicSizeWeight.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// voidCBasicSizeWeight::build()
// Validate the size-weight relationship
//**********************************************************************
void CBasicSizeWeight::build() {
  try {
    // Base
    CSizeWeight::build();

    // Rebuild
    rebuild();
  } catch (string& Ex) {
    Ex = "CBasicSizeWeight.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// voidCBasicSizeWeight::rebuild()
// Validate the size-weight relationship
//**********************************************************************
void CBasicSizeWeight::rebuild() {
  try {
    // Base
    CSizeWeight::rebuild();
  } catch (string& Ex) {
    Ex = "CBasicSizeWeight.rebuild(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CBasicSizeWeight::getMeanWeight(double &size)
// Apply size-weight relationship
//**********************************************************************
double CBasicSizeWeight::getMeanWeight(double& size, string& distribution, double& cv) {
  // weight = a * mean size ^ b * bias correction, where
  // bias correction = (1 + cv of sizes-at-age^2) ^ (b*(b-1)/2)

  double dWeight = dA * pow(size, dB);
  if (distribution == PARAM_NORMAL || distribution == PARAM_LOGNORMAL) {
    dWeight = dWeight * pow(1 + cv * cv, dB * (dB - 1) / 2);
  }
  return (dWeight);
}

//**********************************************************************
// CBasicSizeWeight::~CBasicSizeWeight()
// Destructor
//**********************************************************************
CBasicSizeWeight::~CBasicSizeWeight() {}
