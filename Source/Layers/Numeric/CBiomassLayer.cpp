//============================================================================
// Name        : CBiomassLayer.cpp
// Author      : S.Rasmussen
// Date        : 28/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2012-02-22 14:44:59 +1300 (Wed, 22 Feb 2012) $
//============================================================================

// Local Headers
#include "CBiomassLayer.h"
#include "../../Selectivities/CSelectivityManager.h"
#include "../../World/CWorld.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"

//**********************************************************************
// CBiomassLayer::CBiomassLayer()
// Default Constructor
//**********************************************************************
CBiomassLayer::CBiomassLayer()
{
  // Variables
  sType = PARAM_BIOMASS;
  pWorld = CWorld::Instance();
  bIsStatic = false;

  // Register User allowed parameters
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_SELECTIVITIES);
}

//**********************************************************************
// void CBiomassLayer::addCategory(string value)
// Add A Category to our Biomass Layer
//**********************************************************************
void CBiomassLayer::addCategory(string value)
{
  vCategoryNames.push_back(value);
}

//**********************************************************************
// void CBiomassLayer::addSelectivity(string value)
// Add a selectivity to our list.
//**********************************************************************
void CBiomassLayer::addSelectivity(string value)
{
  vSelectivityNames.push_back(value);
}

//**********************************************************************
// void CBiomassLayer::validate()
// Validate
//**********************************************************************
void CBiomassLayer::validate()
{
  try
  {
    // Base Validate
    CNumericLayer::validate();

    // Populate our Parameters
    pParameterList->fillVector(vCategoryNames, PARAM_CATEGORIES);
    pParameterList->fillVector(vSelectivityNames, PARAM_SELECTIVITIES);

    // Check For Duplicate Categories.
    map<string, int> mList;
    foreach (string Category, vCategoryNames)
    {
      mList[Category] += 1;
      if (mList[Category] > 1)
        CError::errorDuplicate(PARAM_CATEGORY, Category);
    }

    if (vCategoryNames.size() != vSelectivityNames.size())
      CError::errorListSameSize(PARAM_CATEGORIES, PARAM_SELECTIVITIES);
  }
  catch (string &Ex)
  {
    Ex = "CBiomassLayer.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CBiomassLayer::build()
// Build
//**********************************************************************
void CBiomassLayer::build()
{
  try
  {
    // Build Selectivities
    CSelectivityManager *pSelectivityManager = CSelectivityManager::Instance();
    pSelectivityManager->fillVector(vSelectivities, vSelectivityNames);

    // Build Categories
    pWorld->fillCategoryVector(vCategories, vCategoryNames);
  }
  catch (string &Ex)
  {
    Ex = "CBiomassLayer.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double CBiomassLayer::getValue(int RowIndex, int ColIndex, int TargetRow, int TargetCol)
// get Value
//**********************************************************************
double CBiomassLayer::getValue(int RowIndex, int ColIndex, int TargetRow = 0, int TargetCol = 0)
{
#ifndef OPTIMIZE
  try
  {
#endif

    double dResult = 0;

    for (int i = 0; i < pWorld->getAgeSpread(); ++i)
    {
      for (int j = 0; j < (int)vCategories.size(); ++j)
      {
        double dAbundance = vSelectivities[j]->getResult(i) * pWorld->getBaseSquare(RowIndex, ColIndex)->getAbundanceInCategoryForAge(i, vCategories[j]);
        dResult += dAbundance * pWorld->getMeanWeight(i, vCategories[j]);
      }
    }

    return dResult;

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CBiomassLayer.getValue(" + getLabel() + ")->" + Ex;
    throw Ex;
  }

  return 0.0;
#endif
}

//**********************************************************************
// CBiomassLayer::~CBiomassLayer()
// Default De-Constructor
//**********************************************************************
CBiomassLayer::~CBiomassLayer()
{
}
