//============================================================================
// Name        : CNumericLayer.h
// Author      : S.Rasmussen
// Date        : 1/04/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
//============================================================================
#ifndef CNUMERICLAYER_H_
#define CNUMERICLAYER_H_

// Local Headers
#include "../../CLayer.h"

//**********************************************************************
//
//
//**********************************************************************
class CNumericLayer : public CLayer {
public:
  // Functions
  CNumericLayer();
  virtual ~CNumericLayer();
  int            countValidSpaces();
  virtual void   setValue(int RowIndex, int ColIndex, double Value);
  virtual double getValue(int RowIndex, int ColIndex, int TargetRow = 0, int TargetCol = 0) = 0;
  virtual void   addValue(int RowIndex, int ColIndex, double Value);
  virtual void   subValue(int RowIndex, int ColIndex, double Value);
  virtual void   validate();
  virtual void   build() = 0;

protected:
  // Variables
  double** pGrid;
};

#endif /*CNUMERICLAYER_H_*/
