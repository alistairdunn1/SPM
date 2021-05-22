//============================================================================
// Name        : CFrankPreferenceFunction.h
// Author      : C. Marsh
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
//============================================================================
#ifndef CFRANKPREFERENCEFUNCTION_H_
#define CFRANKPREFERENCEFUNCTION_H_

// Local Headers
#include "../CPreferenceFunction.h"

class CPDF;
class CNumericLayer;

//**********************************************************************
//
//
//**********************************************************************
class CFrankPreferenceFunction : public CPreferenceFunction
{
public:
  // Functions
  CFrankPreferenceFunction();
  virtual ~CFrankPreferenceFunction();
  CPreferenceFunction *clone() { return new CFrankPreferenceFunction(*this); }
  double getRho() { return dRho; }
  double getResult(int RIndex, int CIndex, int TRIndex, int TCIndex);
  void validate();
  void build();
  bool getIsStatic();

protected:
  // Variables
  double dRho;
  vector<string> vPDFNames;
  vector<string> vLayerNames;
  vector<string> vPDFTypes;
  vector<CPDF *> vPDFs;
  vector<CNumericLayer *> vLayers;
};

#endif /*CFRANKPREFERENCEFUNCTION_H_*/
