//============================================================================
// Name        : CCategoryTransitionProcess.cpp
// Author      : S.Rasmussen
// Date        : 14/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Headers
#include "CCategoryTransitionProcess.h"

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
// CCategoryTransitionProcess::CCategoryTransitionProcess()
// Default Constructor
//**********************************************************************
CCategoryTransitionProcess::CCategoryTransitionProcess() {
  // Variables
  pTimeStepManager = CTimeStepManager::Instance();
  sType            = PARAM_CATEGORY_TRANSITION;
  pPenalty         = 0;

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_FROM);           // categories
  pParameterList->registerAllowed(PARAM_SELECTIVITIES);  // selectivities for FROM to calculate vulnerable
  pParameterList->registerAllowed(PARAM_TO);             // categories
  pParameterList->registerAllowed(PARAM_YEARS);          // years for layers
  pParameterList->registerAllowed(PARAM_LAYERS);         // n to move
  pParameterList->registerAllowed(PARAM_U_MAX);
  pParameterList->registerAllowed(PARAM_PENALTY);
}

//**********************************************************************
// int CCategoryTransitionProcess::getYears(int index)
// Return the years entry from vector @ index
//**********************************************************************
int CCategoryTransitionProcess::getYears(int index) {
  return vYearsList[index];
}

//**********************************************************************
// string CCategoryTransitionProcess::getLayers(int index)
// Return the layers entry in vector at index
//**********************************************************************
string CCategoryTransitionProcess::getLayers(int index) {
  return vLayersList[index];
}

//**********************************************************************
// string CCategoryTransitionProcess::getCategoryTo(int index)
// Get category from vector at index
//**********************************************************************
string CCategoryTransitionProcess::getCategoryTo(int index) {
  return vCategoryToList[index];
}

//**********************************************************************
// void CCategoryTransitionProcess::validate()
// Validate This Object
//**********************************************************************
void CCategoryTransitionProcess::validate() {
  try {
    // Get our Parameters
    sPenalty = pParameterList->getString(PARAM_PENALTY, true, "");
    dUMax    = pParameterList->getDouble(PARAM_U_MAX, true, 0.99);
    pParameterList->fillVector(vCategoryList, PARAM_FROM);
    pParameterList->fillVector(vSelectivityList, PARAM_SELECTIVITIES);
    pParameterList->fillVector(vCategoryToList, PARAM_TO);
    pParameterList->fillVector(vYearsList, PARAM_YEARS);
    pParameterList->fillVector(vLayersList, PARAM_LAYERS);

    // Base Validation
    CProcess::validate();

    // Local validation
    // Check for Duplicate Year
    map<int, int> mYears;
    foreach (int Year, vYearsList) {
      mYears[Year]++;
      if (mYears[Year] > 1)
        CError::errorDuplicate(PARAM_YEAR, boost::lexical_cast<string>(Year));
    }

    if (getCategoryCount() != getSelectivityCount())
      CError::errorListSameSize(PARAM_FROM, PARAM_SELECTIVITIES);
    if (getCategoryCount() != getCategoryToCount())
      CError::errorListSameSize(PARAM_FROM, PARAM_TO);
    if (getYearsCount() != getLayersCount())
      CError::errorListSameSize(PARAM_YEARS, PARAM_LAYERS);

    if (dUMax > ONE)
      CError::errorGreaterThan(PARAM_U_MAX, PARAM_ONE);
    if (dUMax <= TRUE_ZERO)
      CError::errorLessThanEqualTo(PARAM_U_MAX, PARAM_ZERO);

  } catch (string& Ex) {
    Ex = "CCategoryTransitionProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CCategoryTransitionProcess::build()
// Build our Relationships and Indexes
//**********************************************************************
void CCategoryTransitionProcess::build() {
  try {
    // Base Build
    CProcess::build();

    // Build our Layer Index
    CLayerManager* pLayerManager = CLayerManager::Instance();
    pLayerManager->fillVector(vLayersIndex, vLayersList);

    // Build the category to list
    foreach (string Name, vCategoryToList) { vCategoryToIndex.push_back(pWorld->getCategoryIndexForName(Name)); }

    // Build Penalty
    if (sPenalty != "")
      pPenalty = CPenaltyManager::Instance()->getPenalty(sPenalty);

  } catch (string& Ex) {
    Ex = "CCategoryTransitionProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CCategoryTransitionProcess::execute()
// Execute This Process
//**********************************************************************
void CCategoryTransitionProcess::execute() {
#ifndef OPTIMIZE
  try {
#endif
    // See if we are suppose to be executing first
    bYearMatch   = false;
    iCurrentYear = pTimeStepManager->getCurrentYear();
    for (int i = 0; i < (int)vYearsList.size(); ++i) {
      if (vYearsList[i] == iCurrentYear) {
        bYearMatch = true;
        pLayer     = vLayersIndex[i];
        break;
      }
    }

    // No Match. Don't Execute
    if (!bYearMatch)
      return;

    // Base execute
    CProcess::execute();

    // Loop Through The World Grid (i,j)
    for (int i = 0; i < iWorldHeight; ++i) {
      for (int j = 0; j < iWorldWidth; ++j) {
        // Get Current Square
        pBaseSquare = pWorld->getBaseSquare(i, j);
        if (!pBaseSquare->getEnabled())
          continue;

        pDiff = pWorld->getDifferenceSquare(i, j);

        // Get Layer Value
        dN = pLayer->getValue(i, j);

        // Clear our Vulnerable Amount
        dVulnerable = 0.0;

        // Loop Through Categories & Work out Vulnerable Stock
        for (int k = 0; k < (int)vCategoryIndex.size(); ++k) {
          for (int l = 0; l < iBaseColCount; ++l) {
            dCurrent = pBaseSquare->getValue(vCategoryIndex[k], l) * vSelectivityIndex[k]->getResult(l);
            // Increase Vulnerable Amount
            dVulnerable += dCurrent;
          }
        }

        // Work out exploitation rate to move
        dExploitation = dN / CMath::zeroFun(dVulnerable, ZERO);
        if (dExploitation > dUMax) {
          dExploitation = dUMax;
          if (pPenalty != 0) {  // Throw Penalty
            pPenalty->trigger(sLabel, dN, (dVulnerable * dUMax));
          }
        } else if (dExploitation < 0.0) {
          dExploitation = 0.0;
        }

        // Loop Through Categories & remove individuals
        for (int k = 0; k < (int)vCategoryIndex.size(); ++k) {
          for (int l = 0; l < iBaseColCount; ++l) {
            // Get Amount to move
            dCurrent = pBaseSquare->getValue(vCategoryIndex[k], l) * vSelectivityIndex[k]->getResult(l) * dExploitation;

            // If is Zero, Cont
            if (dCurrent <= 0.0)
              continue;

            // Add these to the categories to move to
            pDiff->addValue(vCategoryToIndex[k], l, dCurrent);
            // Subtract these from the categories to move from
            pDiff->subValue(vCategoryIndex[k], l, dCurrent);
          }
        }
      }
    }

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CCategoryTransitionProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CCategoryTransitionProcess::~CCategoryTransitionProcess()
// Default De-Constructor
//**********************************************************************
CCategoryTransitionProcess::~CCategoryTransitionProcess() {}
