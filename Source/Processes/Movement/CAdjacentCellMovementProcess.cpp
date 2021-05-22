//============================================================================
// Name        : CAdjacentCellMovementProcess.cpp
// Author      : S.Rasmussen
// Date        : 4/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CAdjacentCellMovementProcess.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Layers/CLayerManager.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Selectivities/CSelectivityManager.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CComparer.h"

//**********************************************************************
// CAdjacentCellMovementProcess::CAdjacentCellMovementProcess()
// Default Constructor
//**********************************************************************
CAdjacentCellMovementProcess::CAdjacentCellMovementProcess()
{

  // Default Values
  pLayer = 0;
  sType = PARAM_ADJACENT_CELL_MOVEMENT;

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_SELECTIVITIES);
  pParameterList->registerAllowed(PARAM_LAYER);
  pParameterList->registerAllowed(PARAM_PROPORTION);
}

//**********************************************************************
// void CAdjacentCellMovementProcess::validate()
// validate
//**********************************************************************
void CAdjacentCellMovementProcess::validate()
{
  try
  {

    // Get our Variables
    sLayer = pParameterList->getString(PARAM_LAYER, true, "");
    dProportion = pParameterList->getDouble(PARAM_PROPORTION, true, 1.0);

    pParameterList->fillVector(vCategoryList, PARAM_CATEGORIES);
    pParameterList->fillVector(vSelectivityList, PARAM_SELECTIVITIES);

    // Base Validation
    CMovementProcess::validate();

    // Local Validation
    if (getCategoryCount() == 0)
      CError::errorMissing(PARAM_CATEGORIES);
    if (getSelectivityCount() == 0)
      CError::errorMissing(PARAM_SELECTIVITIES);
    if (getCategoryCount() != getSelectivityCount())
      CError::errorListSameSize(PARAM_CATEGORIES, PARAM_SELECTIVITIES);

    if (getProportion() < 0.0)
      CError::errorLessThan(PARAM_PROPORTION, PARAM_ZERO);
    if (getProportion() > 1.0)
      CError::errorGreaterThan(PARAM_PROPORTION, PARAM_ONE);

    registerEstimable(PARAM_PROPORTION, &dProportion);
  }
  catch (string &Ex)
  {
    Ex = "CAdjacentCellMovementProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAdjacentCellMovementProcess::build()
// build
//**********************************************************************
void CAdjacentCellMovementProcess::build()
{
  try
  {
    // Base Building
    CMovementProcess::build();

    // Get selectivities and categories.
    CSelectivityManager::Instance()->fillVector(vSelectivityIndex, vSelectivityList);
    pWorld->fillCategoryVector(vCategoryIndex, vCategoryList);

    // Get our Layer
    if (sLayer != "")
      pLayer = CLayerManager::Instance()->getNumericLayer(sLayer);
  }
  catch (string &Ex)
  {
    Ex = "CAdjacentCellMovementProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAdjacentCellMovementProcess::execute()
// execute
//**********************************************************************
void CAdjacentCellMovementProcess::execute()
{
#ifndef OPTIMIZE
  try
  {
#endif

    // Base Execution
    CMovementProcess::execute();

    for (int i = 0; i < iWorldHeight; ++i)
    {
      for (int j = 0; j < iWorldWidth; ++j)
      {
        // Get Current Squares
        pBaseSquare = pWorld->getBaseSquare(i, j);
        pDiff = pWorld->getDifferenceSquare(i, j);

        if (!pBaseSquare->getEnabled())
          continue;

        // Loop Through Categories and Ages
        for (int k = 0; k < getCategoryCount(); ++k)
        {
          for (int l = 0; l < iBaseColCount; ++l)
          {
            dCurrent = pBaseSquare->getValue(vCategoryIndex[k], l);

            if (CComparer::isZero(dCurrent))
              continue;
            // get up/down/left/right layer values and convert to proportions

            if (sLayer != "")
            {
              if ((i + 1) < pWorld->getHeight())
                dLayerValueDown = pLayer->getValue(i + 1, j);
              else
                dLayerValueDown = 0.0;
              if ((i - 1) >= 0)
                dLayerValueUp = pLayer->getValue(i - 1, j);
              else
                dLayerValueUp = 0.0;
              if ((j + 1) < pWorld->getWidth())
                dLayerValueRight = pLayer->getValue(i, j + 1);
              else
                dLayerValueRight = 0.0;
              if ((j - 1) >= 0)
                dLayerValueLeft = pLayer->getValue(i, j - 1);
              else
                dLayerValueLeft = 0.0;

              dLayerTotal = dLayerValueUp + dLayerValueDown + dLayerValueLeft + dLayerValueRight;

              if (dLayerTotal > 0.0)
              {
                dValue = dCurrent * dProportion * vSelectivityIndex[k]->getResult(l);
                dLayerValueUp = dValue * dLayerValueUp / dLayerTotal;
                dLayerValueDown = dValue * dLayerValueDown / dLayerTotal;
                dLayerValueLeft = dValue * dLayerValueLeft / dLayerTotal;
                dLayerValueRight = dValue * dLayerValueRight / dLayerTotal;
              }
              else
              {
                dLayerValueUp = 0.0;
                dLayerValueDown = 0.0;
                dLayerValueLeft = 0.0;
                dLayerValueRight = 0.0;
              }
              // or if no layer defined, then just move 1/4 each way
            }
            else
            {
              dValue = dCurrent * dProportion * vSelectivityIndex[k]->getResult(l);
              dLayerValueUp = 0.25 * dValue;
              dLayerValueDown = 0.25 * dValue;
              dLayerValueLeft = 0.25 * dValue;
              dLayerValueRight = 0.25 * dValue;
            }
            // Move
            moveUp(i, j, vCategoryIndex[k], l, dLayerValueUp);
            moveDown(i, j, vCategoryIndex[k], l, dLayerValueDown);
            moveLeft(i, j, vCategoryIndex[k], l, dLayerValueLeft);
            moveRight(i, j, vCategoryIndex[k], l, dLayerValueRight);
          }
        }
      }
    }

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CAdjacentCellMovementProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CAdjacentCellMovementProcess::~CAdjacentCellMovementProcess()
// Default De-Constructor
//**********************************************************************
CAdjacentCellMovementProcess::~CAdjacentCellMovementProcess()
{
}
