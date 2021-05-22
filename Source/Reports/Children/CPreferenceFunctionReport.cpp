//============================================================================
// Name        : CPreferenceFunctionReport.cpp
// Author      : S.Rasmussen
// Date        : 26/03/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

#include <boost/lexical_cast.hpp>

// Local headers
#include "CPreferenceFunctionReport.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"
#include "../../Estimates/CEstimateManager.h"
#include "../../Estimates/CEstimate.h"
#include "../../PreferenceFunctions/CPreferenceFunctionManager.h"
#include "../../PreferenceFunctions/CPreferenceFunction.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/Numeric/CDoubleLayer.h"

//**********************************************************************
// CPreferenceFunctionReport::CPreferenceFunctionReport()
// Constructor
//**********************************************************************
CPreferenceFunctionReport::CPreferenceFunctionReport()
{
  // Variables
  eExecutionState = STATE_FINALIZATION;
  pPreferenceFunction = 0;

  // Register allowed
  pParameterList->registerAllowed(PARAM_PREFERENCE_FUNCTION);
}

//**********************************************************************
// void CPreferenceFunctionReport::validate()
// Validate our selectivity
//**********************************************************************
void CPreferenceFunctionReport::validate()
{
  try
  {

    sPreferenceFunction = pParameterList->getString(PARAM_PREFERENCE_FUNCTION);

    // Validate parent
    CFileReport::validate();

    // Local validation
  }
  catch (string &Ex)
  {
    Ex = "CPreferenceFunctionReport.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPreferenceFunctionReport::build()
// Build our Report
//**********************************************************************
void CPreferenceFunctionReport::build()
{
  try
  {
    // Parent
    CFileReport::build();

    // Get our preference function
    CPreferenceFunctionManager *pManager = CPreferenceFunctionManager::Instance();
    pPreferenceFunction = pManager->getPreferenceFunction(sPreferenceFunction);

    std::string sType = pPreferenceFunction->getType();
    if (sType == PARAM_FRANK_COPULA || sType == PARAM_GAUSSIAN_COPULA || sType == PARAM_GUMBEL_COPULA || sType == PARAM_INDEPENDENCE_COPULA)
    {
      pLayer = 0;
    }
    else
    {
      std::string sLayerName = pPreferenceFunction->getLayerName();
      sLayerType = CLayerManager::Instance()->getLayerType(sLayerName);
      if (sLayerType == PARAM_DOUBLE)
      {
        pLayer = CLayerManager::Instance()->getNumericLayer(sLayerName);
      }
      else if (sLayerType == PARAM_DISTANCE)
      {
        pLayer = CLayerManager::Instance()->getNumericLayer(sLayerName);
      }
      else if (sLayerType == PARAM_LAT_LONG_DISTANCE)
      {
        pLayer = CLayerManager::Instance()->getNumericLayer(sLayerName);
      }
      else if (sLayerType == PARAM_LAT_LONG_DIJKSTRA_DISTANCE)
      {
        pLayer = CLayerManager::Instance()->getNumericLayer(sLayerName);
      }
      else if (sLayerType == PARAM_DIJKSTRA_DISTANCE)
      {
        pLayer = CLayerManager::Instance()->getNumericLayer(sLayerName);
      }
      else if (sLayerType == PARAM_ABUNDANCE)
      {
        pLayer = CLayerManager::Instance()->getNumericLayer(sLayerName);
      }
      else if (sLayerType == PARAM_ABUNDANCE_DENSITY)
      {
        pLayer = CLayerManager::Instance()->getNumericLayer(sLayerName);
      }
      else if (sLayerType == PARAM_BIOMASS)
      {
        pLayer = CLayerManager::Instance()->getNumericLayer(sLayerName);
      }
      else if (sLayerType == PARAM_BIOMASS_DENSITY)
      {
        pLayer = CLayerManager::Instance()->getNumericLayer(sLayerName);
      }
      else if (sLayerType == PARAM_CATEGORICAL)
      {
        pLayer = 0;
      }
      else if (sLayerType == PARAM_META_NUMERIC)
      {
        pLayer = 0;
      }
      else if (sLayerType == PARAM_META_STRING)
      {
        pLayer = 0;
      }
      else
      {
        CError::errorUnknown(PARAM_LAYER, sLayerName);
      }
    }
  }
  catch (string &Ex)
  {
    Ex = "CPreferenceFunctionReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPreferenceFunctionReport::execute()
// Execute
//**********************************************************************
void CPreferenceFunctionReport::execute()
{

  try
  {
    // Check for correct state
    if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
      if (pRuntimeController->getRunMode() != RUN_MODE_PROFILE)
        return;

    this->start();

    CEstimateManager *pEstimateManager = CEstimateManager::Instance();

    CParameterList *pList = pPreferenceFunction->getParameterList();

    // Output Header
    cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
    cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";
    cout << PARAM_LABEL << CONFIG_RATIO_SEPARATOR << " " << sPreferenceFunction << "\n";

    vector<string> vDefinedParameters;
    pList->fillDefinedParameterVector(vDefinedParameters);

    vector<string> vValues;
    foreach (string Parameter, vDefinedParameters)
    {
      pList->fillVector(vValues, Parameter);

      cout << Parameter << ": ";

      /**
       * Check if this parameter is estimated
       * First check if there is only 1 value
       */
      if (vValues.size() == 1)
      {
        string estimableName = "preference_function[" + pPreferenceFunction->getLabel() + "]." + Parameter;

        if (pEstimateManager->hasEstimate(estimableName))
        {
          CEstimate *pEstimate = pEstimateManager->getEstimate(estimableName);
          cout << pEstimate->getValue();
        }
        else
        {
          cout << vValues[0];
        }
      }
      else if (vValues.size() > 1)
      {

        for (int i = 0; i < (int)vValues.size(); ++i)
        {
          string estimableName = "preference_function[" + pPreferenceFunction->getLabel() + "]." + Parameter + "(" + boost::lexical_cast<string>(i + 1) + ")";

          if (pEstimateManager->hasEstimate(estimableName))
          {
            CEstimate *pEstimate = pEstimateManager->getEstimate(estimableName);
            cout << pEstimate->getValue() << (i < (int)vValues.size() ? CONFIG_SPACE_SEPARATOR : "");
          }
          else
          {
            cout << vValues[i] << (i < ((int)vValues.size() - 1) ? CONFIG_SPACE_SEPARATOR : "");
          }
        }
      }
      else
      {
        for (int i = 0; i < (int)vValues.size(); ++i)
        {
          cout << vValues[i] << (i < ((int)vValues.size() - 1) ? CONFIG_SPACE_SEPARATOR : "");
        }
      }

      cout << endl;
    }

    // print out layer type, and
    // value minimum and maximum if a double layer
    cout << "layer_type" << CONFIG_RATIO_SEPARATOR << " " << sLayerType << endl;
    CDoubleLayer *pDoubleLayer = dynamic_cast<CDoubleLayer *>(pLayer);
    if (pDoubleLayer != 0)
    {
      cout << "layer_min" << CONFIG_RATIO_SEPARATOR << " " << pDoubleLayer->getLayerMin() << endl;
      cout << "layer_max" << CONFIG_RATIO_SEPARATOR << " " << pDoubleLayer->getLayerMax() << endl;
    }

    cout << CONFIG_END_REPORT << "\n"
         << endl;

    this->end();
  }
  catch (string &Ex)
  {
    Ex = "CPreferenceFunctionReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CPreferenceFunctionReport::~CPreferenceFunctionReport()
// Destuctor
//**********************************************************************
CPreferenceFunctionReport::~CPreferenceFunctionReport()
{
}
