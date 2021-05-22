//============================================================================
// Name        : CPenalty.h
// Author      : S.Rasmussen
// Date        : 16/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CPENALTY_H_
#define CPENALTY_H_

// Local
#include "../BaseClasses/CBaseValidate.h"

//**********************************************************************
//
//
//**********************************************************************
class CPenalty : public CBaseValidate
{
public:
  // Functions
  CPenalty();
  virtual ~CPenalty();
  void validate();
  void trigger(string Label, double Value1, double Value2);

protected:
  // Variables
  bool bLogScale;
  double dMultiplier;
};

#endif /*CPENALTY_H_*/
