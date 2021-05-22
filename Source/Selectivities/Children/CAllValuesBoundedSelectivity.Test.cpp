//============================================================================
// Name        : CAllValuesBoundedSelectivity.Test.cpp
// Author      : S.Rasmussen
// Date        : 24/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>
#include <boost/lexical_cast.hpp>

// Local Includes
#include "../Factory/CSelectivityFactory.h"
#include "../../TestFixtures/CWorld_Fixture.h"
#include "../../Helpers/CConvertor.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE(AllValuesBoundedSelectivity, CWorld_Fixture)
{

  CSelectivity *pSelectivity = 0;
  BOOST_REQUIRE_NO_THROW(pSelectivity = CSelectivityFactory::buildSelectivity(PARAM_ALL_VALUES_BOUNDED, false));

  pSelectivity->addParameter(PARAM_LABEL, "selectivity");
  pSelectivity->addParameter(PARAM_L, "1");
  pSelectivity->addParameter(PARAM_H, "10");

  for (int i = 0; i < 9; ++i)
    pSelectivity->addParameter(PARAM_V, boost::lexical_cast<string>(i * 2));

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
  BOOST_CHECK_EQUAL(pSelectivity->getResult(9), 16.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(10), 16.0);

  BOOST_CHECK_EQUAL(pSelectivity->getResult(19), 16.0);

  BOOST_REQUIRE_THROW(pSelectivity->getResult(20), std::string);

  delete pSelectivity;
}
#endif
