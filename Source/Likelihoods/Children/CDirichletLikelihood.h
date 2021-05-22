//============================================================================
// Name        : CDirichletLikelihood.h
// Author      : A.Dunn
// Date        : 14/07/2015
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
//============================================================================
#ifndef CDIRICHLETLIKELIHOOD_H_
#define CDIRICHLETLIKELIHOOD_H_

// Local headers
#include "../CLikelihood.h"
#include "../../RandomNumberGenerator/CRandomNumberGenerator.h"

//**********************************************************************
//
//
//**********************************************************************
class CDirichletLikelihood : public CLikelihood
{
public:
  // Functions
  CDirichletLikelihood();
  virtual ~CDirichletLikelihood();
  double adjustErrorValue(const double processError, const double errorValue);
  void getResult(vector<double> &scores, const vector<double> &expected, const vector<double> &observed,
                 const vector<double> &errorValue, const vector<double> &processError, const double delta);
  void simulateObserved(const vector<string> &keys, vector<double> &observed, const vector<double> &expected,
                        const vector<double> &errorValue, const vector<double> &processError, const double delta);
  double getInitialScore(const vector<string> &keys, const vector<double> &expected, const vector<double> &observed,
                         const vector<double> &processError, const vector<double> &errorValue, const double delta);
};

#endif /* CDIRICHLETLIKELIHOOD_H_ */
