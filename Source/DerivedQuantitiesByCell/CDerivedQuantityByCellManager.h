//============================================================================
// Name        : CDerivedQuantityByCellManager.h
// Author      : S.Rasmussen
// Date        : 30/03/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
//============================================================================
#ifndef CDERIVEDQUANTITYBYCELLMANAGER_H_
#define CDERIVEDQUANTITYBYCELLMANAGER_H_

// Local Headers
#include "../BaseClasses/CBaseManager.h"

// Forward Declaration
class CDerivedQuantityByCell;

//**********************************************************************
//
//
//**********************************************************************
class CDerivedQuantityByCellManager : public CBaseManager
{
public:
  static CDerivedQuantityByCellManager *Instance();
  static void Destroy();

  // Functions
  void addDerivedQuantityByCell(CDerivedQuantityByCell *DerivedQuantityByCell);
  CDerivedQuantityByCell *getDerivedQuantityByCell(string label);
  void setInitialisationPhase(int newValue) { iInitialisationPhase = newValue; }
  void validate();
  void build();
  void rebuild();
  void calculate();
  void calculate(int initialisationPhase);
  virtual ~CDerivedQuantityByCellManager();

protected:
  // Functions
  CDerivedQuantityByCellManager();

  // Variables
  vector<CDerivedQuantityByCell *> vDerivedQuantityByCells;
  int iInitialisationPhase;

private:
  static boost::thread_specific_ptr<CDerivedQuantityByCellManager> clInstance;
};

#endif /* CDERIVEDQUANTITYBYCELLMANAGER_H_ */
