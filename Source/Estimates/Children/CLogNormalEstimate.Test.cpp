//============================================================================
// Name        : CLogNormalPrior.Test.cpp
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
const std::string log_normal__estimate =
    R"(
@estimate
parameter selectivity[FishingSel].a50
lower_bound 1
upper_bound 20
type lognormal
mu 3
cv 5
)";

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE(LogNormalEstimate, C1x1_Empty_Fixture) {
  addToConfiguration(two_sex_no_estimates);
  addToConfiguration(log_normal__estimate);
  loadAndRunEnvironment();

  CObjectiveFunction* obj_func = CObjectiveFunction::Instance();
  obj_func->execute();
  BOOST_CHECK_CLOSE(obj_func->getScore(), 2563.1357030902504, 1e-9);

  CEstimate* estimate = CEstimateManager::Instance()->getEstimate("selectivity[FishingSel].a50");
  BOOST_ASSERT(estimate != 0);
  BOOST_CHECK_CLOSE(estimate->getValue(), 8.9817107922136952, 1e-5);

  // Check results
  estimate->setValue(1.0);
  BOOST_CHECK_CLOSE(estimate->getScore(), 0.043178942974616268, 1e-9);
  estimate->setValue(2.0);
  BOOST_CHECK_CLOSE(estimate->getScore(), 0.92290644861305016, 1e-9);
  estimate->setValue(3.0);
  BOOST_CHECK_CLOSE(estimate->getScore(), 1.505874355920795, 1e-9);
  estimate->setValue(4.0);
  BOOST_CHECK_CLOSE(estimate->getScore(), 1.9500982814472527, 1e-9);
  estimate->setValue(5.0);
  BOOST_CHECK_CLOSE(estimate->getScore(), 2.3121580779587432, 1e-9);
}
#endif /* TEST */
