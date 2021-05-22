//============================================================================
// Name        : CNormalLikelihood.Test.cpp
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
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
BOOST_AUTO_TEST_CASE(NormalLikelihood)
{
  CRandomNumberGenerator::Instance()->Reset(31373u);

  // Get Likelihood
  CLikelihood *pLikelihood = CLikelihoodFactory::buildLikelihood(PARAM_ABUNDANCE, PARAM_NORMAL);

  // Generate data
  vector<string> keys;
  vector<double> scores;
  vector<double> observed;
  vector<double> expected;
  vector<double> errorValue;
  vector<double> processError;
  double delta = 1e-11;

  keys.push_back("A");
  observed.push_back(1000);
  expected.push_back(500);
  errorValue.push_back(0.25);
  processError.push_back(0);

  keys.push_back("B");
  observed.push_back(1000);
  expected.push_back(500);
  errorValue.push_back(0.25);
  processError.push_back(0.20);

  keys.push_back("C");
  observed.push_back(500);
  expected.push_back(500);
  errorValue.push_back(0.25);
  processError.push_back(0.00);

  keys.push_back("D");
  observed.push_back(500);
  expected.push_back(500);
  errorValue.push_back(0.25);
  processError.push_back(0.20);

  // run the likelihood
  pLikelihood->getResult(scores, expected, observed, errorValue, processError, delta);

  // Check results
  BOOST_CHECK_CLOSE(12.8283137373, scores[0], 1e-9);
  BOOST_CHECK_CLOSE(9.9537106387, scores[1], 1e-9);
  BOOST_CHECK_CLOSE(4.8283137373, scores[2], 1e-9);
  BOOST_CHECK_CLOSE(5.0756618582, scores[3], 1e-9);

  // Get results
  pLikelihood->simulateObserved(keys, observed, expected, errorValue, processError, delta);

  // Check results
  BOOST_CHECK_CLOSE(observed[0], 557.59511915082294, 1e-9);
  BOOST_CHECK_CLOSE(observed[1], 976.98119489450221, 1e-9);
  BOOST_CHECK_CLOSE(observed[2], 431.078887652900960, 1e-9);
  BOOST_CHECK_CLOSE(observed[3], 392.17240873606607, 1e-9);

  // clear memory
  delete pLikelihood;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE(NormalLikelihood_1x1, C1x1_Fixture)
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
  CLikelihood *pLikelihood = CLikelihoodFactory::buildLikelihood(PARAM_ABUNDANCE, PARAM_LOGNORMAL);

  // run the likelihood
  // vector<double> scores;
  // pLikelihood->getResult(scores, expected, observed, errorValue, processError, delta);

  // Check results
  //BOOST_CHECK_CLOSE(16.300417207752272, scores[0], 1e-9);
  //BOOST_CHECK_CLOSE(12.834681304952547, scores[1], 1e-9);

  // Get results
  //pLikelihood->simulateObserved(keys, observed, expected, errorValue, processError, delta);

  // Check results
  //BOOST_CHECK_CLOSE(observed[0], 650.17691083787884, 1e-9);
  //BOOST_CHECK_CLOSE(observed[1], 598.85217168819054,  1e-9);

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
