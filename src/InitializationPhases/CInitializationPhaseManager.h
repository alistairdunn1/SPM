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
#include "../BaseClasses/CBaseExecutableObject.h"

// Classes
class CInitializationPhase;

//**********************************************************************
//
//
//**********************************************************************
class CInitializationPhaseManager: CBaseBuildableObject {
public:
  // Functions
  static CInitializationPhaseManager* Instance();
  static void                 Destroy();
  void                        clone(CInitializationPhaseManager *Manager);
  void                        addInitializationPhase(CInitializationPhase *value);
  int                         getInitializationPhaseCount() { return vInitializationPhases.size();  }
  CInitializationPhase*       getInitializationPhase(string label);
  CInitializationPhase*       getInitializationPhase(int index);
  void                        validate();
  void                        build();
  virtual                     ~CInitializationPhaseManager();

protected:
  // Functions
  CInitializationPhaseManager();

  // Variables
  vector<CInitializationPhase*> vInitializationPhases;

private:
  // Variables
  static boost::thread_specific_ptr<CInitializationPhaseManager> clInstance;
};

#endif /*CINITIALISATIONPHASEMANAGER_H_*/
