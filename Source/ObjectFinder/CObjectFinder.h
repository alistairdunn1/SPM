//============================================================================
// Name        : CObjectFinder.h
// Author      : S.Rasmussen
// Date        : 25/06/2012
// Copyright   : Copyright NIWA Science �2012 - www.niwa.co.nz
// Description : Unit tests for CEstimateFactory
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef COBJECTFINDER_H_
#define COBJECTFINDER_H_

// Headers
#include "../BaseClasses/CBaseObject.h"

/**
 * Class Definition: CObjectFinder
 */
class CObjectFinder {
public:
  static void         splitParameter(const string parameter, string& objectType, string& objectLabel, string& objectParameter, int& objectIndex);
  static CBaseObject* getObject(string objectAbsoluteName);
  static double*      getObjectEstimable(string estimableAbsoluteName);

private:
  // Methods
  CObjectFinder(){};
  virtual ~CObjectFinder(){};
};

#endif /* COBJECTFINDER_H_ */
