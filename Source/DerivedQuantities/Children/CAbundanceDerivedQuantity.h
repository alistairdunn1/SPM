//============================================================================
// Name        : CSampleDerivedQuantity.h
// Author      : S.Rasmussen
// Date        : 15/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CABUNDANCEDERIVEDQUANTITY_H_
#define CABUNDANCEDERIVEDQUANTITY_H_

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
class CAbundanceDerivedQuantity : public CDerivedQuantity
{
public:
  // Methods
  CAbundanceDerivedQuantity();
  virtual ~CAbundanceDerivedQuantity();
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

#endif /* CABUNDANCEDERIVEDQUANTITY_H_ */
