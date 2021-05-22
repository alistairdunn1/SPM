//============================================================================
// Name        : CLogisticSelectivity.Test.cpp
// Author      : A.Dunn
// Date        : 12/03/2012
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
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
// this test case will use struct F as fixture
BOOST_FIXTURE_TEST_CASE(InverseLogisticSelectivity, CWorld_Fixture)
{

  CSelectivity *pSelectivity = 0;
  BOOST_REQUIRE_NO_THROW(pSelectivity = CSelectivityFactory::buildSelectivity(PARAM_INVERSE_LOGISTIC, false));

  pSelectivity->addParameter(PARAM_LABEL, "selectivity");
  pSelectivity->addParameter(PARAM_A50, "8");
  pSelectivity->addParameter(PARAM_ATO95, "3");

  BOOST_REQUIRE_NO_THROW(pSelectivity->validate());
  BOOST_REQUIRE_NO_THROW(pSelectivity->build());

  BOOST_CHECK_CLOSE(pSelectivity->getResult(0), 0.99896297079312046, 1e-9);
  BOOST_CHECK_CLOSE(pSelectivity->getResult(1), 0.99723756906077343, 1e-9);
  BOOST_CHECK_CLOSE(pSelectivity->getResult(2), 0.99266254192933856, 1e-9);
  BOOST_CHECK_CLOSE(pSelectivity->getResult(3), 0.98065750230016491, 1e-9);
  BOOST_CHECK_CLOSE(pSelectivity->getResult(4), 0.94999999999999996, 1e-9);
  BOOST_CHECK_CLOSE(pSelectivity->getResult(5), 0.87685286197012435, 1e-9);

  BOOST_CHECK_CLOSE(pSelectivity->getResult(10), 0.049999999999999933, 1e-9);
  BOOST_CHECK_CLOSE(pSelectivity->getResult(11), 0.019342497699835093, 1e-9);
  BOOST_CHECK_CLOSE(pSelectivity->getResult(12), 0.0073374580706614401, 1e-9);
  BOOST_CHECK_CLOSE(pSelectivity->getResult(13), 0.0027624309392264568, 1e-9);
  BOOST_CHECK_CLOSE(pSelectivity->getResult(14), 0.0010370292068796472, 1e-9);
  BOOST_CHECK_CLOSE(pSelectivity->getResult(15), 0.00038888525246716377, 1e-9);

  BOOST_CHECK_CLOSE(pSelectivity->getResult(19), 7.6733015146324135e-006, 1e-9);

  BOOST_REQUIRE_THROW(pSelectivity->getResult(20), std::string);

  delete pSelectivity;
}
#endif
