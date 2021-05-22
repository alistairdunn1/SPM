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
BOOST_FIXTURE_TEST_CASE(LogisticProducingSelectivity, CWorld_Fixture)
{

  CSelectivity *pSelectivity = 0;
  BOOST_REQUIRE_NO_THROW(pSelectivity = CSelectivityFactory::buildSelectivity(PARAM_LOGISTIC_PRODUCING, false));

  pSelectivity->addParameter(PARAM_LABEL, "selectivity");
  pSelectivity->addParameter(PARAM_A50, "8");
  pSelectivity->addParameter(PARAM_ATO95, "3");
  pSelectivity->addParameter(PARAM_L, "1");
  pSelectivity->addParameter(PARAM_H, "20");

  BOOST_REQUIRE_NO_THROW(pSelectivity->validate());
  BOOST_REQUIRE_NO_THROW(pSelectivity->build());

  BOOST_CHECK_CLOSE(pSelectivity->getResult(0), 0.0010370292068795884, 1e-9);
  BOOST_CHECK_CLOSE(pSelectivity->getResult(1), 0.0017271928818112837, 1e-9);
  BOOST_CHECK_CLOSE(pSelectivity->getResult(2), 0.0045877003367851103, 1e-9);
  BOOST_CHECK_CLOSE(pSelectivity->getResult(3), 0.012093777212385453, 1e-9);
  BOOST_CHECK_CLOSE(pSelectivity->getResult(4), 0.031262191160784228, 1e-9);
  BOOST_CHECK_CLOSE(pSelectivity->getResult(5), 0.076996987399869044, 1e-9);

  BOOST_CHECK_CLOSE(pSelectivity->getResult(10), 0.59398163205489984, 1e-9);
  BOOST_CHECK_CLOSE(pSelectivity->getResult(11), 0.61315004600329848, 1e-9);
  BOOST_CHECK_CLOSE(pSelectivity->getResult(12), 0.62065612287889804, 1e-9);
  BOOST_CHECK_CLOSE(pSelectivity->getResult(13), 0.62351663033386895, 1e-9);
  BOOST_CHECK_CLOSE(pSelectivity->getResult(14), 0.62459542710961446, 1e-9);
  BOOST_CHECK_CLOSE(pSelectivity->getResult(15), 0.625000675113629, 1e-9);

  BOOST_CHECK_EQUAL(pSelectivity->getResult(19), 1.0);

  BOOST_REQUIRE_THROW(pSelectivity->getResult(20), std::string);

  delete pSelectivity;
}
#endif
