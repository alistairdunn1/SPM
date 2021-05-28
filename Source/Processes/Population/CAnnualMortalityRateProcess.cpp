//============================================================================
// Name        : CAnnualMortalityRateProcess.cpp
// Author      : S.Rasmussen
// Date        : 15/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global headers
#include <boost/lexical_cast.hpp>

// Local headers
#include "../../Helpers/CComparer.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Selectivities/CSelectivityManager.h"
#include "../../TimeSteps/CTimeStepManager.h"
#include "CAnnualMortalityRateProcess.h"

//**********************************************************************
// CAnnualMortalityRateProcess::CAnnualMortalityRateProcess()
// Default constructor
//**********************************************************************
CAnnualMortalityRateProcess::CAnnualMortalityRateProcess() {
  // Variables
  pLayer         = 0;
  sType          = PARAM_ANNUAL_MORTALITY_RATE;
  bRequiresMerge = false;

  // Register user allowed variables
  pParameterList->registerAllowed(PARAM_YEARS);
  pParameterList->registerAllowed(PARAM_M);
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_SELECTIVITIES);
  pParameterList->registerAllowed(PARAM_LAYER);
}

//**********************************************************************
// void CAnnualMortalityRateProcess::validate()
// Validate the process
//**********************************************************************
void CAnnualMortalityRateProcess::validate() {
  try {
    // Get our variables
    sLayer = pParameterList->getString(PARAM_LAYER, true, "");
    pParameterList->fillVector(vYears, PARAM_YEARS);
    pParameterList->fillVector(vMortalityRates, PARAM_M);
    pParameterList->fillVector(vCategoryList, PARAM_CATEGORIES);
    pParameterList->fillVector(vSelectivityList, PARAM_SELECTIVITIES);

    // Validate parent
    CProcess::validate();

    // local validation
    // M must be non-negative
    for (int i = 0; i < (int)vMortalityRates.size(); ++i) {
      if (vMortalityRates[i] < 0.0)
        CError::errorLessThan(PARAM_AGE, PARAM_ZERO);
    }

    for (int i = 0; i < (int)vMortalityRates.size(); ++i) {
      registerEstimable(PARAM_M, i, &vMortalityRates[i]);
    }

    // Check Sizes
    if (vYears.size() != vMortalityRates.size())
      CError::errorListSameSize(PARAM_YEARS, PARAM_M);
    if (vCategoryList.size() != vSelectivityList.size())
      CError::errorListSameSize(PARAM_CATEGORIES, PARAM_SELECTIVITIES);

    // Check unique years
    map<int, int> mYears;
    foreach (int Year, vYears) {
      mYears[Year]++;
      if (mYears[Year] > 1)
        CError::errorDuplicate(PARAM_YEARS, boost::lexical_cast<string>(Year));
    }
  } catch (string& Ex) {
    Ex = "CAnnualMortalityRateProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAnnualMortalityRateProcess::build()
// Build this process
//**********************************************************************
void CAnnualMortalityRateProcess::build() {
  try {
    // Base
    CProcess::build();

    // Get our Layer
    if (sLayer != "")
      pLayer = CLayerManager::Instance()->getNumericLayer(sLayer);

    // Get selectivities and categories.
    CSelectivityManager::Instance()->fillVector(vSelectivityIndex, vSelectivityList);
    pWorld->fillCategoryVector(vCategoryIndex, vCategoryList);

    // Build Refs
    pTimeStepManager = CTimeStepManager::Instance();

    // Rebuild
    rebuild();

  } catch (string& Ex) {
    Ex = "CAnnualMortalityRateProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAnnualMortalityProcess::rebuild()
// Rebuild
//**********************************************************************
void CAnnualMortalityRateProcess::rebuild() {
#ifndef OPTIMIZE
  try {
#endif

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CAnnualMortalityRateProcess.rebuild(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CAnnualMortalityRateProcess::execute()
// Execute this process
//**********************************************************************
void CAnnualMortalityRateProcess::execute() {
#ifndef OPTIMIZE
  try {
#endif
    // Base Execute
    CProcess::execute();

    // Check if we run this year
    double dM = 0.0;
    for (int i = 0; i < (int)vYears.size(); ++i) {
      if (pTimeStepManager->getCurrentYear() == vYears[i]) {
        dM = vMortalityRates[i];
        break;
      }
    }

    if (CComparer::isEqual(dM, 0.0))
      return;  // Don't run this year

    // If a meta-layer, then we need to rebuild the Process to take account of changes in layer values by year
    if (pLayer != 0) {
      if (pLayer->getLayerType() == PARAM_META_NUMERIC) {
        rebuild();
      }
    }

    // Loop through World Grid (i, j)
    for (int i = 0; i < iWorldHeight; ++i) {
      for (int j = 0; j < iWorldWidth; ++j) {
        pBaseSquare = pWorld->getBaseSquare(i, j);
        if (!pBaseSquare->getEnabled())
          continue;

        double dLayerValue = 1.0;
        if (pLayer != 0)
          dLayerValue = pLayer->getValue(i, j);

        for (int k = 0; k < (int)vCategoryIndex.size(); ++k) {
          for (int m = 0; m < iBaseColCount; ++m) {
            double dCurrent = pBaseSquare->getValue(vCategoryIndex[k], m);
            dCurrent *= (1.0 - exp(-dM * dLayerValue)) * vSelectivityIndex[k]->getResult(m);

            pBaseSquare->subValue(vCategoryIndex[k], m, dCurrent);
          }  // for m
        }    // for k
      }      // for j
    }        // for i

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CAnnualMortalityRateProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CAnnualMortalityRateProcess::~CAnnualMortalityRateProcess()
// Destructor
//**********************************************************************
CAnnualMortalityRateProcess::~CAnnualMortalityRateProcess() {}
