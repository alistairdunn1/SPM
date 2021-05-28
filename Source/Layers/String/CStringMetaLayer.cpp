//============================================================================
// Name        : CStringMetaLayer.cpp
// Author      : S.Rasmussen
// Date        : 16/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CStringMetaLayer.h"

#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"
#include "../../InitializationPhases/CInitializationPhase.h"
#include "../../InitializationPhases/CInitializationPhaseManager.h"
#include "../../Layers/CLayerManager.h"
#include "../../TimeSteps/CTimeStepManager.h"
#include "../../World/WorldView/CCompleteWorldView.h"

//**********************************************************************
// CStringMetaLayer::CStringMetaLayer()
// Default constructor
//**********************************************************************
CStringMetaLayer::CStringMetaLayer() {
  pTimeStepManager            = CTimeStepManager::Instance();
  pInitializationPhaseManager = CInitializationPhaseManager::Instance();

  sType = PARAM_META_STRING;

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_DEFAULT_LAYER);
  pParameterList->registerAllowed(PARAM_YEARS);
  pParameterList->registerAllowed(PARAM_LAYERS);
  pParameterList->registerAllowed(PARAM_INITIALIZATION_PHASES);
  pParameterList->registerAllowed(PARAM_INITIALIZATION_LAYERS);

  bHasYears          = true;
  bHasInitialisation = true;
  bIsStatic          = false;
}

//**********************************************************************
// void CStringMetaLayer::validate()
// Validate the layer
//**********************************************************************
void CStringMetaLayer::validate() {
  try {
    // Base
    CLayer::validate();

    // Populate our variables
    sDefaultLayer = pParameterList->getString(PARAM_DEFAULT_LAYER);

    // determine if years defined, and check
    if (pParameterList->hasParameter(PARAM_YEARS)) {
      if (pParameterList->hasParameter(PARAM_LAYERS)) {
        pParameterList->fillVector(vYears, PARAM_YEARS);
        pParameterList->fillVector(vLayerNames, PARAM_LAYERS);
      } else {
        CError::errorMissing(PARAM_LAYERS);
      }
    } else if (pParameterList->hasParameter(PARAM_LAYERS)) {
      CError::errorMissing(PARAM_YEARS);
    } else {
      bHasYears = false;
    }
    // Validate lengths
    if (vYears.size() != vLayerNames.size())
      CError::errorListSameSize(PARAM_YEARS, PARAM_LAYERS);

    // determine if initalisation defined, and check
    if (pParameterList->hasParameter(PARAM_INITIALIZATION_PHASES)) {
      if (pParameterList->hasParameter(PARAM_LAYERS)) {
        pParameterList->fillVector(vInitialisationPhases, PARAM_INITIALIZATION_PHASES);
        pParameterList->fillVector(vInitialisationLayers, PARAM_INITIALIZATION_LAYERS);
      } else {
        CError::errorMissing(PARAM_LAYERS);
      }
    } else if (pParameterList->hasParameter(PARAM_INITIALIZATION_LAYERS)) {
      CError::errorMissing(PARAM_YEARS);
    } else {
      bHasInitialisation = false;
    }
    // Validate lengths
    if (vInitialisationPhases.size() != vInitialisationLayers.size())
      CError::errorListSameSize(PARAM_INITIALIZATION_PHASES, PARAM_INITIALIZATION_LAYERS);
  } catch (string& Ex) {
    Ex = "CStringMetaLayer.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CStringMetaLayer::build()
// Build the layer
//**********************************************************************
void CStringMetaLayer::build() {
  try {
    CLayerManager* pLayerManager = CLayerManager::Instance();

    // Sort out the vector of layers to use in the initialisation
    pInitializationPhaseManager   = CInitializationPhaseManager::Instance();
    int iInitialisationPhaseCount = pInitializationPhaseManager->getNumberInitializationPhases();
    // Fill in as default, then override with the specifics
    for (int i = 0; i < iInitialisationPhaseCount; ++i) {
      vPhaseLayers.push_back(pLayerManager->getCategoricalLayer(sDefaultLayer));
    }
    if (bHasInitialisation) {
      for (int i = 0; i < (int)vInitialisationPhases.size(); ++i) {
        int iPhase           = pInitializationPhaseManager->getInitializationPhaseOrderIndex(vInitialisationPhases[i]);
        vPhaseLayers[iPhase] = pLayerManager->getCategoricalLayer(vInitialisationLayers[i]);
      }
    }

    // Sort out the vector of layers to use for the run years
    // Fill in as default, then override with the specifics
    for (int i = pWorld->getInitialYear(); i <= pWorld->getCurrentYear(); ++i) {
      vYearsIndex.push_back(i);
      vYearsLayers.push_back(pLayerManager->getCategoricalLayer(sDefaultLayer));
    }
    if (bHasYears) {
      for (int i = 0; i < (int)vYearsIndex.size(); ++i) {
        for (int j = 0; j < (int)vYears.size(); ++j) {
          if (vYearsIndex[i] == vYears[j]) {
            vYearsLayers[i] = pLayerManager->getCategoricalLayer(vLayerNames[j]);
          }
        }
      }
    }
  } catch (string& Ex) {
    Ex = "CStringMetaLayer.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// string getValue(int RowIndex, int ColIndex)
// get value
//**********************************************************************
string CStringMetaLayer::getValue(int RowIndex, int ColIndex) {
  try {
    string sValue = "";
    // If initialisation phase, return appropriate layer
    if (pRuntimeController->getCurrentState() == STATE_INITIALIZATION) {
      int iThisPhase = pInitializationPhaseManager->getLastExecutedInitializationPhase();
      sValue         = vPhaseLayers[iThisPhase]->getValue(RowIndex, ColIndex);
    } else {
      int iThisYear = pTimeStepManager->getCurrentYear();
      int iIndex    = 0;
      for (int i = 0; i < (int)vYearsIndex.size(); ++i) {
        if (vYearsIndex[i] == iThisYear) {
          iIndex = i;
        }
      }
      sValue = vYearsLayers[iIndex]->getValue(RowIndex, ColIndex);
    }
    return (sValue);
  } catch (string& Ex) {
    Ex = "CStringMetaLayer.getValue(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CStringMetaLayer::~CStringMetaLayer()
// Destructor
//**********************************************************************
CStringMetaLayer::~CStringMetaLayer() {}
