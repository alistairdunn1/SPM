//============================================================================
// Name        : CAllValuesSelectivity.Test.cpp
// Author      : S.Rasmussen
// Date        : 24/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/lexical_cast.hpp>
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "../../Helpers/CConvertor.h"
#include "../../TestFixtures/CWorld_Fixture.h"
#include "../Factory/CSelectivityFactory.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE(AllValuesSelectivity, CWorld_Fixture) {
  CSelectivity* pSelectivity = 0;
  BOOST_REQUIRE_NO_THROW(pSelectivity = CSelectivityFactory::buildSelectivity(PARAM_ALL_VALUES, false));

  pSelectivity->addParameter(PARAM_LABEL, "selectivity");

  for (int i = 0; i < 20; ++i) pSelectivity->addParameter(PARAM_V, boost::lexical_cast<string>(i * 2));

  pSelectivity->validate();
  BOOST_REQUIRE_NO_THROW(pSelectivity->validate());
  BOOST_REQUIRE_NO_THROW(pSelectivity->build());

  BOOST_CHECK_EQUAL(pSelectivity->getResult(0), 0.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(1), 2.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(2), 4.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(3), 6.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(4), 8.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(5), 10.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(6), 12.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(7), 14.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(8), 16.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(9), 18.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(10), 20.0);

  BOOST_CHECK_EQUAL(pSelectivity->getResult(19), 38.0);

  BOOST_REQUIRE_THROW(pSelectivity->getResult(20), std::string);

  delete pSelectivity;
}
#endif
