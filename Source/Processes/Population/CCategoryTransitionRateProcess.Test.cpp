//============================================================================
// Name        : CCategoryTransitionRateProcess.Test.cpp
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
#include "../../Helpers/CComparer.h"
#include "../../TestFixtures/C1x1_Fixture.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/Ageing.h"
#include "../../TestFixtures/ConfigurationFiles/AgeSize/AgeSize.h"
#include "../../TestFixtures/ConfigurationFiles/SizeWeight/SizeWeight.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/ConstantRecruitment.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/CategoryTransitionRate.h"
#include "../../TestFixtures/ConfigurationFiles/Selectivities/LogisticProducing.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE(CategoryTransitionRateProcess, C1x1_Fixture)
{

    // Add What we need to configuration
    // Then run our model
    addToConfiguration(ageing);
    addToConfiguration(age_size_vonB);
    addToConfiguration(size_weight_none);
    addToConfiguration(constant_recruitment);
    addToConfiguration(category_transition_rate);
    addToConfiguration(category_transition_rate_spawn);
    addToConfiguration(logistic_producing);
    addToTimeStep("ageing constant_recruitment category_transition_rate category_transition_rate_spawn");
    loadAndRunEnvironment();

    // Check our Results
    CWorldSquare *pSquare = getSquare();

    BOOST_CHECK_CLOSE(pSquare->getAbundance(), 1500.0, 1e-9);

    // Our Expected Results
    double immature[] = {100.0, 100.0, 100.0, 100.0, 97.5,
                         93.746396864256383, 85.7573104444905, 72.352503281738606, 55.899419987755721, 126.36907784787302};

    double mature[] = {0.0, 0.0, 0.0, 0.0, 2.4537499999999999,
                       6.0305125640072417, 13.135481771989891, 23.470370866022517, 33.205244335958305, 210.24859361147881};

    double spawning[] = {0.0, 0.0, 0.0, 0.0, 0.046250000000000006,
                         0.22309057173637387, 1.1072077835196072, 4.1771258522388806, 10.895335676285985, 263.38232854064819};

    // Check Expected against model
    BOOST_CHECK_CLOSE(pSquare->getValue(0, 0), immature[0], 1e-9);
    BOOST_CHECK_CLOSE(pSquare->getValue(0, 1), immature[1], 1e-9);
    BOOST_CHECK_CLOSE(pSquare->getValue(0, 2), immature[2], 1e-9);
    BOOST_CHECK_CLOSE(pSquare->getValue(0, 3), immature[3], 1e-9);
    BOOST_CHECK_CLOSE(pSquare->getValue(0, 4), immature[4], 1e-9);
    BOOST_CHECK_CLOSE(pSquare->getValue(0, 5), immature[5], 1e-9);
    BOOST_CHECK_CLOSE(pSquare->getValue(0, 6), immature[6], 1e-9);
    BOOST_CHECK_CLOSE(pSquare->getValue(0, 7), immature[7], 1e-9);
    BOOST_CHECK_CLOSE(pSquare->getValue(0, 8), immature[8], 1e-9);
    BOOST_CHECK_CLOSE(pSquare->getValue(0, 9), immature[9], 1e-9);

    BOOST_CHECK_CLOSE(pSquare->getValue(1, 0), mature[0], 1e-9);
    BOOST_CHECK_CLOSE(pSquare->getValue(1, 1), mature[1], 1e-9);
    BOOST_CHECK_CLOSE(pSquare->getValue(1, 2), mature[2], 1e-9);
    BOOST_CHECK_CLOSE(pSquare->getValue(1, 3), mature[3], 1e-9);
    BOOST_CHECK_CLOSE(pSquare->getValue(1, 4), mature[4], 1e-9);
    BOOST_CHECK_CLOSE(pSquare->getValue(1, 5), mature[5], 1e-9);
    BOOST_CHECK_CLOSE(pSquare->getValue(1, 6), mature[6], 1e-9);
    BOOST_CHECK_CLOSE(pSquare->getValue(1, 7), mature[7], 1e-9);
    BOOST_CHECK_CLOSE(pSquare->getValue(1, 8), mature[8], 1e-9);
    BOOST_CHECK_CLOSE(pSquare->getValue(1, 9), mature[9], 1e-9);

    BOOST_CHECK_CLOSE(pSquare->getValue(2, 0), spawning[0], 1e-9);
    BOOST_CHECK_CLOSE(pSquare->getValue(2, 1), spawning[1], 1e-9);
    BOOST_CHECK_CLOSE(pSquare->getValue(2, 2), spawning[2], 1e-9);
    BOOST_CHECK_CLOSE(pSquare->getValue(2, 3), spawning[3], 1e-9);
    BOOST_CHECK_CLOSE(pSquare->getValue(2, 4), spawning[4], 1e-9);
    BOOST_CHECK_CLOSE(pSquare->getValue(2, 5), spawning[5], 1e-9);
    BOOST_CHECK_CLOSE(pSquare->getValue(2, 6), spawning[6], 1e-9);
    BOOST_CHECK_CLOSE(pSquare->getValue(2, 7), spawning[7], 1e-9);
    BOOST_CHECK_CLOSE(pSquare->getValue(2, 8), spawning[8], 1e-9);
    BOOST_CHECK_CLOSE(pSquare->getValue(2, 9), spawning[9], 1e-9);
}

#endif /* TEST */
