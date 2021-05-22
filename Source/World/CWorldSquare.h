//============================================================================
// Name        : CWorldSquare.h
// Author      : S.Rasmussen
// Date        : 10/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description : This class represents 1 cell in our World-Grid. Each
//       WorldSquare maintains a list of categories and ages; As well as
//       The number of fish in each location
//
// $Date$
//============================================================================
#ifndef CWORLDSQUARE_H_
#define CWORLDSQUARE_H_

// Local Headers
#include "../BaseClasses/CBaseObject.h"

//**********************************************************************
//
//
//**********************************************************************
class CWorldSquare : public CBaseObject
{
public:
  // Functions
  CWorldSquare();
  virtual ~CWorldSquare();
  void setEnabled(bool value) { bEnabled = value; }
  bool getEnabled() { return bEnabled; }
  void setNumberOfCategories(int value) { iNumberOfCategories = value; }
  int getNumberOfCategories() { return iNumberOfCategories; }
  void setMinAge(int value) { iMinAge = value; }
  int getMinAge() { return iMinAge; }
  void setMaxAge(int value) { iMaxAge = value; }
  int getMaxAge() { return iMaxAge; }
  void setAgePlus(bool value) { bAgePlus = value; }
  bool getAgePlus() { return bAgePlus; }
  void setArea(double value) { dArea = value; }
  double getArea() { return dArea; }
  bool makeAdjustments(CWorldSquare *WorldSquare);
  double getValue(int RowIndex, int ColIndex);
  void setValue(int RowIndex, int ColIndex, double Value);
  void addValue(int RowIndex, int ColIndex, double Value);
  void subValue(int RowIndex, int ColIndex, double Value);
  int getHeight() { return iHeight; }
  int getWidth() { return iWidth; }
  double getAbundance();
  double getAbundanceForAge(int AgeIndex);
  double getAbundanceInCategoryForAge(int AgeIndex, int CategoryIndex);
  double getAbundanceForCategory(int CategoryIndex);
  void build();
  void zeroGrid();
  void loadDummyData();

protected:
  // Variables
  double **pGrid;
  bool bEnabled;
  int iHeight;
  int iWidth;
  int iNumberOfCategories;
  int iMinAge;
  int iMaxAge;
  bool bAgePlus;
  double dArea;
};

#endif /*CWORLDSQUARE_H_*/
