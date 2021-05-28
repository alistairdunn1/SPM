//============================================================================
// Name        : CTimeStepFactory.cpp
// Author      : S.Rasmussen
// Date        : 23/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CTimeStepFactory.h"

#include "../../Helpers/CError.h"
#include "../CTimeStepManager.h"

//**********************************************************************
// CTimeStep* CTimeStepFactory::buildTimeStep(string type, bool registerWithManager = true)
// Build our TimeStep based on type
//**********************************************************************
CTimeStep* CTimeStepFactory::buildTimeStep(string type, bool registerWithManager) {
  CTimeStep* pTimeStep = 0;

  if (type == "")
    pTimeStep = new CTimeStep();
  else
    CError::errorUnknown(PARAM_TYPE, type);

  if (registerWithManager)
    CTimeStepManager::Instance()->addTimeStep(pTimeStep);

  return pTimeStep;
}
