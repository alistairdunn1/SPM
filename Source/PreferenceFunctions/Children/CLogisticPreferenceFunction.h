//============================================================================
// Name        : CLogisticPreferenceFunction.h
// Author      : A. Dunn
// Date        : 15/04/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CLOGISTICPREFERENCEFUNCTION_H_
#define CLOGISTICPREFERENCEFUNCTION_H_

// Local Headers
#include "../CPreferenceFunction.h"

//**********************************************************************
//
//
//**********************************************************************
class CLogisticPreferenceFunction : public CPreferenceFunction {
public:
  // Functions
  CLogisticPreferenceFunction();
  virtual ~CLogisticPreferenceFunction();
  CPreferenceFunction* clone() { return new CLogisticPreferenceFunction(*this); }
  double               getA50() { return dA50; }
  double               getAto95() { return dAto95; }
  double               getResult(int RIndex, int CIndex, int TRIndex, int TCIndex);
  void                 validate();
  void                 build();

protected:
  // Variables
  double dA50;
  double dAto95;
};

#endif /*CLOGISTICPREFERENCEFUNCTION_H_*/
