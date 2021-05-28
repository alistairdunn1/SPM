//============================================================================
// Name        : CObservationManager.cpp
// Author      : S.Rasmussen
// Date        : 17/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description : << See CObservationManager.h >>
// $Date$
//============================================================================

// Global headers
#include <iostream>

// Local Headers
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"
#include "CObservation.h"
#include "CObservationManager.h"

// Using
using std::cout;
using std::endl;

// Single Static variable
boost::thread_specific_ptr<CObservationManager> CObservationManager::clInstance;

//**********************************************************************
// CObservationManager::CObservationManager()
// Default Constructor
//**********************************************************************
CObservationManager::CObservationManager() {}

//**********************************************************************
// CObservationManager* CObservationManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CObservationManager* CObservationManager::Instance() {
  if (clInstance.get() == 0)
    clInstance.reset(new CObservationManager());
  return clInstance.get();
}

//**********************************************************************
// void CObservationManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CObservationManager::Destroy() {
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// void CObservationManager::addObservation(CObservation *pObservation)
// Add Proportion To Our List
//**********************************************************************
void CObservationManager::addObservation(CObservation* pObservation) {
  vObservationList.push_back(pObservation);
}

//**********************************************************************
// void CObservationManager::fillVector(vector<CObservation*> &list)
// Fill our vector with the observations
//**********************************************************************
void CObservationManager::fillVector(vector<CObservation*>& list) {
  list.clear();

  foreach (CObservation* Observation, vObservationList) { list.push_back(Observation); }
}

//**********************************************************************
// CObservation* CObservationManager::getObservation(string label)
// Get Observation by label
//**********************************************************************
CObservation* CObservationManager::getObservation(string label) {
#ifndef OPTIMIZE
  try {
#endif
    foreach (CObservation* Observation, vObservationList) {
      if (Observation->getLabel() == label)
        return Observation;
    }

    CError::errorUnknown(PARAM_OBSERVATION, label);

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CObservationManager.getObservation()->" + Ex;
    throw Ex;
  }
#endif

  return 0;
}

//**********************************************************************
// void CObservationManager::clone(CObservationManager *Manager)
// Clone the Observations for Multi-threaded use
//**********************************************************************
void CObservationManager::clone(CObservationManager* Manager) {
  foreach (CObservation* observation, Manager->vObservationList) { vObservationList.push_back(observation->clone()); }
}

//**********************************************************************
// void CObservationManager::validate()
// Loop Through and Validate our Proportions
//**********************************************************************
void CObservationManager::validate() {
  try {
    foreach (CObservation* Observation, vObservationList) { Observation->validate(); }

    // Variables
    vector<CObservation*>::iterator vPtr;
    map<string, int>                mObservationList;

    // Check For Duplicates
    vPtr = vObservationList.begin();
    while (vPtr != vObservationList.end()) {
      // Inc
      mObservationList[(*vPtr)->getLabel()] += 1;

      // Check
      if (mObservationList[(*vPtr)->getLabel()] > 1)
        CError::errorDuplicate(PARAM_LABEL, (*vPtr)->getLabel());

      vPtr++;
    }
  } catch (string& Ex) {
    Ex = "CObservationManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CObservationManager::build()
// Build
//**********************************************************************
void CObservationManager::build() {
  try {
    // Loop and build
    foreach (CObservation* Observation, vObservationList) { Observation->build(); }
  } catch (string& Ex) {
    Ex = "CObservationManager.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CObservationManager::prepare()
// Prepare our observations
//**********************************************************************
void CObservationManager::prepare(int year, int step) {
  foreach (CObservation* observation, vObservationList) {
    if ((observation->getYear() == year) && (observation->getTimeStep() == step)) {
      observation->prepare();
    }
  }
}

//**********************************************************************
// void CObservationManager::execute(int year, int step)
// Execute
//**********************************************************************
void CObservationManager::execute(int year, int step) {
#ifndef OPTIMIZE
  try {
#endif
    // Loop and Test
    foreach (CObservation* Observation, vObservationList) {
      if ((Observation->getYear() == year) && (Observation->getTimeStep() == step)) {
        Observation->execute();
      }
    }
#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CObservationManager.execute()->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CObservationManager::~CObservationManager()
// Default De-Constructor
//**********************************************************************
CObservationManager::~CObservationManager() {
  vector<CObservation*>::iterator vPtr;
  vPtr = vObservationList.begin();
  while (vPtr != vObservationList.end()) {
    delete (*vPtr);
    vPtr++;
  }
  vObservationList.clear();
}
