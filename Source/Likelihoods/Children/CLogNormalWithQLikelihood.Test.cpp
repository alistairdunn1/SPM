//============================================================================
// Name        : CLogNormalLikelihood.Test.cpp
// Author      : S.Rasmussen
// Date        : 29/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "../Factory/CLikelihoodFactory.h"
#include "../../TestFixtures/C1x1_Fixture.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/Ageing.h"
#include "../../TestFixtures/ConfigurationFiles/AgeSize/AgeSize.h"
#include "../../TestFixtures/ConfigurationFiles/SizeWeight/SizeWeight.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/ConstantRecruitment.h"
#include "../../RandomNumberGenerator/CRandomNumberGenerator.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(LogNormalWithQLikelihood)
{
  CRandomNumberGenerator::Instance()->Reset(31373u);

  // Get Likelihood
  CLikelihood *pLikelihood = CLikelihoodFactory::buildLikelihood(PARAM_BIOMASS, PARAM_LOGNORMAL);

  // Generate data
  vector<string> keys;
  vector<double> scores;
  vector<double> observed;
  vector<double> expected;
  vector<double> errorValue;
  vector<double> processError;
  double delta = 1e-05;

  for (int i = 0; i < 4; ++i)
  {
    keys.push_back("A");
    observed.push_back(0.25);
    expected.push_back(0.25);
    errorValue.push_back(0.0001);
    processError.push_back(0);
  }
  for (int i = 0; i < 4; ++i)
  {
    keys.push_back("B");
    observed.push_back(0.25);
    expected.push_back(0.25);
    errorValue.push_back(0.50);
    processError.push_back(0);
  }

  // run the likelihood
  pLikelihood->getResult(scores, expected, observed, errorValue, processError, delta);

  // Check results
  BOOST_CHECK_CLOSE(-9.2103403762649183, scores[0], 1e-9);
  BOOST_CHECK_CLOSE(-9.2103403762649183, scores[1], 1e-9);
  BOOST_CHECK_CLOSE(-9.2103403762649183, scores[2], 1e-9);
  BOOST_CHECK_CLOSE(-9.2103403762649183, scores[3], 1e-9);
  BOOST_CHECK_CLOSE(-0.7220770494654815, scores[4], 1e-9);
  BOOST_CHECK_CLOSE(-0.7220770494654815, scores[5], 1e-9);
  BOOST_CHECK_CLOSE(-0.7220770494654815, scores[6], 1e-9);

  // Get results
  pLikelihood->simulateObserved(keys, observed, expected, errorValue, processError, delta);

  // Check results
  BOOST_CHECK_CLOSE(observed[0], 0.25001151803908866, 1e-9);
  BOOST_CHECK_CLOSE(observed[1], 0.25007450179597446, 1e-9);
  BOOST_CHECK_CLOSE(observed[2], 0.24998621490767847, 1e-9);
  BOOST_CHECK_CLOSE(observed[3], 0.24998315947676214, 1e-9);
  BOOST_CHECK_CLOSE(observed[4], 0.077455283489012747, 1e-9);
  BOOST_CHECK_CLOSE(observed[5], 0.18175128229123977, 1e-9);
  BOOST_CHECK_CLOSE(observed[6], 0.18460806280874451, 1e-9);
  BOOST_CHECK_CLOSE(observed[7], 0.45561177771504574, 1e-9);

  // clear memory
  delete pLikelihood;
}

#endif /* TEST */
