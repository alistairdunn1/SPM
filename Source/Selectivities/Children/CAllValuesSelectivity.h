//============================================================================
// Name        : CAllValuesSelectivity.h
// Author      : S.Rasmussen
// Date        : 16/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CALLVALUESSELECTIVITY_H_
#define CALLVALUESSELECTIVITY_H_

// Local headers
#include "Base/CCachedSelectivity.h"

//**********************************************************************
//
//
//**********************************************************************
class CAllValuesSelectivity : public CCachedSelectivity
{
public:
  CAllValuesSelectivity();
  virtual ~CAllValuesSelectivity();
  CSelectivity *clone() { return new CAllValuesSelectivity(*this); }
  void validate();

protected:
  // Functions
  double calculateResult(int Age);

  // Variables
  vector<double> vVs;
  double dAlpha;
};

#endif /* CALLVALUESSELECTIVITY_H_ */
