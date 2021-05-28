//============================================================================
// Name        : CInitializationPhase.h
// Author      : S.Rasmussen
// Date        : 13/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CINITIALIZATIONPHASE_H_
#define CINITIALIZATIONPHASE_H_

// Local Headers
#include "../BaseClasses/CBaseExecute.h"

// Classes
class CTimeStep;

//**********************************************************************
//
//
//**********************************************************************
class CInitializationPhase : public CBaseExecute {
public:
  CInitializationPhase();
  virtual ~CInitializationPhase();
  void           validate();
  void           build();
  void           rebuild();
  void           execute();
  int            getCurrentTimeStep() { return iCurrentTimeStep; }
  CTimeStep*     getTimeStep(int i) { return vTimeSteps[i]; }
  vector<string> getTimeStepNames() { return vTimeStepNames; }
  void           setExecutionOrderIndex(int index) { iExecutionOrderIndex = index; }
  int            getNYears() { return iYears; }
  int            getActualYears() { return iActualYears; }
  double         getLambda() { return dLambda; }
  bool           getConvergenceCheck() { return bConvergenceCheck; }
  vector<int>    getLambdaHatYears() { return vLambdaHatYears; }
  vector<double> getLambdaHat() { return vLambdaHat; }

protected:
  int                                    iYears;
  int                                    iActualYears;
  int                                    iCurrentTimeStep;
  int                                    iExecutionOrderIndex;
  vector<string>                         vTimeStepNames;
  vector<CTimeStep*>                     vTimeSteps;
  bool                                   bConvergenceCheck;
  double                                 dLambda;
  double                                 dDiffLambda;
  double                                 dTotalLambda;
  vector<int>                            vLambdaYears;
  vector<vector<vector<vector<double>>>> vvWorldCopy;
  CWorldSquare*                          pPreviousSquare;
  vector<double>                         vLambdaHat;
  vector<int>                            vLambdaHatYears;
};

#endif /* CINITIALIZATIONPHASE_H_ */
