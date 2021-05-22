//============================================================================
// Name        : CBiomassDerivedQuantity.h
// Author      : S.Rasmussen
// Date        : 15/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
//============================================================================

#ifndef CBIOMASSDERIVEDQUANTITY_H_
#define CBIOMASSDERIVEDQUANTITY_H_

// Headers
#include "../CDerivedQuantity.h"

// Forward Declarations
class CNumericLayer;
class CSelectivity;
class CTimeStepManager;

//**********************************************************************
//
//
//**********************************************************************
class CBiomassDerivedQuantity : public CDerivedQuantity
{
public:
  // Methods
  CBiomassDerivedQuantity();
  virtual ~CBiomassDerivedQuantity();
  void validate();
  void build();
  void calculate();
  void calculate(int initialisationPhase);

protected:
  // Members
  CTimeStepManager *pTimeStepManager;
  string sTimeStep;
  vector<string> vInitializationTimeStepNames;
  vector<int> vInitializationTimeStepIndex;
  vector<string> vCategoryNames;
  vector<int> vCategories;
  string sLayer;
  CNumericLayer *pLayer;
  vector<string> vSelectivityNames;
  vector<CSelectivity *> vSelectivities;
};

#endif /* CBIOMASSDERIVEDQUANTITY_H_ */
