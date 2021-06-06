//============================================================================
// Name        : CEventMortalityProcess.h
// Author      : S.Rasmussen
// Date        : 9/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
//============================================================================
#ifndef CEVENTMORTALITYPROCESS_H_
#define CEVENTMORTALITYPROCESS_H_

// Local Headers
#include "../CProcess.h"

// Classes
class CTimeStepManager;
class CPenalty;
class CNumericLayer;

//**********************************************************************
//
//
//**********************************************************************
class CEventMortalityProcess : public CProcess {
public:
  // Functions
  CEventMortalityProcess();
  virtual ~CEventMortalityProcess();
  CProcess*      clone() { return new CEventMortalityProcess(*this); }
  double         getUMax() { return dUMax; }
  int            getYearsCount() { return vYearsList.size(); }
  int            getYears(int index);
  vector<int>    getYears() { return vYearsList; }
  int            getLayersCount() { return vLayersList.size(); }
  string         getLayers(int index);
  double         getActualRemovals(int index) { return vActualRemovalsIndex[index]; }
  double         getRecordedRemovals(int index) { return vRecordedRemovalsIndex[index]; }
  CNumericLayer* getRemovalsLayer(int index) { return vLayersIndex[index]; }
  CNumericLayer* getActualRemovalsLayer(int index) { return vActualRemovalsLayersIndex[index]; }

  void validate();
  void build();
  void rebuild();
  void execute();

protected:
  // Variables
  double                 dUMax;
  double                 dCatch;
  double                 dVulnerable;
  double                 dExploitation;
  vector<int>            vYearsList;
  vector<string>         vLayersList;
  vector<CNumericLayer*> vLayersIndex;
  CNumericLayer*         pLayer;
  int                    iCurrentYear;
  bool                   bYearMatch;
  CTimeStepManager*      pTimeStepManager;
  string                 sPenalty;
  CPenalty*              pPenalty;
  vector<double>         vActualRemovalsIndex;
  vector<double>         vRecordedRemovalsIndex;
  CNumericLayer*         pActualRemovalsLayer;
  vector<CNumericLayer*> vActualRemovalsLayersIndex;
};

#endif /*CEVENTMORTALITYPROCESS_H_*/
