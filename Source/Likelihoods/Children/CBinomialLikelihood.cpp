//============================================================================
// Name        : CBinomialLikelihood.cpp
// Author      : S.Rasmussen
// Date        : 14/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global headers
#include <cmath>

// Local headers
#include "CBinomialLikelihood.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/CError.h"

//**********************************************************************
// CBinomialLikelihood::CBinomialLikelihood()
// Default Constructor
//**********************************************************************
CBinomialLikelihood::CBinomialLikelihood()
{
}

//**********************************************************************
// double CBinomialLikelihood::adjustErrorValue(const double processError, const double errorValue)
// Adjust our ErrorValue based on process error
//**********************************************************************
double CBinomialLikelihood::adjustErrorValue(const double processError, const double errorValue)
{
  // adjust for N process error
  if ((errorValue > 0.0) && (processError > 0.0))
    return (1.0 / (1.0 / errorValue + 1.0 / processError));

  return errorValue;
}

//**********************************************************************
// void CBinomialLikelihood::getResult(vector<double> &scores, const vector<double> &expected, const vector<double> &observed,
//    const vector<double> &errorValue, const vector<double> &processError, const double delta)
// Calculate the Result of this Likelihood
//**********************************************************************
void CBinomialLikelihood::getResult(vector<double> &scores, const vector<double> &expected, const vector<double> &observed,
                                    const vector<double> &errorValue, const vector<double> &processError, const double delta)
{

  // Loop through expected values
  for (int i = 0; i < (int)expected.size(); ++i)
  {
    // Calculate Result
    double dErrorValue = adjustErrorValue(processError[i], errorValue[i]);
    double dScore = CMath::lnFactorial(dErrorValue) - CMath::lnFactorial(dErrorValue * (1.0 - observed[i])) - CMath::lnFactorial(dErrorValue * observed[i]) + dErrorValue * observed[i] * log(CMath::zeroFun(expected[i], delta)) + dErrorValue * (1.0 - observed[i]) * log(CMath::zeroFun(1.0 - expected[i], delta));

    scores.push_back(-dScore);
  }
}

//**********************************************************************
// void CBinomialLikelihood::simulateObserved(const vector<string> &keys, vector<double> &observed, const vector<double> &expected,
//    const vector<double> &errorValue, const vector<double> &processError, const double delta)
// Simulate our Observed values
//**********************************************************************
void CBinomialLikelihood::simulateObserved(const vector<string> &keys, vector<double> &observed, const vector<double> &expected,
                                           const vector<double> &errorValue, const vector<double> &processError, const double delta)
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
// CBinomialLikelihood::~CBinomialLikelihood()
// Destructor
//**********************************************************************
CBinomialLikelihood::~CBinomialLikelihood()
{
}
