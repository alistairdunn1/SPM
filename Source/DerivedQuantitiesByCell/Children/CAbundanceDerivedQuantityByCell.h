//============================================================================
// Name        : CAbundanceDerivedQuantityByCell.h
// Author      : S.Rasmussen
// Date        : 23/10/2012
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
//============================================================================
#ifndef CABUNDANCEDERIVEDQUANTITYBYCELL_H_
#define CABUNDANCEDERIVEDQUANTITYBYCELL_H_

// Headers
#include "../CDerivedQuantityByCell.h"

// Forward Declarations
class CNumericLayer;
class CSelectivity;
class CTimeStepManager;

//**********************************************************************
//
//
//**********************************************************************
class CAbundanceDerivedQuantityByCell : public CDerivedQuantityByCell {
public:
  // Methods
  CAbundanceDerivedQuantityByCell();
  virtual ~CAbundanceDerivedQuantityByCell();
  void validate();
  void build();
  void calculate();
  void calculate(int initialisationPhase);

protected:
  // Members
  CTimeStepManager*     pTimeStepManager;
  string                sTimeStep;
  vector<string>        vInitializationTimeStepNames;
  vector<int>           vInitializationTimeStepIndex;
  vector<string>        vCategoryNames;
  vector<int>           vCategories;
  vector<string>        vSelectivityNames;
  vector<CSelectivity*> vSelectivities;
};

#endif /* CABUNDANCEDERIVEDQUANTITYBYCELL_H_ */
