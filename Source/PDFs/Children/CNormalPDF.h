//============================================================================
// Name        : CNormalPDF.h
// Author      : C. Marsh
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
//============================================================================
#ifndef CNORMALPDF_H_
#define CNORMALPDF_H_

// Local Headers
#include "../CPDF.h"

//**********************************************************************
//
//
//**********************************************************************
class CNormalPDF : public CPDF
{
public:
  // Functions
  CNormalPDF();
  virtual ~CNormalPDF();
  CPDF *clone() { return new CNormalPDF(*this); }
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

#endif /*CNORMALPDF_H_*/
