//============================================================================
// Name        : CWorldSquare.cpp
// Author      : S.Rasmussen
// Date        : 10/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description : << See CWorldSquare.h >>
// $Date$
//============================================================================

#include <omp.h>

#include "../Helpers/CError.h"
#include "../Helpers/DefinedValues.h"
#include "CWorld.h"
#include "CWorldSquare.h"

//**********************************************************************
// CWorldSquare::CWorldSquare();
// Default Constructor
//**********************************************************************
CWorldSquare::CWorldSquare()
{

  // Local Vars
  dArea = 0.0;
  iWidth = 0;
  iHeight = 0;
  iMinAge = 0;
  iMaxAge = 0;

  setEnabled(true);
}

//**********************************************************************
// bool CWorldSquare::makeAdjustments(CWorldSquare *WorldSquare)
// Make Adjustments. This will be Adjusting it against a Difference WorldSquare
//**********************************************************************
bool CWorldSquare::makeAdjustments(CWorldSquare *WorldSquare)
{
  for (int i = 0; i < iHeight; ++i)
  {
    for (int j = 0; j < iWidth; ++j)
    {
      pGrid[i][j] += WorldSquare->getValue(i, j);
      if (pGrid[i][j] < TRUE_ZERO)
        pGrid[i][j] = TRUE_ZERO;
    }
  }
  return true;
}

//**********************************************************************
// void CWorldSquare::zeroGrid()
// Zero our Grid Out
//**********************************************************************
void CWorldSquare::zeroGrid()
{
  for (int i = 0; i < iHeight; ++i)
    for (int j = 0; j < iWidth; ++j)
      pGrid[i][j] = 0.0;
}

//**********************************************************************
// double CWorldSquare::getValue(int RowIndex, int ColIndex)
// Get Value From Our Square
//**********************************************************************
double CWorldSquare::getValue(int RowIndex, int ColIndex)
{
#ifndef OPTIMIZE
  try
  {
    if (RowIndex >= iHeight)
      CError::errorGreaterThanEqualTo(PARAM_ROW_INDEX, PARAM_HEIGHT);
    if (RowIndex < 0)
      CError::errorLessThan(PARAM_ROW_INDEX, PARAM_ZERO);
    if (ColIndex >= iWidth)
      CError::errorGreaterThanEqualTo(PARAM_COLUMN_INDEX, PARAM_WIDTH);
    if (ColIndex < 0)
      CError::errorLessThan(PARAM_COLUMN_INDEX, PARAM_ZERO);
#endif

    return pGrid[RowIndex][ColIndex];

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CWorldSquare.getValue->" + Ex;
    throw Ex;
  }

  return 0.0;
#endif
}

