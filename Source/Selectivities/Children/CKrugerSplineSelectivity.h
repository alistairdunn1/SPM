//============================================================================
// Name        : CKrugerSplineSelectivity.h
// Author      : A. Dunn, I. Doonan
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
//============================================================================
#ifndef CKRUGERSPLINESELECTIVITY_H_
#define CKRUGERSPLINESELECTIVITY_H_

// Local Headers
#include "Base/CCachedSelectivity.h"

//**********************************************************************
//
//
//**********************************************************************

class CKrugerSplineSelectivity : public CCachedSelectivity
{
public:
  // Functions
  CKrugerSplineSelectivity();
  virtual ~CKrugerSplineSelectivity();
  CSelectivity *clone() { return new CKrugerSplineSelectivity(*this); }
  void validate();
  void rebuild();
  void build();

protected:
  // Functions
  double calculateResult(int Age);
  // Variables
  vector<double> vKnots;
  vector<double> vValues;
  int iN;
};

#endif /*CKRUGERSPLINESELECTIVITY_H_*/
