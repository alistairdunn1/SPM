//============================================================================
// Name        : CInverseLogisticPreferenceFunction.h
// Author      : A. Dunn
// Date        : 15/04/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CINVERSELOGISTICPREFERENCEFUNCTION_H_
#define CINVERSELOGISTICPREFERENCEFUNCTION_H_

// Local Headers
#include "../CPreferenceFunction.h"

//**********************************************************************
//
//
//**********************************************************************
class CInverseLogisticPreferenceFunction : public CPreferenceFunction {
public:
  // Functions
  CInverseLogisticPreferenceFunction();
  virtual ~CInverseLogisticPreferenceFunction();
  CPreferenceFunction* clone() { return new CInverseLogisticPreferenceFunction(*this); }
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

#endif /*CINVERSELOGISTICPREFERENCEFUNCTION_H_*/
