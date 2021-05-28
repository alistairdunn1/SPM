//============================================================================
// Name        : CLogisticProducingSelectivity.h
// Author      : A. Dunn
// Date        : 7/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CLogisticProducingSELECTIVITY_H_
#define CLogisticProducingSELECTIVITY_H_

// Local Headers
#include "Base/CCachedSelectivity.h"

//**********************************************************************
//
//
//**********************************************************************
class CLogisticProducingSelectivity : public CCachedSelectivity {
public:
  // Functions
  CLogisticProducingSelectivity();
  virtual ~CLogisticProducingSelectivity();
  CSelectivity* clone() { return new CLogisticProducingSelectivity(*this); }
  void          validate();

protected:
  // Functions
  double calculateResult(int Age);

  // Variables
  int    iL;
  int    iH;
  double dA50;
  double dAto95;
  double dAlpha;
};

#endif /*CLogisticProducingSELECTIVITY_H_*/
