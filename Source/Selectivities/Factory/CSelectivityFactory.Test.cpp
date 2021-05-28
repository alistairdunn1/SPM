//============================================================================
// Name        : CSelectivityFactory.Test.cpp
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
#include "../../Translations/Translations.h"
#include "../Children/CAllValuesBoundedSelectivity.h"
#include "../Children/CAllValuesSelectivity.h"
#include "../Children/CConstantSelectivity.h"
#include "../Children/CDoubleExponentialSelectivity.h"
#include "../Children/CDoubleNormalSelectivity.h"
#include "../Children/CIncreasingSelectivity.h"
#include "../Children/CInverseLogisticSelectivity.h"
#include "../Children/CKnifeEdgeSelectivity.h"
#include "../Children/CLogisticProducingSelectivity.h"
#include "../Children/CLogisticSelectivity.h"
#include "CSelectivityFactory.h"

// Namespaces
using namespace std;

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_AllValuesBoundedSelectivity) {
  CSelectivity* pSelectivity = 0;

  BOOST_REQUIRE_NO_THROW(pSelectivity = CSelectivityFactory::buildSelectivity(PARAM_ALL_VALUES_BOUNDED, false));

  CAllValuesBoundedSelectivity* pPtr = dynamic_cast<CAllValuesBoundedSelectivity*>(pSelectivity);
  BOOST_ASSERT(pPtr != 0);

  CAllValuesSelectivity* pPtr2 = dynamic_cast<CAllValuesSelectivity*>(pSelectivity);
  BOOST_ASSERT(pPtr2 == 0);

  delete pSelectivity;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_AllValuesSelectivity) {
  CSelectivity* pSelectivity = 0;

  BOOST_REQUIRE_NO_THROW(pSelectivity = CSelectivityFactory::buildSelectivity(PARAM_ALL_VALUES, false));

  CAllValuesSelectivity* pPtr = dynamic_cast<CAllValuesSelectivity*>(pSelectivity);
  BOOST_ASSERT(pPtr != 0);

  CAllValuesBoundedSelectivity* pPtr2 = dynamic_cast<CAllValuesBoundedSelectivity*>(pSelectivity);
  BOOST_ASSERT(pPtr2 == 0);

  delete pSelectivity;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_ConstantSelectivity) {
  CSelectivity* pSelectivity = 0;

  BOOST_REQUIRE_NO_THROW(pSelectivity = CSelectivityFactory::buildSelectivity(PARAM_CONSTANT, false));

  CConstantSelectivity* pPtr = dynamic_cast<CConstantSelectivity*>(pSelectivity);
  BOOST_ASSERT(pPtr != 0);

  CAllValuesSelectivity* pPtr2 = dynamic_cast<CAllValuesSelectivity*>(pSelectivity);
  BOOST_ASSERT(pPtr2 == 0);

  delete pSelectivity;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_DoubleExponentialSelectivity) {
  CSelectivity* pSelectivity = 0;

  BOOST_REQUIRE_NO_THROW(pSelectivity = CSelectivityFactory::buildSelectivity(PARAM_DOUBLE_EXPONENTIAL, false));

  CDoubleExponentialSelectivity* pPtr = dynamic_cast<CDoubleExponentialSelectivity*>(pSelectivity);
  BOOST_ASSERT(pPtr != 0);

  CConstantSelectivity* pPtr2 = dynamic_cast<CConstantSelectivity*>(pSelectivity);
  BOOST_ASSERT(pPtr2 == 0);

  delete pSelectivity;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_DoubleNormalSelectivity) {
  CSelectivity* pSelectivity = 0;

  BOOST_REQUIRE_NO_THROW(pSelectivity = CSelectivityFactory::buildSelectivity(PARAM_DOUBLE_NORMAL, false));

  CDoubleNormalSelectivity* pPtr = dynamic_cast<CDoubleNormalSelectivity*>(pSelectivity);
  BOOST_ASSERT(pPtr != 0);

  CDoubleExponentialSelectivity* pPtr2 = dynamic_cast<CDoubleExponentialSelectivity*>(pSelectivity);
  BOOST_ASSERT(pPtr2 == 0);

  delete pSelectivity;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_IncreasingSelectivity) {
  CSelectivity* pSelectivity = 0;

  BOOST_REQUIRE_NO_THROW(pSelectivity = CSelectivityFactory::buildSelectivity(PARAM_INCREASING, false));

  CIncreasingSelectivity* pPtr = dynamic_cast<CIncreasingSelectivity*>(pSelectivity);
  BOOST_ASSERT(pPtr != 0);

  CDoubleNormalSelectivity* pPtr2 = dynamic_cast<CDoubleNormalSelectivity*>(pSelectivity);
  BOOST_ASSERT(pPtr2 == 0);

  delete pSelectivity;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_KnifeEdgeSelectivity) {
  CSelectivity* pSelectivity = 0;

  BOOST_REQUIRE_NO_THROW(pSelectivity = CSelectivityFactory::buildSelectivity(PARAM_KNIFE_EDGE, false));

  CKnifeEdgeSelectivity* pPtr = dynamic_cast<CKnifeEdgeSelectivity*>(pSelectivity);
  BOOST_ASSERT(pPtr != 0);

  CIncreasingSelectivity* pPtr2 = dynamic_cast<CIncreasingSelectivity*>(pSelectivity);
  BOOST_ASSERT(pPtr2 == 0);

  delete pSelectivity;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_LogisticProducingSelectivity) {
  CSelectivity* pSelectivity = 0;

  BOOST_REQUIRE_NO_THROW(pSelectivity = CSelectivityFactory::buildSelectivity(PARAM_LOGISTIC_PRODUCING, false));

  CLogisticProducingSelectivity* pPtr = dynamic_cast<CLogisticProducingSelectivity*>(pSelectivity);
  BOOST_ASSERT(pPtr != 0);

  CKnifeEdgeSelectivity* pPtr2 = dynamic_cast<CKnifeEdgeSelectivity*>(pSelectivity);
  BOOST_ASSERT(pPtr2 == 0);

  delete pSelectivity;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_LogisticSelectivity) {
  CSelectivity* pSelectivity = 0;

  BOOST_REQUIRE_NO_THROW(pSelectivity = CSelectivityFactory::buildSelectivity(PARAM_LOGISTIC, false));

  CLogisticSelectivity* pPtr = dynamic_cast<CLogisticSelectivity*>(pSelectivity);
  BOOST_ASSERT(pPtr != 0);

  CLogisticProducingSelectivity* pPtr2 = dynamic_cast<CLogisticProducingSelectivity*>(pSelectivity);
  BOOST_ASSERT(pPtr2 == 0);

  delete pSelectivity;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_InverseLogisticSelectivity) {
  CSelectivity* pSelectivity = 0;

  BOOST_REQUIRE_NO_THROW(pSelectivity = CSelectivityFactory::buildSelectivity(PARAM_INVERSE_LOGISTIC, false));

  CInverseLogisticSelectivity* pPtr = dynamic_cast<CInverseLogisticSelectivity*>(pSelectivity);
  BOOST_ASSERT(pPtr != 0);

  CLogisticProducingSelectivity* pPtr2 = dynamic_cast<CLogisticProducingSelectivity*>(pSelectivity);
  BOOST_ASSERT(pPtr2 == 0);

  delete pSelectivity;
}

#endif
