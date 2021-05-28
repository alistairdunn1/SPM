//============================================================================
// Name        : CAllValuesSelectivity.cpp
// Author      : S.Rasmussen
// Date        : 16/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CAllValuesSelectivity.h"

#include "../../Helpers/CError.h"

//**********************************************************************
// CAllValuesSelectivity::CAllValuesSelectivity()
// Default constructor
//**********************************************************************
CAllValuesSelectivity::CAllValuesSelectivity() {
  // Register allowed parameters
  pParameterList->registerAllowed(PARAM_V);
}

//**********************************************************************
// void CAllValuesSelectivity::validate()
// Validate the selectivity
//**********************************************************************
void CAllValuesSelectivity::validate() {
  try {
    // Fill our vector
    pParameterList->fillVector(vVs, PARAM_V);

    // Validate parent
    CSelectivity::validate();

    // Local validation
    // Make sure we have same amount of V's as Age Spread
    if ((int)vVs.size() != pWorld->getAgeSpread())
      CError::errorListSameSize(PARAM_V, PARAM_AGES);

    // Register the Vs as estimable
    for (int i = 0; i < (int)vVs.size(); ++i) registerEstimable(PARAM_V, i, &vVs[i]);
  } catch (string& Ex) {
    Ex = "CAllValuesSelectivity.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CAllValuesSelectivity::getResult(int Age)
// Get the result from our selectivity
//**********************************************************************
double CAllValuesSelectivity::calculateResult(int Age) {
  double dRet = 0.0;
  dRet        = vVs[Age - pWorld->getMinAge()];
  return dRet;
}

//**********************************************************************
// CAllValuesSelectivity::~CAllValuesSelectivity()
// Destructor
//**********************************************************************
CAllValuesSelectivity::~CAllValuesSelectivity() {}
