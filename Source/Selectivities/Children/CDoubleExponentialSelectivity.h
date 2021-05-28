//============================================================================
// Name        : CDoubleExponentialSelectivity.h
// Author      : S.Rasmussen
// Date        : 20/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CDOUBLEEXPONENTIALSELECTIVITY_H_
#define CDOUBLEEXPONENTIALSELECTIVITY_H_

// Local headers
#include "Base/CCachedSelectivity.h"

//**********************************************************************
//
//
//**********************************************************************
class CDoubleExponentialSelectivity : public CCachedSelectivity {
public:
  // Functions
  CDoubleExponentialSelectivity();
  virtual ~CDoubleExponentialSelectivity();
  CSelectivity* clone() { return new CDoubleExponentialSelectivity(*this); }
  void          validate();

protected:
  // Functions
  double calculateResult(int Age);

  // Variables
  double dX0;
  double dX1;
  double dX2;
  double dY0;
  double dY1;
  double dY2;
  double dAlpha;
};

#endif /* CDOUBLEEXPONENTIALSELECTIVITY_H_ */
