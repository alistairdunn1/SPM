//============================================================================
// Name        : CCatchabilityManager.h
// Author      : S.Rasmussen
// Date        : 28/04/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CQMANAGER_H_
#define CQMANAGER_H_

// Local Headers
#include "../BaseClasses/CBaseManager.h"

// Classes
class CCatchability;

//**********************************************************************
//
//
//**********************************************************************
class CCatchabilityManager : public CBaseManager {
public:
  static CCatchabilityManager* Instance();
  static void                  Destroy();

  // Functions
  void           clone(CCatchabilityManager* Manager);
  void           addCatchability(CCatchability* Q);
  CCatchability* getCatchability(string label);
  void           validate();
  void           build() {}
  virtual ~CCatchabilityManager();

protected:
  // Functions
  CCatchabilityManager();

  // Variables
  vector<CCatchability*> vCatchabilities;

private:
  // Variables
  static boost::thread_specific_ptr<CCatchabilityManager> clInstance;
};

#endif /*CQMANAGER_H_*/
