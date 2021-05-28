//============================================================================
// Name        : CPreferenceFunctionFactory.cpp
// Author      : S.Rasmussen
// Date        : 7/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CPreferenceFunctionFactory.h"

#include "../../Helpers/CError.h"
#include "../../Translations/Translations.h"
#include "../CPreferenceFunctionManager.h"
#include "../Children/CCategoricalMonotonicPreferenceFunction.h"
#include "../Children/CCategoricalPreferenceFunction.h"
#include "../Children/CConstantPreferenceFunction.h"
#include "../Children/CDoubleNormalPreferenceFunction.h"
#include "../Children/CExponentialPreferenceFunction.h"
#include "../Children/CInverseLogisticPreferenceFunction.h"
#include "../Children/CKnifeedgePreferenceFunction.h"
#include "../Children/CLogisticPreferenceFunction.h"
#include "../Children/CNormalPreferenceFunction.h"
#include "../Children/CThresholdPreferenceFunction.h"
//#include "../Children/CClaytonPreferenceFunction.h"
#include "../Children/CFrankPreferenceFunction.h"
#include "../Children/CGaussianPreferenceFunction.h"
#include "../Children/CGumbelPreferenceFunction.h"
#include "../Children/CIndependencePreferenceFunction.h"

//**********************************************************************
// CPreferenceFunction* CPreferenceFunctionFactory::buildPreferenceFunction(string type, bool registerWithManager)
// Build our buildPreferenceFunction
//**********************************************************************
CPreferenceFunction* CPreferenceFunctionFactory::buildPreferenceFunction(string type, bool registerWithManager) {
  CPreferenceFunction* pFunction = 0;

  if (type == PARAM_CONSTANT)
    pFunction = new CConstantPreferenceFunction();
  else if (type == PARAM_DOUBLE_NORMAL)
    pFunction = new CDoubleNormalPreferenceFunction();
  else if (type == PARAM_EXPONENTIAL)
    pFunction = new CExponentialPreferenceFunction();
  else if (type == PARAM_INVERSE_LOGISTIC)
    pFunction = new CInverseLogisticPreferenceFunction();
  else if (type == PARAM_LOGISTIC)
    pFunction = new CLogisticPreferenceFunction();
  else if (type == PARAM_NORMAL)
    pFunction = new CNormalPreferenceFunction();
  else if (type == PARAM_THRESHOLD)
    pFunction = new CThresholdPreferenceFunction();
  else if (type == PARAM_KNIFE_EDGE)
    pFunction = new CKnifeedgePreferenceFunction();
  else if (type == PARAM_CATEGORICAL)
    pFunction = new CCategoricalPreferenceFunction();
  else if (type == PARAM_CATEGORICAL_MONOTONIC)
    pFunction = new CCategoricalMonotonicPreferenceFunction();
  //  else if (type == PARAM_CLAYTON_COPULA)
  //    pFunction = new CClaytonPreferenceFunction();
  else if (type == PARAM_FRANK_COPULA)
    pFunction = new CFrankPreferenceFunction();
  else if (type == PARAM_GAUSSIAN_COPULA)
    pFunction = new CGaussianPreferenceFunction();
  else if (type == PARAM_GUMBEL_COPULA)
    pFunction = new CGumbelPreferenceFunction();
  else if (type == PARAM_INDEPENDENCE_COPULA)
    pFunction = new CIndependencePreferenceFunction();
  else
    CError::errorUnknown(PARAM_TYPE, type);

  if (registerWithManager)
    CPreferenceFunctionManager::Instance()->addPreferenceFunction(pFunction);

  return pFunction;
}
