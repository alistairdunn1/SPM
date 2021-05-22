//============================================================================
// Name        : CLogisticProducingSelectivity.Test.cpp
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
#include "../Factory/CSelectivityFactory.h"
#include "../../TestFixtures/CWorld_Fixture.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE(KnifeEdgeSelectivity, CWorld_Fixture)
{

  CSelectivity *pSelectivity = 0;
  BOOST_REQUIRE_NO_THROW(pSelectivity = CSelectivityFactory::buildSelectivity(PARAM_KNIFE_EDGE, false));

  pSelectivity->addParameter(PARAM_LABEL, "selectivity");
  pSelectivity->addParameter(PARAM_E, "5");

  BOOST_REQUIRE_NO_THROW(pSelectivity->validate());
  BOOST_REQUIRE_NO_THROW(pSelectivity->build());

  BOOST_CHECK_EQUAL(pSelectivity->getResult(0), 0.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(1), 0.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(2), 0.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(3), 0.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(4), 1.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(5), 1.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(6), 1.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(7), 1.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(8), 1.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(9), 1.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(10), 1.0);

  BOOST_CHECK_EQUAL(pSelectivity->getResult(19), 1.0);

  BOOST_REQUIRE_THROW(pSelectivity->getResult(20), std::string);

  delete pSelectivity;
}
#endif
