//============================================================================
// Name        : CCatchability.Test.cpp
// Author      : S.Rasmussen
// Date        : 23/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "Factory/CCatchabilityFactory.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Catchability) {
  // Get prior
  CCatchability* pCatchability = CCatchabilityFactory::buildCatchability("", false);

  // Add parameters
  pCatchability->addParameter(PARAM_LABEL, "catchability");
  pCatchability->addParameter(PARAM_Q, "5.0");

  // Validate and build
  pCatchability->validate();

  // Check results
  BOOST_CHECK_EQUAL(pCatchability->getQ(), 5.0);

  // clear memory
  delete pCatchability;
}

#endif /* TEST */
