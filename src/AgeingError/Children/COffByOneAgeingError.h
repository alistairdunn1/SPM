//============================================================================
// Name        : COffByOneAgeingError.h
// Author      : S.Rasmussen
// Date        : 18/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef COFFBYONEAGEINGERROR_H_
#define COFFBYONEAGEINGERROR_H_

#include "../CAgeingError.h"

//**********************************************************************
//
//
//**********************************************************************
class COffByOneAgeingError: public CAgeingError {
public:
  // Functions
  COffByOneAgeingError();
  virtual                     ~COffByOneAgeingError();
};

#endif /* COFFBYONEAGEINGERROR_H_ */