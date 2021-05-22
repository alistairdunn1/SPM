//============================================================================
// Name        : CExponentialPreferenceFunction.h
// Author      : S.Rasmussen
// Date        : 16/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CEXPONENTIALPREFERENCEFUNCTION_H_
#define CEXPONENTIALPREFERENCEFUNCTION_H_

// Local Headers
#include "../CPreferenceFunction.h"

//**********************************************************************
//
//
//**********************************************************************
class CExponentialPreferenceFunction : public CPreferenceFunction
{
public:
  // Functions
  CExponentialPreferenceFunction();
  virtual ~CExponentialPreferenceFunction();
  CPreferenceFunction *clone() { return new CExponentialPreferenceFunction(*this); }
  double getLambda() { return dLambda; }
  double getResult(int RIndex, int CIndex, int TRIndex, int TCIndex);
  void validate();
  void build();

protected:
  double dLambda;
};

#endif /*CEXPONENTIALPREFERENCEFUNCTION_H_*/
