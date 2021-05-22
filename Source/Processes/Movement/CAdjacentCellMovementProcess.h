//============================================================================
// Name        : CAdjacentCellMovementProcess.h
// Author      : S.Rasmussen
// Date        : 4/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CADJACENTCELLMOVEMENTPROCESS_H_
#define CADJACENTCELLMOVEMENTPROCESS_H_

// Local Headers
#include "Base/CMovementProcess.h"

//**********************************************************************
//
//
//**********************************************************************
class CAdjacentCellMovementProcess : public CMovementProcess
{
public:
  CAdjacentCellMovementProcess();
  virtual ~CAdjacentCellMovementProcess();
  CProcess *clone() { return (new CAdjacentCellMovementProcess(*this)); }
  void validate();
  void build();
  void execute();

protected:
  // Variables
  double dLayerTotal;
  double dLayerValueUp;
  double dLayerValueDown;
  double dLayerValueLeft;
  double dLayerValueRight;
  double dValue;
  CNumericLayer *pLayer;
  string sLayer;
};

#endif /*CADJACENTCELLMOVEMENTPROCESS_H_*/
