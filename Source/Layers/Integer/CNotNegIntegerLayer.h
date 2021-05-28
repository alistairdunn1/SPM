//============================================================================
// Name        : CNotNegIntegerLayer.h
// Author      : S.Mormede
// Date        : 09/02/2018
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CNOTNEGINTEGERLAYER_H_
#define cNOTNEGINTEGERLAYER_H_

// Local Headers
#include "Base/CIntLayer.h"

//**********************************************************************
//
//
//**********************************************************************
class CNotNegIntegerLayer : public CIntLayer {
public:
  // Functions
  CNotNegIntegerLayer();
  virtual ~CNotNegIntegerLayer();
  CLayer* clone() { return (new CNotNegIntegerLayer(*this)); }
  int     getValue(int RowIndex, int ColIndex, int TargetRow, int TargetCol);
  void    setValue(int RowIndex, int ColIndex, int Value);
  int     getLayerMin();
  int     getLayerMax();
  void    validate();
  void    build();
};

#endif /*CNOTNEGINTEGERLAYER_H_*/
