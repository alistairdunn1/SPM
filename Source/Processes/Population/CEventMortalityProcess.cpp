//============================================================================
// Name        : CEventMortalityProcess.cpp
// Author      : S.Rasmussen
// Date        : 9/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global Headers
#include <boost/lexical_cast.hpp>
#include <iostream>

// Local headers
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
#include "../../TimeSteps/CTimeStepManager.h"
#include "CEventMortalityProcess.h"

// Using
using std::cout;
using std::endl;

//**********************************************************************
// CEventMortalityProcess::CEventMortalityProcess()
// Default Constructor
//**********************************************************************
CEventMortalityProcess::CEventMortalityProcess() {
  // Variables
  pTimeStepManager = CTimeStepManager::Instance();
  sType            = PARAM_EVENT_MORTALITY;
  bRequiresMerge   = false;
  pPenalty         = 0;

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_YEARS);
  pParameterList->registerAllowed(PARAM_LAYERS);
  pParameterList->registerAllowed(PARAM_U_MAX);
  pParameterList->registerAllowed(PARAM_SELECTIVITIES);
  pParameterList->registerAllowed(PARAM_PENALTY);
}

//**********************************************************************
// int CEventMortalityProcess::getYears(int index)
// Return the years entry from vector @ index
//**********************************************************************
int CEventMortalityProcess::getYears(int index) {
  return vYearsList[index];
}

//**********************************************************************
// string CEventMortalityProcess::getLayers(int index)
// Return the layers entry in vector at index
//**********************************************************************
string CEventMortalityProcess::getLayers(int index) {
  return vLayersList[index];
}

//**********************************************************************
// void CEventMortalityProcess:validate()
// Validate This
//**********************************************************************
void CEventMortalityProcess::validate() {
  try {
    // Get our Parameters
    dUMax    = pParameterList->getDouble(PARAM_U_MAX, true, 0.99);
    sPenalty = pParameterList->getString(PARAM_PENALTY, true, "");

    pParameterList->fillVector(vCategoryList, PARAM_CATEGORIES);
    pParameterList->fillVector(vYearsList, PARAM_YEARS);
    pParameterList->fillVector(vLayersList, PARAM_LAYERS);
    pParameterList->fillVector(vSelectivityList, PARAM_SELECTIVITIES);

    // Base Validation
    CProcess::validate();

    // Local validation
    if (dUMax >= ONE)
      CError::errorGreaterThanEqualTo(PARAM_U_MAX, PARAM_ONE);
    if (dUMax <= TRUE_ZERO)
      CError::errorLessThanEqualTo(PARAM_U_MAX, PARAM_ZERO);

    if (vCategoryList.size() != vSelectivityList.size())
      CError::errorListSameSize(PARAM_CATEGORIES, PARAM_SELECTIVITIES);
    if (vYearsList.size() != vLayersList.size())
      CError::errorListSameSize(PARAM_YEARS, PARAM_LAYERS);

    // Duplicate Year check
    map<int, int> mYears;
    foreach (int Year, vYearsList) {
      mYears[Year]++;
      if (mYears[Year] > 1)
        CError::errorDuplicate(PARAM_YEAR, boost::lexical_cast<string>(Year));
    }
  } catch (string& Ex) {
    Ex = "CEventMortalityProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CEventMortalityProcess::build()
// Build Our Relationships and Indexes
//**********************************************************************
void CEventMortalityProcess::build() {
  try {
    // Base Build
    CProcess::build();

    // Build our Layer Index
    CLayerManager* pLayerManager = CLayerManager::Instance();
    pLayerManager->fillVector(vLayersIndex, vLayersList);

    // Build Penalty
    if (sPenalty != "")
      pPenalty = CPenaltyManager::Instance()->getPenalty(sPenalty);

    vRecordedRemovalsIndex.resize(getYearsCount());
    vActualRemovalsIndex.resize(getYearsCount());

    // rebuild
    rebuild();

  } catch (string& Ex) {
    Ex = "CEventMortalityProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CEventMortalityProcess::rebuild()
// Build Our Relationships and Indexes
//**********************************************************************
void CEventMortalityProcess::rebuild() {
  try {
  } catch (string& Ex) {
    Ex = "CEventMortalityProcess.rebuild(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CEventMortalityProcess::execute()
// execute this Process
//**********************************************************************
void CEventMortalityProcess::execute() {
#ifndef OPTIMIZE
  try {
#endif
    // See if we are suppose to be executing first
    int iIndexYear = 0;
    bYearMatch     = false;

    iCurrentYear = pTimeStepManager->getCurrentYear();
    for (int i = 0; i < (int)vYearsList.size(); ++i) {
      if (vYearsList[i] == iCurrentYear) {
        bYearMatch                = true;
        iIndexYear                = i;
        vRecordedRemovalsIndex[i] = 0.0;
        vActualRemovalsIndex[i]   = 0.0;
        pLayer                    = vLayersIndex[i];
        break;
      }
    }

    // No Match. Don't Execute
    if (!bYearMatch)
      return;

    // pLayer contains no positive values
    if (pLayer->getIsZero())
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

        // Get Layer Value
        dCatch = pLayer->getValue(i, j);

        // Record the catch
        vRecordedRemovalsIndex[iIndexYear] += dCatch;

        // Clear our Vulnerable Amount
        dVulnerable = 0.0;

        // Loop Through Categories & Work out Vulnerable Stock
        for (int k = 0; k < (int)vCategoryIndex.size(); ++k) {
          for (int l = 0; l < iBaseColCount; ++l) {
            dCurrent = pBaseSquare->getValue(vCategoryIndex[k], l) * vSelectivityIndex[k]->getResult(l);
            if (dCurrent < 0.0)
              dCurrent = 0.0;
            // Increase Vulnerable Amount
            dVulnerable += dCurrent;
          }
        }

        // Work out exploitation rate to remove (catch/vulnerableNumber)
        dExploitation = dCatch / CMath::zeroFun(dVulnerable, ZERO);
        if (dExploitation > dUMax) {
          dExploitation = dUMax;
          if (pPenalty != 0) {  // Throw Penalty
            pPenalty->trigger(sLabel, dCatch, (dVulnerable * dUMax));
          }
        } else if (dExploitation < ZERO) {
          dExploitation = 0.0;
          continue;
        }

        // Loop Through Categories & remove number based on calculated exploitation rate
        for (int k = 0; k < (int)vCategoryIndex.size(); ++k) {
          for (int l = 0; l < iBaseColCount; ++l) {
            // Get Amount to remove
            dCurrent = pBaseSquare->getValue(vCategoryIndex[k], l) * vSelectivityIndex[k]->getResult(l) * dExploitation;
            // If is Zero, Cont
            if (dCurrent <= 0.0)
              continue;

            // Subtract These
            pBaseSquare->subValue(vCategoryIndex[k], l, dCurrent);
            // add this to vActualRemovalsIndex
            vActualRemovalsIndex[iIndexYear] += dCurrent;
          }
        }
      }
    }
#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CEventMortalityProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CEventMortalityProcess::~CEventMortalityProcess()
// Default De-Constructor
//**********************************************************************
CEventMortalityProcess::~CEventMortalityProcess() {}
