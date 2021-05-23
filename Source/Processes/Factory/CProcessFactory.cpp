//============================================================================
// Name        : CProcessFactory.cpp
// Author      : S.Rasmussen
// Date        : 5/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "../../Helpers/CError.h"
#include "../../Translations/Translations.h"
#include "../CProcessManager.h"
#include "../Movement/CAdjacentCellMovementProcess.h"
#include "../Movement/CMigrationMovementProcess.h"
#include "../Movement/COpenMPPreferenceMovementProcess.h"
#include "../Movement/CPreferenceMovementProcess.h"
#include "../Population/CAgeingProcess.h"
#include "../Population/CAgeMortalityRateProcess.h"
#include "../Population/CAnnualMortalityRateProcess.h"
#include "../Population/CBHRecruitmentProcess.h"
#include "../Population/CBHRecruitmentProcess2.h"
#include "../Population/CBiomassEventMortalityProcess.h"
#include "../Population/CCategoryStateByAgeProcess.h"
#include "../Population/CCategoryTransitionByAgeProcess.h"
#include "../Population/CCategoryTransitionProcess.h"
#include "../Population/CCategoryTransitionRateProcess.h"
#include "../Population/CConstantMortalityRateProcess.h"
#include "../Population/CConstantExploitationRateProcess.h"
#include "../Population/CConstantRecruitmentProcess.h"
#include "../Population/CEventMortalityProcess.h"
#include "../Population/CHollingMortalityRateProcess.h"
#include "../Population/CLayerVaryingExploitationRateProcess.h"
#include "../Population/CLayerVaryingExploitationRateByeventProcess.h"
#include "../Population/CLocalBHRecruitmentProcess.h"
#include "../Population/CNoneProcess.h"
#include "../Population/CPreySuitabilityPredationProcess.h"
#include "../Population/CProportionalRecruitmentProcess.h"
#include "CProcessFactory.h"

//**********************************************************************
// CProcessFactory::CProcessFactory()
// Default Constructor
//**********************************************************************
CProcess *CProcessFactory::buildProcess(string type, bool registerWithManager)
{

  CProcess *pProcess = 0;

  if (type == PARAM_CONSTANT_RECRUITMENT)
    pProcess = new CConstantRecruitmentProcess();
  else if (type == PARAM_BH_RECRUITMENT)
    pProcess = new CBHRecruitmentProcess();
  else if (type == PARAM_BH_RECRUITMENT2)
    pProcess = new CBHRecruitmentProcess2();
  else if (type == PARAM_LOCAL_BH_RECRUITMENT)
    pProcess = new CLocalBHRecruitmentProcess();
  else if (type == PARAM_PROPORTIONAL_RECRUITMENT)
    pProcess = new CProportionalRecruitmentProcess();
  else if (type == PARAM_AGEING)
    pProcess = new CAgeingProcess();
  else if (type == PARAM_CONSTANT_MORTALITY_RATE)
    pProcess = new CConstantMortalityRateProcess();
  else if (type == PARAM_AGE_MORTALITY_RATE)
    pProcess = new CAgeMortalityRateProcess();
  else if (type == PARAM_CONSTANT_EXPLOITATION_RATE)
    pProcess = new CConstantExploitationRateProcess();
  else if (type == PARAM_ANNUAL_MORTALITY_RATE)
    pProcess = new CAnnualMortalityRateProcess();
  else if (type == PARAM_LAYER_VARYING_EXPLOITATION_RATE)
    pProcess = new CLayerVaryingExploitationRateProcess();
  else if (type == PARAM_LAYER_VARYING_EXPLOITATION_RATE_BYEVENT)
    pProcess = new CLayerVaryingExploitationRateByeventProcess();
  else if (type == PARAM_EVENT_MORTALITY)
    pProcess = new CEventMortalityProcess();
  else if (type == PARAM_BIOMASS_EVENT_MORTALITY)
    pProcess = new CBiomassEventMortalityProcess();
  else if (type == PARAM_PREY_SUITABILITY_PREDATION)
    pProcess = new CPreySuitabilityPredationProcess();
  else if (type == PARAM_HOLLING_MORTALITY_RATE)
    pProcess = new CHollingMortalityRateProcess();
  else if (type == PARAM_CATEGORY_STATE_BY_AGE)
    pProcess = new CCategoryStateByAgeProcess();
  else if (type == PARAM_CATEGORY_TRANSITION)
    pProcess = new CCategoryTransitionProcess();
  else if (type == PARAM_CATEGORY_TRANSITION_BY_AGE)
    pProcess = new CCategoryTransitionByAgeProcess();
  else if (type == PARAM_CATEGORY_TRANSITION_RATE)
    pProcess = new CCategoryTransitionRateProcess();
  else if (type == PARAM_PREFERENCE_MOVEMENT)
    pProcess = new CPreferenceMovementProcess();
  else if (type == PARAM_PREFERENCE_MOVEMENT_THREADED)
    pProcess = new COpenMPPreferenceMovementProcess();
  else if (type == PARAM_ADJACENT_CELL_MOVEMENT)
    pProcess = new CAdjacentCellMovementProcess();
  else if (type == PARAM_MIGRATION_MOVEMENT)
    pProcess = new CMigrationMovementProcess();
  else if (type == PARAM_NONE)
    pProcess = new CNoneProcess();
  else
    CError::errorUnknown(PARAM_PROCESS, type);

  if (registerWithManager)
    CProcessManager::Instance()->addProcess(pProcess);

  return pProcess;
}
