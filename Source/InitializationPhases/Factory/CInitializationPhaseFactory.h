//============================================================================
// Name        : CInitializationPhaseFactory.h
// Author      : S.Rasmussen
// Date        : 23/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CINITIALIZATIONPHASEFACTORY_H_
#define CINITIALIZATIONPHASEFACTORY_H_

// Global headers
#include <string>

// Local headers
#include "../CInitializationPhase.h"

// Using
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CInitializationPhaseFactory
{
public:
  // Functions
  static CInitializationPhase *buildInitializationPhase(string type, bool registerWithManager = true);

private:
  // Functions
  CInitializationPhaseFactory() {}
  virtual ~CInitializationPhaseFactory() {}
};

#endif /* CINITIALIZATIONPHASEFACTORY_H_ */
