//============================================================================
// Name        : CDerivedQuantityByCellFactory.cpp
// Author      : S.Rasmussen
// Date        : 23/10/2012
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
//============================================================================

// Local includes
#include "CDerivedQuantityByCellFactory.h"

#include "../../Helpers/CError.h"
#include "../CDerivedQuantityByCellManager.h"
#include "../Children/CAbundanceDerivedQuantityByCell.h"
#include "../Children/CBiomassDerivedQuantityByCell.h"

//**********************************************************************
// CDerivedQuantityByCell* CDerivedQuantityByCellFactory::buildDerivedQuantityByCell(string type, bool registerWithManager)
// Build a Derived Layer
//**********************************************************************
CDerivedQuantityByCell* CDerivedQuantityByCellFactory::buildDerivedQuantityByCell(string type, bool registerWithManager) {
  CDerivedQuantityByCell* pLayer = 0;

  if (type == PARAM_ABUNDANCE)
    pLayer = new CAbundanceDerivedQuantityByCell();
  else if (type == PARAM_BIOMASS)
    pLayer = new CBiomassDerivedQuantityByCell();
  else
    CError::errorUnknown(PARAM_DERIVED_QUANTITY_BY_CELL, type);

  if (registerWithManager)
    CDerivedQuantityByCellManager::Instance()->addDerivedQuantityByCell(pLayer);

  return pLayer;
}
