//============================================================================
// Name        : CInitializationPhaseFactory.Test.cpp
// Author      : S.Rasmussen
// Date        : 23/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description : Unit Tests for the Initialization Phase Factory
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Headers
#include "CInitializationPhaseFactory.h"

// Namespaces
using namespace std;

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_InitializationPhase)
{
  // See if we got a Valid Estimate
  CInitializationPhase *pBasic = 0;
  BOOST_REQUIRE_NO_THROW(pBasic = CInitializationPhaseFactory::buildInitializationPhase("", false));
  delete pBasic;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_InitializationPhase_PARAM_INVALID)
{
  // Try to Build Invalid Estimate
  BOOST_REQUIRE_THROW(CInitializationPhaseFactory::buildInitializationPhase(PARAM_ZERO, false), string);
}

#endif
