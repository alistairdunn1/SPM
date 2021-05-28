//============================================================================
// Name        : CDerivedQuantityLayer.cpp
// Author      : S.Rasmussen
// Date        : 28/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2013-04-23 15:41:09 +1200 (Tue, 23 Apr 2013) $
//============================================================================

// Local Headers
#include "CDerivedQuantityLayer.h"

#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Selectivities/CSelectivityManager.h"
#include "../../TimeSteps/CTimeStepManager.h"
#include "../../World/CWorld.h"

//**********************************************************************
// CDerivedQuantityLayer::CDerivedQuantityLayer()
// Default Constructor
//**********************************************************************
CDerivedQuantityLayer::CDerivedQuantityLayer() {
  // Variables
  sType     = PARAM_DERIVED_QUANTITY;
  pWorld    = CWorld::Instance();
  bIsStatic = false;

  // Register User allowed parameters
  pParameterList->registerAllowed(PARAM_DERIVED_QUANTITY);
  pParameterList->registerAllowed(PARAM_YEAR_OFFSET);
}

//**********************************************************************
// void CDerivedQuantityLayer::validate()
// Validate
//**********************************************************************
void CDerivedQuantityLayer::validate() {
  try {
    // Base Validate
    CNumericLayer::validate();

    // Populate our Parameters
    sDerivedQuantity = pParameterList->getString(PARAM_DERIVED_QUANTITY);
    iOffset          = pParameterList->getInt(PARAM_YEAR_OFFSET);

    // Check iOffset is a non-negative int
    if (iOffset < 0)
      CError::errorLessThan(PARAM_YEAR_OFFSET, PARAM_ZERO);
  } catch (string& Ex) {
    Ex = "CDerivedQuantityLayer.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CDerivedQuantityLayer::build()
// Build
//**********************************************************************
void CDerivedQuantityLayer::build() {
  try {
    // Get our derived layer (SSB)
    pDerivedQuantity = CDerivedQuantityManager::Instance()->getDerivedQuantity(sDerivedQuantity);

    // Figure out the order of timesteps
    pTimeStepManager = CTimeStepManager::Instance();

    if (pTimeStepManager->getCurrentTimeStep() <= pDerivedQuantity->getTimeStep()) {
      iActualOffset = iOffset - 1;
      if (iActualOffset < 0) {
        CError::errorLessThan(PARAM_YEAR_OFFSET, PARAM_ONE);
      }
    } else {
      iActualOffset = iOffset;
    }
  } catch (string& Ex) {
    Ex = "CDerivedQuantityLayer.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CDerivedQuantityLayer::getValue(int RowIndex, int ColIndex, int TargetRow, int TargetCol)
// get Value
//**********************************************************************
double CDerivedQuantityLayer::getValue(int RowIndex, int ColIndex, int TargetRow = 0, int TargetCol = 0) {
#ifndef OPTIMIZE
  try {
#endif

    double dResult = pDerivedQuantity->getValue(iActualOffset);
    ;
    return dResult;

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CDerivedQuantityLayer.getValue(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

  return 0.0;
#endif
}

//**********************************************************************
// CDerivedQuantityLayer::~CDerivedQuantityLayer()
// Default De-Constructor
//**********************************************************************
CDerivedQuantityLayer::~CDerivedQuantityLayer() {}
