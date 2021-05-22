//============================================================================
// Name        : CAllValuesBoundedSelectivity.h
// Author      : S.Rasmussen
// Date        : 20/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CALLVALUESBOUNDEDSELECTIVITY_H_
#define CALLVALUESBOUNDEDSELECTIVITY_H_

// Local headers
#include "Base/CCachedSelectivity.h"

//**********************************************************************
//
//
//**********************************************************************
class CAllValuesBoundedSelectivity : public CCachedSelectivity
{
public:
  // Functions
  CAllValuesBoundedSelectivity();
  virtual ~CAllValuesBoundedSelectivity();
  CSelectivity *clone() { return new CAllValuesBoundedSelectivity(*this); }
  void validate();

protected:
  // Functions
  double calculateResult(int Age);

  // Variables
  int iL;
  int iH;
  vector<double> vVs;
  int iMinAge;
};

#endif /* CALLVALUESBOUNDEDSELECTIVITY_H_ */
