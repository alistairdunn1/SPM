//============================================================================
// Name        : CAbundanceDensityLayer.h
// Author      : S.Rasmussen
// Date        : 16/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CABUNDANCEDENSITYLAYER_H_
#define CABUNDANCEDENSITYLAYER_H_

// Local headers
#include "Base/CNumericLayer.h"

// Classes
class CWorld;
class CSelectivity;

//**********************************************************************
//
//
//**********************************************************************
class CAbundanceDensityLayer : public CNumericLayer {
public:
  // Functions
  CAbundanceDensityLayer();
  virtual ~CAbundanceDensityLayer();
  CLayer* clone() { return (new CAbundanceDensityLayer(*this)); }
  void    addCategory(string value);
  int     getCategoryCount() { return (int)vCategoryNames.size(); }
  void    addSelectivity(string value);
  int     getSelectivityCount() { return (int)vSelectivityNames.size(); }
  double  getValue(int RowIndex, int ColIndex, int TargetRow, int TargetCol);
  void    validate();
  void    build();

protected:
  // Variables
  CWorld*               pWorld;
  vector<string>        vCategoryNames;
  vector<int>           vCategories;
  vector<string>        vSelectivityNames;
  vector<CSelectivity*> vSelectivities;
  string                sBaseLayer;
  CNumericLayer*        pLayer;
};

#endif /* CABUNDANCEDENSITYLAYER_H_ */
