//============================================================================
// Name        : CObservationFactory.h
// Author      : S.Rasmussen
// Date        : 9/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef COBSERVATIONFACTORY_H_
#define COBSERVATIONFACTORY_H_

// Global headers
#include <string>

// Local headers
#include "../CObservation.h"

// Using
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CObservationFactory
{
public:
  // Functions
  static CObservation *buildObservation(string type, bool registerWithManager = true);

private:
  // Functions
  CObservationFactory();
  virtual ~CObservationFactory();
};

#endif /* COBSERVATIONFACTORY_H_ */
