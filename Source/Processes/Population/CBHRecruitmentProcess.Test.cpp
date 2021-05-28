//============================================================================
// Name        : CBHRecruitmentProcess.Test.cpp
// Author      : S.Rasmussen A.Dunn
// Date        : 19/07/2013
// Copyright   : Copyright NIWA Science �2013 - www.niwa.co.nz
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "../../TestFixtures/C1x1_Initialisation_Fixture.h"
#include "../../TestFixtures/ConfigurationFiles/AgeSize/AgeSize.h"
#include "../../TestFixtures/ConfigurationFiles/DerivedQuantities/DerivedQuantity.h"
#include "../../TestFixtures/ConfigurationFiles/Layers/DoubleLayer.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/BHRecruitment.h"
#include "../../TestFixtures/ConfigurationFiles/Selectivities/Constant.h"
#include "../../TestFixtures/ConfigurationFiles/SizeWeight/SizeWeight.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE(BHRecruitmentProcess, C1x1_Initialisation_Fixture) {
  // Add What we need to configuration
  // Then run our model
  addToConfiguration(bh_recruitment);
  addToConfiguration(age_size_vonB);
  addToConfiguration(size_weight_none);
  addToConfiguration(derived_quantity_ssb);
  addToConfiguration(numeric_one);
  addToConfiguration(constant);
  addToTimeStep("ageing bh_recruitment maturation mortality");
  loadAndRunEnvironment();

  // Check our Results
  CWorldSquare* pSquare = getSquare();

  BOOST_CHECK_CLOSE(pSquare->getAbundance(), 648.05610368680971, 1e-4);

  // Immature only should've been recruited
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 1), 54.068567541604381, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 2), 31.940989605026321, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 3), 17.946357966776191, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 4), 6.9598709753328656, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 5), 2.4250172284301641, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 6), 0.8050233300759461, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 7), 0.2622718666422896, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 8), 0.0849696214973172, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(0, 9), 0.00000, 1e-4);

  // mature only
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 1), 20.262529656096195, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 2), 31.940989605026321, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 3), 47.888091187099796, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 4), 49.556838114929484, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 5), 46.075327340173168, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 6), 40.814386043451314, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 7), 35.481968729562840, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 8), 30.674033360532228, 1e-4);
  BOOST_CHECK_CLOSE(pSquare->getValue(1, 9), 144.43098380651526, 1e-4);
}

#endif /* TEST */
