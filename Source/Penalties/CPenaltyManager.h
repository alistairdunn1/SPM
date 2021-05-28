//============================================================================
// Name        : CPenaltyManager.h
// Author      : S.Rasmussen
// Date        : 16/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CPENALTYMANAGER_H_
#define CPENALTYMANAGER_H_

// Local Headers
#include "../BaseClasses/CBaseManager.h"

// Classes
class CPenalty;

// Structure
struct SFlaggedPenalty {
  string Label;
  double Score;
};

//**********************************************************************
//
//
//**********************************************************************
class CPenaltyManager : public CBaseManager {
public:
  static CPenaltyManager* Instance();
  static void             Destroy();
  void                    clone(CPenaltyManager* Manager);
  void                    addPenalty(CPenalty* Penalty);
  void                    fillVectorWithFlagged(vector<SFlaggedPenalty*>& list);
  int                     getPenaltyCount() { return vPenaltyList.size(); }
  CPenalty*               getPenalty(string Label);
  CPenalty*               getPenalty(int index);
  void                    flagPenalty(string Label, double Value);
  void                    clearFlaggedPenaltyList();
  int                     getFlaggedPenaltyCount() { return vFlaggedPenaltyList.size(); }
  SFlaggedPenalty*        getFlaggedPenalty(int Index);
  void                    validate();
  void                    build(){};
  void                    rebuild();
  virtual ~CPenaltyManager();

protected:
  // Functions
  CPenaltyManager();

  // Variables
  vector<CPenalty*>        vPenaltyList;
  vector<SFlaggedPenalty*> vFlaggedPenaltyList;

private:
  static boost::thread_specific_ptr<CPenaltyManager> clInstance;
};

#endif /*CPENALTYMANAGER_H_*/
