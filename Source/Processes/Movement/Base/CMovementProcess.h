//============================================================================
// Name        : CMovementProcess.h
// Author      : S.Rasmussen
// Date        : 14/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-08-19 13:58:53 +1200 (Tue, 19 Aug 2008) $
//============================================================================
#ifndef CMOVEMENTPROCESS_H_
#define CMOVEMENTPROCESS_H_

// Local Headers
#include "../../CProcess.h"

//**********************************************************************
//
//
//**********************************************************************
class CMovementProcess : public CProcess {
public:
  // Functions
  CMovementProcess();
  virtual ~CMovementProcess();
  void              setProportion(double value) { dProportion = value; }
  double            getProportion() { return dProportion; }
  virtual CProcess* clone() = 0;
  virtual void      validate();
  virtual void      build();
  virtual void      execute();

protected:
  // Functions
  void doMove(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty);
  void moveUp(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty);
  void moveDown(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty);
  void moveLeft(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty);
  void moveRight(int RIndex, int CIndex, int SRIndex, int SCIndex, double Qty);

  // Variables
  double        dProportion;
  CWorldSquare* pTargetBase;
  CWorldSquare* pTargetDiff;
};

#endif /*CMOVEMENTPROCESS_H_*/
