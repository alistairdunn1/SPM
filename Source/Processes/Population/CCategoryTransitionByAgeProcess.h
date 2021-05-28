//============================================================================
// Name        : CCategoryTransitionByAgeProcess.cpp
// Author      : A. Dunn
// Date        : 18/04/2014
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
//============================================================================
#ifndef CCATEGORYTRANSITIONBYAGEPROCESS_H_
#define CCATEGORYTRANSITIONBYAGEPROCESS_H_

// Local Headers
#include "../../World/WorldView/CLayerDerivedWorldView.h"
#include "../CProcess.h"

// Classes
class CTimeStepManager;
class CPenalty;
// class CCategoricalLayer;

//**********************************************************************
//
//
//**********************************************************************
class CCategoryTransitionByAgeProcess : public CProcess {
public:
  // Functions
  CCategoryTransitionByAgeProcess();
  virtual ~CCategoryTransitionByAgeProcess();
  CProcess* clone() { return new CCategoryTransitionByAgeProcess(*this); }
  string    getCategoryTo(int index);
  int       getCategoryToCount() { return vCategoryToList.size(); }
  void      validate();
  void      build();
  void      execute();

protected:
  // Variables
  double                      dN;
  double                      dVulnerable;
  double                      dExploitation;
  double                      dUMax;
  string                      sFrom;
  string                      sTo;
  int                         iFromIndex;
  int                         iToIndex;
  int                         iMinAge;
  int                         iMaxAge;
  bool                        bAgePlus;
  int                         iAgeSpread;
  vector<string>              vCategoryToList;
  vector<int>                 vCategoryToIndex;
  int                         iYear;
  string                      sLayer;
  CCategoricalLayer*          pLayer;
  CLayerDerivedWorldView*     pWorldView;
  double*                     pAgeResults;
  map<string, vector<double>> mvNMatrix;
  CTimeStepManager*           pTimeStepManager;
  string                      sPenalty;
  CPenalty*                   pPenalty;
};

#endif /*CCATEGORYTRANSITIONBYAGEPROCESS_H_*/
