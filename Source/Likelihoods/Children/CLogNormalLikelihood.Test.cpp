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
BOOST_AUTO_TEST_CASE(LogNormalLikelihood)
{
  CRandomNumberGenerator::Instance()->Reset(31373u);

  // Get Likelihood
  CLikelihood *pLikelihood = CLikelihoodFactory::buildLikelihood(PARAM_PROPORTIONS_AT_AGE, PARAM_LOGNORMAL);

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
  BOOST_CHECK_CLOSE(observed[0], 0.24999766961330266, 1e-9);
  BOOST_CHECK_CLOSE(observed[1], 0.25006064988144566, 1e-9);
  BOOST_CHECK_CLOSE(observed[2], 0.24997236788346203, 1e-9);
  BOOST_CHECK_CLOSE(observed[3], 0.24996931262178954, 1e-9);
  BOOST_CHECK_CLOSE(observed[4], 0.08611631029079406, 1e-9);
  BOOST_CHECK_CLOSE(observed[5], 0.20207465671160255, 1e-9);
  BOOST_CHECK_CLOSE(observed[6], 0.20525088157834170, 1e-9);
  BOOST_CHECK_CLOSE(observed[7], 0.50655815141926175, 1e-9);

  // clear memory
  delete pLikelihood;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE(LogNormalLikelihood_1x1, C1x1_Fixture)
{

  // Add What we need to configuration
  // Then run our model
  addToConfiguration(ageing);
  addToConfiguration(constant_recruitment);
  addToConfiguration(age_size_vonB);
  addToConfiguration(size_weight_none);

  addToTimeStep("ageing constant_recruitment");
  loadAndRunEnvironment();

  // Check our Results

  // Get Likelihood
  CLikelihood *pLikelihood = CLikelihoodFactory::buildLikelihood(PARAM_PROPORTIONS_AT_AGE, PARAM_LOGNORMAL);

  // Check results
  //  BOOST_CHECK_EQUAL(pLikelihood->simulateObserved(1.0, 0.0001, 0.001, 1e-11), 0.99845193414953692);
  //  BOOST_CHECK_EQUAL(pLikelihood->simulateObserved(1.0, 0.0001, 0.001, 1e-11), 1.0010263962677095);
  //  BOOST_CHECK_EQUAL(pLikelihood->simulateObserved(1.0, 0.0001, 0.001, 1e-11), 0.99947282571698015);
  //  BOOST_CHECK_EQUAL(pLikelihood->simulateObserved(1.0, 0.0001, 0.001, 1e-11), 0.99945174404156234);
  //  BOOST_CHECK_EQUAL(pLikelihood->simulateObserved(1.0, 0.0001, 0.001, 1e-11), 0.9992072565815735);

  // clear memory
  delete pLikelihood;

  // Check Population
  CWorldSquare *pSquare = getSquare();

  BOOST_CHECK_EQUAL(pSquare->getAbundance(), 1500.0);

  // Immature only should've aged
  for (int i = 0; i < 9; ++i)
    BOOST_CHECK_EQUAL(pSquare->getValue(0, i), 100.0);
  BOOST_CHECK_EQUAL(pSquare->getValue(0, 9), 600.0);

  // No population should've been recruited here
  for (int i = 1; i < 3; ++i)
    for (int j = 0; j < 10; ++j)
      BOOST_CHECK_EQUAL(pSquare->getValue(i, j), 0.0);
}

#endif /* TEST */
