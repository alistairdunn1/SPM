//============================================================================
// Name        : CAdjacentCellMovementProcess.Test.cpp
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
#include "../../TestFixtures/C3x3_Fixture.h"
#include "../../TestFixtures/ConfigurationFiles/AgeSize/AgeSize.h"
#include "../../TestFixtures/ConfigurationFiles/SizeWeight/SizeWeight.h"
#include "../../TestFixtures/ConfigurationFiles/Selectivities/Constant.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/Ageing.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/AdjacentCellMovement.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/ConstantRecruitment.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE(AdjacentCellMovementProcess, C3x3_Fixture)
{

  // Add What we need to configuration
  // Then run our model
  addToConfiguration(ageing);
  addToConfiguration(age_size_vonB);
  addToConfiguration(size_weight_none);
  addToConfiguration(constant);
  addToConfiguration(constant_recruitment);
  addToConfiguration(adjacent_cell_movement);
  addToTimeStep("ageing constant_recruitment adjacent_cell");
  BOOST_REQUIRE_NO_THROW(loadAndRunEnvironment());

  // Check our Results
  double immature[] = {11.110772026909721, 159.72208987616949, 151.97735027125543, 159.72208987616943, 292.84392851560114, 215.27791012383045, 151.97735027125543, 215.27791012383045, 142.0905989149781};

  for (int i = 0; i < 3; ++i)
  {
    for (int j = 0; j < 3; ++j)
    {
      CWorldSquare *pSquare = getSquare(i, j);
      BOOST_CHECK_CLOSE(pSquare->getAbundance(), immature[3 * i + j], 1e-9);
    }
  }
}

#endif /* TEST */
