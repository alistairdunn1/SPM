//============================================================================
// Name        : CProfileManager.h
// Author      : S.Rasmussen
// Date        : 2/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description : This class is responsible for mantaining a list of Profiles.
//       Like all managers it's responsible for validate, build and execute
//       calls to children.
//
//       Profiling involves running a Minimiser multiple times but
//       changing the value of 1 Profiled variable each time to record
//       the changes in results. Profiled variables have to be estimated
//       variables too. During a run the estimated variable will be disabled
//       and set to a constant value. This value will be increase on each
//       run through the minimiser by N until it hits U (Upper Bound). Then
//       it is flagged back as estimated and the next profile variable is
//       done.
//
// $Date$
//============================================================================
#ifndef CPROFILEMANAGER_H_
#define CPROFILEMANAGER_H_

// Local Headers
#include "../BaseClasses/CBaseManager.h"

// Classes
class CProfile;

//**********************************************************************
//
//
//**********************************************************************
class CProfileManager : public CBaseManager
{
public:
  static CProfileManager *Instance();
  static void Destroy();

  // Functions
  void addProfile(CProfile *Profile);
  int getProfileCount() { return vProfileList.size(); }
  CProfile *getProfile(int index);
  void clone(CProfileManager *Manager);
  void validate();
  void build();
  void execute();
  virtual ~CProfileManager();

protected:
  // Functions
  CProfileManager();
  void saveState();
  void resetState();

  // Variables
  vector<CProfile *> vProfileList;
  vector<double> vCurrentState;

private:
  static boost::thread_specific_ptr<CProfileManager> clInstance;
};

#endif /*CPROFILEMANAGER_H_*/
