//============================================================================
// Name        : CUniformPDF.h
// Author      : C. Marsh
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
//============================================================================
#ifndef CUNIFORMPDF_H_
#define CUNIFORMPDF_H_

// Local Headers
#include "../CPDF.h"

//**********************************************************************
//
//
//**********************************************************************
class CUniformPDF : public CPDF {
public:
  // Functions
  CUniformPDF();
  virtual ~CUniformPDF();
  CPDF*  clone() { return new CUniformPDF(*this); }
  double getA() { return dA; }
  double getB() { return dB; }
  double getPDFResult(double value);
  double getCDFResult(double value);
  void   validate();

protected:
  // Variables
  double dA;
  double dB;
};

#endif /*CUNIFORMPDF_H_*/
