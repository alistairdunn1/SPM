//============================================================================
// Name        : CSizeWeightManager.cpp
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global headers
#include <iostream>

// Local headers
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"
#include "CSizeWeight.h"
#include "CSizeWeightManager.h"

// Using
using std::cout;
using std::endl;

// Singleton Variable
boost::thread_specific_ptr<CSizeWeightManager> CSizeWeightManager::clInstance;

//**********************************************************************
// CSizeWeightManager::CSizeWeightManager()
// Default Constructor
//**********************************************************************
CSizeWeightManager::CSizeWeightManager() {}

//**********************************************************************
// CSizeWeightManager* CSizeWeightManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CSizeWeightManager* CSizeWeightManager::Instance() {
  if (clInstance.get() == 0)
    clInstance.reset(new CSizeWeightManager());
  return clInstance.get();
}

//**********************************************************************
// void CSizeWeightManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CSizeWeightManager::Destroy() {
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// void CSizeWeightManager::clone(CSizeWeightManager *Manager)
// Clone our Ageing Errors
//**********************************************************************
void CSizeWeightManager::clone(CSizeWeightManager* Manager) {
  foreach (CSizeWeight* sizeWeight, Manager->vSizeWeights) { vSizeWeights.push_back(sizeWeight->clone()); }
}

//**********************************************************************
// void CSizeWeightManager::addSizeWeight(CSizeWeight *SizeWeight)
// Add Ageing Error to the List
//**********************************************************************
void CSizeWeightManager::addSizeWeight(CSizeWeight* SizeWeight) {
  vSizeWeights.push_back(SizeWeight);
}

//**********************************************************************
// CSizeWeight* CSizeWeightManager::getSizeWeight(string label)
// Get our Ageing Error
//**********************************************************************
CSizeWeight* CSizeWeightManager::getSizeWeight(string label) {
  try {
    foreach (CSizeWeight* SizeWeight, vSizeWeights) {
      if (SizeWeight->getLabel() == label)
        return SizeWeight;
    }

    CError::errorUnknown(PARAM_SIZE_WEIGHT, label);
  } catch (string& Ex) {
    Ex = "CSizeWeightManager.getSizeWeight(" + label + ")->" + Ex;
    throw Ex;
  }

  return 0;
}

//**********************************************************************
// void CSizeWeightManager::validate()
// Validate our Ageing Errors
//**********************************************************************
void CSizeWeightManager::validate() {
  try {
    foreach (CSizeWeight* SizeWeight, vSizeWeights) { SizeWeight->validate(); }
    // Look for Duplicate Labels
    map<string, int> mLabelList;
    foreach (CSizeWeight* SizeWeight, vSizeWeights) {
      // Increase Count for this label
      mLabelList[SizeWeight->getLabel()] += 1;

      // Check if we have more than 1
      if (mLabelList[SizeWeight->getLabel()] > 1)
        CError::errorDuplicate(PARAM_SIZE_WEIGHT, SizeWeight->getLabel());
    }
  } catch (string& Ex) {
    Ex = "CSizeWeightManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CSizeWeightManager::build()
// Build our SizeWeights
//**********************************************************************
void CSizeWeightManager::build() {
  try {
    foreach (CSizeWeight* SizeWeight, vSizeWeights) { SizeWeight->build(); }
  } catch (string& Ex) {
    Ex = "CSizeWeightManager.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CSizeWeightManager::rebuild()
// Rebuild our ageing errors
//**********************************************************************
void CSizeWeightManager::rebuild() {
  try {
    foreach (CSizeWeight* SizeWeight, vSizeWeights) { SizeWeight->rebuild(); }
  } catch (string& Ex) {
    Ex = "CSizeWeightManager.rebuild()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CSizeWeightManager::~CSizeWeightManager()
// Destructor
//**********************************************************************
CSizeWeightManager::~CSizeWeightManager() {
  foreach (CSizeWeight* SizeWeight, vSizeWeights) { delete SizeWeight; }
}
