//============================================================================
// Name        : CKnifeedgePreferenceFunction.h
// Author      :
// Date        :
// Copyright   :
// Description :
//============================================================================
#ifndef CKNIFEEDGEPREFERENCEFUNCTION_H_
#define CKNIFEEDGEPREFERENCEFUNCTION_H_

// Local Headers
#include "../CPreferenceFunction.h"

//**********************************************************************
//
//
//**********************************************************************
class CKnifeedgePreferenceFunction : public CPreferenceFunction {
public:
  // Functions
  CKnifeedgePreferenceFunction();
  virtual ~CKnifeedgePreferenceFunction();
  CPreferenceFunction* clone() { return new CKnifeedgePreferenceFunction(*this); }
  double               getResult(int RIndex, int CIndex, int TRIndex, int TCIndex);
  void                 validate();
  void                 build();

protected:
  // Variables
  double dC;
};

#endif /*CKNIFEEDGEPREFERENCEFUNCTION_H_*/
