//============================================================================
// Name        : CExponentialPDF.cpp
// Author      : C. Marsh
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
//============================================================================

// Local Headers
#include "CExponentialPDF.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/DefinedValues.h"

//**********************************************************************
// CExponentialPDF::CExponentialPDF()
// Default Constructor
//**********************************************************************
CExponentialPDF::CExponentialPDF()
{

  sType = PARAM_EXPONENTIAL; // This syntax comes into the Copula setting

  // Register Estimables
  registerEstimable(PARAM_LAMBDA, &dLambda);

  // Register user allowed variables
  pParameterList->registerAllowed(PARAM_LAMBDA);
}

//**********************************************************************
// void CExponentialPDF::validate()
// Validate
//**********************************************************************
void CExponentialPDF::validate()
{
  try
  {

    // Assign our variables
    dLambda = pParameterList->getDouble(PARAM_LAMBDA);

    // Validate parent
    CPDF::validate();

    //Local validation
    if (dLambda <= 0.0)
      CError::errorLessThanEqualTo(PARAM_LAMBDA, PARAM_ZERO);
  }
  catch (string &Ex)
  {
    Ex = "CExponentialPDF.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CExponentialPDF::getPDFResult(double Value)
// get Result
//**********************************************************************
double CExponentialPDF::getPDFResult(double value)
{
  // not required ?

  dRet = 0.0;

#ifndef OPTIMIZE
  try
  {
#endif

    dRet = dLambda * exp(-dLambda * value); // PDF definition

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CNormalPDF.getPDFResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return dRet;
}

//**********************************************************************
// double CExponentialPDF::getCDFResult(double Value)
// get Result
//**********************************************************************
double CExponentialPDF::getCDFResult(double value)
{
  // not required ?

  dRet = 0.0;

#ifndef OPTIMIZE
  try
  {
#endif

    dRet = 1 - exp(-dLambda * value); // CDF definition

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CExponentialPDF.getCDFResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return dRet;
}
//**********************************************************************
// CExponentialPDF::~CExponentialPDF()
// Default De-Constructor
//**********************************************************************
CExponentialPDF::~CExponentialPDF()
{
}
