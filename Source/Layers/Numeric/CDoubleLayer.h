//============================================================================
// Name        : CDoubleLayer.h
// Author      : S.Rasmussen
// Date        : 14/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
//============================================================================
#ifndef CDOUBLELAYER_H_
#define CDOUBLELAYER_H_

// Local Headers
#include "Base/CNumericLayer.h"

//**********************************************************************
//
//
//**********************************************************************
class CDoubleLayer : public CNumericLayer {
public:
  // Functions
  CDoubleLayer();
  virtual ~CDoubleLayer();
  CLayer* clone() { return (new CDoubleLayer(*this)); }
  double  getValue(int RowIndex, int ColIndex, int TargetRow, int TargetCol);
  void    setValue(int RowIndex, int ColIndex, double Value);
  void    addValue(int RowIndex, int ColIndex, double Value);
  void    subValue(int RowIndex, int ColIndex, double Value);
  double  getLayerMin();
  double  getLayerMax();
  void    validate();
  void    build();

protected:
  // Variables
  double dRescale;
};

#endif /*CDOUBLELAYER_H_*/
