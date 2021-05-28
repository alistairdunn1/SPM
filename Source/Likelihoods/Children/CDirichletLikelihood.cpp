//============================================================================
// Name        : CDirichletLikelihood.cpp
// Author      : A.Dunn
// Date        : 14/07/2015
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
//============================================================================

// Global headers
#include <cmath>

// Local headers
#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "CDirichletLikelihood.h"

//**********************************************************************
// CDirichletLikelihood::CDirichletLikelihood()
// Default Constructor
//**********************************************************************
CDirichletLikelihood::CDirichletLikelihood() {}

//**********************************************************************
// double CDirichletLikelihood::adjustErrorValue(const double processError, const double errorValue)
// Adjust error value based on process error
//**********************************************************************
double CDirichletLikelihood::adjustErrorValue(const double processError, const double errorValue) {
  // adjust for N process error
  if ((errorValue > 0.0) && (processError > 0.0))
    return (errorValue * processError);

  return errorValue;
}
//**********************************************************************
// void CDirichletLikelihood::getResult(vector<double> &scores, const vector<double> &expected, const vector<double> &observed,
//    const vector<double> &errorValue, const vector<double> &processError, const double delta)
// Get the result from our likelihood for the observation
//**********************************************************************
void CDirichletLikelihood::getResult(vector<double>& scores, const vector<double>& expected, const vector<double>& observed, const vector<double>& errorValue,
                                     const vector<double>& processError, const double delta) {
  // Loop through expected
  for (int i = 0; i < (int)expected.size(); ++i) {
    // Calculate score
    double dErrorValue = adjustErrorValue(processError[i], errorValue[i]);
    double dAlpha      = CMath::zeroFun(expected[i], delta) * dErrorValue;
    double dA2_A3      = CMath::lnGamma(dAlpha) - ((dAlpha - 1.0) * log(CMath::zeroFun(observed[i], delta)));
    scores.push_back(dA2_A3);
  }
}

//**********************************************************************
// void CDirichletLikelihood::simulateObserved(const vector<string> &keys, vector<double> &observed,
//    const vector<double> &expected, const vector<double> &errorValue, const vector<double> &processError, const double delta)
// Simulate observed value for our observation
//**********************************************************************
void CDirichletLikelihood::simulateObserved(const vector<string>& keys, vector<double>& observed, const vector<double>& expected, const vector<double>& errorValue,
                                            const vector<double>& processError, const double delta) {
  // instance the random number generator
  CRandomNumberGenerator* pRandom = CRandomNumberGenerator::Instance();

  map<string, double> mTotals;

  // Loop through our expected values
  for (int i = 0; i < (int)expected.size(); ++i) {
    // Check for invalid values
    if (errorValue[i] < 0.0)
      CError::errorLessThan(PARAM_ERROR_VALUE, PARAM_ZERO);

    // Add in process error
    double dN = ceil(adjustErrorValue(processError[i], errorValue[i]));

    // Deal with zeros
    if (expected[i] <= 0.0 || dN <= 0.0) {
      observed[i] = 0.0;
    } else {
      // Calculate observed number
      observed[i] = pRandom->getRandomGamma(expected[i] * dN);
      mTotals[keys[i]] += observed[i];
    }
  }

  for (unsigned i = 0; i < expected.size(); ++i) observed[i] /= mTotals[keys[i]];
}

//**********************************************************************
// double CDirichletLikelihood::getInitialScore(const vector<string> &keys, const vector<double> &processError,
//    const vector<double> &errorValue) {
// Get Initial Score
//**********************************************************************
double CDirichletLikelihood::getInitialScore(const vector<string>& keys, const vector<double>& expected, const vector<double>& observed, const vector<double>& processError,
                                             const vector<double>& errorValue, const double delta) {
  double dScore = 0.0;

  // Only one loop through expected
  double dA1 = 0.0;
  for (int i = 0; i < (int)expected.size(); ++i) {
    // Calculate score
    double dErrorValue = adjustErrorValue(processError[i], errorValue[i]);
    dA1 += CMath::zeroFun(expected[i], delta) * dErrorValue;
  }

  dScore = -CMath::lnGamma(dA1);
  return dScore;
}

//**********************************************************************
// CDirichletLikelihood::~CDirichletLikelihood()
// Destructor
//**********************************************************************
CDirichletLikelihood::~CDirichletLikelihood() {}
