//============================================================================
// Name        : CComparer.h
// Author      : S.Rasmussen
// Date        : 7/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
//============================================================================
#ifndef CCOMPARER_H_
#define CCOMPARER_H_

// Global Headers
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

// Local Headers
#include "DefinedValues.h"

// Using
using std::string;
using std::vector;

//**********************************************************************
//
//
//**********************************************************************
class CComparer
{
public:
  // Functions
  static bool isSame(string one, string two, bool useWildCards = true);
  static bool hasDuplicates(const vector<std::string> &vLabels);

  // Inline Functions
  static bool isZero(double A) { return ((A < ZERO) && (A > -ZERO)); }
  static bool isTrueZero(double A) { return ((A < TRUE_ZERO) && (A > -TRUE_ZERO)); }
  static bool isNonNegative(double A) { return (0.0 <= A); }
  static bool isPositive(double A) { return (0.0 < A); }
  static bool isEqual(double A, double B) { return (((A - B) < ZERO) && ((A - B) > -ZERO)); }
  static bool isClose(double A, double B) { return (((A - B) < 1e-12) && ((A - B) > -1e-12)); }
  static bool isBetween(double A, double B, double C)
  {
    return (((A - B) > -ZERO) && ((A - C) < ZERO));
  }

private:
  // Functions
  CComparer();
  virtual ~CComparer();
};

#endif /* CCOMPARER_H_ */
