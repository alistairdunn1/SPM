//============================================================================
// Name        : CMigrationMovementProcess.h
// Author      : S.Rasmussen
// Date        : 4/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CMIGRATIONMOVEMENTPROCESS_H_
#define CMIGRATIONMOVEMENTPROCESS_H_

// Local Headers
#include "Base/CMovementProcess.h"

//**********************************************************************
//
//
//**********************************************************************
class CMigrationMovementProcess : public CMovementProcess
{
public:
  CMigrationMovementProcess();
  virtual ~CMigrationMovementProcess();
  CProcess *clone() { return (new CMigrationMovementProcess(*this)); }
  void validate();
  void build();
  void execute();

protected:
  // Variables
  double dSourceLayerMax;
  double dSinkLayerTotal;
  double dTotal;
  double dSquare;
  CNumericLayer *pSourceLayer;
  CNumericLayer *pSinkLayer;
  string sSourceLayer;
  string sSinkLayer;
};

#endif /*CMIGRATIONMOVEMENTPROCESS_H_*/
