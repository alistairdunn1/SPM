//============================================================================
// Name        : CCategoryTransitionRateProcess.cpp
// Author      : S.Rasmussen
// Date        : 15/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CCategoryTransitionRateProcess.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Selectivities/CSelectivityManager.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CComparer.h"
#include "../../Helpers/ForEach.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"

//**********************************************************************
// CCategoryTransitionRateProcess::CCategoryTransitionRateProcess()
// Default constructor
//**********************************************************************
CCategoryTransitionRateProcess::CCategoryTransitionRateProcess()
{

  // Variables
  pLayer = 0;
  sType = PARAM_CATEGORY_TRANSITION_RATE;
  bRequiresMerge = false;

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_FROM);
  pParameterList->registerAllowed(PARAM_TO);
  pParameterList->registerAllowed(PARAM_PROPORTIONS);
  pParameterList->registerAllowed(PARAM_SELECTIVITIES);
  pParameterList->registerAllowed(PARAM_LAYER);
}

//**********************************************************************
// void CCategoryTransitionRateProcess::validate()
// validate the process
//**********************************************************************
void CCategoryTransitionRateProcess::validate()
{
  try
  {

    // Populate our variables
    sLayer = pParameterList->getString(PARAM_LAYER, true, "");

    pParameterList->fillVector(vFromList, PARAM_FROM);
    pParameterList->fillVector(vToList, PARAM_TO);
    pParameterList->fillVector(vProportions, PARAM_PROPORTIONS);
    pParameterList->fillVector(vSelectivityList, PARAM_SELECTIVITIES);

    // Base Validation
    CProcess::validate();

    // Local validation
    // Validate Sizes
    if (vFromList.size() != vToList.size())
      CError::errorListSameSize(PARAM_FROM, PARAM_TO);
    if (vFromList.size() != vProportions.size())
      CError::errorListSameSize(PARAM_FROM, PARAM_PROPORTIONS);
    if (vFromList.size() != vSelectivityList.size())
      CError::errorListSameSize(PARAM_FROM, PARAM_SELECTIVITIES);

    // Local Validation
    for (int i = 0; i < (int)vProportions.size(); ++i)
    {
      if (vProportions[i] > 1.0)
        CError::errorGreaterThan(PARAM_PROPORTIONS, PARAM_ONE);
      if (vProportions[i] < 0.0)
        CError::errorLessThan(PARAM_PROPORTIONS, PARAM_ZERO);

      // Register estimables
      registerEstimable(PARAM_PROPORTIONS, i, &vProportions[i]);
    }
  }
  catch (string &Ex)
  {
    Ex = "CCategoryTransitionRateProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CCategoryTransitionRateProcess::build()
// Build the process
//**********************************************************************
void CCategoryTransitionRateProcess::build()
{
  try
  {
    // Base Build
    CProcess::build();

    // Get our Category Indexes.
    foreach (string Category, vFromList)
    {
      vFromIndex.push_back(pWorld->getCategoryIndexForName(Category));
    }
    foreach (string Category, vToList)
    {
      vToIndex.push_back(pWorld->getCategoryIndexForName(Category));
    }

    // Get Selectivities
    CSelectivityManager *pSelectivityManager = CSelectivityManager::Instance();
    foreach (string Label, vSelectivityList)
    {
      vSelectivityIndex.push_back(pSelectivityManager->getSelectivity(Label));
    }

    if (sLayer != "")
      pLayer = CLayerManager::Instance()->getNumericLayer(sLayer);
  }
  catch (string &Ex)
  {
    Ex = "CCategoryTransitionRateProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CCategoryTransitionRateProcess::execute()
// Execute the process
//**********************************************************************
void CCategoryTransitionRateProcess::execute()
{
#ifndef OPTIMIZE
  try
  {
#endif
    // Base execute
    CProcess::execute();

    // Loop Through The World Grid (i,j)
    for (int i = 0; i < iWorldHeight; ++i)
    {
      for (int j = 0; j < iWorldWidth; ++j)
      {
        // Get Current Square, and Difference Equal
        pBaseSquare = pWorld->getBaseSquare(i, j);
        if (!pBaseSquare->getEnabled())
          continue;

        for (int l = 0; l < iBaseColCount; ++l)
        {
          // Loop through vectors and make adjustment
          for (int k = 0; k < (int)vFromIndex.size(); ++k)
          {
            dCurrent = pBaseSquare->getValue(vFromIndex[k], l);
            if (CComparer::isZero(dCurrent))
              continue;

            // Multiplayer layer
            if (pLayer != 0)
            {
              double temp = pLayer->getValue(i, j);
              dCurrent *= temp;
              if (temp < 0.0)
              {
                CError::errorLessThan(PARAM_LAYER, PARAM_ZERO);
              }
              else if (temp > 1.0)
              {
                CError::errorGreaterThan(PARAM_LAYER, PARAM_ONE);
              }
            }

            dCurrent = dCurrent * vProportions[k] * vSelectivityIndex[k]->getResult(l);
            pBaseSquare->subValue(vFromIndex[k], l, dCurrent);
            pBaseSquare->addValue(vToIndex[k], l, dCurrent);
          }
        }
      }
    }
#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CCategoryTransitionRateProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CCategoryTransitionRateProcess::~CCategoryTransitionRateProcess()
// Destructor
//**********************************************************************
CCategoryTransitionRateProcess::~CCategoryTransitionRateProcess()
{
  vProportions.clear();
}
