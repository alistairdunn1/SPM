//============================================================================
// Name        : CUniformPDF.cpp
// Author      : C. Marsh
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
//============================================================================

// Local Headers
#include "CUniformPDF.h"

#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"

//**********************************************************************
// CUniformPDF::CUniformPDF()
// Default Constructor
//**********************************************************************
CUniformPDF::CUniformPDF() {
  sType = PARAM_UNIFORM;

  // Register Estimables
  registerEstimable(PARAM_A, &dA);
  registerEstimable(PARAM_B, &dB);

  // Register user allowed variables
  pParameterList->registerAllowed(PARAM_A);
  pParameterList->registerAllowed(PARAM_B);
}

//**********************************************************************
// void CUniformPDF::validate()
// Validate
//**********************************************************************
void CUniformPDF::validate() {
  try {
    // Assign our variables
    dA = pParameterList->getDouble(PARAM_A);
    dB = pParameterList->getDouble(PARAM_B);

    // Validate parent
    CPDF::validate();

    // Local validation
    if (dB <= dA)
      CError::errorLessThanEqualTo(PARAM_B, PARAM_A);
  } catch (string& Ex) {
    Ex = "CUniformPDF.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CUniformPDF::getPDFResult(double Value)
// get Result
//**********************************************************************
double CUniformPDF::getPDFResult(double value) {
  dRet = 0.0;

#ifndef OPTIMIZE
  try {
#endif

    if (value >= dA && value <= dB) {
      dRet = 1.0 / (dB - dA);
    }

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CUniformPDF.getPDFResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return dRet;
}

//**********************************************************************
// double CUniformPDF::getCDFResult(double Value)
// get Result
//**********************************************************************
double CUniformPDF::getCDFResult(double value) {
  dRet = 0.0;

#ifndef OPTIMIZE
  try {
#endif

    if (value < dA) {
      dRet = 0.0;
    } else if (value >= dA && value <= dB) {
      dRet = (value - dA) / (dB - dA);
    } else {
      dRet = 1.0;
    }

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CUniformPDF.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return dRet;
}
//**********************************************************************
// CUniformPDF::~CUniformPDF()
// Default De-Constructor
//**********************************************************************
CUniformPDF::~CUniformPDF() {}
