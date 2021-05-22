//============================================================================
// Name        : CDerivedQuantityByCellLayer.cpp
// Author      : S.Rasmussen
// Date        : 28/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2013-04-23 15:41:09 +1200 (Tue, 23 Apr 2013) $
//============================================================================

// Local Headers
#include "CDerivedQuantityByCellLayer.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Selectivities/CSelectivityManager.h"
#include "../../TimeSteps/CTimeStepManager.h"
#include "../../World/CWorld.h"

//**********************************************************************
// CDerivedQuantityByCellLayer::CDerivedQuantityByCellLayer()
// Default Constructor
//**********************************************************************
CDerivedQuantityByCellLayer::CDerivedQuantityByCellLayer()
{

  // Variables
  sType = PARAM_DERIVED_QUANTITY_BY_CELL;
  pWorld = CWorld::Instance();
  bIsStatic = false;

  // Register User allowed parameters
  pParameterList->registerAllowed(PARAM_DERIVED_QUANTITY_BY_CELL);
  pParameterList->registerAllowed(PARAM_YEAR_OFFSET);
}

//**********************************************************************
// void CDerivedQuantityByCellLayer::validate()
// Validate
//**********************************************************************
void CDerivedQuantityByCellLayer::validate()
{
  try
  {
    // Base Validate
    CNumericLayer::validate();

    // Populate our Parameters
    sDerivedQuantityByCell = pParameterList->getString(PARAM_DERIVED_QUANTITY_BY_CELL);
    iOffset = pParameterList->getInt(PARAM_YEAR_OFFSET);

    //Check iOffset is a non-negative int
    if (iOffset < 0)
      CError::errorLessThan(PARAM_YEAR_OFFSET, PARAM_ZERO);
  }
  catch (string &Ex)
  {
    Ex = "CDerivedQuantityByCellLayer.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CDerivedQuantityByCellLayer::build()
// Build
//**********************************************************************
void CDerivedQuantityByCellLayer::build()
{
  try
  {

    // Get our derived layer (SSB)
    pDerivedQuantityByCell = CDerivedQuantityByCellManager::Instance()->getDerivedQuantityByCell(sDerivedQuantityByCell);

    // Figure out the order of timesteps
    pTimeStepManager = CTimeStepManager::Instance();

    if (pTimeStepManager->getCurrentTimeStep() <= pDerivedQuantityByCell->getTimeStep())
    {
      iActualOffset = iOffset - 1;
      if (iActualOffset < 0)
      {
        CError::errorLessThan(PARAM_YEAR_OFFSET, PARAM_ONE);
      }
    }
    else
    {
      iActualOffset = iOffset;
    }
  }
  catch (string &Ex)
  {
    Ex = "CDerivedQuantityByCellLayer.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CDerivedQuantityByCellLayer::getValue(int RowIndex, int ColIndex, int TargetRow, int TargetCol)
// get Value
//**********************************************************************
double CDerivedQuantityByCellLayer::getValue(int RowIndex, int ColIndex, int TargetRow = 0, int TargetCol = 0)
{
#ifndef OPTIMIZE
  try
  {
#endif

    double dResult = pDerivedQuantityByCell->getValue(iActualOffset, RowIndex, ColIndex);
    return dResult;

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CDerivedQuantityByCellLayer.getValue(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

  return 0.0;
#endif
}

//**********************************************************************
// CDerivedQuantityByCellLayer::~CDerivedQuantityByCellLayer()
// Default De-Constructor
//**********************************************************************
CDerivedQuantityByCellLayer::~CDerivedQuantityByCellLayer()
{
}
