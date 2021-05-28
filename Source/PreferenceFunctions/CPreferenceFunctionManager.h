//============================================================================
// Name        : CPreferenceFunctionManager.h
// Author      : S.Rasmussen
// Date        : 28/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2009-01-12 11:44:49 +1300 (Mon, 12 Jan 2009) $
//============================================================================
#ifndef CPREFERENEFUNCTIONMANAGER_H_
#define CPREFERENEFUNCTIONMANAGER_H_

// Local Headers
#include "../BaseClasses/CBaseManager.h"

// Classes
class CPreferenceFunction;

//**********************************************************************
//
//
//**********************************************************************
class CPreferenceFunctionManager : public CBaseManager {
public:
  static CPreferenceFunctionManager* Instance();
  static void                        Destroy();

  // Functions
  void                 addPreferenceFunction(CPreferenceFunction* Function);
  int                  getPreferenceFunctionCount() { return (int)vPreferenceFunctions.size(); }
  CPreferenceFunction* getPreferenceFunction(int index);
  CPreferenceFunction* getPreferenceFunction(string Label);
  void                 clone(CPreferenceFunctionManager* Manager);
  void                 validate();
  void                 build();
  virtual ~CPreferenceFunctionManager();

protected:
  // Functions
  CPreferenceFunctionManager();

  // Variables
  vector<CPreferenceFunction*> vPreferenceFunctions;

private:
  static boost::thread_specific_ptr<CPreferenceFunctionManager> clInstance;
};

#endif /*CPREFERENEFUNCTIONMANAGER_H_*/
