//============================================================================
// Name        : CTimeStep.h
// Author      : S.Rasmussen
// Date        : 13/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description : A time-step is a unit of work in out model.
//              Each time step will execute multiple processes during it's
//              execution.
// $Date$
//============================================================================
#ifndef CTIMESTEP_H_
#define CTIMESTEP_H_

// Local Headers
#include "../BaseClasses/CBaseExecute.h"
#include "../DerivedQuantities/CDerivedQuantity.h"
#include "../DerivedQuantitiesByCell/CDerivedQuantityByCell.h"

// Classes
class CProcess;

//**********************************************************************
//
//
//**********************************************************************
class CTimeStep : public CBaseExecute {
public:
  CTimeStep();
  virtual ~CTimeStep();
  CTimeStep*     clone() { return new CTimeStep(*this); }
  void           validate();
  void           build();
  void           execute();
  vector<string> getProcessNames() { return vProcessNames; }
  double         getGrowthProportion() { return dGrowthProportion; }
  void           addInitialisationDerivedQuantity(CDerivedQuantity* dq) { vInitialisationDerivedQuantities.push_back(dq); }
  void           addDerivedQuantity(CDerivedQuantity* dq);

protected:
  // Variables
  vector<string>                                 vProcessNames;
  vector<CProcess*>                              vProcesses;
  double                                         dGrowthProportion;
  vector<CDerivedQuantity*>                      vInitialisationDerivedQuantities;
  map<unsigned, vector<CDerivedQuantity*>>       mvDerivedQuantities;
  vector<CDerivedQuantityByCell*>                vInitialisationDerivedQuantitiesByCell;
  map<unsigned, vector<CDerivedQuantityByCell*>> mvDerivedQuantitiesByCell;
};

#endif /*CTIMESTEP_H_*/
