//============================================================================
// Name        : CLikelihood.h
// Author      : S.Rasmussen
// Date        : 14/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CLIKELIHOOD_H_
#define CLIKELIHOOD_H_

// Local headers
#include "../BaseClasses/CBaseObject.h"

//**********************************************************************
//
//
//**********************************************************************
class CLikelihood : public CBaseObject {
public:
  CLikelihood();
  virtual ~CLikelihood();
  virtual double adjustErrorValue(const double processError, const double errorValue) = 0;
  virtual void   getResult(vector<double>& scores, const vector<double>& expected, const vector<double>& observed, const vector<double>& errorValue,
                           const vector<double>& processError, const double delta)
      = 0;
  virtual void simulateObserved(const vector<string>& keys, vector<double>& observed, const vector<double>& expected, const vector<double>& errorValue,
                                const vector<double>& processError, const double delta)
      = 0;
  virtual double getInitialScore(const vector<string>& keys, const vector<double>& expected, const vector<double>& observed, const vector<double>& processError,
                                 const vector<double>& errorValue, const double delta) {
    return 0;
  }

  double adjustLikelihoodValue(const double LikelihoodMultiplier, const double Likelihood);
};

#endif /* CLIKELIHOOD_H_ */
