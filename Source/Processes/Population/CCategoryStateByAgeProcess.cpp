//============================================================================
// Name        : CCategoryStateByAgeProcess.cpp
// Author      : A. Dunn
// Date        : 18/04/2014
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
//============================================================================

// Headers
#include "CCategoryStateByAgeProcess.h"

#include <boost/lexical_cast.hpp>

#include "../../Helpers/CComparer.h"
#include "../../Helpers/CConvertor.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/ForEach.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Penalties/CPenalty.h"
#include "../../Penalties/CPenaltyManager.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Selectivities/CSelectivityManager.h"
#include "../../TimeSteps/CTimeStepManager.h"

//**********************************************************************
// CCategoryStateByAgeProcess::CCategoryStateByAgeProcess()
// Default Constructor
//**********************************************************************
CCategoryStateByAgeProcess::CCategoryStateByAgeProcess() {
  // Variables
  pWorldView       = 0;
  iMinAge          = -1;
  iMaxAge          = -1;
  pTimeStepManager = CTimeStepManager::Instance();
  sType            = PARAM_CATEGORY_STATE_BY_AGE;
  bRequiresMerge   = false;

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_CATEGORY);  // category
  pParameterList->registerAllowed(PARAM_LAYER);     // layer
  pParameterList->registerAllowed(PARAM_MIN_AGE);   // min age
  pParameterList->registerAllowed(PARAM_MAX_AGE);   // max age
  pParameterList->registerAllowed(PARAM_DATA);      // N to state (vector, by age)
}

//**********************************************************************
// void CCategoryStateByAgeProcess::validate()
// Validate This Object
//**********************************************************************
void CCategoryStateByAgeProcess::validate() {
  try {
    // Get our Parameters
    sCategory = pParameterList->getString(PARAM_CATEGORY);
    sLayer    = pParameterList->getString(PARAM_LAYER);
    iMinAge   = pParameterList->getInt(PARAM_MIN_AGE);
    iMaxAge   = pParameterList->getInt(PARAM_MAX_AGE);

    // Base Validation
    CProcess::validate();

    // Local validation
    if (iMinAge < pWorld->getMinAge())
      CError::errorLessThan(PARAM_MIN_AGE, PARAM_MIN_AGE);
    if (iMaxAge > pWorld->getMaxAge())
      CError::errorGreaterThan(PARAM_MAX_AGE, PARAM_MAX_AGE);

    // Find out the Spread in Ages
    iAgeSpread = (iMaxAge + 1) - iMinAge;

    // Get our Ns
    vector<string> vNs;
    pParameterList->fillVector(vNs, PARAM_DATA);

    if ((vNs.size() % (iAgeSpread + 1)) != 0)
      CError::errorListNotSize(PARAM_DATA, iAgeSpread);

    for (int i = 0; i < (int)vNs.size(); i += (iAgeSpread + 1)) {
      for (int j = 0; j < iAgeSpread; ++j) {
        try {
          double dNumber = boost::lexical_cast<double>(vNs[i + j + 1]);
          if (dNumber < 0)
            CError::errorLessThanEqualTo(PARAM_DATA, PARAM_ZERO);
          mvNMatrix[vNs[i]].push_back(dNumber);
        } catch (boost::bad_lexical_cast&) {
          string Ex = string("Non-numeric value in ") + PARAM_DATA + string(" for ") + PARAM_PROCESS + string(" ") + getLabel();
          throw Ex;
        }
      }
    }

    int iCounter = 0;
    for (int i = 0; i < (int)vNs.size(); i += (iAgeSpread + 1)) {
      for (int j = 0; j < iAgeSpread; ++j) {
        registerEstimable(PARAM_DATA, iCounter, &mvNMatrix[vNs[i]][j]);
        iCounter++;
      }
    }
  } catch (string& Ex) {
    Ex = "CCategoryStateByAgeProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CCategoryStateByAgeProcess::build()
// Build our Relationships and Indexes
//**********************************************************************
void CCategoryStateByAgeProcess::build() {
  try {
    // Base Build
    CProcess::build();

    // Get our Layer Pointer
    CLayerManager* pLayerManager = CLayerManager::Instance();
    pLayer                       = pLayerManager->getCategoricalLayer(sLayer);

    // Build our World View
    pWorldView = new CLayerDerivedWorldView(pLayer);
    pWorldView->validate();
    pWorldView->build();

    // Build the category
    iCategoryIndex = pWorld->getCategoryIndexForName(sCategory);
  } catch (string& Ex) {
    Ex = "CCategoryStateByAgeProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CCategoryStateByAgeProcess::execute()
// Execute This Process
//**********************************************************************
void CCategoryStateByAgeProcess::execute() {
#ifndef OPTIMIZE
  try {
#endif

    int iSquareAgeOffset = iMinAge - pWorld->getMinAge();

    // Base execute
    CProcess::execute();
    // Execute pWorldView
    pWorldView->execute();

    // Loop Through each area
    map<string, vector<double>>::iterator mvNPtr = mvNMatrix.begin();
    while (mvNPtr != mvNMatrix.end()) {
      // Get the list of WorldSquares
      vector<CWorldSquare*> vWorldSquares = pWorldView->getWorldSquares((*mvNPtr).first);
      // Loop through each age
      for (int j = 0; j < iAgeSpread; ++j) {
        // count the number of worldSquares
        int count = 0;
        for (int k = 0; k < (int)vWorldSquares.size(); ++k) {
          if ((vWorldSquares[k])->getEnabled())
            count++;
        }
        // Loop through the WorldSquares
        for (int k = 0; k < (int)vWorldSquares.size(); ++k) {
          // Get Current Square
          if (!((vWorldSquares[k])->getEnabled()))
            continue;
          // Add these to the category
          (vWorldSquares[k])->addValue(iCategoryIndex, (iSquareAgeOffset + j), ((*mvNPtr).second)[j] / ((double)count));
        }
      }
      mvNPtr++;
    }

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CCategoryStateByAgeProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CCategoryStateByAgeProcess::~CCategoryStateByAgeProcess()
// Default De-Constructor
//**********************************************************************
CCategoryStateByAgeProcess::~CCategoryStateByAgeProcess() {
  if (pWorldView != 0)
    delete pWorldView;
}
