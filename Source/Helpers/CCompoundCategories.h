//============================================================================
// Name        : CCompoundCategories.h
// Author      : A.Dunn
// Date        : 16/03/2013
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
//============================================================================
#ifndef CCOMPOUNDCATEGORIES_H_
#define CCOMPOUNDCATEGORIES_H_

// Global Headers
#include <string>
#include <vector>

// Local Headers
#include "../World/CWorld.h"

// Using
using std::string;
using std::vector;

//**********************************************************************
//
//
//**********************************************************************
class CCompoundCategories {
public:
  // Functions
  CCompoundCategories();
  void           setCategories(vector<string> value, string label);
  int            setCategoryIndex(int row, int col);
  vector<string> getCategoryNames(int row);
  string         getCategoryName(int row, int col);
  string         getGroup(int row) { return vGroup[row]; }
  int            getCategoryIndex(int row, int col);
  int            getIndex(int row, int col) { return vvElementIndex[row][col]; };

  int getNRows() { return iNRows; }
  int getNElements(int index) { return vNElements[index]; }
  int getNCategories() { return iNCategories; }

private:
  // Functions
  ~CCompoundCategories() {}
  // variables
  CWorld*                pWorld;
  int                    iNRows;
  int                    iNCategories;
  vector<int>            vNElements;
  vector<vector<string>> vvCategoryNames;
  vector<vector<int>>    vvCategoryIndex;
  vector<vector<int>>    vvElementIndex;
  vector<string>         vGroup;
};

#endif /* CCOMPOUNDCATEGORIES_H_ */
