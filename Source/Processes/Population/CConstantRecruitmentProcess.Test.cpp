//============================================================================
// Name        : CConstantRecruitmentProcess.Test.cpp
// Author      : S.Rasmussen
// Date        : 20/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "../../TestFixtures/C1x1_Fixture.h"
#include "../../TestFixtures/ConfigurationFiles/AgeSize/AgeSize.h"
#include "../../TestFixtures/ConfigurationFiles/SizeWeight/SizeWeight.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/Ageing.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/ConstantRecruitment.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE(ConstantRecruitmentProcess, C1x1_Fixture)
{

  // Add What we need to configuration
  // Then run our model
  addToConfiguration(ageing);
  addToConfiguration(constant_recruitment);
  addToConfiguration(age_size_vonB);
  addToConfiguration(size_weight_none);
  addToTimeStep("ageing constant_recruitment");
  loadAndRunEnvironment();

  // Check our Results
  CWorldSquare *pSquare = getSquare();

  BOOST_CHECK_EQUAL(pSquare->getAbundance(), 1500.0);

  // Immature only should've been recruited
  for (int i = 0; i < 9; ++i)
    BOOST_CHECK_EQUAL(pSquare->getValue(0, i), 100.0);
  BOOST_CHECK_EQUAL(pSquare->getValue(0, 9), 600.0);

  // No population should've been recruited here
  for (int i = 1; i < 3; ++i)
    for (int j = 0; j < 10; ++j)
      BOOST_CHECK_EQUAL(pSquare->getValue(i, j), 0.0);
}

#endif /* TEST */
