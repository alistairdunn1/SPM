//============================================================================
// Name        : CBiomassObservation.Test.cpp
// Author      : A.Dunn
// Copyright   : Copyright NIWA Science �2013 - www.niwa.co.nz
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "../../Observations/CObservation.h"
#include "../../Observations/CObservationManager.h"
#include "../../Helpers/CComparer.h"
#include "../../TestFixtures/C3x3_Fixture.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/Ageing.h"
#include "../../TestFixtures/ConfigurationFiles/AgeSize/AgeSize.h"
#include "../../TestFixtures/ConfigurationFiles/SizeWeight/SizeWeight.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/ConstantRecruitment.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/AnnualMortalityRate.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/CategoryTransitionRate.h"
#include "../../TestFixtures/ConfigurationFiles/Selectivities/LogisticProducing.h"
#include "../../TestFixtures/ConfigurationFiles/Selectivities/Constant.h"
#include "../../TestFixtures/ConfigurationFiles/Catchabilities/Catchability.h"
#include "../../TestFixtures/ConfigurationFiles/Layers/StringLayer.h"
#include "../../TestFixtures/ConfigurationFiles/Observations/Biomass.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE(BiomassObservation, C3x3_Fixture)
{

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
  addToConfiguration(biomass_observation);
  addToConfiguration(constant);
  addToTimeStep("ageing constant_recruitment category_transition_rate annual_mortality_rate");
  loadAndRunEnvironment();

  // Check our Results
  CObservationManager *pManager = CObservationManager::Instance();
  CObservation *pObservation = pManager->getObservation("biomass_observation");

  vector<SComparison *> vComparisons;
  pObservation->fillComparisons(vComparisons);

  BOOST_REQUIRE_EQUAL(vComparisons.size(), 6.0);

  SComparison *pComparison = vComparisons[0];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaA");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 0.10, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 60.0, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.45036991830339179, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 1202.7134007388327, 1e-9);

  pComparison = vComparisons[1];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaB");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 0.12, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 40.0, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.30024661220226112, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 837.26363028909884, 1e-9);

  pComparison = vComparisons[2];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaC");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 0.13, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 20.0, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.15012330610113056, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 714.41621457987969, 1e-9);

  pComparison = vComparisons[3];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaD");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 0.14, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 20.0, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.15012330610113056, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 616.95036283520096, 1e-9);

  pComparison = vComparisons[4];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaE");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 0.15, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 20.0, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.15012330610113056, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 538.32830605461959, 1e-9);

  pComparison = vComparisons[5];
  BOOST_CHECK_EQUAL(pComparison->sKey, "AreaF");
  BOOST_CHECK_CLOSE(pComparison->dErrorValue, 0.16, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dObservedValue, 20.0, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dExpectedValue, 0.15012330610113056, 1e-9);
  BOOST_CHECK_CLOSE(pComparison->dScore, 473.98919711083579, 1e-9);

  for (int i = 0; i < 3; ++i)
  {
    for (int j = 0; j < 3; ++j)
    {
      CWorldSquare *pSquare = getSquare(i, j);

      BOOST_CHECK_CLOSE(pSquare->getAbundance(), 150.12330610113057, 1e-9);

      // Our Expected Results
      double immature[] = {11.111111111111111, 11.111111111111111, 11.111111111111111, 11.111111111111111, 10.833333333333332, 10.416266318250708, 9.5285900493878319, 8.039167031304288, 6.2110466653061902, 14.041008649763675};
      double mature[] = {0.0, 0.0, 0.0, 0.0, 0.275260149348305342601493483053126014934830531260149348305312601493483053126014934830531260149348305312601493483053126014934830531, 0.68514671490004475, 1.5301395904028099, 2.8847802067147867, 4.4252416779189687, 36.808881270055224};
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
