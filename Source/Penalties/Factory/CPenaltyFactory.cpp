//============================================================================
// Name        : CPenaltyFactory.cpp
// Author      : S.Rasmussen
// Date        : 12/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CPenaltyFactory.h"
#include "../CPenaltyManager.h"
#include "../../Translations/Translations.h"
#include "../CPenalty.h"
#include "../../Helpers/CError.h"

//**********************************************************************
// CPenalty* CPenaltyFactory::buildPenalty(string type, bool registerWithManager = true)
// Build our penalty based on type
//**********************************************************************
CPenalty *CPenaltyFactory::buildPenalty(string type, bool registerWithManager)
{

  CPenalty *pPenalty = 0;

  if (type == "")
    pPenalty = new CPenalty();
  else
    CError::errorUnknown(PARAM_PENALTY, type);

  if (registerWithManager)
    CPenaltyManager::Instance()->addPenalty(pPenalty);

  return pPenalty;
}
