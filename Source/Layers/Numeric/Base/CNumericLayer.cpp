//============================================================================
// Name        : CNumericLayer.cpp
// Author      : S.Rasmussen
// Date        : 1/04/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global Headers
#include <iostream>

// Local Headers
#include "../../../Helpers/CComparer.h"
#include "../../../Helpers/CError.h"
#include "CNumericLayer.h"

// Using
using std::cout;
using std::endl;

//**********************************************************************
// CNumericLayer::CNumericLayer();
// Default Constructor
//**********************************************************************
CNumericLayer::CNumericLayer() {
  // Default Variables
  sType = "";
  pGrid = 0;
}

//**********************************************************************
// void CNumericLayer::setValue(int X, int Y, double Value)
// Default Set Value
//**********************************************************************
void CNumericLayer::setValue(int X, int Y, double Value) {
  try {
    CError::errorSupported(PARAM_FUNCTION);
  } catch (string& Ex) {
    Ex = "CNumericLayer.setValue(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// int CNumericLayer::countValidSpaces()
// count Valid Spaces
//**********************************************************************
int CNumericLayer::countValidSpaces() {
  int iValidSquares = 0;

  // Loop Through World
  for (int i = 0; i < iHeight; ++i) {
    for (int j = 0; j < iWidth; ++j) {
      // Check if Space is disabled on World first
      if (!pWorld->getBaseSquare(i, j)->getEnabled())
        continue;

      iValidSquares++;
    }
  }

  return iValidSquares;
}

//**********************************************************************
// void CNumericLayer::validate()
// validate
//**********************************************************************
void CNumericLayer::validate() {
  try {
    // Base Validate
    CLayer::validate();

    // Allocate Space for our X (Width)
    pGrid = new double*[iHeight];
    for (int i = 0; i < iHeight; ++i) pGrid[i] = new double[iWidth];
  } catch (string& Ex) {
    Ex = "CNumericLayer.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CNumericLayer::~CNumericLayer()
// Default De-Constructor
//**********************************************************************
CNumericLayer::~CNumericLayer() {
  // Clean Our Grid
  if (pGrid != 0) {
    for (int i = 0; i < iHeight; ++i) {
      delete[] pGrid[i];
      pGrid[i] = 0;
    }
    delete[] pGrid;
  }
}
