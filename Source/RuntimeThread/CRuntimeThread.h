//============================================================================
// Name        : CRuntimeThread.h
// Author      : S.Rasmussen
// Date        : 18/08/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CRUNTIMETHREAD_H_
#define CRUNTIMETHREAD_H_

// Local Headers
#include "../BaseClasses/CBaseExecute.h"

// Classes
class CBaseManager;
class CObjectiveFunction;
class CEstimateManager;

//**********************************************************************
//
//
//**********************************************************************
class CRuntimeThread : public CBaseExecute
{
public:
  // Functions
  CRuntimeThread();
  virtual ~CRuntimeThread();
  EState getCurrentState() { return eCurrentState; }
  CEstimateManager *getEstimateManager() { return pEstimateManager; }
  void setWaiting(bool value);
  bool getWaiting();
  void setTerminate(bool value);
  bool getTerminate();
  double getScore() { return dScore; }
  void validate();
  void build();
  void rebuild();
  void execute() { executeBasicRun(); }
  void executeBasicRun();
  void executeEstimationRun();
  void executeProfileRun();
  void executeMCMC();
  void executeSimulationRun();
  void startModel();

protected:
  // Variables
  EState eCurrentState;
  vector<CBaseManager *> vManagers;
  CObjectiveFunction *pObjectiveFunction;
  CEstimateManager *pEstimateManager;
  int iNumberOfYears;
  bool bTerminate;
  bool bWaiting;
  double dScore;
  boost::mutex mutWaiting;
  boost::mutex mutTerminate;
};

#endif /* CRUNTIMETHREAD_H_ */
