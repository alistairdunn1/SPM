//============================================================================
// Name        : CDerivedQuantityFactory.cpp
// Author      : S.Rasmussen
// Date        : 23/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local includes
#include "CDerivedQuantityFactory.h"
#include "../CDerivedQuantityManager.h"
#include "../../Helpers/CError.h"
#include "../Children/CAbundanceDerivedQuantity.h"
#include "../Children/CBiomassDerivedQuantity.h"

//**********************************************************************
// CDerivedQuantity* CDerivedQuantityFactory::buildDerivedQuantity(string type, bool registerWithManager)
// Build a Derived Quantity
//**********************************************************************
CDerivedQuantity *CDerivedQuantityFactory::buildDerivedQuantity(string type, bool registerWithManager)
{

  CDerivedQuantity *pQuantity = 0;

  if (type == PARAM_ABUNDANCE)
    pQuantity = new CAbundanceDerivedQuantity();
  else if (type == PARAM_BIOMASS)
    pQuantity = new CBiomassDerivedQuantity();
  else
    CError::errorUnknown(PARAM_DERIVED_QUANTITY, type);

  if (registerWithManager)
    CDerivedQuantityManager::Instance()->addDerivedQuantity(pQuantity);

  return pQuantity;
}
