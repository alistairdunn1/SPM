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
    // Base
    CSizeWeight::validate();

    // Get our variables
    dA      = pParameterList->getDouble(PARAM_A);
    dB      = pParameterList->getDouble(PARAM_B);

    // Validate
    if (dA <= 0)
      CError::errorLessThanEqualTo(PARAM_A, PARAM_ZERO);
    if (dB <= 0)
      CError::errorLessThanEqualTo(PARAM_B, PARAM_ZERO);

  } catch (string Ex) {
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

  } catch (string Ex) {
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


  } catch (string Ex) {
    Ex = "CBasicSizeWeight.rebuild(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CBasicSizeWeight::getMeanWeight(double &size)
// Apply size-weight relationship
//**********************************************************************
double CBasicSizeWeight::getMeanWeight(double &size) {
  try {

    double weight = dA*pow(size,dB)*1000;

    return(weight);

  } catch (string Ex) {
    Ex = "CBasicSizeWeight.getMeanWeight(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CBasicSizeWeight::~CBasicSizeWeight()
// Destructor
//**********************************************************************
CBasicSizeWeight::~CBasicSizeWeight() {
}