//============================================================================
// Name        : CUniformLogPrior.Test.cpp
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

#include "../CEstimateManager.h"
#include "../CEstimate.h"
#include "../../TestFixtures/C1x1_Empty_Fixture.h"
#include "../../TestFixtures/Models/TwoSex_NoEstimates.h"
#include "../../ObjectiveFunction/CObjectiveFunction.h"

// strings
const std::string uniform_log_estimate =
    R"(
@estimate
parameter selectivity[FishingSel].a50
lower_bound 1
upper_bound 20
type uniform_log
)";

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE(UniformLogEstimate, C1x1_Empty_Fixture)
{
  addToConfiguration(two_sex_no_estimates);
  addToConfiguration(uniform_log_estimate);
  loadAndRunEnvironment();

  CObjectiveFunction *obj_func = CObjectiveFunction::Instance();
  obj_func->execute();
  BOOST_CHECK_CLOSE(obj_func->getScore(), 2561.9956004278497, 1e-9);

  CEstimate *estimate = CEstimateManager::Instance()->getEstimate("selectivity[FishingSel].a50");
  BOOST_ASSERT(estimate != 0);
  BOOST_CHECK_CLOSE(estimate->getValue(), 8.9820599289404264, 1e-5);

  // Check results
  estimate->setValue(1.0);
  BOOST_CHECK_CLOSE(estimate->getScore(), 0.0, 1e-9);
  estimate->setValue(2.0);
  BOOST_CHECK_CLOSE(estimate->getScore(), 0.69314718055994529, 1e-9);
  estimate->setValue(3.0);
  BOOST_CHECK_CLOSE(estimate->getScore(), 1.0986122886681098, 1e-9);
  estimate->setValue(4.0);
  BOOST_CHECK_CLOSE(estimate->getScore(), 1.3862943611198906, 1e-9);
  estimate->setValue(5.0);
  BOOST_CHECK_CLOSE(estimate->getScore(), 1.6094379124341003, 1e-9);
}
#endif /* TEST */
