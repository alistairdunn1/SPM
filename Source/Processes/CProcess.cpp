//============================================================================
// Name        : CProcess.cpp
// Author      : S.Rasmussen
// Date        : 13/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// headers
#include "CProcess.h"

#include <omp.h>

#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"
#include "../Penalties/CPenaltyManager.h"
#include "../Selectivities/CSelectivityManager.h"

//**********************************************************************
// CProcess::CProcess()
// Default Constructor
//**********************************************************************
CProcess::CProcess() {
  sType              = "";
  bRequiresMerge     = true;
  iNumberOfProcesses = omp_get_num_procs();
}

//**********************************************************************
// string CProcess::getCategory(int index)
// Get category from vector at index
//**********************************************************************
string CProcess::getCategory(int index) {
  return vCategoryList[index];
}

//**********************************************************************
// string CProcess::getSelectivity(int index)
// Get Selectivity from vector at index
//**********************************************************************
string CProcess::getSelectivity(int index) {
  return vSelectivityList[index];
}

//**********************************************************************
// string CProcess::getLayerCategory(int index)
// Get layer category from vector at index
//**********************************************************************
// string CProcess::getLayerCategory(int index) {
//  return vLayerCategoryList[index];
//}

//**********************************************************************
// void CProcess::validate()
// Validate our Base Parameters
//**********************************************************************
void CProcess::validate() {
  try {
    // Base Validation
    CBaseExecute::validate();

    // Check For Duplicate Categories.
    map<string, int> mList;
    if (vCategoryList.size() > 0) {
      foreach (string Category, vCategoryList) {
        mList[Category] += 1;

        if (mList[Category] > 1)
          CError::errorDuplicate(PARAM_CATEGORY, Category);
      }
      mList.clear();
    }
  } catch (string& Ex) {
    Ex = "CProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}
//**********************************************************************
// void CProcess::build()
// Build our Base Objects
//**********************************************************************
void CProcess::build() {
  try {
    CSelectivityManager* pSelectivityManager = CSelectivityManager::Instance();
    foreach (string Name, vSelectivityList) { vSelectivityIndex.push_back(pSelectivityManager->getSelectivity(Name)); }

    foreach (string Name, vCategoryList) { vCategoryIndex.push_back(pWorld->getCategoryIndexForName(Name)); }

    // Setup Vars
    iBaseColCount = pWorld->getBaseSquare(0, 0)->getWidth();
  } catch (string& Ex) {
    Ex = "CProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProcess::execute()
// Base execution
//**********************************************************************
void CProcess::execute() {
  // Default Variables
  dCurrent = 0.0;

  // Set Up Our Layer
  //    if (bDependsOnLayer) {
  //      if ( (dLayerMin >= 0.0) && (dLayerMax >= 0.0) )
  //        pLayer->setMinMax(dLayerMin, dLayerMax);
  //      else
  //        pLayer->defaultMinMax();
  //    }
}
//**********************************************************************
// bool CProcess::checkUsableSquare(CWorldSquare *Square, int iX, int iY)
// Check If Square Is Usable
//**********************************************************************
// bool CProcess::checkUsableSquare(CWorldSquare *Square, int iX, int iY) {
//#ifndef OPTIMIZE
//  try {
//#endif
//    if (!Square->getEnabled())
//      return false;
//
//#ifndef OPTIMIZE
//  } catch (string Ex) {
//    Ex = "CProcess.checkUsableSquare(" + getLabel() + ")->" + Ex;
//    throw Ex;
//  }
//#endif
//  return true;
//}

//**********************************************************************
// bool CProcess::checkUsableBaseSquare(int RowIndex, int ColIndex)
// Check If base Square Is Usable
//**********************************************************************
// bool CProcess::checkUsableBaseSquare(int RowIndex, int ColIndex) {
//#ifndef OPTIMIZE
//  try {
//#endif
//    // Check if Enabled
//    if (!pBase->getEnabled())
//      return false;
//
//    // Check if Layer Oks It
//    if (bDependsOnLayer)
//      if (!pLayer->checkSpace(RowIndex, ColIndex))
//        return false;
//
//#ifndef OPTIMIZE
//  } catch (string Ex) {
//    Ex = "CProcess.checkUsableSquare(" + getLabel() + ")->" + Ex;
//    throw Ex;
//  }
//#endif
//
//  // Default
//  return true;
//}

//**********************************************************************
// CProcess::~CProcess()
// Default De-Constructor
//**********************************************************************
CProcess::~CProcess() {}
