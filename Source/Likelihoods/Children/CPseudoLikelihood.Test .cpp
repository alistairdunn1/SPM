//============================================================================
// Name        : CPseudoLikelihood.Test.cpp
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "../Factory/CLikelihoodFactory.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(PseudoLikelihood)
{

  // Generate data
  vector<double> scores;
  vector<double> expected;
  vector<double> observed;
  vector<double> errorValue;
  vector<double> processError;
  double delta = 1e-05;

  // Test case 1
  expected.push_back(0.1);
  observed.push_back(0.1);
  errorValue.push_back(50);
  processError.push_back(0.0);
  // Test case 2
  expected.push_back(0.2);
  observed.push_back(0.1);
  errorValue.push_back(50);
  processError.push_back(0.0);
  // Test case 3
  expected.push_back(0.3);
  observed.push_back(0.1);
  errorValue.push_back(50);
  processError.push_back(0.0);
  // Test case 4
  expected.push_back(0.4);
  observed.push_back(0.1);
  errorValue.push_back(50);
  processError.push_back(0.0);
  // Test case 5
  expected.push_back(0.5);
  observed.push_back(0.1);
  errorValue.push_back(50);
  processError.push_back(0.0);
  // Test case 6
  expected.push_back(0.5);
  observed.push_back(0.1);
  errorValue.push_back(50);
  processError.push_back(10);
  // Test case 7
  expected.push_back(0.5);
  observed.push_back(0.1);
  errorValue.push_back(50);
  processError.push_back(15);

  // Run the likelihood
  CLikelihood *pLikelihood_PAA = CLikelihoodFactory::buildLikelihood(PARAM_PROPORTIONS_AT_AGE, PARAM_PSEUDO);
  pLikelihood_PAA->getResult(scores, expected, observed, errorValue, processError, delta);
  delete pLikelihood_PAA;

  // Check results
  BOOST_CHECK_EQUAL(0.0, scores[0]);
  BOOST_CHECK_EQUAL(0.0, scores[1]);
  BOOST_CHECK_EQUAL(0.0, scores[2]);
  BOOST_CHECK_EQUAL(0.0, scores[3]);
  BOOST_CHECK_EQUAL(0.0, scores[4]);
  BOOST_CHECK_EQUAL(0.0, scores[5]);
  BOOST_CHECK_EQUAL(0.0, scores[6]);

  // Run the likelihood
  CLikelihood *pLikelihood_AB = CLikelihoodFactory::buildLikelihood(PARAM_ABUNDANCE, PARAM_PSEUDO);
  pLikelihood_AB->getResult(scores, expected, observed, errorValue, processError, delta);
  delete pLikelihood_AB;

  // Check results
  BOOST_CHECK_EQUAL(0.0, scores[0]);
  BOOST_CHECK_EQUAL(0.0, scores[1]);
  BOOST_CHECK_EQUAL(0.0, scores[2]);
  BOOST_CHECK_EQUAL(0.0, scores[3]);
  BOOST_CHECK_EQUAL(0.0, scores[4]);
  BOOST_CHECK_EQUAL(0.0, scores[5]);
  BOOST_CHECK_EQUAL(0.0, scores[6]);

  // Run the likelihood
  CLikelihood *pLikelihood_BIO = CLikelihoodFactory::buildLikelihood(PARAM_BIOMASS, PARAM_PSEUDO);
  pLikelihood_BIO->getResult(scores, expected, observed, errorValue, processError, delta);
  delete pLikelihood_BIO;

  // Check results
  BOOST_CHECK_EQUAL(0.0, scores[0]);
  BOOST_CHECK_EQUAL(0.0, scores[1]);
  BOOST_CHECK_EQUAL(0.0, scores[2]);
  BOOST_CHECK_EQUAL(0.0, scores[3]);
  BOOST_CHECK_EQUAL(0.0, scores[4]);
  BOOST_CHECK_EQUAL(0.0, scores[5]);
  BOOST_CHECK_EQUAL(0.0, scores[6]);

  // Run the likelihood
  CLikelihood *pLikelihood_PBC = CLikelihoodFactory::buildLikelihood(PARAM_PROPORTIONS_BY_CATEGORY, PARAM_PSEUDO);
  pLikelihood_PBC->getResult(scores, expected, observed, errorValue, processError, delta);
  delete pLikelihood_PBC;

  // Check results
  BOOST_CHECK_EQUAL(0.0, scores[0]);
  BOOST_CHECK_EQUAL(0.0, scores[1]);
  BOOST_CHECK_EQUAL(0.0, scores[2]);
  BOOST_CHECK_EQUAL(0.0, scores[3]);
  BOOST_CHECK_EQUAL(0.0, scores[4]);
  BOOST_CHECK_EQUAL(0.0, scores[5]);
  BOOST_CHECK_EQUAL(0.0, scores[6]);
}

#endif /* TEST */
