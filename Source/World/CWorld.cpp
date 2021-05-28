//============================================================================
// Name        : CWorld.cpp
// Author      : S.Rasmussen
// Date        : 3/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description : << See CWorld.h >>
// $Date$
//============================================================================

// Global headers
#include <iostream>

// Local Headers
#include "../AgeSize/CAgeSize.h"
#include "../AgeSize/CAgeSizeManager.h"
#include "../Helpers/CError.h"
#include "../Helpers/DefinedValues.h"
#include "../Helpers/ForEach.h"
#include "../InitializationPhases/CInitializationPhaseManager.h"
#include "../Layers/CLayerManager.h"
#include "../Layers/Numeric/Base/CNumericLayer.h"
#include "../TimeSteps/CTimeStepManager.h"
#include "CWorld.h"
#include "CWorldSquare.h"

// Using
using std::cout;
using std::endl;

// Singleton Var
boost::thread_specific_ptr<CWorld> CWorld::clInstance;

//**********************************************************************
// CWorld::CWorld()
// Default Constructor
//**********************************************************************
CWorld::CWorld() {
  // Set Default Variable Values
  pGrid               = 0;
  pDifferenceGrid     = 0;
  iWidth              = 0;
  iHeight             = 0;
  dCellLength         = 0;
  sBaseLayer          = "";
  pBaseLayer          = 0;
  iEnabledSquareCount = 0;

  // Register user defined variables
  pParameterList->registerAllowed(PARAM_CELL_LENGTH);
  pParameterList->registerAllowed(PARAM_NROWS);
  pParameterList->registerAllowed(PARAM_NCOLS);
  pParameterList->registerAllowed(PARAM_LAYER);
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_MIN_AGE);
  pParameterList->registerAllowed(PARAM_MAX_AGE);
  pParameterList->registerAllowed(PARAM_AGE_PLUS_GROUP);
  pParameterList->registerAllowed(PARAM_INITIALIZATION_PHASES);
  pParameterList->registerAllowed(PARAM_INITIAL_YEAR);
  pParameterList->registerAllowed(PARAM_CURRENT_YEAR);
  // pParameterList->registerAllowed(PARAM_FINAL_YEAR);
  pParameterList->registerAllowed(PARAM_TIME_STEPS);
  pParameterList->registerAllowed(PARAM_AGE_SIZE);
}

//**********************************************************************
// CWorld* CWorld::Instance()
// Instance Method - Singleton
//**********************************************************************
CWorld* CWorld::Instance() {
  if (clInstance.get() == 0) {
    clInstance.reset(new CWorld());
  }
  return clInstance.get();
}

//**********************************************************************
// void CWorld::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CWorld::Destroy() {
  if (clInstance.get() != 0) {
    clInstance.reset();
  }
}

