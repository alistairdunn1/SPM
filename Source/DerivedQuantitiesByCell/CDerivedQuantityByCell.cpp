//============================================================================
// Name        : CDerivedQuantityByCell.cpp
// Author      : S.Rasmussen
// Date        : 15/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
//============================================================================

// Global headers
#include <iostream>

// Local headers
#include "CDerivedQuantityByCell.h"

//**********************************************************************
// CDerivedQuantityByCell::CDerivedQuantityByCell()
// Default Constructor
//**********************************************************************
CDerivedQuantityByCell::CDerivedQuantityByCell() : iCurrentInitialisationPhase(0) {}

//**********************************************************************
// CDerivedQuantityByCell::~CDerivedQuantityByCell()
// Destructor
//**********************************************************************
CDerivedQuantityByCell::~CDerivedQuantityByCell() {}

//**********************************************************************
// vector<vector<double> > CDerivedQuantityByCell::getValue(int offset)
// Get Value From our Derived Layer
//**********************************************************************
vector<vector<double>> CDerivedQuantityByCell::getValue(int offset) {
  int phasesCrossed = 0;

  if (vValues.size() > 0) {
    if (offset >= (int)vValues.size()) {
      offset -= vValues.size();
      phasesCrossed = 1;
    } else {
      return vValues[vValues.size() - (offset + 1)];
    }
  }

  /**
   * If we have no values at all, return 0.0
   */
  if (vvInitialisationValues.size() == 0)
    return vBlankData;

  /**
   * Since we don't have any values that are not in the initialisation stage
   * or we've crossed because the offset was too large we need to start working
   * backwards through the initialisation values
   */
  vector<vector<Data>>::reverse_iterator vvIter;
  for (vvIter = vvInitialisationValues.rbegin(); vvIter != vvInitialisationValues.rend(); ++vvIter) {
    if (offset >= (int)vvIter->size()) {
      /**
       * If we have already crossed a phase then we want to return the first element
       * of the new phase, we cannot ever cross more than 1 phase
       */
      if (phasesCrossed == 1) {
        return (*vvIter->begin());
      } else {
        offset -= vvIter->size();
        phasesCrossed = 1;
      }
    } else {
      return vvIter->at(vvIter->size() - (offset + 1));
    }
  }

  /**
   * Return the first value
   */

  return *vvInitialisationValues.begin()->begin();
}

//**********************************************************************
// double CDerivedQuantityByCell::getValue(int offset, int RowIndex, int ColIndex)
// Get Value From our Derived Layer
//**********************************************************************
double CDerivedQuantityByCell::getValue(int offset, int RowIndex, int ColIndex) {
  int phasesCrossed = 0;

  if (vValues.size() > 0) {
    if (offset >= (int)vValues.size()) {
      offset -= vValues.size();
      phasesCrossed = 1;
    } else {
      return vValues[vValues.size() - (offset + 1)][RowIndex][ColIndex];
    }
  }

  /**
   * If we have no values at all, return 0.0
   */
  if (vvInitialisationValues.size() == 0)
    return 0.0;

  /**
   * Since we don't have any values that are not in the initialisation stage
   * or we've crossed because the offset was too large we need to start working
   * backwards through the initialisation values
   */
  vector<vector<Data>>::reverse_iterator vvIter;
  for (vvIter = vvInitialisationValues.rbegin(); vvIter != vvInitialisationValues.rend(); ++vvIter) {
    if (offset >= (int)vvIter->size()) {
      /**
       * If we have already crossed a phase then we want to return the first element
       * of the new phase, we cannot ever cross more than 1 phase
       */
      if (phasesCrossed == 1) {
        return ((*vvIter->begin())[RowIndex][ColIndex]);
      } else {
        offset -= vvIter->size();
        phasesCrossed = 1;
      }
    } else {
      return (vvIter->at(vvIter->size() - (offset + 1)))[RowIndex][ColIndex];
    }
  }

  /**
   * Return the first value
   */

  return (*vvInitialisationValues.begin()->begin())[RowIndex][ColIndex];
}

//**********************************************************************
// void CDerivedQuantityByCell::rebuild()
// Rebuild our derived layer
//**********************************************************************
void CDerivedQuantityByCell::build() {
  // We have to build the blank data object to return when we haven't yet
  // built some data during the initialisation phases
  iHeight = pWorld->getHeight();
  iWidth  = pWorld->getWidth();

  vBlankData.resize(iHeight);
  for (int i = 0; i < iHeight; ++i) vBlankData[i].assign(iWidth, 0.0);
}

//**********************************************************************
// void CDerivedQuantityByCell::rebuild()
// Rebuild our derived layer
//**********************************************************************
void CDerivedQuantityByCell::rebuild() {
  iCurrentInitialisationPhase = 0;
  vvInitialisationValues.clear();
  vValues.clear();
}
