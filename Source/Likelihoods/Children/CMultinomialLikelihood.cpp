//============================================================================
// Name        : CMultinomialLikelihood.cpp
// Author      : S.Rasmussen
// Date        : 14/04/2009
// Copyright   : Copyright NIWA Science ©2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global headers
#include <cmath>

// Local headers
#include "CMultinomialLikelihood.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/CError.h"

//**********************************************************************
// CMultinomialLikelihood::CMultinomialLikelihood()
// Default Constructor
//**********************************************************************
CMultinomialLikelihood::CMultinomialLikelihood() {
}

//**********************************************************************
// double CMultinomialLikelihood::adjustErrorValue(const double processError, const double errorValue)
// Adjust error value based on process error
//**********************************************************************
double CMultinomialLikelihood::adjustErrorValue(const double processError, const double errorValue) {
  // adjust for N process error
  if( (errorValue > 0.0) && (processError > 0.0) )
    return (1.0/(1.0/errorValue + 1.0/processError));

  return errorValue;
}
//**********************************************************************
// void CMultinomialLikelihood::getResult(vector<double> &scores, const vector<double> &expected, const vector<double> &observed,
//    const vector<double> &errorValue, const vector<double> &processError, const double delta)
// Get the result from our likelihood for the observation
//**********************************************************************
void CMultinomialLikelihood::getResult(vector<double> &scores, const vector<double> &expected, const vector<double> &observed,
    const vector<double> &errorValue, const vector<double> &processError, const double delta) {

  // Loop through expected
  for (int i = 0; i < (int)expected.size(); ++i) {
    // Calculate score
    double dErrorValue = adjustErrorValue(processError[i], errorValue[i]);
    double dScore      = CMath::lnFactorial(dErrorValue * observed[i])
                         - dErrorValue * observed[i] * log(CMath::zeroFun(expected[i],delta));

    scores.push_back(dScore);
  }
}

//**********************************************************************
// void CMultinomialLikelihood::simulateObserved(const vector<string> &keys, vector<double> &observed,
//    const vector<double> &expected, const vector<double> &errorValue, const vector<double> &processError, const double delta)
// Simulate observed value for our observation
//**********************************************************************
void CMultinomialLikelihood::simulateObserved(const vector<string> &keys, vector<double> &observed,
    const vector<double> &expected, const vector<double> &errorValue, const vector<double> &processError, const double delta) {

  // instance the random number generator
  CRandomNumberGenerator *pRandom = CRandomNumberGenerator::Instance();

  // Check for invalid values
  for (int i = 1; i < (int)keys.size(); ++i) {
    if (errorValue[i] < 0.0)
      CError::errorLessThan(PARAM_ERROR_VALUE, PARAM_ZERO);
  }

  // Count unique keys (observation rows)
  vector<string> vUniqueKeys;
  vector<int> vN;
  vUniqueKeys.push_back(keys[0]);
  vN.push_back((int)ceil(adjustErrorValue(processError[0], errorValue[0])));
  if(keys.size() > 1) {
    for (int i = 1; i < (int)keys.size(); ++i) {
	  if(keys[i]!=keys[i-1]) {
	    vUniqueKeys.push_back(keys[i]);
		vN.push_back((int)ceil(adjustErrorValue(processError[i], errorValue[i])));
	  }
    }
  }
  
  // loop through unique keys
  for(int i = 0; i < (int)vUniqueKeys.size(); ++i) {
	// get expected vector
	vector<double> vExpected;
	double dTotal = 0.0;
	// Get expected values for this key
    for (int j = 0; j < (int)keys.size(); ++j) {
	  if(vUniqueKeys[i] == keys[j]) {
		vExpected.push_back(expected[i]);
		dTotal += expected[i];
	  }
	}
	// rescale to ensure the total expected = 1
	for( int j =0; j < (int)vExpected.size(); ++j) {
	  vExpected[j] /= dTotal;
	  // and make expected a cumulative sum
	  if(j>0) vExpected[j] = vExpected[j] + vExpected[j-1];
	}
	// simulate an observed vector
	vector<double> vObserved (vExpected.size(), 0.0);
	for(int j =0; j < vN[i]; ++j) {
	  double temp = pRandom->getRandomUniform_01();	  
	  for( int k = 0; k < (int)vExpected.size(); ++k) {;
	    if( temp <= vExpected[k] ) {
		  vObserved[k]++;
		  break;
		}
	  }
    }
	// rescale to ensure the total expected = 1
	for( int j =0; j < (int)vObserved.size(); ++j) {
	  vObserved[j] /= vN[i];
	}
	// populate observed for the simulation
	int iCount =0;
    for (int j = 0; j < (int)keys.size(); ++j) {
	  if(vUniqueKeys[i] == keys[j]) {
		observed[j] = vObserved[iCount];
		iCount ++;
	  }
	}
  }
}

//**********************************************************************
// double CMultinomialLikelihood::getInitialScore(const vector<string> &keys, const vector<double> &processError,
//    const vector<double> &errorValue) {
// Get Initial Score
//**********************************************************************
double CMultinomialLikelihood::getInitialScore(const vector<string> &keys, const vector<double> &expected, const vector<double> &observed,
                                               const vector<double> &processError, const vector<double> &errorValue, const double delta) {

  double dScore   = 0.0;
  string sLastKey = "";

  for (int i = 0; i < (int)keys.size(); ++i) {
    // Only once per key
    if (keys[i] == sLastKey)
      continue;

    dScore    += -CMath::lnFactorial(adjustErrorValue(processError[i], errorValue[i]));
    sLastKey  = keys[i];
  }

  return dScore;
}

//**********************************************************************
// CMultinomialLikelihood::~CMultinomialLikelihood()
// Destructor
//**********************************************************************
CMultinomialLikelihood::~CMultinomialLikelihood() {
}
