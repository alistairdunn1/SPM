//============================================================================
// Name        : CAgeingErrorManager.h
// Author      : S.Rasmussen
// Date        : 18/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CAGEINGERRORMANAGER_H_
#define CAGEINGERRORMANAGER_H_

// Local header
#include "../BaseClasses/CBaseManager.h"

// Forward-Dec
class CAgeingError;

//**********************************************************************
//
//
//**********************************************************************
class CAgeingErrorManager : public CBaseManager
{
public:
  static CAgeingErrorManager *Instance();
  static void Destroy();

  // Functions
  void clone(CAgeingErrorManager *Manager);
  void addAgeingError(CAgeingError *ageingError);
  CAgeingError *getAgeingError(string label);
  void validate();
  void build();
  void rebuild();
  virtual ~CAgeingErrorManager();

protected:
  // Function
  CAgeingErrorManager();

  // Variables
  vector<CAgeingError *> vAgeingErrors;

private:
  // Variables
  static boost::thread_specific_ptr<CAgeingErrorManager> clInstance;
};

#endif /* CAGEINGERRORMANAGER_H_ */
