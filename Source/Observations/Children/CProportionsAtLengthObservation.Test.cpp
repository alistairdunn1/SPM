//============================================================================
// Name        : CProportionsAtLengthObservation.Test.cpp
// Author      :
// Date        :
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "../../Helpers/CComparer.h"
#include "../../Observations/CObservation.h"
#include "../../Observations/CObservationManager.h"
#include "../../TestFixtures/C3x3_Fixture.h"
#include "../../TestFixtures/ConfigurationFiles/AgeSize/AgeSize.h"
#include "../../TestFixtures/ConfigurationFiles/AgeingError/AgeingError.h"
#include "../../TestFixtures/ConfigurationFiles/Catchabilities/Catchability.h"
#include "../../TestFixtures/ConfigurationFiles/Layers/StringLayer.h"
#include "../../TestFixtures/ConfigurationFiles/Observations/ProportionsAtLength.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/Ageing.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/AnnualMortalityRate.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/CategoryTransitionRate.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/ConstantRecruitment.h"
#include "../../TestFixtures/ConfigurationFiles/Selectivities/Constant.h"
#include "../../TestFixtures/ConfigurationFiles/Selectivities/LogisticProducing.h"
#include "../../TestFixtures/ConfigurationFiles/SizeWeight/SizeWeight.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE(ProportionsAtLengthObservation, C3x3_Fixture) {
  // Add What we need to configuration
  // Then run our model
  addToConfiguration(ageing);
  addToConfiguration(age_size_vonB);
  addToConfiguration(size_weight_none);
  addToConfiguration(constant_recruitment);
  addToConfiguration(annual_mortality_rate);
  addToConfiguration(category_transition_rate);
  addToConfiguration(logistic_producing);
  addToConfiguration(catchability_basic);
  addToConfiguration(string_layer);
  addToConfiguration(proportions_at_length_observation);
  addToConfiguration(constant);
  addToTimeStep("ageing constant_recruitment category_transition_rate annual_mortality_rate");
  BOOST_REQUIRE_NO_THROW(loadAndRunEnvironment());

  // Check our Results
  CObservationManager* pManager     = CObservationManager::Instance();
  CObservation*        pObservation = pManager->getObservation("proportions_at_length_observation");

  vector<SComparison*> vComparisons;
  pObservation->fillComparisons(vComparisons);

  BOOST_REQUIRE_EQUAL(vComparisons.size(), 36.0);

  SComparison* pComparison = vComparisons[0];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaA");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 100, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.1, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.074013232186787223, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 41.139526457358429, 1e-9);

  pComparison = vComparisons[1];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaA");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 100, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.2, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.074013232186787223, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 94.405844229329148, 1e-9);

  pComparison = vComparisons[2];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaA");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 100, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.3, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.14802646437357445, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 131.96916258490614, 1e-9);

  pComparison = vComparisons[3];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaA");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 100, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.20, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.29437590032737282, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 66.793571576349024, 1e-9);

  pComparison = vComparisons[4];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaA");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 100, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.10, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.40957117092547829, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 24.030858485242309, 1e-9);

  pComparison = vComparisons[5];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaA");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 100, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.1, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 275.32024460802086, 1e-9);

  pComparison = vComparisons[6];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaB");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 120, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.20, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.074013232186787237, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 117.26900272040723, 1e-9);

  pComparison = vComparisons[7];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaB");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 120, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.30, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.074013232186787237, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 189.44610452559681, 1e-9);

  pComparison = vComparisons[8];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaB");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 120, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.20, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.14802646437357447, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 100.63347038696853, 1e-9);

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      CWorldSquare* pSquare = getSquare(i, j);

      BOOST_CHECK_CLOSE(pSquare->getAbundance(), 150.12330610113057, 1e-9);

      // Our Expected Results
      double immature[] = {11.111111111111111, 11.111111111111111, 11.111111111111111, 11.111111111111111, 10.833333333333332,
                           10.416266318250708, 9.5285900493878319, 8.039167031304288,  6.2110466653061902, 14.041008649763675};
      double mature[]   = {
          0.0,
          0.0,
          0.0,
          0.0,
          0.275260149348305342601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531,
          0.68514671490004475,
          1.5301395904028099,
          2.8847802067147867,
          4.4252416779189687,
          36.808881270055224};
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
  }
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE(ProportionsAtLengthObservationWithCompoundCategories, C3x3_Fixture) {
  // Add What we need to configuration
  // Then run our model
  addToConfiguration(ageing);
  addToConfiguration(age_size_vonB);
  addToConfiguration(size_weight_none);
  addToConfiguration(constant_recruitment);
  addToConfiguration(annual_mortality_rate);
  addToConfiguration(category_transition_rate);
  addToConfiguration(logistic_producing);
  addToConfiguration(catchability_basic);
  addToConfiguration(string_layer);
  addToConfiguration(proportions_at_length_observation_with_compound_categories);
  addToConfiguration(constant);
  addToTimeStep("ageing constant_recruitment category_transition_rate annual_mortality_rate");
  BOOST_REQUIRE_NO_THROW(loadAndRunEnvironment());

  // Check our Results
  CObservationManager* pManager     = CObservationManager::Instance();
  CObservation*        pObservation = pManager->getObservation("proportions_at_length_observation_with_compound_categories");

  vector<SComparison*> vComparisons;
  pObservation->fillComparisons(vComparisons);

  BOOST_REQUIRE_EQUAL(vComparisons.size(), 72.0);

  SComparison* pComparison = vComparisons[0];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaA");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 100, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.025, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.074013232186787209, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 7.709752073417584, 1e-9);

  pComparison = vComparisons[1];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaA");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 100, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.05, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.074013232186787209, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 17.805048684923065, 1e-9);

  pComparison = vComparisons[2];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaA");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 100, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.175, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.14802646437357442, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 68.374689414579322, 1e-9);

  pComparison = vComparisons[3];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaA");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 100, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.025, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.25856982330329736, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 4.5824473823874285, 1e-9);

  pComparison = vComparisons[4];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaA");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 100, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.05, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.13490280650645317, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 14.803495300969626, 1e-9);

  pComparison = vComparisons[5];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaA");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 100, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.175, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 490.32102183803761, 1e-9);

  pComparison = vComparisons[6];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaA");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 100, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.025, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.0, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 66.254931611083194, 1e-9);

  pComparison = vComparisons[7];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaA");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 100, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.05, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 134.89540776025427, 1e-9);

  pComparison = vComparisons[8];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaA");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 100, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 0.175, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 490.32102183803761, 1e-9);

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      CWorldSquare* pSquare = getSquare(i, j);

      BOOST_CHECK_CLOSE(pSquare->getAbundance(), 150.12330610113057, 1e-9);

      // Our Expected Results
      double immature[] = {11.111111111111111, 11.111111111111111, 11.111111111111111, 11.111111111111111, 10.833333333333332,
                           10.416266318250708, 9.5285900493878319, 8.039167031304288,  6.2110466653061902, 14.041008649763675};
      double mature[]   = {
          0.0,
          0.0,
          0.0,
          0.0,
          0.275260149348305342601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531,
          0.68514671490004475,
          1.5301395904028099,
          2.8847802067147867,
          4.4252416779189687,
          36.808881270055224};
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
  }
}

#endif /* TEST */
