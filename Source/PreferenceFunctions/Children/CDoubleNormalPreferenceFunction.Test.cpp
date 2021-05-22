//============================================================================
// Name        : CDoubleNormalPreferenceFunction.Test.cpp
// Author      : S.Rasmussen
// Date        : 19/02/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "../Factory/CPreferenceFunctionFactory.h"
#include "../../TestFixtures/CLayer_Fixture.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE(DoubleNormalPreferenceFunction_DoubleLayer, CLayer_Fixture)
{

  CPreferenceFunction *pPreference = 0;
  BOOST_REQUIRE_NO_THROW(pPreference = CPreferenceFunctionFactory::buildPreferenceFunction(PARAM_DOUBLE_NORMAL, false));

  pPreference->addParameter(PARAM_LABEL, "double_normal");
  pPreference->addParameter(PARAM_ALPHA, "3");
  pPreference->addParameter(PARAM_MU, "3.0");
  pPreference->addParameter(PARAM_SIGMA_L, "1.0");
  pPreference->addParameter(PARAM_SIGMA_R, "5.0");
  pPreference->addParameter(PARAM_LAYER, "double_layer");

  BOOST_REQUIRE_NO_THROW(pPreference->validate());
  BOOST_REQUIRE_NO_THROW(pPreference->build());

  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 0, 0), 0.000244140625, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 0, 1), 0.125, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 0, 2), 1.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 0, 3), 0.92018765062487506, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 0, 4), 0.71697762400791376, 1e-9);

  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 3, 0), 7.8543760039098104e-007, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 3, 1), 8.3133200785541867e-008, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 3, 2), 7.4505805969238281e-009, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 3, 3), 5.6540355290986891e-010, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 3, 4), 3.6331200649193931e-011, 1e-9);

  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 0, 0), 0.000244140625, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(1, 0, 0, 1), 0.125, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 2, 0, 2), 1.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(3, 0, 0, 3), 0.92018765062487506, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 4, 0, 4), 0.71697762400791376, 1e-9);

  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 3, 0), 7.8543760039098104e-007, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 1, 3, 1), 8.3133200785541867e-008, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(2, 0, 3, 2), 7.4505805969238281e-009, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 3, 3, 3), 5.6540355290986891e-010, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(4, 0, 3, 4), 3.6331200649193931e-011, 1e-9);

  delete pPreference;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE(DoubleNormalPreferenceFunction_DistanceLayer, CLayer_Fixture)
{

  CPreferenceFunction *pPreference = 0;
  BOOST_REQUIRE_NO_THROW(pPreference = CPreferenceFunctionFactory::buildPreferenceFunction(PARAM_DOUBLE_NORMAL, false));

  pPreference->addParameter(PARAM_LABEL, "double_normal");
  pPreference->addParameter(PARAM_ALPHA, "3");
  pPreference->addParameter(PARAM_MU, "3.0");
  pPreference->addParameter(PARAM_SIGMA_L, "1.0");
  pPreference->addParameter(PARAM_SIGMA_R, "5.0");
  pPreference->addParameter(PARAM_LAYER, "distance_layer");

  BOOST_REQUIRE_NO_THROW(pPreference->validate());
  BOOST_REQUIRE_NO_THROW(pPreference->build());

  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 0, 0), 7.4505805969238281e-009, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 0, 1), 0.000244140625, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 0, 2), 0.125, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 0, 3), 1.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 0, 4), 0.92018765062487506, 1e-9);

  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 3, 0), 1.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 3, 1), 0.99781199339836735, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 3, 2), 0.96995983845870126, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 3, 3), 0.87946696632102028, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 3, 4), 0.71697762400791376, 1e-9);

  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 0, 0), 7.4505805969238281e-009, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(1, 0, 0, 1), 0.0053577542439030125, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 2, 0, 2), 7.4505805969238281e-009, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(3, 0, 0, 3), 0.87946696632102028, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 4, 0, 4), 7.4505805969238281e-009, 1e-9);

  BOOST_CHECK_CLOSE(pPreference->getResult(0, 0, 3, 0), 1.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 1, 3, 1), 1.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(2, 0, 3, 2), 0.29714182499600678, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(0, 3, 3, 3), 1.0, 1e-9);
  BOOST_CHECK_CLOSE(pPreference->getResult(4, 0, 3, 4), 0.90039880704002817, 1e-9);

  delete pPreference;
}

#endif
