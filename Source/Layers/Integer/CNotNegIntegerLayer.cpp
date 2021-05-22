//============================================================================
// Name        : CNotNegIntegerLayer.cpp
// Author      : S.Mormede
// Date        : 07/02/2018
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Global Headers
#include <iostream>
#include <boost/lexical_cast.hpp>

// Local Includes
#include "CNotNegIntegerLayer.h"
#include "../../World/CWorld.h"
#include "../../World/CWorldSquare.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CComparer.h"
#include "../../Helpers/CConvertor.h"

// Namespace
using std::cout;
using std::endl;

//**********************************************************************
// CNotNegIntegerLayer::CNotNegIntegerLayer()
// Default Constructor
//**********************************************************************
CNotNegIntegerLayer::CNotNegIntegerLayer()
{

  sType = PARAM_NOT_NEG_INT;

  // Register Allowed Parameters
  pParameterList->registerAllowed(PARAM_DATA);
}

//**********************************************************************
// int CNotNegIntegerLayer::getValue(int RowIndex, int ColIndex, int TargetRow=0, int TargetCol=0)
// Get Value From Our Layer
//**********************************************************************
int CNotNegIntegerLayer::getValue(int RowIndex, int ColIndex, int TargetRow = 0, int TargetCol = 0)
{
#ifndef OPTIMIZE
  try
  {
    // Check
    if (RowIndex >= iHeight)
      CError::errorGreaterThanEqualTo(PARAM_ROW_INDEX, PARAM_LAYER_HEIGHT);
    if (ColIndex >= iWidth)
      CError::errorGreaterThanEqualTo(PARAM_COLUMN_INDEX, PARAM_LAYER_WIDTH);
    if (RowIndex < 0)
      CError::errorLessThanEqualTo(PARAM_ROW, PARAM_ZERO);
    if (ColIndex < 0)
      CError::errorLessThanEqualTo(PARAM_COLUMN, PARAM_ZERO);
  }
  catch (string &Ex)
  {
    Ex = "CNotNegIntegerLayer.getValue(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return pGrid[RowIndex][ColIndex];
}

//**********************************************************************
// void CNotNegIntegerLayer::addValue(int RowIndex, int ColIndex, int Value)
// Add Value to our Grid
//**********************************************************************
void CNotNegIntegerLayer::setValue(int RowIndex, int ColIndex, int Value)
{
#ifndef OPTIMIZE
  try
  {
    if (RowIndex >= iHeight)
      CError::errorGreaterThanEqualTo(PARAM_ROW, PARAM_LAYER_HEIGHT);
    if (ColIndex >= iWidth)
      CError::errorGreaterThanEqualTo(PARAM_COLUMN, PARAM_LAYER_WIDTH);
    if (RowIndex < 0)
      CError::errorLessThanEqualTo(PARAM_ROW, PARAM_ZERO);
    if (ColIndex < 0)
      CError::errorLessThanEqualTo(PARAM_COLUMN, PARAM_ZERO);
  }
  catch (string &Ex)
  {
    Ex = "CNotNegIntegerLayer.addValue()->" + Ex;
    throw Ex;
  }
#endif

  pGrid[RowIndex][ColIndex] = Value;
}

//**********************************************************************
// void CNotNegIntegerLayer::validate()
// Validate Our Layer
//**********************************************************************
void CNotNegIntegerLayer::validate()
{
  try
  {
    // Base Validate
    CIntLayer::validate();

    // Fill a new vector with our row information
    vector<string> vData;
    pParameterList->fillVector(vData, PARAM_DATA);

    int iRow = 0;
    int iCol = 0;

    for (int i = 0; i < (int)vData.size(); ++i)
    {
      if (vData[i] == PARAM_DATA)
        continue;

      // Read data and if enough on theis row, then start filling out the next row
      if (iCol >= iWidth)
      {
        iCol = 0;
        iRow++;
      }

      // Read data and if too much data, report an error
      if (iRow >= iHeight)
        CError::errorTooMuch(PARAM_DATA);

      try
      {
        // Set grid data
        pGrid[iRow][iCol] = boost::lexical_cast<int>(vData[i]);
        // register as estimable - don't do for integer values for now
        // registerEstimable(PARAM_DATA, i, &pGrid[iRow][iCol]);
      }
      catch (boost::bad_lexical_cast &)
      {
        string Ex = string("Non-integer value in layer ") + getLabel();
        throw Ex;
      }
      iCol++;
    }

    if (((iRow + 1) != iHeight) || (iCol != iWidth))
      CError::errorNotEnough(PARAM_DATA);
  }
  catch (string &Ex)
  {
    Ex = "CNotNegIntegerLayer.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// int getLayerMin();
// Get layer value min
//**********************************************************************
int CNotNegIntegerLayer::getLayerMin()
{
  try
  {

    int dMin = pGrid[0][0];

    for (int i = 0; i < iHeight; ++i)
    {
      for (int j = 0; j < iWidth; ++j)
      {
        dMin = std::min(dMin, pGrid[i][j]);
      }
    }
    // check it's positive
    if (dMin <= ZERO)
      CError::errorLessThanEqualTo(PARAM_VALUE, PARAM_ZERO);

    return (dMin);
  }
  catch (string &Ex)
  {
    Ex = "CNotNegIntegerLayer.getLayerMin(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// int getLayerMax();
// Get layer value max
//**********************************************************************
int CNotNegIntegerLayer::getLayerMax()
{
  try
  {

    int dMax = pGrid[0][0];

    for (int i = 0; i < iHeight; ++i)
    {
      for (int j = 0; j < iWidth; ++j)
      {
        dMax = std::max(dMax, pGrid[i][j]);
      }
    }

    return (dMax);
  }
  catch (string &Ex)
  {
    Ex = "CNotNegIntegerLayer.getLayerMax(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CNotNegIntegerLayer::build()
// Build our layer
//**********************************************************************
void CNotNegIntegerLayer::build()
{
  try
  {
    for (int i = 0; i < iHeight; ++i)
    {
      for (int j = 0; j < iWidth; ++j)
      {
        pGrid[i][j] = pGrid[i][j];
      }
    }
  }
  catch (string &Ex)
  {
    Ex = "CNotNegIntegerLayer.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CNotNegIntegerLayer::~CNotNegIntegerLayer()
// Default De-Constructor
//**********************************************************************
CNotNegIntegerLayer::~CNotNegIntegerLayer()
{
}
