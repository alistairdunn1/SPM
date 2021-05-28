//============================================================================
// Name        : CExponentialPDF.h
// Author      : C. Marsh
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
//============================================================================
#ifndef CEXPONENTIALPDF_H_
#define CEXPONENTIALPDF_H_

// Local Headers
#include "../CPDF.h"

//**********************************************************************
//
//
//**********************************************************************
class CExponentialPDF : public CPDF {
public:
  // Functions
  CExponentialPDF();
  virtual ~CExponentialPDF();
  CPDF*  clone() { return new CExponentialPDF(*this); }
  double getLambda() { return dLambda; }
  double getPDFResult(double value);
  double getCDFResult(double value);
  void   validate();

protected:
  // Variables
  double dLambda;
};

#endif /*CEXPONENTIALPDF_H_*/
