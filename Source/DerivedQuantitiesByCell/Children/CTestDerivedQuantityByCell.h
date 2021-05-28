//============================================================================
// Name        : CSampleDerivedQuantityByCell.h
// Author      : S.Rasmussen
// Date        : 15/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
//============================================================================
#ifndef CTESTDERIVEDQUANTITYBYCELL_H_
#define CTESTDERIVEDQUANTITYBYCELL_H_

#include "../CDerivedQuantityByCell.h"

//**********************************************************************
//
//
//**********************************************************************
class CTestDerivedQuantityByCell : public CDerivedQuantityByCell {
public:
  CTestDerivedQuantityByCell();
  virtual ~CTestDerivedQuantityByCell();
  void calculate();
  void calculate(int initialisationPhase);
  void build(){};
};

#endif /* CTESTDERIVEDQUANTITYBYCELL_H_ */
