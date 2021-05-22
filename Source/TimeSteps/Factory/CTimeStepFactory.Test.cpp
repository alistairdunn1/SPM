//============================================================================
// Name        : CTimeStepFactory.Test.cpp
// Author      : S.Rasmussen
// Date        : 27/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Headers
#include "CTimeStepFactory.h"

// Namespaces
using namespace std;

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_TimeStep)
{
  // See if we got a Valid Estimate
  CTimeStep *pBasic = 0;
  BOOST_REQUIRE_NO_THROW(pBasic = CTimeStepFactory::buildTimeStep("", false));
  delete pBasic;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_TimeStep_PARAM_INVALID)
{
  // Try to Build Invalid Estimate
  BOOST_REQUIRE_THROW(CTimeStepFactory::buildTimeStep(PARAM_ZERO, false), string);
}

#endif
