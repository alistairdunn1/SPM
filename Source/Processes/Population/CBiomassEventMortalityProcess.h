//============================================================================
// Name        : CBiomassEventMortalityProcess.h
// Author      : S.Rasmussen
// Date        : 9/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
//============================================================================
#ifndef CBIOMASSEVENTMORTALITYPROCESS_H_
#define CBIOMASSEVENTMORTALITYPROCESS_H_

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
class CBiomassEventMortalityProcess : public CProcess {
public:
  // Functions
  CBiomassEventMortalityProcess();
  virtual ~CBiomassEventMortalityProcess();
  CProcess*   clone() { return new CBiomassEventMortalityProcess(*this); }
  double      getUMax() { return dUMax; }
  int         getYearsCount() { return vYearsList.size(); }
  int         getYears(int index);
  vector<int> getYears() { return vYearsList; }
  int         getLayersCount() { return vLayersList.size(); }
  string      getLayers(int index);
  double      getActualRemovals(int index) { return vActualRemovalsIndex[index]; }
  double      getRecordedRemovals(int index) { return vRecordedRemovalsIndex[index]; }
  void        validate();
  void        build();
  void        rebuild();
  void        execute();

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
  CNumericLayer*         pActualCatchLayer;
  int                    iCurrentYear;
  bool                   bYearMatch;
  CTimeStepManager*      pTimeStepManager;
  string                 sPenalty;
  CPenalty*              pPenalty;
  vector<double>         vActualRemovalsIndex;
  vector<double>         vRecordedRemovalsIndex;
};

#endif /*CBIOMASSEVENTMORTALITYPROCESS_H_*/
