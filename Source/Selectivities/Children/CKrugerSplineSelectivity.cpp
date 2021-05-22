//============================================================================
// Name        : CKrugerSplineSelectivity.cpp
// Author      : A. Dunn
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
//============================================================================

// Local Headers
#include "CKrugerSplineSelectivity.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/DefinedValues.h"
#include "../../Helpers/CMath.h"
#include <math.h>

//**********************************************************************
// CLogisticproducingSelectivity::CKrugerSplineSelectivity()
// Default Constructor
//**********************************************************************
CKrugerSplineSelectivity::CKrugerSplineSelectivity()
{

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_KNOTS);
  pParameterList->registerAllowed(PARAM_VALUES);
}

//**********************************************************************
// void CKrugerSplineSelectivity::validate()
// validate
//**********************************************************************
void CKrugerSplineSelectivity::validate()
{
  try
  {

    // Populate our variables
    pParameterList->fillVector(vKnots, PARAM_KNOTS);
    pParameterList->fillVector(vValues, PARAM_VALUES);

    // Validate parent
    CSelectivity::validate();

    // Useful parameters
    iN = vKnots.size();

    // Local validation
    if (vKnots.size() != vValues.size())
      CError::errorListSameSize(PARAM_KNOTS, PARAM_VALUES);
    if (iN < 2)
      CError::errorNotEnough(PARAM_KNOTS);
    if (vKnots[0] != pWorld->getMinAge())
      CError::errorNotEqual(PARAM_KNOTS, PARAM_MIN_AGE);
    if (vKnots[vKnots.size() - 1] != pWorld->getMaxAge())
      CError::errorNotEqual(PARAM_KNOTS, PARAM_MAX_AGE);
    for (int i = 0; i < (int)vValues.size(); ++i)
    {
      if (vValues[i] < 0)
        CError::errorLessThanEqualTo(PARAM_VALUES, PARAM_ZERO);
    }
  }
  catch (string &Ex)
  {
    Ex = "CKrugerSplineSelectivity.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CCachedSelectivity::build()
// Rebuild the selectivity
//**********************************************************************
void CKrugerSplineSelectivity::build()
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
void CKrugerSplineSelectivity::rebuild()
{
  try
  {

    vector<double> vF1;
    vector<double> vF2;
    vector<double> vF3;
    vector<double> vF4;

    //vF1[0] = 2.0 / ((vKnots[2] � vKnots[1]) / (vValues[2] � vValues[1]) + (vKnots[1] � vKnots[0]) / (vValues[1] � vValuies[0]));
    //vF2[0] = 3.0 / 2.0 * (vValues[1] � vValues[0])/(vKnots[1] � vKnots[0]) - vF1[0] / 2.0;
    //vF3[0] = -2.0 * (vF1[0] + 2* f'1(x0))/(x1 � x0) + 6*(y1 � y0)/ (x1 � x0)2

    CCachedSelectivity::rebuild();
  }
  catch (string &Ex)
  {
    Ex = "CCachedSelectivity.rebuild(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CKrugerSplineSelectivity::calculateResult(int Age)
// Calculate Our Result
//**********************************************************************
double CKrugerSplineSelectivity::calculateResult(int Age)
{

  try
  {
  }
  catch (string &Ex)
  {
    Ex = "CKrugerSplineSelectivity.calculateResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
  return 0.0;
}

//**********************************************************************
// CKrugerSplineSelectivity::~CKrugerSplineSelectivity()
// Default De-Constructor
//**********************************************************************
CKrugerSplineSelectivity::~CKrugerSplineSelectivity()
{
}
