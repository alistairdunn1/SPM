//============================================================================
// Name        : CConstantSelectivity.Test.cpp
// Author      : S.Rasmussen
// Date        : 12/02/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "../../TestFixtures/CWorld_Fixture.h"
#include "../Factory/CSelectivityFactory.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE(ConstantSelectivity, CWorld_Fixture) {
  CSelectivity* pSelectivity = 0;
  BOOST_REQUIRE_NO_THROW(pSelectivity = CSelectivityFactory::buildSelectivity(PARAM_CONSTANT, false));

  pSelectivity->addParameter(PARAM_LABEL, "selectivity");
  pSelectivity->addParameter(PARAM_C, "5");

  BOOST_REQUIRE_NO_THROW(pSelectivity->validate());
  BOOST_REQUIRE_NO_THROW(pSelectivity->build());

  BOOST_CHECK_EQUAL(pSelectivity->getResult(0), 5.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(1), 5.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(2), 5.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(3), 5.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(4), 5.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(5), 5.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(6), 5.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(7), 5.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(8), 5.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(9), 5.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(10), 5.0);

  BOOST_CHECK_EQUAL(pSelectivity->getResult(19), 5.0);

  BOOST_REQUIRE_THROW(pSelectivity->getResult(20), std::string);

  delete pSelectivity;
}
#endif
