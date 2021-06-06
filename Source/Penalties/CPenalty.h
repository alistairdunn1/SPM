//============================================================================
// Name        : CPenalty.h
// Author      : S.Rasmussen
// Date        : 16/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
//============================================================================
#ifndef CPENALTY_H_
#define CPENALTY_H_

// Local
#include "../BaseClasses/CBaseValidate.h"

//**********************************************************************
//
//
//**********************************************************************
class CPenalty : public CBaseValidate {
public:
  // Functions
  CPenalty();
  virtual ~CPenalty();
  void validate();
  void trigger(string Label, double Value1, double Value2);
  void triggerZero(string Label);

protected:
  // Variables
  bool   bLogScale;
  double dMultiplier;
};

#endif /*CPENALTY_H_*/
