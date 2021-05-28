//============================================================================
// Name        : CObjectiveFunction.cpp
// Author      : S.Rasmussen
// Date        : 24/04/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

#include <iostream>
using std::cout;
using std::endl;

// Local Headers
#include "../Estimates/CEstimate.h"
#include "../Estimates/CEstimateManager.h"
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"
#include "../Observations/CObservation.h"
#include "../Observations/CObservationManager.h"
#include "../Penalties/CPenaltyManager.h"
#include "CObjectiveFunction.h"

// Single Static variable
boost::thread_specific_ptr<CObjectiveFunction> CObjectiveFunction::clInstance;

//**********************************************************************
// CObjectiveFunction::CObjectiveFunction()
// Default Constructor
//**********************************************************************
CObjectiveFunction::CObjectiveFunction() {
  // Variables
  sLabel = PARAM_OBJECTIVE;
  dScore = 0.0;
}

//**********************************************************************
// CObjectiveFunction* CObjectiveFunction::Instance()
// Instance Method - Singleton
//**********************************************************************
CObjectiveFunction* CObjectiveFunction::Instance() {
  if (clInstance.get() == 0)
    clInstance.reset(new CObjectiveFunction());
  return clInstance.get();
}

//**********************************************************************
// void CObjectiveFunction::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CObjectiveFunction::Destroy() {
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// SScore* CObjectiveFunction::getScore(int Index)
// Get A Score From Our List
//**********************************************************************
SScore* CObjectiveFunction::getScore(int Index) {
#ifndef OPTIMIZE
  try {
    // Validate
    if (Index < 0)
      CError::errorLessThan(PARAM_INDEX, PARAM_ZERO);
    if (Index >= (int)vScoreList.size())
      CError::errorGreaterThanEqualTo(PARAM_INDEX, PARAM_SCORES_INDEX);
  } catch (string& Ex) {
    Ex = "CObjectiveFunction.getScore()->" + Ex;
    throw Ex;
  }
#endif

  return &vScoreList[Index];
}

//**********************************************************************
// void CObjectiveFunction::addScore(string Label, double Value)
// Add a score to our Vector
//**********************************************************************
void CObjectiveFunction::addScore(string Label, double Value) {
  // Create Structure
  SScore stScore;
  stScore.Label = Label;
  stScore.Score = Value;

  // Push into vector
  vScoreList.push_back(stScore);
}

//**********************************************************************
// void CObjectiveFunction::execute()
// Execute our Object Function
//**********************************************************************
void CObjectiveFunction::execute() {
  // Variables
  dScore       = 0;
  dLikelihoods = 0;
  dPenalties   = 0;
  dPriors      = 0;
  vScoreList.clear();
  string sLabel;
  double dValue;

  // Loop Through Observations
  vector<CObservation*> vObservations;
  CObservationManager::Instance()->fillVector(vObservations);

  foreach (CObservation* Observation, vObservations) {
    // Get Vars
    sLabel = PARAM_OBS + string("->") + Observation->getLabel();
    dValue = Observation->getScore();

    // Increment Score, and Add Value to Vector
    dLikelihoods += dValue;
    addScore(sLabel, dValue);
  }

  // Loop Through Penalties
  vector<SFlaggedPenalty*> vPenalties;
  CPenaltyManager::Instance()->fillVectorWithFlagged(vPenalties);

  foreach (SFlaggedPenalty* Penalty, vPenalties) {
    // Get Vars
    sLabel = PARAM_PENALTY + string("->") + Penalty->Label;
    dValue = Penalty->Score;

    // Inc Score, Add Value to Vector
    dPenalties += dValue;
    addScore(sLabel, dValue);
  }

  // Loop Through Priors
  vector<CEstimate*> vEstimates;
  CEstimateManager::Instance()->fillVector(vEstimates);

  foreach (CEstimate* Estimate, vEstimates) {
    // Get Vars
    sLabel = PARAM_PRIOR + string("->") + Estimate->getParameter();
    dValue = Estimate->getScore();

    // Inc Score, Add Value to vector
    dPriors += dValue;
    addScore(sLabel, dValue);
  }

  // Now sum for out total score
  dScore = dLikelihoods + dPenalties + dPriors;
}

//**********************************************************************
// CObjectiveFunction::~CObjectiveFunction()
// Default De-Constructor
//**********************************************************************
CObjectiveFunction::~CObjectiveFunction() {}
