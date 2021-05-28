//============================================================================
// Name        : CConstantMortalityRateProcess.cpp
// Author      : S.Rasmussen
// Date        : 15/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CConstantMortalityRateProcess.h"

#include "../../Helpers/CComparer.h"
#include "../../Helpers/CError.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Selectivities/CSelectivity.h"

//**********************************************************************
// CConstantMortalityRateProcess::CConstantMortalityRateProcess()
// Default Constructor
//**********************************************************************
CConstantMortalityRateProcess::CConstantMortalityRateProcess() {
  // Variables
  pGrid          = 0;
  pLayer         = 0;
  sType          = PARAM_CONSTANT_MORTALITY_RATE;
  bRequiresMerge = false;

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_M);
  pParameterList->registerAllowed(PARAM_SELECTIVITIES);
  pParameterList->registerAllowed(PARAM_LAYER);
}

//**********************************************************************
// void CConstantMortalityRateProcess::validate()
// Validate our process
//**********************************************************************
void CConstantMortalityRateProcess::validate() {
  try {
    // Get our parameters
    sLayer = pParameterList->getString(PARAM_LAYER, true, "");

    pParameterList->fillVector(vCategoryList, PARAM_CATEGORIES);
    pParameterList->fillVector(vSelectivityList, PARAM_SELECTIVITIES);
    pParameterList->fillVector(vMortalityRates, PARAM_M);

    // Base Validation
    CProcess::validate();

    // Register Estimables
    for (int i = 0; i < (int)vMortalityRates.size(); ++i) registerEstimable(PARAM_M, i, &vMortalityRates[i]);

    // Local Validation
    if (getCategoryCount() != getSelectivityCount())
      CError::errorListSameSize(PARAM_CATEGORY, PARAM_SELECTIVITY);
    if (getCategoryCount() != (int)vMortalityRates.size())
      CError::errorListSameSize(PARAM_CATEGORY, PARAM_M);
  } catch (string& Ex) {
    Ex = "CConstantMortalityRateProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CConstantMortalityRateProcess::build()
// Build our process
//**********************************************************************
void CConstantMortalityRateProcess::build() {
  try {
    // Base Build
    CProcess::build();

    // Allocate our Grid
    if (pGrid == 0) {
      // Allocate Space for our X (Height) Y (Width) Grid
      pGrid = new CWorldSquare*[iWorldHeight];
      for (int i = 0; i < iWorldHeight; ++i) {
        pGrid[i] = new CWorldSquare[iWorldWidth];
      }

      // Build our Grid
      for (int i = 0; i < iWorldHeight; ++i)
        for (int j = 0; j < iWorldWidth; ++j) pGrid[i][j].build();
    }

    if (sLayer != "")
      pLayer = CLayerManager::Instance()->getNumericLayer(sLayer);

    // Rebuild
    rebuild();
  } catch (string& Ex) {
    Ex = "CConstantMortalityRateProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CConstantMortalityProcess::rebuild()
// Rebuild
//**********************************************************************
void CConstantMortalityRateProcess::rebuild() {
#ifndef OPTIMIZE
  try {
#endif
    // Populate Grid With Values
    for (int i = 0; i < iWorldHeight; ++i) {
      for (int j = 0; j < iWorldWidth; ++j) {
        for (int k = 0; k < (int)vCategoryIndex.size(); ++k) {
          for (int l = 0; l < iBaseColCount; ++l) {
            // Get Our Selectivity Result
            dSelectivityResult = vSelectivityIndex[k]->getResult(l);
            // Calculate Our Value
            double dValue = vMortalityRates[k] * dSelectivityResult;

            // Multiply it by Layer Value
            if (pLayer != 0)
              dValue *= pLayer->getValue(i, j);

            // Convert To Proportion
            dValue = 1 - exp(-dValue);

            // Assign it to our Grid
            pGrid[i][j].setValue(vCategoryIndex[k], l, dValue);
          }
        }
      }
    }

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CConstantMortalityRateProcess.rebuild(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CConstantMortalityRateProcess::execute()
// Execute our process
//**********************************************************************
void CConstantMortalityRateProcess::execute() {
#ifndef OPTIMIZE
  try {
#endif
    // Base execute
    CProcess::execute();

    // If a meta-layer, then we need to rebuild the Process to take account of changes in layer values by year
    if (pLayer != 0) {
      if (pLayer->getLayerType() == PARAM_META_NUMERIC) {
        rebuild();
      }
    }

    // Loop Through The World Grid (i,j)
    for (int i = 0; i < iWorldHeight; ++i) {
      for (int j = 0; j < iWorldWidth; ++j) {
        // Get Current Square, and Difference Equal
        pBaseSquare = pWorld->getBaseSquare(i, j);
        // Check Square Ok
        if (!pBaseSquare->getEnabled())
          continue;

        // Loop Through Categories and Ages
        for (int k = 0; k < (int)vCategoryIndex.size(); ++k) {
          for (int l = 0; l < iBaseColCount; ++l) {
            // Get Current Value
            dCurrent = pBaseSquare->getValue(vCategoryIndex[k], l);

            // Check 0
            if (CComparer::isZero(dCurrent))
              continue;

            // Get Amount To Subtract
            dCurrent *= pGrid[i][j].getValue(vCategoryIndex[k], l);

            // Do Add/Subs
            pBaseSquare->subValue(vCategoryIndex[k], l, dCurrent);
          }
        }
      }
    }

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CConstantMortalityRateProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CConstantMortalityRateProcess::~CConstantMortalityRateProcess()
// Destructor
//**********************************************************************
CConstantMortalityRateProcess::~CConstantMortalityRateProcess() {
  // Clean Our Grid
  if (pGrid != 0) {
    for (int i = 0; i < iWorldHeight; ++i) {
      delete[] pGrid[i];
      pGrid[i] = 0;
    }
    delete[] pGrid;
  }
}
