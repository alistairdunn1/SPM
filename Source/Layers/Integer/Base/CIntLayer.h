//============================================================================
// Name        : CIntLayer.h
// Author      : S.Mormede
// Date        : 07/02/2018
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CINTLAYER_H_
#define CINTLAYER_H_

// Local Headers
#include "../../CLayer.h"

//**********************************************************************
//
//
//**********************************************************************
class CIntLayer : public CLayer
{
public:
  // Functions
  CIntLayer();
  virtual ~CIntLayer();
  int countValidSpaces();
  virtual void setValue(int RowIndex, int ColIndex, int Value);
  virtual int getValue(int RowIndex, int ColIndex, int TargetRow = 0, int TargetCol = 0) = 0;
  virtual void validate();
  virtual void build() = 0;

protected:
  // Variables
  int **pGrid;
};

#endif /*CINTLAYER_H_*/
