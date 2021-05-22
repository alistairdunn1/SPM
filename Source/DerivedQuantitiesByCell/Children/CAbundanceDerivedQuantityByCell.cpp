//============================================================================
// Name        : CAbundanceDerivedQuantityByCell.cpp
// Author      : S.Rasmussen
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
//============================================================================

// Headers
#include "CAbundanceDerivedQuantityByCell.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"
#include "../../InitializationPhases/CInitializationPhase.h"
#include "../../InitializationPhases/CInitializationPhaseManager.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Selectivities/CSelectivityManager.h"
#include "../../TimeSteps/CTimeStepManager.h"
#include "../../World/WorldView/CCompleteWorldView.h"

// Using
using std::cout;
using std::endl;

//**********************************************************************
//
//
//**********************************************************************
CAbundanceDerivedQuantityByCell::CAbundanceDerivedQuantityByCell()
{

  //Variables
  pLayer = 0;
  iHeight = 0;
  iWidth = 0;

  // Register allowed parameters
  pParameterList->registerAllowed(PARAM_TIME_STEP);
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_LAYER);
  pParameterList->registerAllowed(PARAM_SELECTIVITIES);
  pParameterList->registerAllowed(PARAM_INITIALIZATION_TIME_STEPS);
}

//**********************************************************************
// void CDerivedQuantityByCell::validate()
// Validate our Derived Layer
//**********************************************************************
void CAbundanceDerivedQuantityByCell::validate()
{
  try
  {
    // Base
    CBaseBuild::validate();

    // Get our parameters
    sTimeStep = pParameterList->getString(PARAM_TIME_STEP);
    sLayer = pParameterList->getString(PARAM_LAYER, true, "");
    pParameterList->fillVector(vInitializationTimeStepNames, PARAM_INITIALIZATION_TIME_STEPS, true);
    pParameterList->fillVector(vCategoryNames, PARAM_CATEGORIES);
    pParameterList->fillVector(vSelectivityNames, PARAM_SELECTIVITIES);

    // Validate
    if (vCategoryNames.size() != vSelectivityNames.size())
      CError::errorListSameSize(PARAM_CATEGORIES, PARAM_SELECTIVITIES);

    int initialisationPhaseCount = CInitializationPhaseManager::Instance()->getNumberInitializationPhases();
    if (vInitializationTimeStepNames.size() != 0 && (int)vInitializationTimeStepNames.size() != initialisationPhaseCount)
      CError::error(PARAM_INITIALIZATION_TIME_STEPS + string(" size must be same as the number of initialisation phases"));
  }
  catch (string &Ex)
  {
    Ex = "CAbundanceDerivedQuantityByCell.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CDerivedQuantityByCell::build()
// Build our Derived Layer
//**********************************************************************
void CAbundanceDerivedQuantityByCell::build()
{
  try
  {
    CDerivedQuantityByCell::build();

    // Get TimeStep and Layer
    pTimeStepManager = CTimeStepManager::Instance();
    iTimeStep = pTimeStepManager->getTimeStepOrderIndex(sTimeStep);

    if (sLayer != "")
      pLayer = CLayerManager::Instance()->getNumericLayer(sLayer);

    iHeight = pWorld->getHeight();
    iWidth = pWorld->getWidth();

    // Get a vector of Initialisation indexes
    if (vInitializationTimeStepNames.size() > 0)
    {
      CInitializationPhaseManager *initialisationManager = CInitializationPhaseManager::Instance();

      for (int i = 0; i < (int)vInitializationTimeStepNames.size(); ++i)
      {
        vector<string> vTimeStepNames = initialisationManager->getInitializationPhase(i)->getTimeStepNames();
        bool bValidTimeStepName = false;
        for (int j = 0; j < (int)vTimeStepNames.size(); ++j)
        {
          if (vInitializationTimeStepNames[i] == vTimeStepNames[j])
          {
            bValidTimeStepName = true;
            vInitializationTimeStepIndex.push_back(j);
          }
        }
        if (bValidTimeStepName == false)
          CError::errorUnknown(PARAM_TIME_STEP, vInitializationTimeStepNames[i]);
      }
    }
    else
    {
      CInitializationPhaseManager *initialisationManager = CInitializationPhaseManager::Instance();
      int iPhases = initialisationManager->getNumberInitializationPhases();
      for (int i = 0; i < iPhases; ++i)
      {
        vector<string> vTimeStepNames = initialisationManager->getInitializationPhase(i)->getTimeStepNames();
        vInitializationTimeStepNames.push_back(vTimeStepNames[vTimeStepNames.size() - 1]);
        vInitializationTimeStepIndex.push_back(vTimeStepNames.size() - 1);
      }
    }

    // Get our Selectivitys and Categories
    CSelectivityManager::Instance()->fillVector(vSelectivities, vSelectivityNames);
    pWorld->fillCategoryVector(vCategories, vCategoryNames);
  }
  catch (string &Ex)
  {
    Ex = "CAbundanceDerivedQuantityByCell.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CSampleDerivedQuantityByCell::calculate()
// Calculate a value during a standard model run
//**********************************************************************
void CAbundanceDerivedQuantityByCell::calculate()
{

  if (pTimeStepManager->getCurrentTimeStep() != iTimeStep)
  {
    return;
  }

  Data newData;
  newData.resize(iHeight);

  for (int i = 0; i < iHeight; ++i)
  {
    newData[i].assign(iWidth, 0.0);

    for (int j = 0; j < iWidth; ++j)
    {

      pBaseSquare = pWorld->getBaseSquare(i, j);
      if (!pBaseSquare->getEnabled())
        continue;

      double dValue = 0.0;

      for (int k = 0; k < (int)vCategories.size(); ++k)
      {
        for (int l = 0; l < pBaseSquare->getWidth(); ++l)
        {
          dValue += pBaseSquare->getValue(vCategories[k], l) * vSelectivities[k]->getResult(l);
        }
      }

      if (sLayer != "")
        newData[i][j] = dValue * pLayer->getValue(i, j);
      else
        newData[i][j] = dValue;
    }
  }

  vValues.push_back(newData);
}

//**********************************************************************
// void CSampleDerivedQuantityByCell::calculate(int initialisationPhase)
// Calculate a value during one of our initialisation phases
//**********************************************************************
void CAbundanceDerivedQuantityByCell::calculate(int initialisationPhase)
{

  //Check if we're in the right timestep for the initialisation phase we are in
  CInitializationPhase *phase = CInitializationPhaseManager::Instance()->getInitializationPhase(initialisationPhase);
  if (phase->getCurrentTimeStep() != vInitializationTimeStepIndex[initialisationPhase])
    return;

  // If a new initialisation phase, then grow the result to hold the new vector of derived layers
  if ((int)vvInitialisationValues.size() <= initialisationPhase)
    vvInitialisationValues.resize(initialisationPhase + 1);

  Data newData;
  newData.resize(iHeight);

  for (int i = 0; i < iHeight; ++i)
  {
    newData[i].assign(iWidth, 0.0);

    for (int j = 0; j < iWidth; ++j)
    {

      pBaseSquare = pWorld->getBaseSquare(i, j);
      if (!pBaseSquare->getEnabled())
        continue;

      double dValue = 0.0;

      for (int k = 0; k < (int)vCategories.size(); ++k)
      {
        for (int l = 0; l < pBaseSquare->getWidth(); ++l)
        {
          dValue += pBaseSquare->getValue(vCategories[k], l) * vSelectivities[k]->getResult(l);
        }
      }

      if (sLayer != "")
        newData[i][j] = dValue * pLayer->getValue(i, j);
      else
        newData[i][j] = dValue;
    }
  }

  // And add the value to our results
  vvInitialisationValues[initialisationPhase].push_back(newData);
}

//**********************************************************************
//
//
//**********************************************************************
CAbundanceDerivedQuantityByCell::~CAbundanceDerivedQuantityByCell()
{
}
