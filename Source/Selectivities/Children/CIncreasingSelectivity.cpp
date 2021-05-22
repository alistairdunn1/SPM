//============================================================================
// Name        : CIncreasingSelectivity.cpp
// Author      : S.Rasmussen
// Date        : 20/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CIncreasingSelectivity.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CComparer.h"
//**********************************************************************
// CIncreasingSelectivity::CIncreasingSelectivity()
// Default constructor
//**********************************************************************
CIncreasingSelectivity::CIncreasingSelectivity()
{
  // Register user allowed variables
  pParameterList->registerAllowed(PARAM_L);
  pParameterList->registerAllowed(PARAM_H);
  pParameterList->registerAllowed(PARAM_V);
  pParameterList->registerAllowed(PARAM_ALPHA);
}

//**********************************************************************
// void CIncreasingSelectivity::validate()
// Validate the selectivity
//**********************************************************************
void CIncreasingSelectivity::validate()
{
  try
  {

    // Get our values
    iL = pParameterList->getInt(PARAM_L);
    iH = pParameterList->getInt(PARAM_H);
    dAlpha = pParameterList->getDouble(PARAM_ALPHA, true, 1.0);

    pParameterList->fillVector(vVs, PARAM_V);

    // Validate parent
    CSelectivity::validate();

    // Local validation
    if (dAlpha <= 0)
      CError::errorLessThanEqualTo(PARAM_ALPHA, PARAM_ZERO);
    if (iL < pWorld->getMinAge())
      CError::errorLessThan(PARAM_L, PARAM_MIN_AGE);
    if (iL > pWorld->getMaxAge())
      CError::errorGreaterThan(PARAM_L, PARAM_MAX_AGE);
    if (iH <= iL)
      CError::errorLessThanEqualTo(PARAM_H, PARAM_L);
    if ((int)vVs.size() != (iH - iL + 1))
      CError::errorListNotSize(PARAM_V, (iH - iL + 1));
    for (int i = 0; i < (int)vVs.size(); ++i)
    {
      if ((vVs[i] > 1.0) || (vVs[i] < 0.0))
        CError::errorNotBetween(PARAM_V, PARAM_ZERO, PARAM_ONE);
    }

    // Register Estimables
    registerEstimable(PARAM_ALPHA, &dAlpha);
    for (int i = 0; i < (int)vVs.size(); ++i)
      registerEstimable(PARAM_V, i, &vVs[i]);
  }
  catch (string &Ex)
  {
    Ex = "CIncreasingSelectivity.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CIncreasingSelectivity::getResult(int Index)
// Get the result from the selectivity
//**********************************************************************
double CIncreasingSelectivity::calculateResult(int Age)
{
#ifndef OPTIMIZE
  try
  {
#endif

    double dRet = 0.0;

    if (Age <= iL)
    {
      dRet = 0.0;
    }
    else if (Age > iH)
    {
      dRet = vVs[iH - iL];
    }
    else
    {
      dRet = vVs[0];
      for (int i = (iL + 1); i < Age; i++)
      {
        if (i > iH || dRet >= dAlpha)
          break;
        dRet += (dAlpha - dRet) * vVs[i - iL];
      }
    }
    return dRet;

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CIncreasingSelectivity.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
  return 0;
#endif
}

//**********************************************************************
// CIncreasingSelectivity::~CIncreasingSelectivity()
// Destructor
//**********************************************************************
CIncreasingSelectivity::~CIncreasingSelectivity()
{
}
