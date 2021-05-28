//============================================================================
// Name        : CDerivedQuantity.cpp
// Author      : S.Rasmussen
// Date        : 15/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global headers
#include <iostream>

// Local headers
#include "CDerivedQuantity.h"

//**********************************************************************
// CDerivedQuantity::CDerivedQuantity()
// Default Constructor
//**********************************************************************
CDerivedQuantity::CDerivedQuantity() : iCurrentInitialisationPhase(0) {}

//**********************************************************************
// CDerivedQuantity::~CDerivedQuantity()
// Destructor
//**********************************************************************
CDerivedQuantity::~CDerivedQuantity() {}

//**********************************************************************
// double CDerivedQuantity::getValue(int offset)
// Get Value From our Derived Quantity
//**********************************************************************
double CDerivedQuantity::getValue(int offset) {
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
    return 0.0;

  /**
   * Since we don't have any values that are not in the initialisation stage
   * or we've crossed because the offset was too large we need to start working
   * backwards through the initialisation values
   */
  vector<vector<double>>::reverse_iterator vvIter;
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
