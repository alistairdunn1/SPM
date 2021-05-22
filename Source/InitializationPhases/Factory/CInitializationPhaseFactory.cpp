//============================================================================
// Name        : CInitializationPhaseFactory.cpp
// Author      : S.Rasmussen
// Date        : 23/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CInitializationPhaseFactory.h"
#include "../CInitializationPhaseManager.h"

//**********************************************************************
// CInitializationPhase* CInitializationPhaseFactory::buildInitializationPhase
//                                        (string type, bool registerWithManager)
// Build our Initialization Phase based on type
//**********************************************************************
CInitializationPhase *CInitializationPhaseFactory::buildInitializationPhase(string type, bool registerWithManager)
{

  CInitializationPhase *pPhase = 0;

  if (type == "")
    pPhase = new CInitializationPhase();
  else
    throw string("Unknown type: " + type);

  if (registerWithManager)
    CInitializationPhaseManager::Instance()->addInitializationPhase(pPhase);

  return pPhase;
}
