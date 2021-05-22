//============================================================================
// Name        : CDerivedQuantityManager.h
// Author      : S.Rasmussen
// Date        : 30/03/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CDERIVEDQUANTITYMANAGER_H_
#define CDERIVEDQUANTITYMANAGER_H_

// Local Headers
#include "../BaseClasses/CBaseManager.h"

// Forward Declaration
class CDerivedQuantity;

//**********************************************************************
//
//
//**********************************************************************
class CDerivedQuantityManager : public CBaseManager
{
public:
  static CDerivedQuantityManager *Instance();
  static void Destroy();

  // Functions
  void addDerivedQuantity(CDerivedQuantity *DerivedQuantity);
  CDerivedQuantity *getDerivedQuantity(string label);
  void setInitialisationPhase(int newValue) { iInitialisationPhase = newValue; }
  void validate();
  void build();
  void rebuild();
  void calculate();
  void calculate(int initialisationPhase);
  virtual ~CDerivedQuantityManager();

protected:
  // Functions
  CDerivedQuantityManager();

  // Variables
  vector<CDerivedQuantity *> vDerivedQuantities;
  int iInitialisationPhase;

private:
  static boost::thread_specific_ptr<CDerivedQuantityManager> clInstance;
};

#endif /* CDERIVEDQUANTITYMANAGER_H_ */
