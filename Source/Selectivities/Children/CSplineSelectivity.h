//============================================================================
// Name        : CSplineSelectivity.h
// Author      : A. Dunn
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
//============================================================================
#ifndef CSPLINESELECTIVITY_H_
#define CSPLINESELECTIVITY_H_

// Local Headers
#include "Base/CCachedSelectivity.h"
#include "../../Helpers/CSpline.h"

using namespace magnet::math;

//**********************************************************************
//
//
//**********************************************************************

class CSplineSelectivity : public CCachedSelectivity
{
public:
  // Functions
  CSplineSelectivity();
  virtual ~CSplineSelectivity();
  CSelectivity *clone() { return new CSplineSelectivity(*this); }
  void validate();
  void rebuild();
  void build();

protected:
  // Functions
  double calculateResult(int Age);
  double transform(double x);
  double inverseTransform(double x);
  // Variables
  Spline spline;
  vector<double> vKnots;
  vector<double> vValues;
  int iN;
  string sMethod;
};

#endif /*CSPLINESELECTIVITY_H_*/
