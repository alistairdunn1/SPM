//============================================================================
// Name        : CSampleDerivedQuantityByCell.h
// Author      : S.Rasmussen
// Date        : 15/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
//============================================================================
#ifndef CBIOMASSDERIVEDQUANTITYBYCELL_H_
#define CBIOMASSDERIVEDQUANTITYBYCELL_H_

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
class CBiomassDerivedQuantityByCell : public CDerivedQuantityByCell {
public:
  // Methods
  CBiomassDerivedQuantityByCell();
  virtual ~CBiomassDerivedQuantityByCell();
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

#endif /* CBIOMASSDERIVEDQUANTITYBYCELL_H_ */
