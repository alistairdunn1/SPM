//============================================================================
// Name        : CBiomassDensityLayer.cpp
// Author      : S.Rasmussen
// Date        : 16/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CBiomassDensityLayer.h"

#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/ForEach.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Selectivities/CSelectivityManager.h"
#include "../../World/CWorld.h"

//**********************************************************************
// CBiomassDensityLayer::CBiomassDensityLayer()
// Default Constructor
//**********************************************************************
CBiomassDensityLayer::CBiomassDensityLayer() {
  // Variables
  sType     = PARAM_BIOMASS_DENSITY;
  pWorld    = CWorld::Instance();
  bIsStatic = false;

  // Register User allowed parameters
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_SELECTIVITIES);
}

//**********************************************************************
// void CBiomassDensityLayer::addCategory(string value)
// Add A Category to our Biomass Layer
//**********************************************************************
void CBiomassDensityLayer::addCategory(string value) {
  vCategoryNames.push_back(value);
}

//**********************************************************************
// void CBiomassDensityLayer::addSelectivity(string value)
// Add a selectivity to our list.
//**********************************************************************
void CBiomassDensityLayer::addSelectivity(string value) {
  vSelectivityNames.push_back(value);
}

//**********************************************************************
// void CBiomassDensityLayer::validate()
// Validate the layer
//**********************************************************************
void CBiomassDensityLayer::validate() {
  try {
    // Base validate
    CNumericLayer::validate();

    // Populate our Parameters
    pParameterList->fillVector(vCategoryNames, PARAM_CATEGORIES);
    pParameterList->fillVector(vSelectivityNames, PARAM_SELECTIVITIES);

    // Check For Duplicate Categories.
    map<string, int> mList;
    foreach (string Category, vCategoryNames) {
      mList[Category] += 1;
      if (mList[Category] > 1)
        CError::errorDuplicate(PARAM_CATEGORY, Category);
    }

    if (vCategoryNames.size() != vSelectivityNames.size())
      CError::errorListSameSize(PARAM_CATEGORIES, PARAM_SELECTIVITIES);
  } catch (string& Ex) {
    Ex = "CBiomassDensityLayer.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CBiomassDensityLayer::build()
// Build the layer
//**********************************************************************
void CBiomassDensityLayer::build() {
  try {
    // Build Selectivities
    CSelectivityManager* pSelectivityManager = CSelectivityManager::Instance();
    pSelectivityManager->fillVector(vSelectivities, vSelectivityNames);

    // Build Categories
    pWorld->fillCategoryVector(vCategories, vCategoryNames);

    // Get our base Layer Pointer
    sBaseLayer                   = pWorld->getBaseLayer();
    CLayerManager* pLayerManager = CLayerManager::Instance();
    pLayer                       = pLayerManager->getNumericLayer(sBaseLayer);
  } catch (string& Ex) {
    Ex = "CBiomassDensityLayer.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CBiomassDensityLayer::getValue(int RowIndex, int ColIndex, int TargetRow, int TargetCol)
// get Value
//**********************************************************************
double CBiomassDensityLayer::getValue(int RowIndex, int ColIndex, int TargetRow = 0, int TargetCol = 0) {
#ifndef OPTIMIZE
  try {
#endif

    double dResult = 0;

    for (int i = 0; i < pWorld->getAgeSpread(); ++i) {
      for (int j = 0; j < (int)vCategories.size(); ++j) {
        double dAbundance = vSelectivities[j]->getResult(i) * pWorld->getBaseSquare(RowIndex, ColIndex)->getAbundanceInCategoryForAge(i, vCategories[j]);
        dResult += dAbundance * pWorld->getMeanWeight(i, vCategories[j]);
      }
    }

    return dResult / CMath::zeroFun(pLayer->getValue(RowIndex, ColIndex), ZERO);

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CBiomassDensityLayer.getValue(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

  return 0.0;
#endif
}

//**********************************************************************
// CBiomassDensityLayer::~CBiomassDensityLayer()
// Destructor
//**********************************************************************
CBiomassDensityLayer::~CBiomassDensityLayer() {}
