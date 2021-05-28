//============================================================================
// Name        : CCategoryTransitionProcess.h
// Author      : S.Rasmussen
// Date        : 14/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CCATEGORYTRANSITIONPROCESS_H_
#define CCATEGORYTRANSITIONPROCESS_H_

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
class CCategoryTransitionProcess : public CProcess {
public:
  // Functions
  CCategoryTransitionProcess();
  virtual ~CCategoryTransitionProcess();
  CProcess* clone() { return new CCategoryTransitionProcess(*this); }
  int       getYearsCount() { return vYearsList.size(); }
  int       getYears(int index);
  int       getLayersCount() { return vLayersList.size(); }
  string    getLayers(int index);
  string    getCategoryTo(int index);
  int       getCategoryToCount() { return vCategoryToList.size(); }
  void      validate();
  void      build();
  void      execute();

protected:
  // Variables
  double                 dN;
  double                 dVulnerable;
  double                 dExploitation;
  double                 dUMax;
  string                 sFrom;
  string                 sTo;
  int                    iFromIndex;
  int                    iToIndex;
  string                 sSelectivity;
  vector<string>         vCategoryToList;
  vector<int>            vCategoryToIndex;
  CSelectivity*          pSelectivity;
  vector<int>            vYearsList;
  vector<string>         vLayersList;
  vector<CNumericLayer*> vLayersIndex;
  CNumericLayer*         pLayer;
  int                    iCurrentYear;
  bool                   bYearMatch;
  CTimeStepManager*      pTimeStepManager;
  string                 sPenalty;
  CPenalty*              pPenalty;
};

#endif /*CCATEGORYTRANSITIONPROCESS_H_*/
