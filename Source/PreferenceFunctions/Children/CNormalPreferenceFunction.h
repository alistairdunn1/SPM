//============================================================================
// Name        : CNormalPreferenceFunction.h
// Author      : S.Rasmussen
// Date        : 16/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CNORMALPREFERENCEFUNCTION_H_
#define CNORMALPREFERENCEFUNCTION_H_

// Local Headers
#include "../CPreferenceFunction.h"

//**********************************************************************
//
//
//**********************************************************************
class CNormalPreferenceFunction : public CPreferenceFunction
{
public:
  // Functions
  CNormalPreferenceFunction();
  virtual ~CNormalPreferenceFunction();
  CPreferenceFunction *clone() { return new CNormalPreferenceFunction(*this); }
  double getMu() { return dMu; }
  double getSigma() { return dSigma; }
  double getResult(int RIndex, int CIndex, int TRIndex, int TCIndex);
  void validate();
  void build();

protected:
  // Variables
  double dMu;
  double dSigma;
};

#endif /*CNORMALPREFERENCEFUNCTION_H_*/
