//============================================================================
// Name        : CPreferenceFunctionFactory.Test.cpp
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
#include "../Children/CCategoricalMonotonicPreferenceFunction.h"
#include "../Children/CCategoricalPreferenceFunction.h"
#include "../Children/CConstantPreferenceFunction.h"
#include "../Children/CDoubleNormalPreferenceFunction.h"
#include "../Children/CExponentialPreferenceFunction.h"
#include "../Children/CInverseLogisticPreferenceFunction.h"
#include "../Children/CLogisticPreferenceFunction.h"
#include "../Children/CNormalPreferenceFunction.h"
#include "../Children/CThresholdPreferenceFunction.h"
#include "CPreferenceFunctionFactory.h"

// Namespaces
using namespace std;

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_ConstantPreferenceFunction) {
  CPreferenceFunction* pFunction = 0;
  BOOST_REQUIRE_NO_THROW(pFunction = CPreferenceFunctionFactory::buildPreferenceFunction(PARAM_CONSTANT, false));

  CConstantPreferenceFunction* pPtr = dynamic_cast<CConstantPreferenceFunction*>(pFunction);
  BOOST_ASSERT(pPtr != 0);

  CDoubleNormalPreferenceFunction* pPtr2 = dynamic_cast<CDoubleNormalPreferenceFunction*>(pFunction);
  BOOST_ASSERT(pPtr2 == 0);

  delete pFunction;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_DoubleNormalPreferenceFunction) {
  CPreferenceFunction* pFunction = 0;
  BOOST_REQUIRE_NO_THROW(pFunction = CPreferenceFunctionFactory::buildPreferenceFunction(PARAM_DOUBLE_NORMAL, false));

  CDoubleNormalPreferenceFunction* pPtr = dynamic_cast<CDoubleNormalPreferenceFunction*>(pFunction);
  BOOST_ASSERT(pPtr != 0);

  CConstantPreferenceFunction* pPtr2 = dynamic_cast<CConstantPreferenceFunction*>(pFunction);
  BOOST_ASSERT(pPtr2 == 0);

  delete pFunction;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_ExponentialPreferenceFunction) {
  CPreferenceFunction* pFunction = 0;
  BOOST_REQUIRE_NO_THROW(pFunction = CPreferenceFunctionFactory::buildPreferenceFunction(PARAM_EXPONENTIAL, false));

  CExponentialPreferenceFunction* pPtr = dynamic_cast<CExponentialPreferenceFunction*>(pFunction);
  BOOST_ASSERT(pPtr != 0);

  CDoubleNormalPreferenceFunction* pPtr2 = dynamic_cast<CDoubleNormalPreferenceFunction*>(pFunction);
  BOOST_ASSERT(pPtr2 == 0);

  delete pFunction;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_InverseLogisticPreferenceFunction) {
  CPreferenceFunction* pFunction = 0;
  BOOST_REQUIRE_NO_THROW(pFunction = CPreferenceFunctionFactory::buildPreferenceFunction(PARAM_INVERSE_LOGISTIC, false));

  CInverseLogisticPreferenceFunction* pPtr = dynamic_cast<CInverseLogisticPreferenceFunction*>(pFunction);
  BOOST_ASSERT(pPtr != 0);

  CExponentialPreferenceFunction* pPtr2 = dynamic_cast<CExponentialPreferenceFunction*>(pFunction);
  BOOST_ASSERT(pPtr2 == 0);

  delete pFunction;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_LogisticPreferenceFunction) {
  CPreferenceFunction* pFunction = 0;
  BOOST_REQUIRE_NO_THROW(pFunction = CPreferenceFunctionFactory::buildPreferenceFunction(PARAM_LOGISTIC, false));

  CLogisticPreferenceFunction* pPtr = dynamic_cast<CLogisticPreferenceFunction*>(pFunction);
  BOOST_ASSERT(pPtr != 0);

  CInverseLogisticPreferenceFunction* pPtr2 = dynamic_cast<CInverseLogisticPreferenceFunction*>(pFunction);
  BOOST_ASSERT(pPtr2 == 0);

  delete pFunction;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_NormalPreferenceFunction) {
  CPreferenceFunction* pFunction = 0;
  BOOST_REQUIRE_NO_THROW(pFunction = CPreferenceFunctionFactory::buildPreferenceFunction(PARAM_NORMAL, false));

  CNormalPreferenceFunction* pPtr = dynamic_cast<CNormalPreferenceFunction*>(pFunction);
  BOOST_ASSERT(pPtr != 0);

  CLogisticPreferenceFunction* pPtr2 = dynamic_cast<CLogisticPreferenceFunction*>(pFunction);
  BOOST_ASSERT(pPtr2 == 0);

  delete pFunction;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_ThresholdPreferenceFunction) {
  CPreferenceFunction* pFunction = 0;
  BOOST_REQUIRE_NO_THROW(pFunction = CPreferenceFunctionFactory::buildPreferenceFunction(PARAM_THRESHOLD, false));

  CThresholdPreferenceFunction* pPtr = dynamic_cast<CThresholdPreferenceFunction*>(pFunction);
  BOOST_ASSERT(pPtr != 0);

  CLogisticPreferenceFunction* pPtr2 = dynamic_cast<CLogisticPreferenceFunction*>(pFunction);
  BOOST_ASSERT(pPtr2 == 0);

  delete pFunction;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_CategoricalPreferenceFunction) {
  CPreferenceFunction* pFunction = 0;
  BOOST_REQUIRE_NO_THROW(pFunction = CPreferenceFunctionFactory::buildPreferenceFunction(PARAM_CATEGORICAL, false));

  CCategoricalPreferenceFunction* pPtr = dynamic_cast<CCategoricalPreferenceFunction*>(pFunction);
  BOOST_ASSERT(pPtr != 0);

  CLogisticPreferenceFunction* pPtr2 = dynamic_cast<CLogisticPreferenceFunction*>(pFunction);
  BOOST_ASSERT(pPtr2 == 0);

  delete pFunction;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_CategoricalMonotonicPreferenceFunction) {
  CPreferenceFunction* pFunction = 0;
  BOOST_REQUIRE_NO_THROW(pFunction = CPreferenceFunctionFactory::buildPreferenceFunction(PARAM_CATEGORICAL_MONOTONIC, false));

  CCategoricalMonotonicPreferenceFunction* pPtr = dynamic_cast<CCategoricalMonotonicPreferenceFunction*>(pFunction);
  BOOST_ASSERT(pPtr != 0);

  CLogisticPreferenceFunction* pPtr2 = dynamic_cast<CLogisticPreferenceFunction*>(pFunction);
  BOOST_ASSERT(pPtr2 == 0);

  delete pFunction;
}
#endif
