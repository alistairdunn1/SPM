//============================================================================
// Name        : CDerivedQuantity.Test.cpp
// Author      : S.Rasmussen
// Date        : 23/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "CDerivedQuantityManager.h"
#include "CDerivedQuantity.h"
#include "../Helpers/CComparer.h"
#include "../TestFixtures/C1x1_Fixture.h"
#include "../TestFixtures/ConfigurationFiles/Processes/Ageing.h"
#include "../TestFixtures/ConfigurationFiles/AgeSize/AgeSize.h"
#include "../TestFixtures/ConfigurationFiles/SizeWeight/SizeWeight.h"
#include "../TestFixtures/ConfigurationFiles/Processes/ConstantRecruitment.h"
#include "../TestFixtures/ConfigurationFiles/Selectivities/Constant.h"
#include "../TestFixtures/ConfigurationFiles/DerivedQuantities/DerivedQuantity.h"
#include "../TestFixtures/ConfigurationFiles/Layers/DoubleLayer.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE( Derived_Quantity, C1x1_Fixture ) {

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
  CDerivedQuantityManager *pManager     = CDerivedQuantityManager::Instance();
  CDerivedQuantity        *pQuantity    = pManager->getDerivedQuantity("derived_quantity");
  CWorldSquare            *pSquare      = getSquare();

  // Check Results
  BOOST_CHECK_EQUAL(pSquare->getAbundance(), pQuantity->getValue(0));
  BOOST_CHECK_EQUAL(pQuantity->getValue(1), 1400.0);
  BOOST_CHECK_EQUAL(pQuantity->getValue(2), 1300.0);
  BOOST_CHECK_EQUAL(pQuantity->getValue(3), 1200.0);
  BOOST_CHECK_EQUAL(pQuantity->getValue(4), 1100.0);
  BOOST_CHECK_EQUAL(pQuantity->getValue(5), 1000.0);
  BOOST_CHECK_EQUAL(pQuantity->getValue(6), 900.0);
  BOOST_CHECK_EQUAL(pQuantity->getValue(7), 800.0);
  BOOST_CHECK_EQUAL(pQuantity->getValue(8), 700.0);
  BOOST_CHECK_EQUAL(pQuantity->getValue(9), 600.0);
  BOOST_CHECK_EQUAL(pQuantity->getValue(10), 500.0);
  BOOST_CHECK_EQUAL(pQuantity->getValue(11), 400.0);
  BOOST_CHECK_EQUAL(pQuantity->getValue(12), 300.0);
  BOOST_CHECK_EQUAL(pQuantity->getValue(13), 200.0);
  BOOST_CHECK_EQUAL(pQuantity->getValue(14), 100.0);
  BOOST_CHECK_EQUAL(pQuantity->getValue(15), 0.0);
  BOOST_CHECK_EQUAL(pQuantity->getValue(16), 0.0); // Too Large, should return 0.0
  BOOST_CHECK_EQUAL(pQuantity->getValue(17), 0.0); // ""
}

#endif
