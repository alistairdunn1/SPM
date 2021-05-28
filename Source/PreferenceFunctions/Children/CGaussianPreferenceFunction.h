//============================================================================
// Name        : CGaussianPreferenceFunction.h
// Author      : C. Marsh
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
//============================================================================
#ifndef CGAUSSIANPREFERENCEFUNCTION_H_
#define CGAUSSIANPREFERENCEFUNCTION_H_

// Local Headers
#include "../CPreferenceFunction.h"

class CPDF;
class CNumericLayer;

//**********************************************************************
//
//
//**********************************************************************
class CGaussianPreferenceFunction : public CPreferenceFunction {
public:
  // Functions
  CGaussianPreferenceFunction();
  virtual ~CGaussianPreferenceFunction();
  CPreferenceFunction* clone() { return new CGaussianPreferenceFunction(*this); }
  double               getRho() { return dRho; }
  double               getResult(int RIndex, int CIndex, int TRIndex, int TCIndex);
  void                 validate();
  void                 build();
  bool                 getIsStatic();

protected:
  // Functions
  double NormalInverse(double p);
  // Variables
  double                 dRho;
  vector<string>         vPDFNames;
  vector<string>         vLayerNames;
  vector<string>         vPDFTypes;
  vector<CPDF*>          vPDFs;
  vector<CNumericLayer*> vLayers;
};

#endif /*CGAUSSIANPREFERENCEFUNCTION_H_*/
