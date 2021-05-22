//============================================================================
// Name        : CInitializationPhaseManager.cpp
// Author      : S.Rasmussen
// Date        : 29/04/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global headers
#include <iostream>

// Local Headers
#include "CInitializationPhaseManager.h"
#include "CInitializationPhase.h"
#include "../Reports/CReportManager.h"
#include "../DerivedQuantities/CDerivedQuantityManager.h"
#include "../DerivedQuantitiesByCell/CDerivedQuantityByCellManager.h"
#include "../Helpers/ForEach.h"
#include "../Helpers/CError.h"

// Using
using std::cout;
using std::endl;

// Singleton Variable
boost::thread_specific_ptr<CInitializationPhaseManager> CInitializationPhaseManager::clInstance;

//**********************************************************************
// CInitializationPhaseManager::CInitializationPhaseManager()
// Default Constructor
//**********************************************************************
CInitializationPhaseManager::CInitializationPhaseManager()
{
  // Variables
  lastExecutedInitializationPhase = -1;
  pReportManager = 0;
}

//**********************************************************************
// CInitializationPhaseManager* CInitializationPhaseManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CInitializationPhaseManager *CInitializationPhaseManager::Instance()
{
  if (clInstance.get() == 0)
    clInstance.reset(new CInitializationPhaseManager());
  return clInstance.get();
}

//**********************************************************************
// void CInitializationPhaseManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CInitializationPhaseManager::Destroy()
{
  if (clInstance.get() != 0)
  {
    clInstance.reset();
  }
}

//**********************************************************************
// void CInitializationPhaseManager::addInitializationPhase(CInitializationPhase *value)
// Add our Timestep To The List
//**********************************************************************
void CInitializationPhaseManager::addInitializationPhase(CInitializationPhase *value)
{
  vInitializationPhases.push_back(value);
}

//**********************************************************************
// void CInitializationPhaseManager::loadInitializationPhaseOrder(vector<string> &order)
// Populate the ordered vector with phases based on the vector parameter
//**********************************************************************
void CInitializationPhaseManager::loadInitializationPhaseOrder(vector<string> &order)
{
  vInitializationPhaseOrder.clear();

  foreach (string Label, order)
  {
    foreach (CInitializationPhase *Phase, vInitializationPhases)
    {
      if (Phase->getLabel() == Label)
      {
        vInitializationPhaseOrder.push_back(Phase);
        break;
      }
    }
  }
}

//**********************************************************************
// int CInitializationPhaseManager::getInitializationPhaseOrderIndex(string label)
// Get the Index for our Initializaton Phase when Ordered
//**********************************************************************
int CInitializationPhaseManager::getInitializationPhaseOrderIndex(string label)
{
  try
  {
    // Get the Index for our Initialization Phase
    for (int i = 0; i < (int)vInitializationPhaseOrder.size(); ++i)
      if (vInitializationPhaseOrder[i]->getLabel() == label)
        return i;

    CError::errorUnknown(PARAM_INITIALIZATION_PHASE, label);
  }
  catch (string &Ex)
  {
    Ex = "CInitializationPhaseManager.getInitializationPhaseOrderIndex(" + label + ")->" + Ex;
    throw Ex;
  }

  return -1;
}

//**********************************************************************
// void CInitializationPhaseManager::validate()
// Validate our TimeSteps
//**********************************************************************
void CInitializationPhaseManager::validate()
{
  try
  {
    foreach (CInitializationPhase *InitializationPhase, vInitializationPhases)
    {
      InitializationPhase->validate();
    }

    // Look for Duplicate Labels
    map<string, int> mLabelList;
    foreach (CInitializationPhase *InitializationPhase, vInitializationPhases)
    {
      // Increase Count for this label
      mLabelList[InitializationPhase->getLabel()] += 1;

      // Check if we have more than 1
      if (mLabelList[InitializationPhase->getLabel()] > 1)
        CError::errorDuplicate(PARAM_INITIALIZATION_PHASE, InitializationPhase->getLabel());
    }
  }
  catch (string &Ex)
  {
    Ex = "CInitialisationManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CInitializationPhaseManager::build()
// Build our Time Steps
//**********************************************************************
void CInitializationPhaseManager::build()
{
  try
  {
    // Now, Call TimeStep Validations
    foreach (CInitializationPhase *InitializationPhase, vInitializationPhases)
    {
      InitializationPhase->build();
    }

    // Variables
    pDerivedQuantityByCellManager = CDerivedQuantityByCellManager::Instance();
    pDerivedQuantityManager = CDerivedQuantityManager::Instance();
    pReportManager = CReportManager::Instance();
  }
  catch (string &Ex)
  {
    Ex = "CInitialisationManager.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CInitializationPhaseManager::rebuild()
// Rebuild our initialisation phases
//**********************************************************************
void CInitializationPhaseManager::rebuild()
{
#ifndef OPTIMIZE
  try
  {
#endif
    foreach (CInitializationPhase *InitializationPhase, vInitializationPhases)
    {
      InitializationPhase->rebuild();
    }

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CInitializationPhaseManager.rebuild()->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CInitializationPhaseManager::execute()
// Execute our Initialization Phases
//**********************************************************************
void CInitializationPhaseManager::execute()
{

  // rebuild any relationships that need rebuilding
  rebuild();

  // Reset Last Executed
  lastExecutedInitializationPhase = -1;

  foreach (CInitializationPhase *Phase, vInitializationPhaseOrder)
  {
    // Increment Place holder
    lastExecutedInitializationPhase++;

    pDerivedQuantityByCellManager->setInitialisationPhase(lastExecutedInitializationPhase);
    pDerivedQuantityManager->setInitialisationPhase(lastExecutedInitializationPhase);

    Phase->setExecutionOrderIndex(lastExecutedInitializationPhase);
    Phase->execute();

    pReportManager->execute(STATE_INITIALIZATION);
  }
}

//**********************************************************************
// CInitializationPhaseManager::~CInitializationPhaseManager()
// Default De-Constructor
//**********************************************************************
CInitializationPhaseManager::~CInitializationPhaseManager()
{
  // Delete Our Layers
  foreach (CInitializationPhase *InitializationPhase, vInitializationPhases)
  {
    delete InitializationPhase;
  }

  // Clear Vector
  vInitializationPhases.clear();
}
