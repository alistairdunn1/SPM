//============================================================================
// Name        : CProfileFactory.Test.cpp
// Author      : S.Rasmussen
// Date        : 26/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Headers
#include "CProfileFactory.h"

// Namespaces
using namespace std;

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_Profile)
{
  CProfile *pProfile = 0;

  BOOST_REQUIRE_NO_THROW(pProfile = CProfileFactory::buildProfile("", false));
  delete pProfile;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_Profile_PARAM_INVALID)
{
  // Try to Build Invalid Estimate
  BOOST_REQUIRE_THROW(CProfileFactory::buildProfile(PARAM_ZERO, false), string);
}

#endif
