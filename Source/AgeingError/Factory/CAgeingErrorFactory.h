//============================================================================
// Name        : CAgeingErrorFactory.h
// Author      : S.Rasmussen
// Date        : 18/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CAGEINGERRORFACTORY_H_
#define CAGEINGERRORFACTORY_H_

// Global headers
#include <string>

// Local headers
#include "../CAgeingError.h"

// Using
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CAgeingErrorFactory
{
public:
  // Functions
  static CAgeingError *buildAgeingError(string type, bool registerWithManager = true);

private:
  // Functions
  CAgeingErrorFactory() {}
  virtual ~CAgeingErrorFactory() {}
};

#endif /* CAGEINGERRORFACTORY_H_ */
