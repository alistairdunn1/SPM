//============================================================================
// Name        : CBinomialApproxLikelihood.cpp
// Author      : S.Rasmussen
// Date        : 14/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CBinomialApproxLikelihood.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/CError.h"

//**********************************************************************
// CBinomialApproxLikelihood::CBinomialApproxLikelihood()
// Default Constructor
//**********************************************************************
CBinomialApproxLikelihood::CBinomialApproxLikelihood()
{
}

//**********************************************************************
// double CBinomialApproxLikelihood::adjustErrorValue(const double processError, const double errorValue)
// Adjust our error value based on process error
//**********************************************************************
double CBinomialApproxLikelihood::adjustErrorValue(const double processError, const double errorValue)
{
  // adjust for N process error
  if ((errorValue > 0.0) && (processError > 0.0))
    return (1.0 / (1.0 / errorValue + 1.0 / processError));

  return errorValue;
}

//**********************************************************************
// void CBinomialApproxLikelihood::getResult(vector<double> &scores, const vector<double> &expected, const vector<double> &observed,
//    const vector<double> &errorValue, const vector<double> &processError, const double delta)
// Get the result from our likelihood
//**********************************************************************
void CBinomialApproxLikelihood::getResult(vector<double> &scores, const vector<double> &expected, const vector<double> &observed,
                                          const vector<double> &errorValue, const vector<double> &processError, const double delta)
{

  // Loop through expected values
  for (int i = 0; i < (int)expected.size(); ++i)
  {
    // Calculate Scores
    double dErrorValue = adjustErrorValue(processError[i], errorValue[i]);
    double dStdError = sqrt((CMath::zeroFun(expected[i], delta) * CMath::zeroFun(1.0 - expected[i], delta)) / dErrorValue);
    double dScore = log(dStdError) + 0.5 * pow((observed[i] - expected[i]) / dStdError, 2.0);

    scores.push_back(dScore);
  }
}

//**********************************************************************
// void CBinomialApproxLikelihood::simulateObserved(const vector<string> &keys, vector<double> &observed,
//    const vector<double> &expected, const vector<double> &errorValue, const vector<double> &processError, const double delta)
// Simulate observed value from our observation
//**********************************************************************
void CBinomialApproxLikelihood::simulateObserved(const vector<string> &keys, vector<double> &observed,
                                                 const vector<double> &expected, const vector<double> &errorValue, const vector<double> &processError, const double delta)
{

  // instance the random number generator
  CRandomNumberGenerator *pRandom = CRandomNumberGenerator::Instance();

  // Loop through our expected values
  for (int i = 0; i < (int)expected.size(); ++i)
  {

    // Check for invalid values
    if (errorValue[i] < 0.0)
      CError::errorLessThan(PARAM_ERROR_VALUE, PARAM_ZERO);

    // Add in process error
    double dN = ceil(adjustErrorValue(processError[i], errorValue[i]));

    // Deal with zeros
    if (expected[i] <= 0.0 || dN <= 0.0)
    {
      observed[i] = 0.0;
    }
    else
    {
      // Calculate observed proportion
      observed[i] = pRandom->getRandomBinomial(expected[i], dN) / dN;
    }
  }
}

//**********************************************************************
// CBinomialApproxLikelihood::~CBinomialApproxLikelihood()
// Destructor
//**********************************************************************
CBinomialApproxLikelihood::~CBinomialApproxLikelihood()
{
}
