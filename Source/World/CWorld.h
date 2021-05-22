//============================================================================
// Name        : CWorld.h
// Author      : S.Rasmussen
// Date        : 10/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description : This class represents our world object. The central
//    points of interest for this class are the grids and the runMode
//    calls.
//
//    The world maintains a Grid (pGrid) of WorldSquare objects. This
//    represents the current state of the world as it is now. A second
//    grid called the Drifference Grid (pDifferenceGrid) is an exact copy
//    of pGrid in dimensions, but it maintains only the difference
//    (adjustments) we need to make to the world. After each process is run
//    the difference grid is merged into the world grid to update the current
//    state.
//
//    The runMode calls allow the application entry (int main()) easy access
//    to call functions based on each run mode. The World then sets up what
//    is required to kick-off each type of run.
//
//    Note: CWorld is a singleton because we only want one ever. Multiple
//    worlds are not prohibited.
//
// $Date$
//============================================================================
#ifndef CWORLD_H_
#define CWORLD_H_

// Local Headers
#include "../BaseClasses/CBaseManager.h"

// Classes
class CWorldSquare;
class CNumericLayer;
class CAgeSize;

//**********************************************************************
//
//
//**********************************************************************
class CWorld : public CBaseManager
{
public:
  static CWorld *Instance();
  static void Destroy();

  // Functions
  void clone(CWorld *World);
  void validate();
  void build();
  void rebuild();
  void fillCategoryVector(vector<int> &list, vector<string> &names);
  int getWidth() { return iWidth; }
  int getHeight() { return iHeight; }
  double getCellLength() { return dCellLength; }
  string getBaseLayer() { return sBaseLayer; }
  int getMinAge() { return iMinAge; }
  int getMaxAge() { return iMaxAge; }
  int getAgeSpread() { return ((iMaxAge + 1) - iMinAge); }
  bool getAgePlusGroup() { return bAgePlusGroup; }
  int getInitialYear() { return iInitialYear; }
  int getCurrentYear() { return iCurrentYear; }
  int getTimeStepCount() { return (int)vTimeSteps.size(); }
  int getInitializationPhaseCount() { return (int)vInitializationPhases.size(); }
  int getCategoryCount() { return (int)vCategories.size(); }
  string getInitializationPhase(int index);
  CWorldSquare *getBaseSquare(int RowIndex, int ColIndex);
  CWorldSquare *getDifferenceSquare(int RowIndex, int ColIndex);
  int getEnabledSquareCount() { return iEnabledSquareCount; };
  int getCategoryIndexForName(string Name);
  string getCategoryNameForIndex(int Index);
  int getColIndexForAge(int Age);
  double getMeanWeight(int AgeIndex, int iCategoryIndex);
  vector<double> getLengthFrequency(int AgeIndex, int CategoryIndex, vector<double> &LengthBins);
  void mergeDifferenceGrid();
  void zeroGrid();
  void debugToScreen();
  virtual ~CWorld();

protected:
  // Functions
  CWorld();

  // Variables
  double dCellLength;
  int iWidth;
  int iHeight;
  string sBaseLayer;
  CNumericLayer *pBaseLayer;
  vector<string> vCategories;
  int iMinAge;
  int iMaxAge;
  bool bAgePlusGroup;
  vector<string> vInitializationPhases;
  int iInitialYear;
  int iCurrentYear;
  int iFinalYear;
  vector<string> vTimeSteps;
  CWorldSquare **pGrid;
  CWorldSquare **pDifferenceGrid;
  int iEnabledSquareCount;
  vector<string> vAgeSizeList;
  vector<CAgeSize *> vAgeSizeIndex;

private:
  static boost::thread_specific_ptr<CWorld> clInstance;
};

#endif /*CWORLD_H_*/
