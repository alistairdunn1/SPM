//============================================================================
// Name        : CBiomassDerivedQuantity.Test.cpp
// Author      : A.Dunn
// Copyright   : Copyright NIWA Science �2013 - www.niwa.co.nz
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "CBiomassDerivedQuantity.h"
#include "../CDerivedQuantityManager.h"
#include "../CDerivedQuantity.h"
#include "../../Helpers/CComparer.h"
#include "../../TestFixtures/C1x1_Fixture.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/Ageing.h"
#include "../../TestFixtures/ConfigurationFiles/AgeSize/AgeSize.h"
#include "../../TestFixtures/ConfigurationFiles/SizeWeight/SizeWeight.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/ConstantRecruitment.h"
#include "../../TestFixtures/ConfigurationFiles/Selectivities/Constant.h"
#include "../../TestFixtures/ConfigurationFiles/DerivedQuantities/DerivedQuantity.h"
#include "../../TestFixtures/ConfigurationFiles/Layers/DoubleLayer.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE(Biomass_Derived_Quantity, C1x1_Fixture)
{

  // Add What we need to configuration
  // Then run our model
  addToConfiguration(ageing);
  addToConfiguration(age_size_vonB);
  addToConfiguration(size_weight_none);
  addToConfiguration(constant_recruitment);
  addToConfiguration(derived_quantity);
  addToConfiguration(constant);
  addToConfiguration(numeric);
  addToTimeStep("ageing constant_recruitment");
  loadAndRunEnvironment();

  // Check our Results
  CDerivedQuantityManager *pManager = CDerivedQuantityManager::Instance();
  CDerivedQuantity *pQuantity = pManager->getDerivedQuantity("derived_quantity");
  CWorldSquare *pSquare = getSquare();

  // Check Results
  BOOST_CHECK_EQUAL(15, pQuantity->getValuesSize());
  BOOST_CHECK_EQUAL(pSquare->getAbundance() * 2, pQuantity->getValue(0));
  BOOST_CHECK_EQUAL(pQuantity->getValue(1), 2800.0);
  BOOST_CHECK_EQUAL(pQuantity->getValue(2), 2600.0);
  BOOST_CHECK_EQUAL(pQuantity->getValue(3), 2400.0);
  BOOST_CHECK_EQUAL(pQuantity->getValue(4), 2200.0);
  BOOST_CHECK_EQUAL(pQuantity->getValue(5), 2000.0);
  BOOST_CHECK_EQUAL(pQuantity->getValue(6), 1800.0);
  BOOST_CHECK_EQUAL(pQuantity->getValue(7), 1600.0);
  BOOST_CHECK_EQUAL(pQuantity->getValue(8), 1400.0);
  BOOST_CHECK_EQUAL(pQuantity->getValue(9), 1200.0);
  BOOST_CHECK_EQUAL(pQuantity->getValue(10), 1000.0);
  BOOST_CHECK_EQUAL(pQuantity->getValue(11), 800.0);
  BOOST_CHECK_EQUAL(pQuantity->getValue(12), 600.0);
  BOOST_CHECK_EQUAL(pQuantity->getValue(13), 400.0);
  BOOST_CHECK_EQUAL(pQuantity->getValue(14), 200.0);
  BOOST_CHECK_EQUAL(pQuantity->getValue(15), 0.0);
  BOOST_CHECK_EQUAL(pQuantity->getValue(16), 0.0); // Too Large, should return 0.0
  BOOST_CHECK_EQUAL(pQuantity->getValue(17), 0.0); // ""
}

#endif