//**********************************************************************
// void CWorld::clone(CWorld *World)
// Clone our World
//**********************************************************************
void CWorld::clone(CWorld* World) {
  try {
    iWidth      = World->getWidth();
    iHeight     = World->getHeight();
    dCellLength = World->getCellLength();
    sBaseLayer  = World->getBaseLayer();
  } catch (string& Ex) {
    Ex = "CWorld.clone()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CWorld::validateWorld()
// Validate The World
//**********************************************************************
void CWorld::validate() {
  try {
    // Check our parameters
    pParameterList->checkInvalidParameters();

    // Load our Variable values
    dCellLength   = pParameterList->getDouble(PARAM_CELL_LENGTH, true, 1.0);
    iHeight       = pParameterList->getInt(PARAM_NROWS);
    iWidth        = pParameterList->getInt(PARAM_NCOLS);
    sBaseLayer    = pParameterList->getString(PARAM_LAYER);
    iMinAge       = pParameterList->getInt(PARAM_MIN_AGE);
    iMaxAge       = pParameterList->getInt(PARAM_MAX_AGE);
    bAgePlusGroup = pParameterList->getBool(PARAM_AGE_PLUS_GROUP, true, true);
    iInitialYear  = pParameterList->getInt(PARAM_INITIAL_YEAR);
    iCurrentYear  = pParameterList->getInt(PARAM_CURRENT_YEAR);
    //  iFinalYear        = pParameterList->getInt(PARAM_FINAL_YEAR);

    pParameterList->fillVector(vCategories, PARAM_CATEGORIES);
    pParameterList->fillVector(vInitializationPhases, PARAM_INITIALIZATION_PHASES, true);
    pParameterList->fillVector(vTimeSteps, PARAM_TIME_STEPS);
    pParameterList->fillVector(vAgeSizeList, PARAM_AGE_SIZE);

    // Validation
    if (iHeight > 1000)
      CError::errorGreaterThan(PARAM_NROWS, PARAM_ONE_THOUSAND);
    if (iWidth > 1000)
      CError::errorGreaterThan(PARAM_NCOLS, PARAM_ONE_THOUSAND);
    if (iCurrentYear < iInitialYear)
      CError::errorLessThan(PARAM_CURRENT_YEAR, PARAM_INITIAL_YEAR);
    if (dCellLength <= ZERO)
      CError::errorLessThan(PARAM_CELL_LENGTH, PARAM_ZERO);
    if (vAgeSizeList.size() != vCategories.size())
      CError::errorNotEqual(PARAM_AGE_SIZE, PARAM_CATEGORIES);
  } catch (string& Ex) {
    Ex = "CWorld.validateWorld->" + Ex;
    throw Ex;
  }
}
//**********************************************************************
// void CWorld::buildWorld()
// Build our World
//**********************************************************************
void CWorld::build() {
  try {
    // Load TimeStep Order
    CTimeStepManager* pTimeStepManager = CTimeStepManager::Instance();
    pTimeStepManager->setTimeStepOrder(vTimeSteps);

    // Load Initialization Phase Order
    CInitializationPhaseManager* pInitialManager = CInitializationPhaseManager::Instance();
    pInitialManager->loadInitializationPhaseOrder(vInitializationPhases);

    if (pGrid == 0) {
      // Allocate Space for our X (Height)
      pGrid = new CWorldSquare*[iHeight];
      for (int i = 0; i < iHeight; ++i) {
        pGrid[i] = new CWorldSquare[iWidth];
      }

      // Allocate Our Difference Grid
      pDifferenceGrid = new CWorldSquare*[iHeight];
      for (int i = 0; i < iHeight; ++i) {
        pDifferenceGrid[i] = new CWorldSquare[iWidth];
      }

      // Set Variables (Can't do it above. Stupid blah ISO C++)
      for (int i = 0; i < iHeight; ++i) {
        for (int j = 0; j < iWidth; ++j) {
          pGrid[i][j].build();
          pDifferenceGrid[i][j].build();
        }
      }
    }

    if (pBaseLayer == 0) {
      // Get Our Base Layer
      CLayerManager* pLayerManager = CLayerManager::Instance();
      pBaseLayer                   = pLayerManager->getNumericLayer(getBaseLayer());

      if (pBaseLayer->getLayerType() == PARAM_META_NUMERIC) {
        throw string("The base layer (" + sBaseLayer + ") cannot be a meta-layer");
      }

      // Set Enabled Square Count
      iEnabledSquareCount = iHeight * iWidth;

      // Flag any as Disabled if they don't match our Base_Layer
      for (int i = 0; i < iHeight; ++i) {
        for (int j = 0; j < iWidth; ++j) {
          if (pBaseLayer->getValue(i, j) == 0) {
            pGrid[i][j].setEnabled(false);
            iEnabledSquareCount--;
          } else if (pBaseLayer->getValue(i, j) < 0) {
            throw string(ERROR_NEGATIVE_BASE_LAYER);
          } else
            pGrid[i][j].setArea(pBaseLayer->getValue(i, j));
        }
      }

      if (iEnabledSquareCount <= 0)
        throw string(ERROR_VALID_SQUARES_WITH_LAYER);
    }

    // Build our AgeSize object
    foreach (string label, vAgeSizeList) { vAgeSizeIndex.push_back(CAgeSizeManager::Instance()->getAgeSize(label)); }
  } catch (string& Ex) {
    Ex = "CWorld.buildWorld()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CWorld::rebuild()
// Rebuild our World
//**********************************************************************
void CWorld::rebuild() {
  // Clear the Grid
  zeroGrid();
}

//**********************************************************************
// void CWorld::fillCategoryVector(vector<int> &list, vector<string> &names)
// Fill A Vector with Category Indexes.
//**********************************************************************
void CWorld::fillCategoryVector(vector<int>& list, vector<string>& names) {
  list.clear();

  foreach (string Name, names) { list.push_back(getCategoryIndexForName(Name)); }
}

//**********************************************************************
// CWorldSquare* CWorld::getBaseSquare(int RowIndex, int ColIndex)
// Get a square from our Base Grid
//**********************************************************************
CWorldSquare* CWorld::getBaseSquare(int RowIndex, int ColIndex) {
#ifndef OPTIMIZE
  try {
    if (RowIndex >= iHeight)
      CError::errorGreaterThanEqualTo(PARAM_ROW_INDEX, PARAM_HEIGHT);
    if (ColIndex >= iWidth)
      CError::errorGreaterThanEqualTo(PARAM_COLUMN_INDEX, PARAM_WIDTH);
#endif
    CWorldSquare* pPtr = dynamic_cast<CWorldSquare*>(&pGrid[RowIndex][ColIndex]);
    if (pPtr == 0)
      throw string(ERROR_BAD_CAST_WOLD_SQUARE);

    return pPtr;
#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CWorld.getBaseSquare()->" + Ex;
    throw Ex;
  }

  return 0;
#endif
}
//**********************************************************************
// CWorldSquare* CWorld::getDifferenceSquare(int RowIndex, int ColIndex)
// Get a square from our Difference Grid
//**********************************************************************
CWorldSquare* CWorld::getDifferenceSquare(int RowIndex, int ColIndex) {
#ifndef OPTIMIZE
  try {
    if (RowIndex >= iHeight)
      CError::errorGreaterThanEqualTo(PARAM_ROW_INDEX, PARAM_HEIGHT);
    if (ColIndex >= iWidth)
      CError::errorGreaterThanEqualTo(PARAM_COLUMN_INDEX, PARAM_WIDTH);
#endif

    return &pDifferenceGrid[RowIndex][ColIndex];

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CWorld.getDifferenceSquare()->" + Ex;
    throw Ex;
  }

  return 0;
#endif
}

//**********************************************************************
// int CWorld::getCategoryIndexForName(string Name)
//
//**********************************************************************
int CWorld::getCategoryIndexForName(string Name) {
  try {
    // Validate
    for (int i = 0; i < (int)vCategories.size(); ++i) {
      if (vCategories[i] == Name)
        return i;
    }

    CError::errorUnknown(PARAM_CATEGORY, Name);
  } catch (string& Ex) {
    Ex = "CWorld.getCategoryNameForIndex()->" + Ex;
    throw Ex;
  }

  return -1;
}

//**********************************************************************
// CWorldSquare* CWorld::getMeanWeight(int AgeIndex, int CategoryIndex)
// Get a square from our Difference Grid
//**********************************************************************
double CWorld::getMeanWeight(int AgeIndex, int CategoryIndex) {
  double dAge    = (double)(AgeIndex + iMinAge);
  double dWeight = vAgeSizeIndex[CategoryIndex]->getMeanWeight(dAge);
  return dWeight;
}

//**********************************************************************
// CWorldSquare* CWorld::getLengthFreqency(int AgeIndex, int CategoryIndex, vector<double> LengthBins)
// Get a square from our Difference Grid
//**********************************************************************
vector<double> CWorld::getLengthFrequency(int AgeIndex, int CategoryIndex, vector<double>& LengthBins) {
  double         dAge = (double)(AgeIndex + iMinAge);
  vector<double> expected;
  for (int i = 0; i < ((int)LengthBins.size() - 1); ++i) {
    double dProportion = vAgeSizeIndex[CategoryIndex]->getProportionInLengthBin(dAge, LengthBins[i], LengthBins[i + 1]);
    expected.push_back(dProportion);
  }
  return (expected);
}

//**********************************************************************
// string CWorld::getCategoryNameForIndex(int Index)
//
//**********************************************************************
string CWorld::getCategoryNameForIndex(int Index) {
  return vCategories[Index];
}

//**********************************************************************
// int CWorld::getColIndexForAge(int Age)
//
//**********************************************************************
int CWorld::getColIndexForAge(int Age) {
  return (Age - iMinAge);
}

//**********************************************************************
// string CWorld::getInitializationPhase(int index)
//
//**********************************************************************
string CWorld::getInitializationPhase(int index) {
  return vInitializationPhases[index];
}

//**********************************************************************
// void CWorld::mergeDifferenceGrid()
// Merge Difference Grid onto our Main Grid
//**********************************************************************
void CWorld::mergeDifferenceGrid() {
#ifndef OPTIMIZE
  try {
#endif
    for (int i = 0; i < iHeight; ++i)
      for (int j = 0; j < iWidth; ++j) {
        pGrid[i][j].makeAdjustments(&pDifferenceGrid[i][j]);
        pDifferenceGrid[i][j].zeroGrid();
      }
#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CWorld.mergeDifferenceGrid->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CWorld::zeroGrid()
// Reset the WorldGrid To 0
//**********************************************************************
void CWorld::zeroGrid() {
#ifndef OPTIMIZE
  try {
#endif

    // Zero our Grid
    for (int i = 0; i < iHeight; ++i)
      for (int j = 0; j < iWidth; ++j) pGrid[i][j].zeroGrid();

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CWorld.zeroGrid()->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CWorld::debugToScreen()
// Debug the World To Screen
//**********************************************************************
void CWorld::debugToScreen() {
  //
  //  for (int i = 0; i < iHeight; ++i) {
  //    for (int j = 0; j < iWidth; ++j) {
  //      CWorldSquare *pS = &pGrid[i][j];
  //
  //      cout << "Cat: ";
  //      for (int k = 0; k < vCategories.size(); ++k) {
  //        for (int L = 0; L < (iMaxAge+1)-iMinAge; ++L)
  //          cout << pS->getValue(k, L) << " ";
  //        cout << endl;
  //      }
  //      cout << "----------------" << endl;
  //    }
  //  }
}

//**********************************************************************
// CWorld::~CWorld()
// Default De-Constructor
//**********************************************************************
CWorld::~CWorld() {
  // Clean Our DifferenceGrid
  if (pDifferenceGrid != 0) {
    for (int i = 0; i < iHeight; ++i) {
      delete[] pDifferenceGrid[i];
      pDifferenceGrid[i] = 0;
    }
    delete[] pDifferenceGrid;
  }

  // Clean Our Grid
  if (pGrid != 0) {
    for (int i = 0; i < iHeight; ++i) {
      delete[] pGrid[i];
      pGrid[i] = 0;
    }
    delete[] pGrid;
  }
}
