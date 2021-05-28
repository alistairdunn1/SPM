//============================================================================
// Name        : CNormalPDF.cpp
// Author      : C. Marsh
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
//============================================================================

// Local Headers
#include "CNormalPDF.h"

#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/DefinedValues.h"

//**********************************************************************
// CNormalPDF::CNormalPDF()
// Default Constructor
//**********************************************************************
CNormalPDF::CNormalPDF() {
  sType = PARAM_NORMAL;

  // Register Estimables
  registerEstimable(PARAM_MU, &dMu);
  registerEstimable(PARAM_SIGMA, &dSigma);

  // Register user allowed variables
  pParameterList->registerAllowed(PARAM_MU);
  pParameterList->registerAllowed(PARAM_SIGMA);
}

//**********************************************************************
// void CNormalPDF::validate()
// Validate
//**********************************************************************
void CNormalPDF::validate() {
  try {
    // Assign our variables
    dMu    = pParameterList->getDouble(PARAM_MU);
    dSigma = pParameterList->getDouble(PARAM_SIGMA);

    // Validate parent
    CPDF::validate();

    // Local validation
    if (dSigma <= 0.0)
      CError::errorLessThanEqualTo(PARAM_SIGMA, PARAM_ZERO);
  } catch (string& Ex) {
    Ex = "CNormalPDF.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CNormalPDF::getPDFResult(double Value)
// get Result
//**********************************************************************
double CNormalPDF::getPDFResult(double value) {
  // not required ?

  dRet = 0.0;

#ifndef OPTIMIZE
  try {
#endif

    dRet = exp((-(value - dMu) * (value - dMu)) / (2.0 * dSigma * dSigma)) / (dSigma * sqrt(TWO_PI));

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CNormalPDF.getPDFResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return dRet;
}

//**********************************************************************
// double CNormalPDF::getCDFResult(double Value)
// get Result
//**********************************************************************
double CNormalPDF::getCDFResult(double value) {
  // not required ?
  dRet = 0;

#ifndef OPTIMIZE
  try {
#endif

    double x = (value - dMu) / dSigma;
    // constants for the error function
    double a1 = 0.254829592;
    double a2 = -0.284496736;
    double a3 = 1.421413741;
    double a4 = -1.453152027;
    double a5 = 1.061405429;
    double p  = 0.3275911;

    double sign = 1.0;
    if (x < 0) {
      sign = -1.0;
    }

    x        = fabs(x) / sqrt(2.0);
    double t = 1.0 / (1.0 + p * x);
    double y = 1.0 - (((((a5 * t + a4) * t) + a3) * t + a2) * t + a1) * t * exp(-x * x);

    dRet = (0.5 * (1.0 + sign * y));

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CNormalCDF.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return dRet;
}
//**********************************************************************
// CNormalPDF::~CNormalPDF()
// Default De-Constructor
//**********************************************************************
CNormalPDF::~CNormalPDF() {}
