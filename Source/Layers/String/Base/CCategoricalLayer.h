//============================================================================
// Name        : CCategoricalLayer.h
// Author      : S.Rasmussen
// Date        : 1/04/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CCATEGORICALLAYER_H_
#define CCATEGORICALLAYER_H_

// Local Headers
#include "../../CLayer.h"

//**********************************************************************
//
//
//**********************************************************************
class CCategoricalLayer : public CLayer {
public:
  // Functions
  CCategoricalLayer();
  virtual ~CCategoricalLayer();
  int            countValidSpaces();
  virtual void   setValue(int RowIndex, int ColIndex, string Value);
  virtual string getValue(int RowIndex, int ColIndex) = 0;
  virtual void   validate();
  virtual void   build() = 0;

protected:
  // Variables
  double** pGrid;
};

#endif /*CCATEGORICALLAYER_H_*/
