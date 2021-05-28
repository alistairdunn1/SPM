//============================================================================
// Name        : CAllValuesBoundedSelectivity.cpp
// Author      : S.Rasmussen
// Date        : 20/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global headers
#include <iostream>

// Local headers
#include "../../Helpers/CError.h"
#include "CAllValuesBoundedSelectivity.h"

// Using
using std::cout;
using std::endl;

//**********************************************************************
// CAllValuesBoundedSelectivity::CAllValuesBoundedSelectivity()
// Default Constructor
//**********************************************************************
CAllValuesBoundedSelectivity::CAllValuesBoundedSelectivity() {
  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_L);
  pParameterList->registerAllowed(PARAM_H);
  pParameterList->registerAllowed(PARAM_V);
}

//**********************************************************************
// void CAllValuesBoundedSelectivity::validate()
// Validate the selectivity
//**********************************************************************
void CAllValuesBoundedSelectivity::validate() {
  try {
    // Get our variables
    iL = pParameterList->getInt(PARAM_L);
    iH = pParameterList->getInt(PARAM_H);

    pParameterList->fillVector(vVs, PARAM_V);

    // Validate parent
    CSelectivity::validate();

    // Local validation
    if (iL < pWorld->getMinAge())
      CError::errorLessThan(PARAM_L, PARAM_MIN_AGE);
    if (iL > pWorld->getMaxAge())
      CError::errorGreaterThan(PARAM_L, PARAM_MAX_AGE);
    if (iH <= iL)
      CError::errorLessThanEqualTo(PARAM_H, PARAM_L);
    if ((int)vVs.size() != (iH - iL))
      CError::errorListNotSize(PARAM_V, (iH - iL));

    // Register our vector as estimable
    for (int i = 0; i < (int)vVs.size(); ++i) registerEstimable(PARAM_V, i, &vVs[i]);

    iMinAge = pWorld->getMinAge();
  } catch (string& Ex) {
    Ex = "CAllValuesBoundedSelectivity.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CAllValuesBoundedSelectivity::calculateResult(int Age)
// Calculate a cached result for this selectivity
//**********************************************************************
double CAllValuesBoundedSelectivity::calculateResult(int Age) {
  double dRet = 0.0;

  if (Age < iL)
    dRet = 0.0;
  else if (Age >= iH)
    dRet = vVs[vVs.size() - 1];
  else
    dRet = vVs[(Age - iL)];

  return dRet;
}

//**********************************************************************
// CAllValuesBoundedSelectivity::~CAllValuesBoundedSelectivity()
// Destructor
//**********************************************************************
CAllValuesBoundedSelectivity::~CAllValuesBoundedSelectivity() {}
