//============================================================================
// Name        : CDerivedQuantityLayer.h
// Author      : A.Dunn
// Date        : 02/09/2013
// Copyright   : Copyright NIWA Science �2013 - www.niwa.co.nz
//============================================================================
#ifndef CDERIVEDQUANTITYLAYER_H_
#define CDERIVEDQUANTITYLAYER_H_

// Local Headers
#include "Base/CNumericLayer.h"
#include "../../DerivedQuantities/CDerivedQuantity.h"
#include "../../DerivedQuantities/CDerivedQuantityManager.h"

// Classes
class CWorld;
class CSelectivity;
class CDerivedQuantity;

// Forward Declarations
class CTimeStepManager;

//**********************************************************************
//
//
//**********************************************************************
class CDerivedQuantityLayer : public CNumericLayer
{
public:
  // Functions
  CDerivedQuantityLayer();
  virtual ~CDerivedQuantityLayer();
  CLayer *clone() { return (new CDerivedQuantityLayer(*this)); }
  void addCategory(string value);
  int getCategoryCount() { return (int)vCategoryNames.size(); }
  void addSelectivity(string value);
  int getSelectivityCount() { return (int)vSelectivityNames.size(); }
  double getValue(int RowIndex, int ColIndex, int TargetRow, int TargetCol);
  void validate();
  void build();

protected:
  // Members
  CTimeStepManager *pTimeStepManager;
  CWorld *pWorld;
  // Variables
  vector<string> vCategoryNames;
  vector<int> vCategories;
  vector<string> vSelectivityNames;
  vector<CSelectivity *> vSelectivities;
  string sDerivedQuantity;
  int iOffset;
  int iActualOffset;
  CDerivedQuantity *pDerivedQuantity;
};

#endif /*CDERIVEDQUANTITYLAYER_H_*/
