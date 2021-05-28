//============================================================================
// Name        : CMinimizerFactory.Test.cpp
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
#include "../DESolver/CDESolver.h"
#include "../GammaDiff/CGammaDiff.h"
#include "CMinimizerFactory.h"

// Namespaces
using namespace std;

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_DESolver) {
  CMinimizer* pMinimizer = 0;
  BOOST_REQUIRE_NO_THROW(pMinimizer = CMinimizerFactory::buildMinimizer(PARAM_DE_SOLVER, false));

  CDESolver* pPtr = dynamic_cast<CDESolver*>(pMinimizer);
  BOOST_ASSERT(pPtr != 0);

  CGammaDiff* pPtr2 = dynamic_cast<CGammaDiff*>(pMinimizer);
  BOOST_ASSERT(pPtr2 == 0);

  delete pMinimizer;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_GammaDiff) {
  CMinimizer* pMinimizer = 0;
  BOOST_REQUIRE_NO_THROW(pMinimizer = CMinimizerFactory::buildMinimizer(PARAM_GAMMADIFF, false));

  CGammaDiff* pPtr = dynamic_cast<CGammaDiff*>(pMinimizer);
  BOOST_ASSERT(pPtr != 0);

  CDESolver* pPtr2 = dynamic_cast<CDESolver*>(pMinimizer);
  BOOST_ASSERT(pPtr2 == 0);

  delete pMinimizer;
}

#endif
