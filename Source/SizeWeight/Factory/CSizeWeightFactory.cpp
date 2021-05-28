//============================================================================
// Name        : CSizeWeightFactory.cpp
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CSizeWeightFactory.h"

#include "../../Helpers/CError.h"
#include "../CSizeWeight.h"
#include "../CSizeWeightManager.h"
#include "../Children/CBasicSizeWeight.h"
#include "../Children/CNoneSizeWeight.h"

//**********************************************************************
// CSizeWeight* CSizeWeightFactory::buildSizeWeight(string type, bool registerWithManager)
//
//**********************************************************************
CSizeWeight* CSizeWeightFactory::buildSizeWeight(string type, bool registerWithManager) {
  CSizeWeight* pSizeWeight = 0;

  if (type == PARAM_NONE)
    pSizeWeight = new CNoneSizeWeight();
  else if (type == PARAM_BASIC)
    pSizeWeight = new CBasicSizeWeight();
  else
    CError::errorUnknown(PARAM_SIZE_WEIGHT, type);

  if (registerWithManager)
    CSizeWeightManager::Instance()->addSizeWeight(pSizeWeight);

  return pSizeWeight;
}
