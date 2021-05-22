//============================================================================
// Name        : CMCMCManager.h
// Author      : S.Rasmussen
// Date        : 11/01/2020
// Copyright   : Copyright NIWA Science �2020 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CMCMCMANAGER_H_
#define CMCMCMANAGER_H_

// Local Headers
#include "../BaseClasses/CBaseManager.h"

// Forward Declarations
class CRuntimeThread;
class CMCMC;

//**********************************************************************
//
//
//**********************************************************************
class CMCMCManager : public CBaseManager
{
public:
  static CMCMCManager *Instance();
  static void Destroy();

  // Functions
  void addMCMC(CMCMC *value);
  void addThread(CRuntimeThread *Thread);
  CMCMC *getMCMC() { return pMCMC; }
  void clone(CMCMCManager *Manager) {}
  void validate();
  void build();
  void execute();

  // accessor
  string getActiveMCMCLabel() { return sMCMC; }

protected:
  // Functions
  CMCMCManager();
  virtual ~CMCMCManager();

  // Variables
  CMCMC *pMCMC;
  string sMCMC;
  vector<CMCMC *> vMCMCList;

private:
  static CMCMCManager *clInstance;
};

#endif /*CMCMCMANAGER_H_*/
