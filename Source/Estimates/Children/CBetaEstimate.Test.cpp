//============================================================================
// Name        : CBetaPrior.Test.cpp
// Author      : S.Rasmussen
// Date        : 23/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// headers
#include <boost/test/unit_test.hpp>
#include <string>

#include "../../ObjectiveFunction/CObjectiveFunction.h"
#include "../../TestFixtures/C1x1_Empty_Fixture.h"
#include "../../TestFixtures/Models/TwoSex_NoEstimates.h"
#include "../CEstimate.h"
#include "../CEstimateManager.h"

// strings
const std::string beta_estimate =
    R"(
@estimate
parameter selectivity[FishingSel].a50
lower_bound 1
upper_bound 20
type beta
mu 0.3
sigma 0.05
a 0
b 10
)";

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE(BetaEstimate, C1x1_Empty_Fixture) {
  addToConfiguration(two_sex_no_estimates);
  addToConfiguration(beta_estimate);
  loadAndRunEnvironment();

  CObjectiveFunction* obj_func = CObjectiveFunction::Instance();
  obj_func->execute();
  BOOST_CHECK_CLOSE(obj_func->getScore(), 1726.6295023192379, 1e-9);

  CEstimate* estimate = CEstimateManager::Instance()->getEstimate("selectivity[FishingSel].a50");
  BOOST_ASSERT(estimate != 0);
  BOOST_CHECK_CLOSE(estimate->getValue(), 7.2724038656178385, 1e-5);

  // Check results
  estimate->setValue(1.0);
  BOOST_CHECK_CLOSE(estimate->getScore(), -2476.5137933614251, 1e-9);
  estimate->setValue(2.0);
  BOOST_CHECK_CLOSE(estimate->getScore(), -2367.250113991935, 1e-9);
  estimate->setValue(3.0);
  BOOST_CHECK_CLOSE(estimate->getScore(), -2230.4867585646953, 1e-9);
  estimate->setValue(4.0);
  BOOST_CHECK_CLOSE(estimate->getScore(), -2066.4915312599851, 1e-9);
  estimate->setValue(5.0);
  BOOST_CHECK_CLOSE(estimate->getScore(), -1868.5574163359895, 1e-9);
}

#endif /* TEST */
