//============================================================================
// Name        : CInitializationPhaseManager.h
// Author      : S.Rasmussen
// Date        : 29/04/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CINITIALIZATIONPHASEMANAGER_H_
#define CINITIALIZATIONPHASEMANAGER_H_

// Local Headers
#include "../BaseClasses/CBaseManager.h"

// Classes
class CInitializationPhase;
class CReportManager;
class CDerivedQuantityManager;
class CDerivedQuantityByCellManager;

//**********************************************************************
//
//
//**********************************************************************
class CInitializationPhaseManager : public CBaseManager {
public:
  // Functions
  static CInitializationPhaseManager* Instance();
  static void                         Destroy();
  void                                addInitializationPhase(CInitializationPhase* value);
  void                                loadInitializationPhaseOrder(vector<string>& order);
  int                                 getInitializationPhaseOrderIndex(string label);
  int                                 getLastExecutedInitializationPhase() { return lastExecutedInitializationPhase; }
  int                                 getNumberInitializationPhases() { return vInitializationPhases.size(); }
  CInitializationPhase*               getInitializationPhase(int index) { return vInitializationPhaseOrder[index]; };
  void                                validate();
  void                                build();
  void                                rebuild();
  void                                execute();
  virtual ~CInitializationPhaseManager();

protected:
  // Functions
  CInitializationPhaseManager();

  // Variables
  vector<CInitializationPhase*>  vInitializationPhases;
  vector<CInitializationPhase*>  vInitializationPhaseOrder;
  int                            lastExecutedInitializationPhase;
  CReportManager*                pReportManager;
  CDerivedQuantityByCellManager* pDerivedQuantityByCellManager;
  CDerivedQuantityManager*       pDerivedQuantityManager;

private:
  // Variables
  static boost::thread_specific_ptr<CInitializationPhaseManager> clInstance;
};

#endif /*CINITIALISATIONPHASEMANAGER_H_*/
