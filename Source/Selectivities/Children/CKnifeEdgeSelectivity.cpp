//============================================================================
// Name        : CKnifeEdgeSelectivity.cpp
// Author      : A. Dunn
// Date        : 12/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CKnifeEdgeSelectivity.h"
#include "../../Helpers/CError.h"

//**********************************************************************
// CKnifeEdgeSelectivity::CKnifeEdgeSelectivity()
// Default Constructor
//**********************************************************************
CKnifeEdgeSelectivity::CKnifeEdgeSelectivity()
{
  // Register estimable
  registerEstimable(PARAM_E, &dE);
  registerEstimable(PARAM_ALPHA, &dAlpha);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_E);
  pParameterList->registerAllowed(PARAM_ALPHA);
}

//**********************************************************************
// void CKnifeEdgeSelectivity::validate()
// validate
//**********************************************************************
void CKnifeEdgeSelectivity::validate()
{
  try
  {

    // Populate our variable
    dE = pParameterList->getDouble(PARAM_E);
    dAlpha = pParameterList->getDouble(PARAM_ALPHA, true, 1.0);

    // Validate parent
    CSelectivity::validate();

    // Local validation
    if (dAlpha <= 0)
      CError::errorLessThanEqualTo(PARAM_ALPHA, PARAM_ZERO);
  }
  catch (string &Ex)
  {
    Ex = "CKnifeedgeSelectivity.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CKnifeEdgeSelectivity::getResult(int Param)
// get Result
//**********************************************************************
double CKnifeEdgeSelectivity::getResult(int Param)
{
#ifndef OPTIMIZE
  try
  {
    if ((Param + pWorld->getMinAge()) > pWorld->getMaxAge())
      CError::errorTooHigh(PARAM_PARAMETER);
#endif

    // Get the column Index for the passed in Age
    Param = pWorld->getMinAge() + Param;

    if (Param >= dE)
      return (dAlpha);

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CKnifeedgeSelectivity.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
  return 0.0;
}

//**********************************************************************
// CKnifeEdgeSelectivity::~CKnifeEdgeSelectivity()
// Default De-Constructor
//**********************************************************************
CKnifeEdgeSelectivity::~CKnifeEdgeSelectivity()
{
}
