//============================================================================
// Name        : CIntLayer.cpp
// Author      : S. Mormede
// Date        : 07/02/2018
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global Headers
#include <iostream>

// Local Headers
#include "CIntLayer.h"
#include "../../../Helpers/CComparer.h"
#include "../../../Helpers/CError.h"

// Using
using std::cout;
using std::endl;

//**********************************************************************
// CIntLayer::CIntLayer();
// Default Constructor
//**********************************************************************
CIntLayer::CIntLayer()
{

  // Default Variables
  sType = "";
  pGrid = 0;
}

//**********************************************************************
// void CIntLayer::setValue(int X, int Y, int Value)
// Default Set Value
//**********************************************************************
void CIntLayer::setValue(int X, int Y, int Value)
{
  try
  {
    CError::errorSupported(PARAM_FUNCTION);
  }
  catch (string &Ex)
  {
    Ex = "CIntLayer.setValue(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// int CIntLayer::countValidSpaces()
// count Valid Spaces
//**********************************************************************
int CIntLayer::countValidSpaces()
{

  int iValidSquares = 0;

  // Loop Through World
  for (int i = 0; i < iHeight; ++i)
  {
    for (int j = 0; j < iWidth; ++j)
    {
      // Check if Space is disabled on World first
      if (!pWorld->getBaseSquare(i, j)->getEnabled())
        continue;

      iValidSquares++;
    }
  }

  return iValidSquares;
}

//**********************************************************************
// void CIntLayer::validate()
// validate
//**********************************************************************
void CIntLayer::validate()
{
  try
  {
    // Base Validate
    CLayer::validate();

    // Allocate Space for our X (Width)
    pGrid = new int *[iHeight];
    for (int i = 0; i < iHeight; ++i)
      pGrid[i] = new int[iWidth];
  }
  catch (string &Ex)
  {
    Ex = "CIntLayer.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CIntLayer::~CIntLayer()
// Default De-Constructor
//**********************************************************************
CIntLayer::~CIntLayer()
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
