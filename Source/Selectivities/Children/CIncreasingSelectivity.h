//============================================================================
// Name        : CIncreasingSelectivity.h
// Author      : S.Rasmussen
// Date        : 20/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CINCREASINGSELECTIVITY_H_
#define CINCREASINGSELECTIVITY_H_

// Local headers
#include "Base/CCachedSelectivity.h"

//**********************************************************************
//
//
//**********************************************************************
class CIncreasingSelectivity : public CCachedSelectivity {
public:
  // Functions
  CIncreasingSelectivity();
  virtual ~CIncreasingSelectivity();
  CSelectivity* clone() { return new CIncreasingSelectivity(*this); }
  void          validate();

protected:
  // Functions
  double calculateResult(int Age);

  // Variables
  int            iL;
  int            iH;
  vector<double> vVs;
  double         dAlpha;
};

#endif /* CINCREASINGSELECTIVITY_H_ */
