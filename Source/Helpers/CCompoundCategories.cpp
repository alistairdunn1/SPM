//============================================================================
// Name        : CCompoundCategories.cpp
// Author      : A.Dunn
// Date        : 16/03/2013
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
//============================================================================

// Local Headers
#include "CCompoundCategories.h"
#include "CError.h"
#include "CComparer.h"
#include "../Translations/Translations.h"

//**********************************************************************
// CProportionsAtAgeObservation::CProportionsAtAgeObservation()
// Default Constructor
//**********************************************************************
CCompoundCategories::CCompoundCategories()
{

  // Default Values
  vvCategoryNames.resize(0);
  iNRows = 0;
  vNElements.resize(0);
  iNCategories = 0;
  pWorld = CWorld::Instance();
}

//**********************************************************************
// void  setCategories(vector<string> value);
//**********************************************************************
void CCompoundCategories::setCategories(vector<string> vCategoryNames, string label)
{

  try
  {
    // Neither first or last element may be the '+' symbol
    if (vCategoryNames[0] == CONFIG_AND || vCategoryNames[vCategoryNames.size() - 1] == CONFIG_AND)
      CError::error("Invalid category: " + string(CONFIG_AND) + " in " + label);

    // Otherwise get categories
    int iCount = 1;
    vector<string> tempCategories;
    tempCategories.push_back(vCategoryNames[0]);
    // Create vvCategories object
    while (iCount < (int)vCategoryNames.size())
    {
      if (vCategoryNames[iCount] == CONFIG_AND)
      {
        ++iCount;
        tempCategories.push_back(vCategoryNames[iCount]);
      }
      else
      {
        vvCategoryNames.push_back(tempCategories);
        tempCategories.resize(0);
        tempCategories.push_back(vCategoryNames[iCount]);
      }
      ++iCount;
    }
    vvCategoryNames.push_back(tempCategories);

    // Create iNRows, iNElements, and iNCategories
    iNRows = vvCategoryNames.size();
    for (int i = 0; i < (int)vvCategoryNames.size(); ++i)
    {
      vNElements.push_back(vvCategoryNames[i].size());
      iNCategories += vvCategoryNames[i].size();
    }

    // Create vvCategoryIndex, vvElementIndex, and vGroup objects
    iCount = 0;
    vector<string> vCheckCategoryList;
    for (int i = 0; i < (int)vvCategoryNames.size(); ++i)
    {
      vector<int> tempCategories;
      vector<int> tempIndex;
      string tempGroup = "";
      for (int j = 0; j < (int)vvCategoryNames[i].size(); ++j)
      {
        vCheckCategoryList.push_back(vvCategoryNames[i][j]);
        tempCategories.push_back(setCategoryIndex(i, j));
        tempIndex.push_back(iCount);
        ++iCount;
        tempGroup = std::string(tempGroup) + std::string(vvCategoryNames[i][j]) + std::string(j < ((int)vvCategoryNames[i].size() - 1) ? CONFIG_AND : "");
      }
      vvCategoryIndex.push_back(tempCategories);
      vvElementIndex.push_back(tempIndex);
      vGroup.push_back(tempGroup);
    }
    if (CComparer::hasDuplicates(vCheckCategoryList))
      CError::errorDuplicate(PARAM_CATEGORIES, label);
  }
  catch (string &Ex)
  {
    Ex = "CCompoundCategories.setCompoundCategories()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// vector<string>  getCategoryNames(int row);
//**********************************************************************
vector<string> CCompoundCategories::getCategoryNames(int row)
{

  return (vvCategoryNames[row]);
}

//**********************************************************************
// string getCategoryName(int row, int col);
//**********************************************************************
string CCompoundCategories::getCategoryName(int row, int col)
{

  return (vvCategoryNames[row][col]);
}

//**********************************************************************
//  int setCompoundCategories(int row);
//**********************************************************************
int CCompoundCategories::setCategoryIndex(int row, int col)
{

  int Index = pWorld->getCategoryIndexForName(vvCategoryNames[row][col]);

  return (Index);
}

//**********************************************************************
// static vector<string>  getCompoundCategories(int row);
//**********************************************************************
int CCompoundCategories::getCategoryIndex(int row, int col)
{

  int Index = vvCategoryIndex[row][col];

  return (Index);
}
