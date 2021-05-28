//============================================================================
// Name        : CStringLayer.cpp
// Author      : S.Rasmussen
// Date        : 14/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local Headers
#include "CStringLayer.h"

#include "../../Helpers/CComparer.h"
#include "../../Helpers/CConvertor.h"
#include "../../Helpers/CError.h"

//**********************************************************************
// CStringLayer::CStringLayer()
// Default Constructor
//**********************************************************************
CStringLayer::CStringLayer() {
  // Vars
  sType = PARAM_STRING;
  pGrid = 0;

  // Register user allowed variables
  pParameterList->registerAllowed(PARAM_DATA);
}

//**********************************************************************
// string CStringLayer::getValue(int RowIndex, int ColIndex)
// get Value
//**********************************************************************
string CStringLayer::getValue(int RowIndex, int ColIndex) {
#ifndef OPTIMIZE
  try {
    // Check
    if (RowIndex >= iHeight)
      CError::errorGreaterThanEqualTo(PARAM_ROW_INDEX, PARAM_LAYER_HEIGHT);
    if (ColIndex >= iWidth)
      CError::errorGreaterThanEqualTo(PARAM_COLUMN_INDEX, PARAM_LAYER_WIDTH);
  } catch (string& Ex) {
    Ex = "CStringLayer.getValue(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return pGrid[RowIndex][ColIndex];
}

//**********************************************************************
// void CStringLayer::Validate()
// Validate
//**********************************************************************
void CStringLayer::validate() {
  try {
    // Base Validate
    CLayer::validate();

    // Build 2D Array
    pGrid = new string*[iHeight];
    for (int i = 0; i < iHeight; ++i) {
      pGrid[i] = new string[iWidth];
    }

    // Fill a new vector with our row information
    vector<string> vData;

    pParameterList->fillVector(vData, PARAM_DATA);

    int iRow = 0;
    int iCol = 0;

    for (int i = 0; i < (int)vData.size(); ++i) {
      if (vData[i] == PARAM_DATA)
        continue;

      // Read data and if enough on theis row, then start filling out the next row
      if (iCol >= iWidth) {
        iCol = 0;
        iRow++;
      }

      // Read data and if too much data, report an error
      if (iRow >= iHeight)
        CError::errorTooMuch(PARAM_DATA);

      pGrid[iRow][iCol] = vData[i];
      iCol++;
    }

    if (((iRow + 1) != iHeight) || (iCol != iWidth))
      CError::errorNotEnough(PARAM_DATA);
  } catch (string& Ex) {
    Ex = "CStringLayer.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CStringLayer::~CStringLayer()
// Default De-Constructor
//**********************************************************************
CStringLayer::~CStringLayer() {
  // Clean Our Grid
  if (pGrid != 0) {
    for (int i = 0; i < iHeight; ++i) {
      delete[] pGrid[i];
      pGrid[i] = 0;
    }

    delete[] pGrid;
  }
}
