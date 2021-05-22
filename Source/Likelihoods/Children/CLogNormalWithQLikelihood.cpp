//============================================================================
// Name        : CLogNormalWithQLikelihood.cpp
// Author      : S.Rasmussen
// Date        : 15/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global headers
#include <cmath>

// Local headers
#include "CLogNormalWithQLikelihood.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/CError.h"

//**********************************************************************
// CLogNormalWithQLikelihood::CLogNormalWithQLikelihood()
// Default Constructor
//**********************************************************************
CLogNormalWithQLikelihood::CLogNormalWithQLikelihood()
{
}

//**********************************************************************
// double CLogNormalWithQLikelihood::adjustErrorValue(const double processError, const double errorValue)
// Adjust our ErrorValue based on Process Error
//**********************************************************************
double CLogNormalWithQLikelihood::adjustErrorValue(const double processError, const double errorValue)
{
  // adjust for c.v. process error
  if (processError > 0.0)
    return (sqrt(errorValue * errorValue + processError * processError));

  return errorValue;
}

//**********************************************************************
// void CLogNormalWithQLikelihood::getResult(vector<double> &scores, const vector<double> &expected, const vector<double> &observed,
//     const vector<double> &errorValue, const vector<double> &processError, const double delta)
// Get the result from our likelihood for the observation
//**********************************************************************
void CLogNormalWithQLikelihood::getResult(vector<double> &scores, const vector<double> &expected, const vector<double> &observed,
                                          const vector<double> &errorValue, const vector<double> &processError, const double delta)
{

  // Loop through expected
  for (int i = 0; i < (int)expected.size(); ++i)
  {
    // Calculate score
    double dErrorValue = adjustErrorValue(processError[i], errorValue[i]);
    double dSigma = sqrt(log(1 + dErrorValue * dErrorValue));
    double dScore = log(observed[i] / CMath::zeroFun(expected[i], delta)) / dSigma + 0.5 * dSigma;
    dScore = log(dSigma) + 0.5 * (dScore * dScore);

    scores.push_back(dScore);
  }
}

//**********************************************************************
// void CLogNormalWithQLikelihood::simulateObserved(const vector<string> &keys, vector<double> &observed,
//    const vector<double> &expected, const vector<double> &errorValue, const vector<double> &processError, const double delta)
// Simulate our observed values
//**********************************************************************
void CLogNormalWithQLikelihood::simulateObserved(const vector<string> &keys, vector<double> &observed,
                                                 const vector<double> &expected, const vector<double> &errorValue, const vector<double> &processError, const double delta)
{

  // instance the random number generator
  CRandomNumberGenerator *pRandom = CRandomNumberGenerator::Instance();

  // Loop through our expected values
  map<string, double> mTotals;
  for (int i = 0; i < (int)expected.size(); ++i)
  {

    double dCV = adjustErrorValue(processError[i], errorValue[i]);
    // Check for invalid values
    if (expected[i] <= 0.0 || dCV <= 0.0)
    {
      observed[i] = delta;
    }
    else
    {
      // Generate random observation
      observed[i] = pRandom->getRandomLogNormal(expected[i], dCV);
    }
  }
}

//**********************************************************************
// CLogNormalWithQLikelihood::~CLogNormalWithQLikelihood()
// Destructor
//**********************************************************************
CLogNormalWithQLikelihood::~CLogNormalWithQLikelihood()
{
}
