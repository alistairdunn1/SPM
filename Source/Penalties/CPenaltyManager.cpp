//============================================================================
// Name        : CPenaltyManager.cpp
// Author      : S.Rasmussen
// Date        : 16/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
//============================================================================

// Local Headers
#include "CPenaltyManager.h"

#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"
#include "CPenalty.h"

// Single Static variable
boost::thread_specific_ptr<CPenaltyManager> CPenaltyManager::clInstance;

//**********************************************************************
// CPenaltyManager::CPenaltyManager()
// Default Constructor
//**********************************************************************
CPenaltyManager::CPenaltyManager() {}

//**********************************************************************
// CPenaltyManager* CPenaltyManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CPenaltyManager* CPenaltyManager::Instance() {
  if (clInstance.get() == 0)
    clInstance.reset(new CPenaltyManager());
  return clInstance.get();
}

//**********************************************************************
// void CPenaltyManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CPenaltyManager::Destroy() {
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// void CPenaltyManager::addPenalty(CPenalty *Penalty)
// add Penalty to our list
//**********************************************************************
void CPenaltyManager::addPenalty(CPenalty* Penalty) {
  vPenaltyList.push_back(Penalty);
}

//**********************************************************************
// void CPenaltyManager::fillVectorWithFlagged(vector<SFlaggedPenalty*> &list)
// Fill our vector with the penalties
//**********************************************************************
void CPenaltyManager::fillVectorWithFlagged(vector<SFlaggedPenalty*>& list) {
  list.clear();

  foreach (SFlaggedPenalty* Penalty, vFlaggedPenaltyList) { list.push_back(Penalty); }
}

//**********************************************************************
// CPenalty* CPenaltyManager::getPenalty(string Label)
// Get Penalty Pointer
//**********************************************************************
CPenalty* CPenaltyManager::getPenalty(string Label) {
  try {
    foreach (CPenalty* Penalty, vPenaltyList) {
      if (Penalty->getLabel() == Label)
        return Penalty;
    }

    CError::errorUnknown(PARAM_PENALTY, Label);
  } catch (string& Ex) {
    Ex = "CPenaltyManager.getPenalty()->" + Ex;
    throw Ex;
  }

  return 0;
}

//**********************************************************************
// CPenalty* CPenaltyManager::getPenalty(int index)
// Get the penalty from our vector @ index
//**********************************************************************
CPenalty* CPenaltyManager::getPenalty(int index) {
  try {
    if (index >= (int)vPenaltyList.size())
      CError::errorGreaterThanEqualTo(PARAM_INDEX, PARAM_PENALTY);
    if (index < 0)
      CError::errorLessThan(PARAM_INDEX, PARAM_ZERO);
  } catch (string& Ex) {
    Ex = "CPenaltyManager.getPenalty()->" + Ex;
    throw Ex;
  }

  return vPenaltyList[index];
}

//**********************************************************************
// void CPenaltyManager::addPenalty(string Label, double Value)
// Add A Penalty to our list of Executed ones.
//**********************************************************************
void CPenaltyManager::flagPenalty(string Label, double Value) {
  // Check if Penalty has alread been flagged, and if so, add to it
  bool bExists = false;
  for (int i = 0; i < (int)vFlaggedPenaltyList.size(); ++i) {
    if (getFlaggedPenalty(i)->Label == Label)
      getFlaggedPenalty(i)->Score += Value;
    bExists = true;
    break;
  }
  // Else create new penalty
  if (!bExists) {
    SFlaggedPenalty* stPenalty = new SFlaggedPenalty();
    stPenalty->Label           = Label;
    stPenalty->Score           = Value;
    vFlaggedPenaltyList.push_back(stPenalty);
  }
}

//**********************************************************************
// void CPenaltyManager::clearFlaggedPenaltyList()
// Clear Our Penalty List
//**********************************************************************
void CPenaltyManager::clearFlaggedPenaltyList() {
  vFlaggedPenaltyList.clear();
}

//**********************************************************************
// SFlaggedPenalty* CPenaltyManager::getFlaggedPenalty(int Index)
//
//**********************************************************************
SFlaggedPenalty* CPenaltyManager::getFlaggedPenalty(int Index) {
#ifndef OPTIMIZE
  try {
    if (Index < 0)
      CError::errorLessThan(PARAM_INDEX, PARAM_ZERO);
    if (Index >= (int)vFlaggedPenaltyList.size())
      CError::errorGreaterThanEqualTo(PARAM_INDEX, PARAM_FLAGGED_PENALTIES);
#endif

    return vFlaggedPenaltyList[Index];

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CPenaltyManager.getFlaggedPenalty()->" + Ex;
    throw Ex;
  }

  return 0;
#endif
}

//**********************************************************************
// void CPenaltyManager::clone(CPenaltyManager *Manager)
// Clone the Manager to match the one passed in
//**********************************************************************
void CPenaltyManager::clone(CPenaltyManager* Manager) {
  try {
    for (int i = 0; i < Manager->getPenaltyCount(); ++i) {
      CPenalty* pPenalty = Manager->getPenalty(i);
      vPenaltyList.push_back(new CPenalty(*pPenalty));
    }
  } catch (string& Ex) {
    Ex = "CPenaltyManager.clone()->" + Ex;
    throw Ex;
  }
}
//**********************************************************************
// void CPenaltyManager::validate()
// validate
//**********************************************************************
void CPenaltyManager::validate() {
  try {
    // Loop and Validate
    foreach (CPenalty* Penalty, vPenaltyList) { Penalty->validate(); }

    // Look for Duplicate Labels
    map<string, int> mLabelList;
    foreach (CPenalty* Penalty, vPenaltyList) {
      // Increase Count for this label
      mLabelList[Penalty->getLabel()] += 1;

      // Check if we have more than 1
      if (mLabelList[Penalty->getLabel()] > 1)
        CError::errorDuplicate(PARAM_PENALTY, Penalty->getLabel());
    }
  } catch (string& Ex) {
    Ex = "CPenaltyManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPenaltyManager::rebuild()
// Rebuild our Penalty Manager
//**********************************************************************
void CPenaltyManager::rebuild() {
  // Clear the Flagged Penalties
  clearFlaggedPenaltyList();
}

//**********************************************************************
// CPenaltyManager::~CPenaltyManager()
// Default De-Constructor
//**********************************************************************
CPenaltyManager::~CPenaltyManager() {
  // De-Allocate our Memory
  foreach (CPenalty* Penalty, vPenaltyList) { delete Penalty; }

  foreach (SFlaggedPenalty* Penalty, vFlaggedPenaltyList) { delete Penalty; }
}
