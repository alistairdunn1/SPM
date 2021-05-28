//============================================================================
// Name        : CSampleDerivedQuantity.h
// Author      : S.Rasmussen
// Date        : 15/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
//============================================================================

#ifndef CTESTDERIVEDQUANTITY_H_
#define CTESTDERIVEDQUANTITY_H_

#include "../CDerivedQuantity.h"

//**********************************************************************
//
//
//**********************************************************************
class CTestDerivedQuantity : public CDerivedQuantity {
public:
  CTestDerivedQuantity();
  virtual ~CTestDerivedQuantity();
  void calculate();
  void calculate(int initialisationPhase);
  void build(){};
};

#endif /* CTESTDERIVEDQUANTITY_H_ */
