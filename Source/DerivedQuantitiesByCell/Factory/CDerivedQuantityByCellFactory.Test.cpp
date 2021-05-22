//============================================================================
// Name        : CDerivedQuantityByCellFactory.Test.cpp
// Author      : S.Rasmussen
// Date        : 23/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Headers
#include "CDerivedQuantityByCellFactory.h"

// Namespaces
using namespace std;

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_Abundance_DerivedQuantityByCell)
{

  CDerivedQuantityByCell *pBasic = 0;
  BOOST_REQUIRE_NO_THROW(pBasic = CDerivedQuantityByCellFactory::buildDerivedQuantityByCell(PARAM_ABUNDANCE, false));
  delete pBasic;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_Biomass_DerivedQuantityByCell)
{

  CDerivedQuantityByCell *pBasic = 0;
  BOOST_REQUIRE_NO_THROW(pBasic = CDerivedQuantityByCellFactory::buildDerivedQuantityByCell(PARAM_BIOMASS, false));
  delete pBasic;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_DerivedQuantityByCell_PARAM_INVALID)
{
  // Try to Build Invalid Estimate
  BOOST_REQUIRE_THROW(CDerivedQuantityByCellFactory::buildDerivedQuantityByCell(PARAM_ZERO, false), string);
}

#endif
