//============================================================================
// Name        : CDoubleNormalPreferenceFunction.h
// Author      : S.Rasmussen
// Date        : 16/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CDOUBLENORMALPREFERENCEFUNCTION_H_
#define CDOUBLENORMALPREFERENCEFUNCTION_H_

// Local Headers
#include "../CPreferenceFunction.h"

//**********************************************************************
//
//
//**********************************************************************
class CDoubleNormalPreferenceFunction : public CPreferenceFunction
{
public:
  // Functions
  CDoubleNormalPreferenceFunction();
  virtual ~CDoubleNormalPreferenceFunction();
  CPreferenceFunction *clone() { return new CDoubleNormalPreferenceFunction(*this); }
  double getSigmaL() { return dSigmaL; }
  double getSigmaR() { return dSigmaR; }
  double getMu() { return dMu; }
  double getResult(int RIndex, int CIndex, int TRIndex, int TCIndex);
  void validate();
  void build();

protected:
  // Variables
  double dSigmaL;
  double dSigmaR;
  double dMu;
};

#endif /*CDOUBLENORMALPREFERENCEFUNCTION_H_*/
