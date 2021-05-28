//============================================================================
// Name        : CConstantPreferenceFunction.Test.cpp
// Author      : S.Rasmussen
// Date        : 18/02/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "../../TestFixtures/CLayer_Fixture.h"
#include "../Factory/CPreferenceFunctionFactory.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE(ConstantPreferenceFunction_DoubleLayer, CLayer_Fixture) {
  CPreferenceFunction* pPreference = 0;
  BOOST_REQUIRE_NO_THROW(pPreference = CPreferenceFunctionFactory::buildPreferenceFunction(PARAM_CONSTANT, false));

  pPreference->addParameter(PARAM_LABEL, "constant");
  pPreference->addParameter(PARAM_ALPHA, "2");
  pPreference->addParameter(PARAM_LAYER, "double_layer");

  BOOST_REQUIRE_NO_THROW(pPreference->validate());
  BOOST_REQUIRE_NO_THROW(pPreference->build());

  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 0, 0), 1.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 0, 1), 4.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 0, 2), 9.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 0, 3), 16.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 0, 4), 25.0, 1e-9);

  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 2, 0), 121.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 2, 1), 144.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 2, 2), 169.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 2, 3), 196.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 2, 4), 225.0, 1e-9);

  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 0, 0), 1.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(1, 0, 0, 1), 4.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 2, 0, 2), 9.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(3, 0, 0, 3), 16.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 4, 0, 4), 25.0, 1e-9);

  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 2, 0), 121.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 1, 2, 1), 144.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(2, 0, 2, 2), 169.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 3, 2, 3), 196.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(4, 0, 2, 4), 225.0, 1e-9);

  delete pPreference;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE(ConstantPreferenceFunction_DistanceLayer, CLayer_Fixture) {
  CPreferenceFunction* pPreference = 0;
  BOOST_REQUIRE_NO_THROW(pPreference = CPreferenceFunctionFactory::buildPreferenceFunction(PARAM_CONSTANT, false));

  pPreference->addParameter(PARAM_LABEL, "constant");
  pPreference->addParameter(PARAM_ALPHA, "3");
  pPreference->addParameter(PARAM_LAYER, "distance_layer");

  BOOST_REQUIRE_NO_THROW(pPreference->validate());
  BOOST_REQUIRE_NO_THROW(pPreference->build());

  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 0, 0), 5.0000000000000004e-016, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 1, 0, 0), 1.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 2, 0, 0), 8.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 3, 0, 0), 27.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 4, 0, 0), 64.0, 1e-9);

  BOOST_CHECK_CLOSE(pPreference->getResult(1, 0, 0, 0), 1.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(1, 1, 0, 0), 2.8284271247461907, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(1, 2, 0, 0), 11.180339887498951, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(1, 3, 0, 0), 31.6227766016838, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(1, 4, 0, 0), 70.092795635500238, 1e-9);

  BOOST_CHECK_CLOSE(pPreference->getResult(2, 0, 0, 0), 8.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(2, 1, 0, 1), 8.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(2, 2, 0, 2), 8.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(2, 3, 0, 3), 8.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(2, 4, 0, 4), 8.0, 1e-9);

  BOOST_CHECK_CLOSE(pPreference->getResult(3, 0, 0, 0), 27.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(3, 1, 1, 0), 11.180339887498951, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(3, 2, 2, 0), 11.180339887498951, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(3, 3, 3, 0), 27.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(3, 4, 4, 0), 70.092795635500238, 1e-9);

  delete pPreference;
}

#endif
