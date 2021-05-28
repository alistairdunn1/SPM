//============================================================================
// Name        : CPseudoLikelihood.cpp
// Author      : S.Rasmussen
// Date        : 14/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CPseudoLikelihood.h"

//**********************************************************************
// CPseudoLikelihood::CPseudoLikelihood()
// Default Constructor
//**********************************************************************
CPseudoLikelihood::CPseudoLikelihood() {}

//**********************************************************************
// double CPseudoLikelihood::adjustErrorValue(const double processError, const double errorValue)
// Adjust our error value based on process error
//**********************************************************************
double CPseudoLikelihood::adjustErrorValue(const double processError, const double errorValue) {
  return 0.0;
}

//**********************************************************************
// void CPseudoLikelihood::getResult(vector<double> &scores, const vector<double> &expected, const vector<double> &observed,
//     const vector<double> &errorValue, const vector<double> &processError, const double delta)
// Get the result from our likelihood for the observation
//**********************************************************************
void CPseudoLikelihood::getResult(vector<double>& scores, const vector<double>& expected, const vector<double>& observed, const vector<double>& errorValue,
                                  const vector<double>& processError, const double delta) {
  // Loop through expected
  for (int i = 0; i < (int)expected.size(); ++i) {
    scores.push_back(0.0);
  }
}

//**********************************************************************
// void CPseudoLikelihood::simulateObserved(const vector<string> &keys, vector<double> &observed,
//    const vector<double> &expected, const vector<double> &errorValue, const vector<double> &processError, const double delta)
// Simulate an observed value from our expected
//**********************************************************************
void CPseudoLikelihood::simulateObserved(const vector<string>& keys, vector<double>& observed, const vector<double>& expected, const vector<double>& errorValue,
                                         const vector<double>& processError, const double delta) {}

//**********************************************************************
// CPseudoLikelihood::~CPseudoLikelihood()
// Destructor
//**********************************************************************
CPseudoLikelihood::~CPseudoLikelihood() {}
