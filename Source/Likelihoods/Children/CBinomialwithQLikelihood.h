//============================================================================
// Name        : CBinomialwithQLikelihood.h
// Author      : C.Marsh, A. Dunn
// Copyright   : Copyright NIWA Science �2015 - www.niwa.co.nz
//============================================================================
#ifndef CBINOMIALWITHQLIKELIHOOD_H_
#define CBINOMIALWITHQLIKELIHOOD_H_

// Local headers
#include "../../RandomNumberGenerator/CRandomNumberGenerator.h"
#include "../CLikelihood.h"

//**********************************************************************
//
//
//**********************************************************************
class CBinomialwithQLikelihood : public CLikelihood {
public:
  CBinomialwithQLikelihood();
  virtual ~CBinomialwithQLikelihood();
  double adjustErrorValue(const double processError, const double errorValue);
  void   getResult(vector<double>& scores, const vector<double>& expected, const vector<double>& observed, const vector<double>& errorValue, const vector<double>& processError,
                   const double delta);
  void simulateObserved(const vector<string>& keys, vector<double>& observed, const vector<double>& expected, const vector<double>& errorValue, const vector<double>& processError,
                        const double delta);
};

#endif /* CBINOMIALWITHQLIKELIHOOD_H_ */
