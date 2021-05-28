//============================================================================
// Name        : CSelectivityFactory.cpp
// Author      : S.Rasmussen
// Date        : 9/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CSelectivityFactory.h"

#include "../../Helpers/CError.h"
#include "../CSelectivityManager.h"
#include "../Children/CAllValuesBoundedSelectivity.h"
#include "../Children/CAllValuesSelectivity.h"
#include "../Children/CConstantSelectivity.h"
#include "../Children/CDoubleExponentialSelectivity.h"
#include "../Children/CDoubleNormalSelectivity.h"
#include "../Children/CIncreasingSelectivity.h"
#include "../Children/CInverseLogisticSelectivity.h"
#include "../Children/CKnifeEdgeSelectivity.h"
#include "../Children/CKrugerSplineSelectivity.h"
#include "../Children/CLogisticProducingSelectivity.h"
#include "../Children/CLogisticSelectivity.h"
#include "../Children/CSplineSelectivity.h"

//**********************************************************************
// CSelectivity* CSelectivityFactory::buildSelectivity(string type, bool registerWithManager)
// Build a selectivity based on type
//**********************************************************************
CSelectivity* CSelectivityFactory::buildSelectivity(string type, bool registerWithManager) {
  CSelectivity* pSelectivity = 0;

  if (type == PARAM_ALL_VALUES_BOUNDED)
    pSelectivity = new CAllValuesBoundedSelectivity();
  else if (type == PARAM_ALL_VALUES)
    pSelectivity = new CAllValuesSelectivity();
  else if (type == PARAM_CONSTANT)
    pSelectivity = new CConstantSelectivity();
  else if (type == PARAM_DOUBLE_EXPONENTIAL)
    pSelectivity = new CDoubleExponentialSelectivity();
  else if (type == PARAM_DOUBLE_NORMAL)
    pSelectivity = new CDoubleNormalSelectivity();
  else if (type == PARAM_INCREASING)
    pSelectivity = new CIncreasingSelectivity();
  else if (type == PARAM_KNIFE_EDGE)
    pSelectivity = new CKnifeEdgeSelectivity();
  else if (type == PARAM_LOGISTIC_PRODUCING)
    pSelectivity = new CLogisticProducingSelectivity();
  else if (type == PARAM_LOGISTIC)
    pSelectivity = new CLogisticSelectivity();
  else if (type == PARAM_INVERSE_LOGISTIC)
    pSelectivity = new CInverseLogisticSelectivity();
  else if (type == PARAM_SPLINE)
    pSelectivity = new CSplineSelectivity();
  // else if (type == PARAM_KRUGER_SPLINE)
  //  pSelectivity = new CKrugerSplineSelectivity();
  else
    CError::errorUnknown(PARAM_TYPE, type);

  if (registerWithManager)
    CSelectivityManager::Instance()->addSelectivity(pSelectivity);

  return pSelectivity;
}
