//============================================================================
// Name        : CLogisticSelectivity.h
// Author      : S.Rasmussen
// Date        : 6/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CLOGISTICSELECTIVITY_H_
#define CLOGISTICSELECTIVITY_H_

// Local Headers
#include "Base/CCachedSelectivity.h"

//**********************************************************************
//
//
//**********************************************************************
class CLogisticSelectivity : public CCachedSelectivity {
public:
  // Functions
  CLogisticSelectivity();
  virtual ~CLogisticSelectivity();
  CSelectivity* clone() { return new CLogisticSelectivity(*this); }
  void          validate();

protected:
  // Functions
  double calculateResult(int Age);

  // Variables
  double dA50;
  double dAto95;
  double dAlpha;
};

#endif /*CLOGISTICSELECTIVITY_H_*/
