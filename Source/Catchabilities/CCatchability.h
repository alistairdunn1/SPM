//============================================================================
// Name        : CCatchability.h
// Author      : S.Rasmussen
// Date        : 28/04/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CCATCHABILITY_H_
#define CCATCHABILITY_H_

// Local Headers
#include "../BaseClasses/CBaseValidate.h"

//**********************************************************************
//
//
//**********************************************************************
class CCatchability : public CBaseValidate {
public:
  // Functions
  CCatchability();
  virtual ~CCatchability();
  CCatchability* clone() { return new CCatchability(*this); }
  double         getQ() { return dQ; }
  void           validate();

protected:
  // Variables
  double dQ;
};

#endif /*CCATCHABILITY_H_*/
