//============================================================================
// Name        : CSizeWeightFactory.h
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CSIZEWEIGHTFACTORY_H_
#define CSIZEWEIGHTFACTORY_H_

// Global headers
#include <string>

// Local headers
#include "../CSizeWeight.h"

// Using
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CSizeWeightFactory {
public:
  // Functions
  static CSizeWeight* buildSizeWeight(string type, bool registerWithManager = true);

private:
  // Functions
  CSizeWeightFactory() {}
  virtual ~CSizeWeightFactory() {}
};

#endif /* CSIZEWEIGHTFACTORY_H_ */
