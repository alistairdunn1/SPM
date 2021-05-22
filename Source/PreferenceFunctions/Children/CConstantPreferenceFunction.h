//============================================================================
// Name        : CConstantPreferenceFunction.h
// Author      : A. Dunn
// Date        : 15/04/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CCONSTANTPREFERENCEFUNCTION_H_
#define CCONSTANTPREFERENCEFUNCTION_H_

// Local Headers
#include "../CPreferenceFunction.h"

//**********************************************************************
//
//
//**********************************************************************
class CConstantPreferenceFunction : public CPreferenceFunction
{
public:
  // Functions
  CConstantPreferenceFunction();
  virtual ~CConstantPreferenceFunction();
  CPreferenceFunction *clone() { return new CConstantPreferenceFunction(*this); }
  double getResult(int RIndex, int CIndex, int TRIndex, int TCIndex);
  void validate();
  void build();

protected:
  // Variables
  double dC;
};

#endif /*CCONSTANTPREFERENCEFUNCTION_H_*/
