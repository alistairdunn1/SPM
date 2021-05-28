//============================================================================
// Name        : CInverseLogisticSelectivity.h
// Author      : A.Dunn
// Date        : 15/03/2012
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
//============================================================================
#ifndef CINVERSELOGISTICSELECTIVITY_H_
#define CINVERSELOGISTICSELECTIVITY_H_

// Local Headers
#include "Base/CCachedSelectivity.h"

//**********************************************************************
//
//
//**********************************************************************
class CInverseLogisticSelectivity : public CCachedSelectivity {
public:
  // Functions
  CInverseLogisticSelectivity();
  virtual ~CInverseLogisticSelectivity();
  CSelectivity* clone() { return new CInverseLogisticSelectivity(*this); }
  void          validate();

protected:
  // Functions
  double calculateResult(int Age);

  // Variables
  double dA50;
  double dAto95;
  double dAlpha;
};

#endif /*CINVERSELOGISTICSELECTIVITY_H_*/
