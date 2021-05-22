//============================================================================
// Name        : CTimeStepManager.cpp
// Author      : S.Rasmussen
// Date        : 13/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description : << See CTimeStepManager.h >>
// $Date$
//============================================================================

// Global headers
#include <iostream>

// Local Headers
#include "CTimeStepManager.h"
#include "CTimeStep.h"
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"
#include "../Helpers/CConvertor.h"
#include "../World/CWorld.h"
#include "../Observations/CObservationManager.h"
#include "../Reports/CReportManager.h"
#include "../DerivedQuantities/CDerivedQuantityManager.h"
#include "../DerivedQuantitiesByCell/CDerivedQuantityByCellManager.h"

// Using
using std::cout;
using std::endl;

// Single Static variable
boost::thread_specific_ptr<CTimeStepManager> CTimeStepManager::clInstance;

//**********************************************************************
// CTimeStepManager::CTimeStepManager()
// Default Constructor
//**********************************************************************
CTimeStepManager::CTimeStepManager()
{
  pObservationManager = 0;
  pReporterManager = 0;
  pDerivedQuantityManager = 0;
  pDerivedQuantityByCellManager = 0;

  iCurrentYear = 0;
}

//**********************************************************************
// CTimeStepManager* CTimeStepManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CTimeStepManager *CTimeStepManager::Instance()
{
  if (clInstance.get() == 0)
    clInstance.reset(new CTimeStepManager());
  return clInstance.get();
}

//**********************************************************************
// void CTimeStepManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CTimeStepManager::Destroy()
{
  if (clInstance.get() != 0)
  {
    clInstance.reset();
  }
}

//**********************************************************************
// void CTimeStepManager::addTimeStep(CTimeStep *value)
// Add New Time Step To The List
//**********************************************************************
void CTimeStepManager::addTimeStep(CTimeStep *value)
{
  vMasterTimeStepList.push_back(value);
}

//**********************************************************************
// void CTimeStepManager::fillVector(vector<string> &labels, vector<CTimeStep*> &result)
// Populate the <result> vector with timesteps that have matching <labels>
//**********************************************************************
void CTimeStepManager::fillVector(vector<string> &labels, vector<CTimeStep *> &result)
{
  foreach (string label, labels)
  {
    foreach (CTimeStep *timeStep, vMasterTimeStepList)
    {
      if (timeStep->getLabel() == label)
      {
        result.push_back(timeStep);
        break;
      }
    }
  }
}

//**********************************************************************
// void CTimeStepManager::setTimeStepOrder(vector<string> &order)
// Load the TimeStep Order for Execution
//**********************************************************************
void CTimeStepManager::setTimeStepOrder(vector<string> &order)
{
  vTimeSteps.clear();

  foreach (string Label, order)
  {
    foreach (CTimeStep *TimeStep, vMasterTimeStepList)
    {
      if (TimeStep->getLabel() == Label)
      {
        vTimeSteps.push_back(TimeStep);
        break;
      }
    }
  }
}

//**********************************************************************
// int CTimeStepManager::getTimeStepOrderIndex(string label)
// Get the Index of a TimeStep in our Order
//**********************************************************************
int CTimeStepManager::getTimeStepOrderIndex(string label)
{
#ifndef OPTIMIZE
  try
  {
#endif
    for (int i = 0; i < (int)vTimeSteps.size(); ++i)
      if (vTimeSteps[i]->getLabel() == label)
        return i;

    CError::errorUnknown(PARAM_TIME_STEP, label);

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CTimeStepManager.getTimeStepOrderIndex()->" + Ex;
    throw Ex;
  }
#endif

  return 0;
}

//**********************************************************************
// string getFirstTimeStepLabel()
// Get the label of the first TimeStep in our Order
//**********************************************************************
string CTimeStepManager::getFirstTimeStepLabel()
{
  try
  {
    return (vTimeSteps[0]->getLabel());
  }
  catch (string &Ex)
  {
    Ex = "CTimeStepManager.getFirstTimeStep()->" + Ex;
    throw Ex;
  }

  return 0;
}

//**********************************************************************
// void CTimeStepManager::getTimeStepIndexForProcess(string &label)
// get Time Step Index For Process
//**********************************************************************
int CTimeStepManager::getTimeStepIndexForProcess(string &label)
{
  for (int i = 0; i < (int)vTimeSteps.size(); ++i)
  {
    vector<string> processes = vTimeSteps[i]->getProcessNames();
    for (int j = 0; j < (int)processes.size(); ++j)
    {
      if (processes[j] == label)
        return i;
    }
  }

  CError::errorUnknown(PARAM_PROCESS, label);
  return -1;
}

//**********************************************************************
// void CTimeStepManager::validate()
// Validate The Time Steps
//**********************************************************************
void CTimeStepManager::validate()
{
  try
  {
    if ((int)vMasterTimeStepList.size() == 0)
      CError::errorMissing(PARAM_TIME_STEPS);

    // Call TimeStep Validations
    foreach (CTimeStep *TimeStep, vMasterTimeStepList)
    {
      TimeStep->validate();
    }

    // Look for Duplicate Labels
    map<string, int> mLabelList;
    foreach (CTimeStep *TimeStep, vMasterTimeStepList)
    {
      // Increase Count for this label
      mLabelList[TimeStep->getLabel()] += 1;

      // Check if we have more than 1
      if (mLabelList[TimeStep->getLabel()] > 1)
        CError::errorDuplicate(PARAM_TIME_STEP, TimeStep->getLabel());
    }
  }
  catch (string &Ex)
  {
    Ex = "CTimeStepManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CTimeStepManager::build()
// Build out TimeSteps
//**********************************************************************
void CTimeStepManager::build()
{
#ifndef OPTIMIZE
  try
  {
#endif

    foreach (CTimeStep *TimeStep, vMasterTimeStepList)
    {
      TimeStep->build();
    }

    CWorld *pWorld = CWorld::Instance();
    iFirstHumanYear = pWorld->getInitialYear();
    iNumberOfYears = pWorld->getCurrentYear() - iFirstHumanYear;

    pDerivedQuantityByCellManager = CDerivedQuantityByCellManager::Instance();
    pDerivedQuantityManager = CDerivedQuantityManager::Instance();
    pObservationManager = CObservationManager::Instance();
    pReporterManager = CReportManager::Instance();

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CTimeStepManager.build()->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CTimeStepManager::execute()
// Execute Our TimeSteps
//**********************************************************************
void CTimeStepManager::execute()
{

  for (int i = 0; i <= iNumberOfYears; ++i)
  {
    iCurrentYear = i + iFirstHumanYear;

    for (int j = 0; j < (int)vTimeSteps.size(); ++j)
    {
      iCurrentTimeStep = j;

      // Prepare our Observations
      pObservationManager->prepare(iCurrentYear, j);

      // Execute Time Step
      vTimeSteps[j]->execute();

      // Execute Other Tasks
      pDerivedQuantityByCellManager->calculate();
      pDerivedQuantityManager->calculate();
      pObservationManager->execute(iCurrentYear, j);
      pReporterManager->execute();
    }
  }
}

//**********************************************************************
// CTimeStepManager::~CTimeStepManager()
// Default De-constructor
//**********************************************************************
CTimeStepManager::~CTimeStepManager()
{
  // Delete Our Layers
  foreach (CTimeStep *TimeStep, vMasterTimeStepList)
  {
    delete TimeStep;
  }
}
