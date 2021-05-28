//============================================================================
// Name        : CAbundanceLayer.cpp
// Author      : S.Rasmussen
// Date        : 28/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local Headers
#include "CAbundanceLayer.h"

#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Selectivities/CSelectivityManager.h"
#include "../../World/CWorld.h"

//**********************************************************************
// CAbundanceLayer::CAbundanceLayer()
// Default Constructor
//**********************************************************************
CAbundanceLayer::CAbundanceLayer() {
  // Variables
  sType     = PARAM_ABUNDANCE;
  pWorld    = CWorld::Instance();
  bIsStatic = false;

  // Register User allowed parameters
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_SELECTIVITIES);
}

//**********************************************************************
// void CAbundanceLayer::addCategory(string value)
// Add A Category to our Abundance Layer
//**********************************************************************
void CAbundanceLayer::addCategory(string value) {
  vCategoryNames.push_back(value);
}

//**********************************************************************
// void CAbundanceLayer::addSelectivity(string value)
// Add a selectivity to our list.
//**********************************************************************
void CAbundanceLayer::addSelectivity(string value) {
  vSelectivityNames.push_back(value);
}

//**********************************************************************
// void CAbundanceLayer::validate()
// Validate
//**********************************************************************
void CAbundanceLayer::validate() {
  try {
    // Base Validate
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
    Ex = "CAbundanceLayer.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAbundanceLayer::build()
// Build
//**********************************************************************
void CAbundanceLayer::build() {
  try {
    // Build Selectivities
    CSelectivityManager* pSelectivityManager = CSelectivityManager::Instance();
    pSelectivityManager->fillVector(vSelectivities, vSelectivityNames);

    // Build Categories
    pWorld->fillCategoryVector(vCategories, vCategoryNames);
  } catch (string& Ex) {
    Ex = "CAbundanceLayer.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CAbundanceLayer::getValue(int RowIndex, int ColIndex, int TargetRow, int TargetCol)
// get Value
//**********************************************************************
double CAbundanceLayer::getValue(int RowIndex, int ColIndex, int TargetRow = 0, int TargetCol = 0) {
#ifndef OPTIMIZE
  try {
#endif

    double dResult = 0;

    for (int i = 0; i < pWorld->getAgeSpread(); ++i) {
      for (int j = 0; j < (int)vCategories.size(); ++j) {
        dResult += vSelectivities[j]->getResult(i) * pWorld->getBaseSquare(RowIndex, ColIndex)->getAbundanceInCategoryForAge(i, vCategories[j]);
      }
    }

    return dResult;

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CAbundanceLayer.getValue(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

  return 0.0;
#endif
}

//**********************************************************************
// CAbundanceLayer::~CAbundanceLayer()
// Default De-Constructor
//**********************************************************************
CAbundanceLayer::~CAbundanceLayer() {}
