//============================================================================
// Name        : CDerivedQuantityByCell.Test.cpp
// Author      : S.Rasmussen
// Date        : 23/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "../../Helpers/CComparer.h"
#include "../../TestFixtures/C1x1_Fixture.h"
#include "../../TestFixtures/ConfigurationFiles/AgeSize/AgeSize.h"
#include "../../TestFixtures/ConfigurationFiles/DerivedQuantitiesByCell/DerivedQuantityByCell.h"
#include "../../TestFixtures/ConfigurationFiles/Layers/DoubleLayer.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/Ageing.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/ConstantRecruitment.h"
#include "../../TestFixtures/ConfigurationFiles/Selectivities/Constant.h"
#include "../../TestFixtures/ConfigurationFiles/SizeWeight/SizeWeight.h"
#include "../CDerivedQuantityByCell.h"
#include "../CDerivedQuantityByCellManager.h"
#include "CTestDerivedQuantityByCell.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE(Test_Derived_QuantityByCell, C1x1_Fixture) {
  CTestDerivedQuantityByCell tdq;

  /**
   * Check for default value of 0.0
   */
  //  BOOST_CHECK_EQUAL(tdq.getValue(0), 0.0);
  //  BOOST_CHECK_EQUAL(tdq.getValue(1), 0.0);
  //  BOOST_CHECK_EQUAL(tdq.getValue(100), 0.0);

  /**
   * Generate 5 Items
   * 100 200 300 400 500
   */
  //  for (unsigned i = 0; i < 5; ++i)
  //    tdq.calculate(0);
  //  BOOST_CHECK_EQUAL(tdq.getValue(0), 500);
  //  BOOST_CHECK_EQUAL(tdq.getValue(1), 400);
  //  BOOST_CHECK_EQUAL(tdq.getValue(2), 300);
  //  BOOST_CHECK_EQUAL(tdq.getValue(3), 200);
  //  BOOST_CHECK_EQUAL(tdq.getValue(4), 100);
  //  BOOST_CHECK_EQUAL(tdq.getValue(5), 100);

  /**
   * Generate a 2nd initialisation phase of 5 values
   * 200 400 600 800 1000
   */
  //  for (unsigned i = 0; i < 5; ++i)
  //    tdq.calculate(1);
  //  BOOST_CHECK_EQUAL(tdq.getValue(0), 1000);
  //  BOOST_CHECK_EQUAL(tdq.getValue(1), 800);
  //  BOOST_CHECK_EQUAL(tdq.getValue(2), 600);
  //  BOOST_CHECK_EQUAL(tdq.getValue(3), 400);
  //  BOOST_CHECK_EQUAL(tdq.getValue(4), 200);
  // Now, We'll go back 1 phase
  //  BOOST_CHECK_EQUAL(tdq.getValue(5), 500);
  //  BOOST_CHECK_EQUAL(tdq.getValue(6), 400);
  //  BOOST_CHECK_EQUAL(tdq.getValue(7), 300);
  //  BOOST_CHECK_EQUAL(tdq.getValue(8), 200);
  //  BOOST_CHECK_EQUAL(tdq.getValue(9), 100);
  // Right back at the beginning now
  //  BOOST_CHECK_EQUAL(tdq.getValue(10), 100);
  //  BOOST_CHECK_EQUAL(tdq.getValue(99), 100);

  /**
   * Generate a 3rd initialisation phase of 5 values
   * 400 800 1200 1600 2000
   */
  //  for (unsigned i = 0; i < 5; ++i)
  //    tdq.calculate(2);
  //  BOOST_CHECK_EQUAL(tdq.getValue(0), 1500);
  //  BOOST_CHECK_EQUAL(tdq.getValue(1), 1200);
  //  BOOST_CHECK_EQUAL(tdq.getValue(2), 900);
  //  BOOST_CHECK_EQUAL(tdq.getValue(3), 600);
  //  BOOST_CHECK_EQUAL(tdq.getValue(4), 300);
  // Now, we'll go back 1 phase
  //  BOOST_CHECK_EQUAL(tdq.getValue(5), 1000);
  //  BOOST_CHECK_EQUAL(tdq.getValue(6), 800);
  //  BOOST_CHECK_EQUAL(tdq.getValue(7), 600);
  //  BOOST_CHECK_EQUAL(tdq.getValue(8), 400);
  //  BOOST_CHECK_EQUAL(tdq.getValue(9), 200);
  // Now, we'll try to go back more, but we should be blocked
  //  BOOST_CHECK_EQUAL(tdq.getValue(10), 200);
  //  BOOST_CHECK_EQUAL(tdq.getValue(20), 200);
  //  BOOST_CHECK_EQUAL(tdq.getValue(99), 200);

  /**
   * Calculate 5 model values
   * 0 1 2 3 4 5
   */
  //  for (unsigned i = 0; i < 5; ++i)
  //    tdq.calculate();
  //  BOOST_CHECK_EQUAL(tdq.getValue(0), 4);
  //  BOOST_CHECK_EQUAL(tdq.getValue(1), 3);
  //  BOOST_CHECK_EQUAL(tdq.getValue(2), 2);
  //  BOOST_CHECK_EQUAL(tdq.getValue(3), 1);
  //  BOOST_CHECK_EQUAL(tdq.getValue(4), 0);
  // Now, we'll go back into the last initialisation phase
  //  BOOST_CHECK_EQUAL(tdq.getValue(5), 1500);
  //  BOOST_CHECK_EQUAL(tdq.getValue(6), 1200);
  //  BOOST_CHECK_EQUAL(tdq.getValue(7), 900);
  //  BOOST_CHECK_EQUAL(tdq.getValue(8), 600);
  //  BOOST_CHECK_EQUAL(tdq.getValue(9), 300);
  // Now, we'll try to go back more, but we should be blocked
  //  BOOST_CHECK_EQUAL(tdq.getValue(10), 300);
  //  BOOST_CHECK_EQUAL(tdq.getValue(20), 300);
  //  BOOST_CHECK_EQUAL(tdq.getValue(99), 300);
}

#endif
