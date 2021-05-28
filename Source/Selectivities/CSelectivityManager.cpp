//============================================================================
// Name        : CSelectivityManager.cpp
// Author      : S.Rasmussen
// Date        : 14/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description : << See CSelectivityManager.h >>
// $Date$
//============================================================================

// Local Headers
#include "CSelectivityManager.h"

#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"
#include "CSelectivity.h"

// Single Static variable
boost::thread_specific_ptr<CSelectivityManager> CSelectivityManager::clInstance;

//**********************************************************************
// CSelectivityManager::CSelectivityManager()
// Default Constructor
//**********************************************************************
CSelectivityManager::CSelectivityManager() {}

//**********************************************************************
// CSelectivityManager* CSelectivityManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CSelectivityManager* CSelectivityManager::Instance() {
  if (clInstance.get() == 0)
    clInstance.reset(new CSelectivityManager());
  return clInstance.get();
}

//**********************************************************************
// void CSelectivityManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CSelectivityManager::Destroy() {
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// void CSelectivityManager::addSelectivity(CSelectivity* Selectivity)
// Add Selectivity
//**********************************************************************
void CSelectivityManager::addSelectivity(CSelectivity* Selectivity) {
  vSelectivities.push_back(Selectivity);
}

//**********************************************************************
// void CSelectivityManager::fillVector(vector<CSelectivity*> &list, vector<string> &names)
// Fill our Vector with Selectivities
//**********************************************************************
void CSelectivityManager::fillVector(vector<CSelectivity*>& list, vector<string>& names) {
  list.clear();

  foreach (string Label, names) {
    int iIndex = getSelectivityIndex(Label);
    list.push_back(vSelectivities[iIndex]);
  }
}

//**********************************************************************
// int CSelectivityManager::getSelectivityIndex(string Label)
// get The selectivity Index
//**********************************************************************
int CSelectivityManager::getSelectivityIndex(string Label) {
  try {
    vector<CSelectivity*>::iterator vPtr   = vSelectivities.begin();
    int                             iCount = 0;
    while (vPtr != vSelectivities.end()) {
      if ((*vPtr)->getLabel() == Label)
        return iCount;
      iCount++;
      vPtr++;
    }

    CError::errorUnknown(PARAM_SELECTIVITY, Label);
  } catch (string& Ex) {
    Ex = "CSelectivityManager.getSelectivityIndex()->" + Ex;
    throw Ex;
  }

  return -1;
}

//**********************************************************************
// CSelectivity* CSelectivityManager::getSelectivity(string Label)
// Get our Selectivity
//**********************************************************************
CSelectivity* CSelectivityManager::getSelectivity(string Label) {
  try {
    vector<CSelectivity*>::iterator vPtr = vSelectivities.begin();
    while (vPtr != vSelectivities.end()) {
      if ((*vPtr)->getLabel() == Label)
        return (*vPtr);
      vPtr++;
    }

    CError::errorUnknown(PARAM_SELECTIVITY, Label);
  } catch (string& Ex) {
    Ex = "CSelectivityManager.getSelectivity()->" + Ex;
    throw Ex;
  }

  return 0;
}

//**********************************************************************
// void CSelectivityManager::clone(CSelectivityManager *Manager)
// Clone
//**********************************************************************
void CSelectivityManager::clone(CSelectivityManager* Manager) {
  try {
    foreach (CSelectivity* Selectivity, Manager->vSelectivities) { vSelectivities.push_back(Selectivity->clone()); }
  } catch (string& Ex) {
    Ex = "CSelectivityManager.clone()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CSelectivityManager::Validate()
// Validate Selectivities
//**********************************************************************
void CSelectivityManager::validate() {
  try {
    // Validate
    foreach (CSelectivity* Selectivity, vSelectivities) { Selectivity->validate(); }

    // Check For duplicate labels
    map<string, int> mSelectivityList;
    foreach (CSelectivity* Selectivity, vSelectivities) {
      mSelectivityList[Selectivity->getLabel()] += 1;

      if (mSelectivityList[Selectivity->getLabel()] > 1)
        CError::errorDuplicate(PARAM_SELECTIVITY, Selectivity->getLabel());
    }
  } catch (string& Ex) {
    Ex = "CSelectivityManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CSelectivityManager::build()
// build
//**********************************************************************
void CSelectivityManager::build() {
#ifndef OPTIMIZE
  try {
#endif

    // build Selectivities
    foreach (CSelectivity* Selectivity, vSelectivities) { Selectivity->build(); }

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CSelectivityManager.build()->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CSelectivityManager::rebuild()
// rebuild
//**********************************************************************
void CSelectivityManager::rebuild() {
#ifndef OPTIMIZE
  try {
#endif

    // build Selectivities
    foreach (CSelectivity* Selectivity, vSelectivities) { Selectivity->rebuild(); }

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CSelectivityManager.rebuild()->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CSelectivityManager::~CSelectivityManager()
// Default De-Constructor
//**********************************************************************
CSelectivityManager::~CSelectivityManager() {
  vector<CSelectivity*>::iterator vPtr;
  vPtr = vSelectivities.begin();
  while (vPtr != vSelectivities.end()) {
    delete (*vPtr);
    vPtr++;
  }
  vSelectivities.clear();
}
