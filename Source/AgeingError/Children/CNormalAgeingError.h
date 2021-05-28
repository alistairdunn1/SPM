//============================================================================
// Name        : CNormalAgeingError.h
// Author      : S.Rasmussen
// Date        : 18/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CNORMALAGEINGERROR_H_
#define CNORMALAGEINGERROR_H_

// Local headers
#include "../CAgeingError.h"

//**********************************************************************
//
//
//**********************************************************************
class CNormalAgeingError : public CAgeingError {
public:
  // Functions
  CNormalAgeingError();
  virtual ~CNormalAgeingError();
  CAgeingError* clone() { return new CNormalAgeingError(*this); }
  void          validate();
  void          build();
  void          rebuild();
  void          getExpected(vector<double>& expected);

protected:
  double dCV;
  int    iK;
};

#endif /* CNORMALAGEINGERROR_H_ */
