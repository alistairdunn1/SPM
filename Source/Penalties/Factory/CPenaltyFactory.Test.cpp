//============================================================================
// Name        : CPenaltyFactory.Test.cpp
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
#include "CPenaltyFactory.h"

// Namespaces
using namespace std;

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_Penalty) {
  CPenalty* pPenalty = 0;
  BOOST_REQUIRE_NO_THROW(pPenalty = CPenaltyFactory::buildPenalty("", false));
  delete pPenalty;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_InvalidPenalty) {
  BOOST_REQUIRE_THROW(CPenaltyFactory::buildPenalty(PARAM_ZERO, false), string);
}

#endif
