//============================================================================
// Name        : CLogNormalPDF.h
// Author      : C. Marsh
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
//============================================================================
#ifndef CLOGNORMALPDF_H_
#define CLOGNORMALPDF_H_

// Local Headers
#include "../CPDF.h"

//**********************************************************************
//
//
//**********************************************************************
class CLogNormalPDF : public CPDF
{
public:
  // Functions
  CLogNormalPDF();
  virtual ~CLogNormalPDF();
  CPDF *clone() { return new CLogNormalPDF(*this); }
  double getMu() { return dMu; }
  double getSigma() { return dSigma; }
  double getPDFResult(double value);
  double getCDFResult(double value);
  void validate();

protected:
  // Variables
  double dMu;
  double dSigma;
};

#endif /*CLOGNORMALPDF_H_*/
