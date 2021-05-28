//============================================================================
// Name        : CConfigurationLoader.Test.cpp
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
#include "../CConfiguration.h"
#include "../Estimates/CEstimate.h"
#include "../Estimates/CEstimateManager.h"
#include "../Helpers/CComparer.h"
#include "../TestFixtures/C1x1_Fixture.h"
#include "../TestFixtures/ConfigurationFiles/AgeSize/AgeSize.h"
#include "../TestFixtures/ConfigurationFiles/Estimation/Estimation.h"
#include "../TestFixtures/ConfigurationFiles/Processes/Ageing.h"
#include "../TestFixtures/ConfigurationFiles/Processes/AnnualMortalityRate.h"
#include "../TestFixtures/ConfigurationFiles/Processes/CategoryTransitionRate.h"
#include "../TestFixtures/ConfigurationFiles/Processes/ConstantRecruitment.h"
#include "../TestFixtures/ConfigurationFiles/Selectivities/LogisticProducing.h"
#include "../TestFixtures/ConfigurationFiles/SizeWeight/SizeWeight.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE(ConfigurationLoader_NoEstimateValues, C1x1_Fixture) {
  // Add What we need to configuration
  // Then run our model
  addToConfiguration(ageing);
  addToConfiguration(age_size_vonB);
  addToConfiguration(size_weight_none);
  addToConfiguration(constant_recruitment);
  addToConfiguration(annual_mortality_rate);
  addToConfiguration(category_transition_rate);
  addToConfiguration(logistic_producing);
  addToConfiguration(basic_estimation);
  addToTimeStep("ageing constant_recruitment category_transition_rate annual_mortality_rate");
  loadAndRunEnvironment();

  // Check our Results
  CWorldSquare* pSquare = getSquare();

  BOOST_CHECK_CLOSE(pSquare->getAbundance(), 1351.1097549101755, 1e-9);

  // Our Expected Results
  double immature[] = {100.0, 100.0, 100.0, 100.0, 97.5, 93.746396864256383, 85.7573104444905, 72.352503281738606, 55.899419987755721, 126.36907784787311};
  double mature[]   = {0.0, 0.0, 0.0, 0.0, 2.4773413441347478, 6.1663204341004025, 13.77125631362529, 25.963021860433084, 39.827175101270718, 331.27993143049707};
  double spawning[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

  // Check Expected against model
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 0), immature[0], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 1), immature[1], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 2), immature[2], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 3), immature[3], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 4), immature[4], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 5), immature[5], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 6), immature[6], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 7), immature[7], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 8), immature[8], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 9), immature[9], 1e-9);

  BOOST_CHECK_CLOSE(pSquare->getValue(1, 0), mature[0], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 1), mature[1], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 2), mature[2], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 3), mature[3], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 4), mature[4], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 5), mature[5], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 6), mature[6], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 7), mature[7], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 8), mature[8], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 9), mature[9], 1e-9);

  BOOST_CHECK_CLOSE(pSquare->getValue(2, 0), spawning[0], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(2, 1), spawning[1], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(2, 2), spawning[2], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(2, 3), spawning[3], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(2, 4), spawning[4], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(2, 5), spawning[5], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(2, 6), spawning[6], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(2, 7), spawning[7], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(2, 8), spawning[8], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(2, 9), spawning[9], 1e-9);
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE(ConfigurationLoader_EstimateValues, C1x1_Fixture) {
  // Add What we need to configuration
  // Then run our model
  addToConfiguration(ageing);
  addToConfiguration(age_size_vonB);
  addToConfiguration(size_weight_none);
  addToConfiguration(constant_recruitment);
  addToConfiguration(annual_mortality_rate);
  addToConfiguration(category_transition_rate);
  addToConfiguration(logistic_producing);
  addToConfiguration(basic_estimation);
  addToTimeStep("ageing constant_recruitment category_transition_rate annual_mortality_rate");
  string estimateValues = "process[category_transition_rate].proportions(1)\n0.3\n0.4\n0.7";
  addToEstimateValueConfiguation(estimateValues);
  loadAndRunEnvironment();

  // Check our Results - Configuration
  CConfiguration* pConfig = CConfiguration::Instance();
  BOOST_CHECK(pConfig->getUseEstimateValues());

  // Check Results - Estimates
  CEstimateManager* pEstimateManager = CEstimateManager::Instance();
  BOOST_CHECK_EQUAL(pEstimateManager->getEstimateCount(), 1);
  BOOST_CHECK_EQUAL(pEstimateManager->getEstimateValueCount(), 3);

  CEstimate* pEstimate = 0;
  BOOST_REQUIRE_NO_THROW(pEstimate = pEstimateManager->getEstimate("process[category_transition_rate].proportions(1)"));

  BOOST_REQUIRE_NO_THROW(pEstimateManager->loadEstimateValues(0));
  BOOST_CHECK_EQUAL(pEstimate->getValue(), 0.3);
  BOOST_REQUIRE_NO_THROW(pEstimateManager->loadEstimateValues(1));
  BOOST_CHECK_EQUAL(pEstimate->getValue(), 0.4);
  BOOST_REQUIRE_NO_THROW(pEstimateManager->loadEstimateValues(2));
  BOOST_CHECK_EQUAL(pEstimate->getValue(), 0.7);

  // Check Results - Population structure
  CWorldSquare* pSquare = getSquare();

  BOOST_CHECK_CLOSE(pSquare->getAbundance(), 1321.6237024688548, 1e-9);

  // Our Expected Results
  double immature[] = {100.0, 100.0, 100.0, 100.0, 96.5, 91.298853501138851, 80.406144692466285, 62.810438831323388, 42.813956761878572, 64.982319957953905};
  double mature[]   = {0.0, 0.0, 0.0, 0.0, 3.4682778817886466, 8.5797029794486157, 18.944535868720013, 34.918273762480382, 51.592800873478531, 365.3083973581779};
  double spawning[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

  // Check Expected against model
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 0), immature[0], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 1), immature[1], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 2), immature[2], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 3), immature[3], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 4), immature[4], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 5), immature[5], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 6), immature[6], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 7), immature[7], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 8), immature[8], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 9), immature[9], 1e-9);

  BOOST_CHECK_CLOSE(pSquare->getValue(1, 0), mature[0], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 1), mature[1], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 2), mature[2], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 3), mature[3], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 4), mature[4], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 5), mature[5], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 6), mature[6], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 7), mature[7], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 8), mature[8], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 9), mature[9], 1e-9);

  BOOST_CHECK_CLOSE(pSquare->getValue(2, 0), spawning[0], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(2, 1), spawning[1], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(2, 2), spawning[2], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(2, 3), spawning[3], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(2, 4), spawning[4], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(2, 5), spawning[5], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(2, 6), spawning[6], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(2, 7), spawning[7], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(2, 8), spawning[8], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(2, 9), spawning[9], 1e-9);
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE(ConfigurationLoader_EstimateValuesx5, C1x1_Fixture) {
  // Add What we need to configuration
  // Then run our model
  addToConfiguration(ageing);
  addToConfiguration(age_size_vonB);
  addToConfiguration(size_weight_none);
  addToConfiguration(constant_recruitment);
  addToConfiguration(annual_mortality_rate);
  addToConfiguration(category_transition_rate);
  addToConfiguration(logistic_producing);
  addToConfiguration(basic_estimation);
  addToTimeStep("ageing constant_recruitment category_transition_rate annual_mortality_rate");
  string estimateValues = "process[category_transition_rate].proportions(1)\n0.3\n0.4\n0.7\n0.2\n0.5";
  addToEstimateValueConfiguation(estimateValues);
  loadAndRunEnvironment();

  // Check our Results - Configuration
  CConfiguration* pConfig = CConfiguration::Instance();
  BOOST_CHECK(pConfig->getUseEstimateValues());

  // Check Results - Estimates
  CEstimateManager* pEstimateManager = CEstimateManager::Instance();
  BOOST_CHECK_EQUAL(pEstimateManager->getEstimateCount(), 1);
  BOOST_CHECK_EQUAL(pEstimateManager->getEstimateValueCount(), 5);

  CEstimate* pEstimate = 0;
  BOOST_REQUIRE_NO_THROW(pEstimate = pEstimateManager->getEstimate("process[category_transition_rate].proportions(1)"));

  BOOST_REQUIRE_NO_THROW(pEstimateManager->loadEstimateValues(0));
  BOOST_CHECK_EQUAL(pEstimate->getValue(), 0.3);
  BOOST_REQUIRE_NO_THROW(pEstimateManager->loadEstimateValues(1));
  BOOST_CHECK_EQUAL(pEstimate->getValue(), 0.4);
  BOOST_REQUIRE_NO_THROW(pEstimateManager->loadEstimateValues(2));
  BOOST_CHECK_EQUAL(pEstimate->getValue(), 0.7);
  BOOST_REQUIRE_NO_THROW(pEstimateManager->loadEstimateValues(3));
  BOOST_CHECK_EQUAL(pEstimate->getValue(), 0.2);
  BOOST_REQUIRE_NO_THROW(pEstimateManager->loadEstimateValues(4));
  BOOST_CHECK_EQUAL(pEstimate->getValue(), 0.5);

  // Check Results - Population structure
  CWorldSquare* pSquare = getSquare();

  BOOST_CHECK_CLOSE(pSquare->getAbundance(), 1351.1097549101755, 1e-9);

  // Our Expected Results
  double immature[] = {100.0, 100.0, 100.0, 100.0, 97.5, 93.746396864256383, 85.7573104444905, 72.352503281738606, 55.899419987755721, 126.36907784787311};
  double mature[]   = {0.0, 0.0, 0.0, 0.0, 2.4773413441347478, 6.1663204341004025, 13.77125631362529, 25.963021860433084, 39.827175101270718, 331.27993143049707};
  double spawning[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

  // Check Expected against model
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 0), immature[0], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 1), immature[1], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 2), immature[2], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 3), immature[3], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 4), immature[4], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 5), immature[5], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 6), immature[6], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 7), immature[7], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 8), immature[8], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 9), immature[9], 1e-9);

  BOOST_CHECK_CLOSE(pSquare->getValue(1, 0), mature[0], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 1), mature[1], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 2), mature[2], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 3), mature[3], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 4), mature[4], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 5), mature[5], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 6), mature[6], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 7), mature[7], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 8), mature[8], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 9), mature[9], 1e-9);

  BOOST_CHECK_CLOSE(pSquare->getValue(2, 0), spawning[0], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(2, 1), spawning[1], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(2, 2), spawning[2], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(2, 3), spawning[3], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(2, 4), spawning[4], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(2, 5), spawning[5], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(2, 6), spawning[6], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(2, 7), spawning[7], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(2, 8), spawning[8], 1e-9);
  BOOST_CHECK_CLOSE(pSquare->getValue(2, 9), spawning[9], 1e-9);
}

#endif /* TEST */
