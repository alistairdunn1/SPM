//============================================================================
// Name        : CDoubleNormalSelectivity.Test.cpp
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
BOOST_FIXTURE_TEST_CASE(DoubleNormalSelectivity, CWorld_Fixture)
{

  CSelectivity *pSelectivity = 0;
  BOOST_REQUIRE_NO_THROW(pSelectivity = CSelectivityFactory::buildSelectivity(PARAM_DOUBLE_NORMAL, false));

  pSelectivity->addParameter(PARAM_LABEL, "selectivity");
  pSelectivity->addParameter(PARAM_MU, "5");
  pSelectivity->addParameter(PARAM_SIGMA_L, "1");
  pSelectivity->addParameter(PARAM_SIGMA_R, "10");

  BOOST_REQUIRE_NO_THROW(pSelectivity->validate());
  BOOST_REQUIRE_NO_THROW(pSelectivity->build());

  BOOST_CHECK_EQUAL(pSelectivity->getResult(0), 1.52587890625e-05);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(1), 0.001953125);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(2), 0.0625);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(3), 0.5);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(4), 1.0);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(5), 0.99309249543703593);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(6), 0.97265494741228553);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(7), 0.9395227492140118);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(8), 0.89502507092797245);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(9), 0.8408964152537145);
  BOOST_CHECK_EQUAL(pSelectivity->getResult(10), 0.7791645796604999);

  BOOST_CHECK_EQUAL(pSelectivity->getResult(19), 0.21022410381342863);

  BOOST_REQUIRE_THROW(pSelectivity->getResult(20), std::string);

  delete pSelectivity;
}
#endif
