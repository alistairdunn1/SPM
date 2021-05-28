//============================================================================
// Name        : CAgeMortalityRateProcess.cpp
// Author      :
// Date        :
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
//============================================================================

// Local Headers
#include "CAgeMortalityRateProcess.h"

#include "../../Helpers/CComparer.h"
#include "../../Helpers/CError.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Selectivities/CSelectivity.h"

//**********************************************************************
// CAgeMortalityRateProcess::CAgeMortalityRateProcess()
// Default Constructor
//**********************************************************************
CAgeMortalityRateProcess::CAgeMortalityRateProcess() {
  // Variables
  pGrid          = 0;
  pLayer         = 0;
  sType          = PARAM_AGE_MORTALITY_RATE;
  bRequiresMerge = false;

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_M);
  pParameterList->registerAllowed(PARAM_LAYER);
}

//**********************************************************************
// void CAgeMortalityRateProcess::validate()
// Validate our process
//**********************************************************************
void CAgeMortalityRateProcess::validate() {
  try {
    // Get our parameters
    sLayer = pParameterList->getString(PARAM_LAYER, true, "");

    pParameterList->fillVector(vCategoryList, PARAM_CATEGORIES);
    pParameterList->fillVector(vMortalityRates, PARAM_M);

    // Base Validation
    CProcess::validate();

    // Register Estimables
    for (int i = 0; i < (int)vMortalityRates.size(); ++i) registerEstimable(PARAM_M, i, &vMortalityRates[i]);

    // Local Validation
    if ((int)vMortalityRates.size() != pWorld->getAgeSpread())
      CError::errorListSameSize(PARAM_M, PARAM_AGES);
  } catch (string& Ex) {
    Ex = "CAgeMortalityRateProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAgeMortalityRateProcess::build()
// Build our process
//**********************************************************************
void CAgeMortalityRateProcess::build() {
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
    Ex = "CAgeMortalityRateProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CConstantMortalityProcess::rebuild()
// Rebuild
//**********************************************************************
void CAgeMortalityRateProcess::rebuild() {
#ifndef OPTIMIZE
  try {
#endif
    // Populate Grid With Values
    for (int i = 0; i < iWorldHeight; ++i) {
      for (int j = 0; j < iWorldWidth; ++j) {
        for (int k = 0; k < (int)vCategoryIndex.size(); ++k) {
          for (int l = 0; l < iBaseColCount; ++l) {
            // Calculate Our Value
            double dValue = vMortalityRates[l];

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
    Ex = "CAgeMortalityRateProcess.rebuild(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CAgeMortalityRateProcess::execute()
// Execute our process
//**********************************************************************
void CAgeMortalityRateProcess::execute() {
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

            if (pLayer != 0)
              dCurrent *= pLayer->getValue(i, j);

            // Do Add/Subs
            pBaseSquare->subValue(vCategoryIndex[k], l, dCurrent);
          }
        }
      }
    }

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CAgeMortalityRateProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CAgeMortalityRateProcess::~CAgeMortalityRateProcess()
// Destructor
//**********************************************************************
CAgeMortalityRateProcess::~CAgeMortalityRateProcess() {
  // Clean Our Grid
  if (pGrid != 0) {
    for (int i = 0; i < iWorldHeight; ++i) {
      delete[] pGrid[i];
      pGrid[i] = 0;
    }
    delete[] pGrid;
  }
}
