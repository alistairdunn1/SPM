//============================================================================
// Name        : CDESolverCallback.h
// Author      : S.Rasmussen
// Date        : 2/05/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CDESOLVERCALLBACK_H_
#define CDESOLVERCALLBACK_H_

// Local Headers
#include "../../BaseClasses/CBaseObject.h"
#include "Engine/DESolverEngine.h"

// Classes
class CEstimateManager;

//**********************************************************************
//
//
//**********************************************************************
class CDESolverCallback : public CBaseObject, public DESolverEngine {
public:
  // Functions
  CDESolverCallback(int vectorsize, int populationsize, double tolerance);
  virtual ~CDESolverCallback();
  double EnergyFunction(vector<double> vTrialValues);

protected:
  // Variables
  CEstimateManager* pEstimateManager;
};

#endif /*CDESOLVERCALLBACK_H_*/
