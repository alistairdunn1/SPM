//============================================================================
// Name        : CEstimateInfo.Test.cpp
// Author      : S.Rasmussen
// Date        : 25/06/2012
// Copyright   : Copyright NIWA Science �2012 - www.niwa.co.nz
// Description : Unit tests for CEstimateInfo
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Headers
#include "CEstimateInfo.h"

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <string>

#include "../TestFixtures/C1x1_Fixture.h"
#include "../TestFixtures/ConfigurationFiles/AgeSize/AgeSize.h"
#include "../TestFixtures/ConfigurationFiles/Estimation/EstimateInfo.h"
#include "../TestFixtures/ConfigurationFiles/Processes/Ageing.h"
#include "../TestFixtures/ConfigurationFiles/Processes/CategoryTransitionRate.h"
#include "../TestFixtures/ConfigurationFiles/Processes/ConstantRecruitment.h"
#include "../TestFixtures/ConfigurationFiles/Selectivities/LogisticProducing.h"
#include "../TestFixtures/ConfigurationFiles/SizeWeight/SizeWeight.h"
#include "CEstimate.h"
#include "CEstimateManager.h"

// Namespaces
using namespace std;

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE(CEstimateInfo_1_Estimate, C1x1_Fixture) {
  // Add What we need to configuration
  // Then run our model
  addToConfiguration(ageing);
  addToConfiguration(age_size_vonB);
  addToConfiguration(size_weight_none);
  addToConfiguration(constant_recruitment);
  addToConfiguration(category_transition_rate_both);
  addToConfiguration(logistic_producing);
  addToConfiguration(basic_estimate_info);
  addToTimeStep("ageing constant_recruitment category_transition_rate_both");
  loadAndRunEnvironment();

  // Check our Results
  CWorldSquare* pSquare = getSquare();

  BOOST_CHECK_CLOSE(pSquare->getAbundance(), 1500.0, 1e-9);

  CEstimateManager* pManager = CEstimateManager::Instance();

  BOOST_REQUIRE_EQUAL(pManager->getEnabledEstimateCount(), 1);
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE(CEstimateInfo_2_Estimates, C1x1_Fixture) {
  // Add What we need to configuration
  // Then run our model
  addToConfiguration(ageing);
  addToConfiguration(age_size_vonB);
  addToConfiguration(size_weight_none);
  addToConfiguration(constant_recruitment);
  addToConfiguration(category_transition_rate_both);
  addToConfiguration(logistic_producing);
  addToConfiguration(basic_estimate_info_2_estimates);
  addToTimeStep("ageing constant_recruitment category_transition_rate_both");
  loadAndRunEnvironment();

  // Check our Results
  CWorldSquare* pSquare = getSquare();

  BOOST_CHECK_CLOSE(pSquare->getAbundance(), 1500.0, 1e-9);

  CEstimateManager* pManager = CEstimateManager::Instance();

  BOOST_REQUIRE_EQUAL(pManager->getEnabledEstimateCount(), 2);
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE(CEstimateInfo_Vector, C1x1_Fixture) {
  // Add What we need to configuration
  // Then run our model
  addToConfiguration(ageing);
  addToConfiguration(age_size_vonB);
  addToConfiguration(size_weight_none);
  addToConfiguration(constant_recruitment);
  addToConfiguration(category_transition_rate_both);
  addToConfiguration(logistic_producing);
  addToConfiguration(basic_estimate_info_vector);
  addToTimeStep("ageing constant_recruitment category_transition_rate_both");
  loadAndRunEnvironment();

  // Check our Results
  CWorldSquare* pSquare = getSquare();

  BOOST_CHECK_CLOSE(pSquare->getAbundance(), 1500.0, 1e-9);

  CEstimateManager* pManager = CEstimateManager::Instance();

  BOOST_REQUIRE_EQUAL(pManager->getEnabledEstimateCount(), 2);
}

#endif
