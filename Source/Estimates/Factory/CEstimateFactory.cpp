//============================================================================
// Name        : CEstimateFactory.cpp
// Author      : S.Rasmussen
// Date        : 12/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description : << See CEstimateFactory.h >>
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CEstimateFactory.h"

#include "../../Helpers/CError.h"
#include "../CEstimateManager.h"
#include "../Children/CBetaEstimate.h"
#include "../Children/CLogNormalEstimate.h"
#include "../Children/CNormalByStdevEstimate.h"
#include "../Children/CNormalEstimate.h"
#include "../Children/CNormalLogEstimate.h"
#include "../Children/CUniformEstimate.h"
#include "../Children/CUniformLogEstimate.h"

//**********************************************************************
// CEstimateInfo* CEstimateFactory::buildEstimateInfo(bool registerWithManager)
// Build our estimates
//**********************************************************************
CEstimateInfo* CEstimateFactory::buildEstimateInfo(bool registerWithManager) {
  CEstimateInfo* pInfo = new CEstimateInfo();

  if (registerWithManager)
    CEstimateManager::Instance()->addEstimateInfo(pInfo);

  return pInfo;
}

/**
 *
 */
CEstimate* CEstimateFactory::buildEstimate(const string& type, bool registerWithManager) {
  CEstimate* estimate = 0;

  if (type == PARAM_BETA)
    estimate = new CBetaEstimate();
  else if (type == PARAM_LOGNORMAL)
    estimate = new CLogNormalEstimate();
  else if (type == PARAM_NORMAL_BY_STDEV)
    estimate = new CNormalByStdevEstimate();
  else if (type == PARAM_NORMAL)
    estimate = new CNormalEstimate();
  else if (type == PARAM_NORMAL_LOG)
    estimate = new CNormalLogEstimate();
  else if (type == PARAM_UNIFORM)
    estimate = new CUniformEstimate();
  else if (type == PARAM_UNIFORM_LOG)
    estimate = new CUniformLogEstimate();
  else
    CError::errorUnknown(PARAM_ESTIMATE, type);

  if (registerWithManager)
    CEstimateManager::Instance()->addEstimate(estimate);

  return estimate;
}
