//============================================================================
// Name        : CThresholdPreferenceFunction.h
// Author      : S.Rasmussen
// Date        : 16/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CTHRESHOLDPREFERENCEFUNCTION_H_
#define CTHRESHOLDPREFERENCEFUNCTION_H_

// Local Headers
#include "../CPreferenceFunction.h"

//**********************************************************************
//
//
//**********************************************************************
class CThresholdPreferenceFunction : public CPreferenceFunction
{
public:
  // Functions
  CThresholdPreferenceFunction();
  virtual ~CThresholdPreferenceFunction();
  CPreferenceFunction *clone() { return new CThresholdPreferenceFunction(*this); }
  double getN() { return dN; }
  double getLambda() { return dLambda; }
  double getResult(int RIndex, int CIndex, int TRIndex, int TCIndex);
  void validate();
  void build();

protected:
  // Variables
  double dN;
  double dLambda;
  vector<string> vCategories;
  vector<string> vSelectivities;
};

#endif /*CTHRESHOLDPREFERENCEFUNCTION_H_*/
