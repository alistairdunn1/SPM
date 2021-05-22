//============================================================================
// Name        : CDerivedQuantityFactory.Test.cpp
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

// Local Headers
#include "CDerivedQuantityFactory.h"

// Namespaces
using namespace std;

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_DerivedQuantity)
{

  CDerivedQuantity *pBasic = 0;
  BOOST_REQUIRE_NO_THROW(pBasic = CDerivedQuantityFactory::buildDerivedQuantity(PARAM_ABUNDANCE, false));
  delete pBasic;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_DerivedQuantity_PARAM_INVALID)
{
  // Try to Build Invalid Estimate
  BOOST_REQUIRE_THROW(CDerivedQuantityFactory::buildDerivedQuantity(PARAM_ZERO, false), string);
}

#endif
