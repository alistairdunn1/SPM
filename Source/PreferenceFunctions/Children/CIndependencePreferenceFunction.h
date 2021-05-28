//============================================================================
// Name        : CIndependencePreferenceFunction.h
// Author      : C. Marsh
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
//============================================================================
#ifndef CINDEPENDENCEPREFERENCEFUNCTION_H_
#define CINDEPENDENCEPREFERENCEFUNCTION_H_

// Local Headers
#include "../CPreferenceFunction.h"

class CPDF;
class CNumericLayer;

//**********************************************************************
//
//
//**********************************************************************
class CIndependencePreferenceFunction : public CPreferenceFunction {
public:
  // Functions
  CIndependencePreferenceFunction();
  virtual ~CIndependencePreferenceFunction();
  CPreferenceFunction* clone() { return new CIndependencePreferenceFunction(*this); }
  double               getResult(int RIndex, int CIndex, int TRIndex, int TCIndex);
  void                 validate();
  void                 build();
  bool                 getIsStatic();

protected:
  // Variables
  vector<string>         vPDFNames;
  vector<string>         vLayerNames;
  vector<string>         vPDFTypes;
  vector<CPDF*>          vPDFs;
  vector<CNumericLayer*> vLayers;
};

#endif /*CINDEPENDENCEPREFERENCEFUNCTION_H_*/