//**********************************************************************
// void CWorldSquare::setValue(int RowIndex, int ColIndex, double Value)
// Set Value
//**********************************************************************
void CWorldSquare::setValue(int RowIndex, int ColIndex, double Value)
{
#ifndef OPTIMIZE
  try
  {
    if (RowIndex >= iHeight)
      CError::errorGreaterThanEqualTo(PARAM_ROW_INDEX, PARAM_HEIGHT);
    if (RowIndex < 0)
      CError::errorLessThan(PARAM_ROW_INDEX, PARAM_ZERO);
    if (ColIndex >= iWidth)
      CError::errorGreaterThanEqualTo(PARAM_COLUMN_INDEX, PARAM_WIDTH);
    if (ColIndex < 0)
      CError::errorLessThan(PARAM_COLUMN_INDEX, PARAM_ZERO);
#endif

    pGrid[RowIndex][ColIndex] = Value;

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CWorldSquare.setValue->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CWorldSquare::addValue(int RowIndex, int ColIndex, double Value)
// Add Value To Our Square
//**********************************************************************
void CWorldSquare::addValue(int RowIndex, int ColIndex, double Value)
{
#ifndef OPTIMIZE
  try
  {
    if (RowIndex >= iHeight)
      CError::errorGreaterThanEqualTo(PARAM_ROW_INDEX, PARAM_HEIGHT);
    if (RowIndex < 0)
      CError::errorLessThan(PARAM_ROW_INDEX, PARAM_ZERO);
    if (ColIndex >= iWidth)
      CError::errorGreaterThanEqualTo(PARAM_COLUMN_INDEX, PARAM_WIDTH);
    if (ColIndex < 0)
      CError::errorLessThan(PARAM_COLUMN_INDEX, PARAM_ZERO);
#endif

#pragma omp atomic
    pGrid[RowIndex][ColIndex] += Value;

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CWorldSquare.addValue->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CWorldSquare::subValue(int RowIndex, int ColIndex, double Value)
// Sub Value From Our Square
//**********************************************************************
void CWorldSquare::subValue(int RowIndex, int ColIndex, double Value)
{
#ifndef OPTIMIZE
  try
  {
    if (RowIndex >= iHeight)
      CError::errorGreaterThanEqualTo(PARAM_ROW_INDEX, PARAM_HEIGHT);
    if (RowIndex < 0)
      CError::errorLessThan(PARAM_ROW_INDEX, PARAM_ZERO);
    if (ColIndex >= iWidth)
      CError::errorGreaterThanEqualTo(PARAM_COLUMN_INDEX, PARAM_WIDTH);
    if (ColIndex < 0)
      CError::errorLessThan(PARAM_COLUMN_INDEX, PARAM_ZERO);
#endif

#pragma omp atomic
    pGrid[RowIndex][ColIndex] -= Value;

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CWorldSquare.subValue->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// double CWorldSquare::getAbundance()
// get Population for this square
//**********************************************************************
double CWorldSquare::getAbundance()
{
  // Variables
  double dRet = 0.0;

#ifndef OPTIMIZE
  try
  {
#endif

    // Loop Through Grid
    for (int i = 0; i < iHeight; ++i)
      for (int j = 0; j < iWidth; ++j)
        dRet += pGrid[i][j];

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CWorldSquare.getAbundance()->" + Ex;
    throw Ex;
  }
#endif

  return dRet;
}

//**********************************************************************
// double CWorldSquare::getAbundanceForAge(int AgeIndex)
// Get Population for Age across all categories
//**********************************************************************
double CWorldSquare::getAbundanceForAge(int AgeIndex)
{
  // Variables
  double dRet = 0.0;

#ifndef OPTIMIZE
  try
  {
    if (AgeIndex > iWidth)
      CError::errorGreaterThan(PARAM_AGE_INDEX, PARAM_WIDTH);
    if (AgeIndex < 0)
      CError::errorLessThan(PARAM_AGE_INDEX, PARAM_WIDTH);
#endif

    for (int i = 0; i < iHeight; ++i)
      dRet += pGrid[i][AgeIndex];

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CWorldSquare.getAbundanceForAge()->" + Ex;
    throw Ex;
  }
#endif

  return dRet;
}

//**********************************************************************
// double CWorldSquare::getAbundanceInCategoryForAge(int AgeIndex, int CategoryIndex)
// Get Population for an Age and Category
//**********************************************************************
double CWorldSquare::getAbundanceInCategoryForAge(int AgeIndex, int CategoryIndex)
{
  // Variables
  double dRet = 0.0;

#ifndef OPTIMIZE
  try
  {
    if (AgeIndex > iWidth)
      CError::errorGreaterThan(PARAM_AGE_INDEX, PARAM_WIDTH);
    if (AgeIndex < 0)
      CError::errorLessThan(PARAM_AGE_INDEX, PARAM_ZERO);
    if (CategoryIndex > iHeight)
      CError::errorGreaterThan(PARAM_CATEGORY_INDEX, PARAM_HEIGHT);
    if (CategoryIndex < 0)
      CError::errorLessThan(PARAM_CATEGORY_INDEX, PARAM_ZERO);
#endif

    dRet = pGrid[CategoryIndex][AgeIndex];

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CWorldSquare.getAbundanceInCategoryForAge()->" + Ex;
    throw Ex;
  }
#endif

  return dRet;
}

//**********************************************************************
// double CWorldSquare::getAbundanceForCategory(int CategoryIndex)
// Get Population for a Category
//**********************************************************************
double CWorldSquare::getAbundanceForCategory(int CategoryIndex)
{
  // Variables
  double dRet = 0.0;

#ifndef OPTIMIZE
  try
  {
    if (CategoryIndex > iHeight)
      CError::errorGreaterThan(PARAM_CATEGORY_INDEX, PARAM_HEIGHT);
    if (CategoryIndex < 0)
      CError::errorLessThan(PARAM_CATEGORY_INDEX, PARAM_ZERO);
#endif

    for (int i = 0; i < iWidth; ++i)
      dRet += pGrid[CategoryIndex][i];

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CWorldSquare.getAbundanceForCategory()->" + Ex;
    throw Ex;
  }
#endif

  return dRet;
}

//**********************************************************************
// void CWorldSquare::loadDummyData()
// Populate the square with Random dummy data for testing
//**********************************************************************
void CWorldSquare::loadDummyData()
{

  // Set up Seed
  static int iTime = time(0);
  srand(iTime);
  iTime += rand() % 696;

  for (int i = 0; i < iHeight; ++i)
  {
    for (int j = 0; j < iWidth; ++j)
    {
      pGrid[i][j] = 100;
      //pGrid[i][j] = rand() % 20 + 1;
    }
  }
}

//**********************************************************************
// void CWorldSquare::build()
// Build
//**********************************************************************
void CWorldSquare::build()
{
#ifndef OPTIMIZE
  try
  {
#endif

    // Get our Values From World
    CWorld *pWorld = CWorld::Instance();
    iNumberOfCategories = pWorld->getCategoryCount();
    iMinAge = pWorld->getMinAge();
    iMaxAge = pWorld->getMaxAge();
    bAgePlus = pWorld->getAgePlusGroup();

#ifndef OPTIMIZE
    if (iNumberOfCategories <= 0)
      CError::errorMissing(PARAM_CATEGORIES);
    if (iMinAge < 0)
      CError::errorMissing(PARAM_MIN_AGE);
    if (iMaxAge <= 0)
      CError::errorMissing(PARAM_MAX_AGE);
    if (iMaxAge < iMinAge)
      CError::errorLessThan(PARAM_MAX_AGE, PARAM_MIN_AGE);
#endif

    // Build our Grid
    iHeight = iNumberOfCategories;
    iWidth = (iMaxAge + 1) - iMinAge;

    pGrid = new double *[iHeight];
    for (int i = 0; i < iHeight; ++i)
      pGrid[i] = new double[iWidth];

    // Zero it
    zeroGrid();

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CWorldSquare.build()->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CWorldSquare::~CWorldSquare()
// Default De-Constructor
//**********************************************************************
CWorldSquare::~CWorldSquare()
{
  // Clean Our Grid
  if (pGrid != 0)
  {
    for (int i = 0; i < iHeight; ++i)
    {
      delete[] pGrid[i];
      pGrid[i] = 0;
    }
    delete[] pGrid;
  }
}
