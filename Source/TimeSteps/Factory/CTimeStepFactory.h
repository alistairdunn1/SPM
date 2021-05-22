//============================================================================
// Name        : CTimeStepFactory.h
// Author      : S.Rasmussen
// Date        : 23/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CTIMESTEPFACTORY_H_
#define CTIMESTEPFACTORY_H_

// Global headers
#include <string>

// Local headers
#include "../CTimeStep.h"

// Using
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CTimeStepFactory
{
public:
  // Functions
  static CTimeStep *buildTimeStep(string type, bool registerWithManager = true);

private:
  // Functions
  CTimeStepFactory() {}
  virtual ~CTimeStepFactory() {}
};

#endif /* CTIMESTEPFACTORY_H_ */
