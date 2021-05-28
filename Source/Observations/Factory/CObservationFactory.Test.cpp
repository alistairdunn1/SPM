//============================================================================
// Name        : CObservationFactory.Test.cpp
// Author      : S.Rasmussen
// Date        : 23/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Headers
#include "../Children/CAbundanceObservation.h"
#include "../Children/CProportionsAtAgeObservation.h"
#include "../Children/CProportionsByCategoryObservation.h"
#include "CObservationFactory.h"

// Namespaces
using namespace std;

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_AbundanceObservation) {
  // See if we got a Valid Estimate
  CObservation* pObservation = 0;
  BOOST_REQUIRE_NO_THROW(pObservation = CObservationFactory::buildObservation(PARAM_ABUNDANCE, false));

  CAbundanceObservation* pPtr = dynamic_cast<CAbundanceObservation*>(pObservation);
  BOOST_ASSERT(pPtr != 0);

  CProportionsAtAgeObservation* pPtr2 = dynamic_cast<CProportionsAtAgeObservation*>(pObservation);
  BOOST_ASSERT(pPtr2 == 0);

  delete pObservation;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_ProportionsAtAgeObservation) {
  // See if we got a Valid Estimate
  CObservation* pObservation = 0;
  BOOST_REQUIRE_NO_THROW(pObservation = CObservationFactory::buildObservation(PARAM_PROPORTIONS_AT_AGE, false));

  CProportionsAtAgeObservation* pPtr = dynamic_cast<CProportionsAtAgeObservation*>(pObservation);
  BOOST_ASSERT(pPtr != 0);

  CAbundanceObservation* pPtr2 = dynamic_cast<CAbundanceObservation*>(pObservation);
  BOOST_ASSERT(pPtr2 == 0);

  delete pObservation;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_ProportionsByCategoryObservation) {
  // See if we got a Valid Estimate
  CObservation* pObservation = 0;
  BOOST_REQUIRE_NO_THROW(pObservation = CObservationFactory::buildObservation(PARAM_PROPORTIONS_BY_CATEGORY, false));

  CProportionsByCategoryObservation* pPtr = dynamic_cast<CProportionsByCategoryObservation*>(pObservation);
  BOOST_ASSERT(pPtr != 0);

  CProportionsAtAgeObservation* pPtr2 = dynamic_cast<CProportionsAtAgeObservation*>(pObservation);
  BOOST_ASSERT(pPtr2 == 0);

  delete pObservation;
}

#endif
