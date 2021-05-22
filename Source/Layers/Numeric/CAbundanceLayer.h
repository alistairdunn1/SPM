//============================================================================
// Name        : CAbundanceLayer.h
// Author      : S.Rasmussen
// Date        : 28/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CABUNDANCELAYER_H_
#define CABUNDANCELAYER_H_

// Local Headers
#include "Base/CNumericLayer.h"

// Classes
class CWorld;
class CSelectivity;

//**********************************************************************
//
//
//**********************************************************************
class CAbundanceLayer : public CNumericLayer
{
public:
  // Functions
  CAbundanceLayer();
  virtual ~CAbundanceLayer();
  CLayer *clone() { return (new CAbundanceLayer(*this)); }
  void addCategory(string value);
  int getCategoryCount() { return (int)vCategoryNames.size(); }
  void addSelectivity(string value);
  int getSelectivityCount() { return (int)vSelectivityNames.size(); }
  double getValue(int RowIndex, int ColIndex, int TargetRow, int TargetCol);
  void validate();
  void build();

protected:
  // Variables
  CWorld *pWorld;
  vector<string> vCategoryNames;
  vector<int> vCategories;
  vector<string> vSelectivityNames;
  vector<CSelectivity *> vSelectivities;
};

#endif /*CABUNDANCELAYER_H_*/
