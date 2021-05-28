//============================================================================
// Name        : CPenaltyFactory.h
// Author      : S.Rasmussen
// Date        : 12/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CPENALTYFACTORY_H_
#define CPENALTYFACTORY_H_

// Global headers
#include <string>

// Local headers
#include "../CPenalty.h"

// Using
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CPenaltyFactory {
public:
  // Functions
  static CPenalty* buildPenalty(string type, bool registerWithManager = true);

private:
  // Functions
  CPenaltyFactory();
  virtual ~CPenaltyFactory();
};

#endif /* CPENALTYFACTORY_H_ */
