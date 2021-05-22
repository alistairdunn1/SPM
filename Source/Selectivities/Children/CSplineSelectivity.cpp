//============================================================================
// Name        : CSplineSelectivity.cpp
// Author      : A. Dunn
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
//============================================================================

// Local Headers
#include "CSplineSelectivity.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/DefinedValues.h"
#include "../../Helpers/CMath.h"
#include <math.h>

//**********************************************************************
// CLogisticproducingSelectivity::CSplineSelectivity()
// Default Constructor
//**********************************************************************
CSplineSelectivity::CSplineSelectivity()
{

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_KNOTS);
  pParameterList->registerAllowed(PARAM_VALUES);
  pParameterList->registerAllowed(PARAM_METHOD);
}

//**********************************************************************
// void CSplineSelectivity::validate()
// validate
//**********************************************************************
void CSplineSelectivity::validate()
{
  try
  {

    // Populate our variables
    pParameterList->fillVector(vKnots, PARAM_KNOTS);
    pParameterList->fillVector(vValues, PARAM_VALUES);
    sMethod = pParameterList->getString(PARAM_METHOD, true, PARAM_NATURAL);

    // Validate parent
    CSelectivity::validate();

    // Useful parameters
    iN = vKnots.size();

    // Local validation
    if (vKnots.size() != vValues.size())
      CError::errorListSameSize(PARAM_KNOTS, PARAM_VALUES);
    if (iN < 2)
      CError::errorNotEnough(PARAM_KNOTS);

    for (int i = 0; i < (int)vValues.size(); ++i)
    {
      if (vValues[i] < 0)
        CError::errorLessThanEqualTo(PARAM_VALUES, PARAM_ZERO);
      if (vValues[i] > 1)
        CError::errorGreaterThanEqualTo(PARAM_VALUES, PARAM_ONE);
    }

    if (sMethod == PARAM_NATURAL)
    {
      //A "natural spline" where the second derivatives are set to 0 at the boundaries
      spline.setLowBC(Spline::FIXED_2ND_DERIV_BC, 0);
      spline.setHighBC(Spline::FIXED_2ND_DERIV_BC, 0);
    }
    else if (sMethod == PARAM_FIXED)
    {
      //A spline with a fixed first derivative at the boundaries
      spline.setLowBC(Spline::FIXED_1ST_DERIV_BC, 0);
      spline.setHighBC(Spline::FIXED_1ST_DERIV_BC, 0);
    }
    else if (sMethod == PARAM_PARABOLA)
    {
      //A spline which turns into a parabola at the boundaries
      spline.setLowBC(Spline::PARABOLIC_RUNOUT_BC);
      spline.setHighBC(Spline::PARABOLIC_RUNOUT_BC);
    }
    else
    {
      CError::errorUnknown(PARAM_METHOD, sMethod);
    }

    // Register our values vector as estimable
    for (int i = 0; i < (int)vValues.size(); ++i)
      registerEstimable(PARAM_VALUES, i, &vValues[i]);
  }
  catch (string &Ex)
  {
    Ex = "CSplineSelectivity.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CCachedSelectivity::build()
// Rebuild the selectivity
//**********************************************************************
void CSplineSelectivity::build()
{
  try
  {

    rebuild();
  }
  catch (string &Ex)
  {
    Ex = "CCachedSelectivity.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CCachedSelectivity::rebuild()
// Rebuild the selectivity
//**********************************************************************
void CSplineSelectivity::rebuild()
{
  try
  {

    for (int i = 0; i < iN; ++i)
    {
      spline.addPoint(vKnots[i], transform(vValues[i]));
    }

    CCachedSelectivity::rebuild();
  }
  catch (string &Ex)
  {
    Ex = "CCachedSelectivity.rebuild(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CSplineSelectivity::transform()
// transformation using logit
//**********************************************************************
double CSplineSelectivity::transform(double x)
{
  //double result = log( x / CMath::zeroFun(1.0 - x, ZERO) );
  //double result = tan( 3.141592653589793238463 * ( x - 0.5 ) );
  double result = log(CMath::zeroFun(x, ZERO));
  return (result);
}

//**********************************************************************
// void CSplineSelectivity::inverse()
// inverse transformation using logit
//**********************************************************************
double CSplineSelectivity::inverseTransform(double x)
{
  //double result = 1.0 / ( 1.0 + exp(-x) );
  //double result = 1/3.141592653589793238463 * atan( x ) + 0.5;
  double result = exp(x);
  return (result);
}

//**********************************************************************
// double CSplineSelectivity::calculateResult(int Age)
// Calculate Our Result
//**********************************************************************
double CSplineSelectivity::calculateResult(int Age)
{

  try
  {
    return (inverseTransform(spline((double)Age)));
  }
  catch (string &Ex)
  {
    Ex = "CSplineSelectivity.calculateResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
  return 0.0;
}

//**********************************************************************
// CSplineSelectivity::~CSplineSelectivity()
// Default De-Constructor
//**********************************************************************
CSplineSelectivity::~CSplineSelectivity()
{
}
