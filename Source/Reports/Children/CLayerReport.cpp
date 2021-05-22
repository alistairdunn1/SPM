//============================================================================
// Name        : CLayerReport.cpp
// Author      : S.Rasmussen
// Date        : 26/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Headers
#include <boost/lexical_cast.hpp>

#include "CLayerReport.h"
#include "../../Helpers/CConvertor.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/Numeric/CDijkstraDistanceLayer.h"
#include "../../Layers/Numeric/CLatLongDijkstraDistanceLayer.h"
#include "../../Layers/Numeric/CLatLongDistanceLayer.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Layers/String/Base/CCategoricalLayer.h"
#include "../../TimeSteps/CTimeStepManager.h"

//**********************************************************************
// CLayerReport::CLayerReport()
// Default Constructor
//**********************************************************************
CLayerReport::CLayerReport()
{
  // Variables
  eExecutionState = STATE_MODELLING;
  pTimeStepManager = CTimeStepManager::Instance();
  pLayerManager = CLayerManager::Instance();

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_YEARS);
  pParameterList->registerAllowed(PARAM_TIME_STEP);
  pParameterList->registerAllowed(PARAM_LAYER);

  sLayerType = "";
  sType = "";
}

//**********************************************************************
// void CLayerReport::validate()
// Validate this reporter
//**********************************************************************
void CLayerReport::validate()
{
  try
  {

    // Assign Variables
    pParameterList->fillVector(vYears, PARAM_YEARS, true);
    if (vYears.size() == 0)
      vYears.push_back(pWorld->getInitialYear());

    sTimeStep = pParameterList->getString(PARAM_TIME_STEP, true, "");
    sLayer = pParameterList->getString(PARAM_LAYER);

    // Validate parent
    CFileReport::validate();

    // Local validation
    // Validate Year Range
    foreach (int year, vYears)
    {
      if (year < pWorld->getInitialYear())
        CError::errorLessThan(PARAM_YEAR, PARAM_INITIAL_YEAR);
      else if (year > pWorld->getCurrentYear())
        CError::errorGreaterThan(PARAM_YEAR, PARAM_CURRENT_YEAR);
    }
  }
  catch (string &Ex)
  {
    Ex = "CLayerReport.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CLayerReport::build()
// Build this reporter
//**********************************************************************
void CLayerReport::build()
{
  try
  {
    // Base
    CFileReport::build();

    // Populate TimeStepIndex
    if (sTimeStep != "")
      iTimeStep = pTimeStepManager->getTimeStepOrderIndex(sTimeStep);
    else
    {
      iTimeStep = 0;
      sTimeStep = pTimeStepManager->getFirstTimeStepLabel();
    }

    sLayerType = pLayerManager->getLayerType(sLayer);
    if (sLayerType == PARAM_ABUNDANCE_DENSITY || sLayerType == PARAM_ABUNDANCE ||
        sLayerType == PARAM_BIOMASS_DENSITY || sLayerType == PARAM_BIOMASS ||
        sLayerType == PARAM_DOUBLE || sLayerType == PARAM_META_NUMERIC ||
        sLayerType == PARAM_DERIVED_QUANTITY || sLayerType == PARAM_DERIVED_QUANTITY_BY_CELL)
    {
      pNumericLayer = pLayerManager->getNumericLayer(sLayer);
      sType = PARAM_DOUBLE;
    }
    else if (sLayerType == PARAM_DISTANCE)
    {
      pNumericLayer = pLayerManager->getNumericLayer(sLayer);
      sType = PARAM_DISTANCE;
    }
    else if (sLayerType == PARAM_LAT_LONG_DISTANCE)
    {
      pNumericLayer = pLayerManager->getNumericLayer(sLayer);
      sType = PARAM_LAT_LONG_DISTANCE;
    }
    else if (sLayerType == PARAM_DIJKSTRA_DISTANCE)
    {
      pNumericLayer = pLayerManager->getNumericLayer(sLayer);
      sType = PARAM_DIJKSTRA_DISTANCE;
    }
    else if (sLayerType == PARAM_LAT_LONG_DIJKSTRA_DISTANCE)
    {
      pNumericLayer = pLayerManager->getNumericLayer(sLayer);
      sType = PARAM_LAT_LONG_DIJKSTRA_DISTANCE;
    }
    else if (sLayerType == PARAM_STRING || sLayerType == PARAM_META_STRING)
    {
      pCategoricalLayer = pLayerManager->getCategoricalLayer(sLayer);
      sType = PARAM_STRING;
    }
    else
    {
      CError::error(string("Invalid ") + PARAM_LAYER + " " + PARAM_TYPE + " (" + sLayerType + ") for report " + string(sLabel));
    }
  }
  catch (string &Ex)
  {
    Ex = "CLayerReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CLayerReport::execute()
// Execute reporter
//**********************************************************************
void CLayerReport::execute()
{
  try
  {
    // Check for correct state
    if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
      return;
    if (std::find(vYears.begin(), vYears.end(), pTimeStepManager->getCurrentYear()) == vYears.end())
      return;
    if (iTimeStep != pTimeStepManager->getCurrentTimeStep())
      return;

    this->start();

    // Print Out
    std::cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
    std::cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";
    if (sType == PARAM_DOUBLE)
    {
      std::cout << PARAM_LAYER << CONFIG_RATIO_SEPARATOR << " " << pNumericLayer->getLabel() << "\n";
    }
    else if (sType == PARAM_DISTANCE || sType == PARAM_LAT_LONG_DISTANCE || sType == PARAM_DIJKSTRA_DISTANCE || sType == PARAM_LAT_LONG_DIJKSTRA_DISTANCE)
    {
      std::cout << PARAM_LAYER << CONFIG_RATIO_SEPARATOR << " " << pNumericLayer->getLabel() << "\n";
    }
    else if (sType == PARAM_STRING)
    {
      std::cout << PARAM_LAYER << CONFIG_RATIO_SEPARATOR << " " << pCategoricalLayer->getLabel() << "\n";
    }
    std::cout << PARAM_LAYER << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pLayerManager->getLayerType(sLayer) << "\n";
    std::cout << PARAM_YEAR << CONFIG_RATIO_SEPARATOR << " " << pTimeStepManager->getCurrentYear() << "\n";
    std::cout << PARAM_TIME_STEP << CONFIG_RATIO_SEPARATOR << " " << sTimeStep << "\n";

    if (sType == PARAM_DOUBLE)
    {
      for (int i = 0; i < pNumericLayer->getHeight(); ++i)
      {
        for (int j = 0; j < pNumericLayer->getWidth(); ++j)
        {
          std::cout << pNumericLayer->getValue(i, j) << (j < ((int)pNumericLayer->getWidth() - 1) ? CONFIG_SPACE_SEPARATOR : "\n");
        }
      }
    }
    else if (sType == PARAM_DISTANCE)
    {
      std::cout << "from_" << PARAM_ROW << CONFIG_SPACE_SEPARATOR << "from_" << PARAM_COLUMN << CONFIG_SPACE_SEPARATOR
                << "to_" << PARAM_ROW << CONFIG_SPACE_SEPARATOR << "to_" << PARAM_COLUMN << CONFIG_SPACE_SEPARATOR
                << PARAM_DISTANCE << "\n";
      for (int i = 0; i < pNumericLayer->getHeight(); ++i)
      {
        for (int j = 0; j < pNumericLayer->getWidth(); ++j)
        {
          for (int k = 0; k < pNumericLayer->getHeight(); ++k)
          {
            for (int l = 0; l < pNumericLayer->getWidth(); ++l)
            {
              std::cout << i + 1 << " " << j + 1 << " "
                        << k + 1 << " " << l + 1 << " "
                        << pNumericLayer->getValue(i, j, k, l) << "\n";
            }
          }
        }
      }
    }
    else if (sType == PARAM_LAT_LONG_DISTANCE)
    {
      CLatLongDistanceLayer *pLatLongDistanceLayer = dynamic_cast<CLatLongDistanceLayer *>(pNumericLayer);
      std::cout << "from_" << PARAM_ROW << CONFIG_SPACE_SEPARATOR << "from_" << PARAM_COLUMN << CONFIG_SPACE_SEPARATOR
                << "to_" << PARAM_ROW << CONFIG_SPACE_SEPARATOR << "to_" << PARAM_COLUMN << CONFIG_SPACE_SEPARATOR
                << PARAM_DISTANCE << "\n";
      for (int i = 0; i < pLatLongDistanceLayer->getHeight(); ++i)
      {
        for (int j = 0; j < pLatLongDistanceLayer->getWidth(); ++j)
        {
          for (int k = 0; k < pLatLongDistanceLayer->getHeight(); ++k)
          {
            for (int l = 0; l < pLatLongDistanceLayer->getWidth(); ++l)
            {
              std::cout << pLatLongDistanceLayer->getLong(i, j) << " " << pLatLongDistanceLayer->getLat(i, j) << " " << pLatLongDistanceLayer->getLong(k, l) << " " << pLatLongDistanceLayer->getLat(k, l) << " " << pLatLongDistanceLayer->getValue(i, j, k, l) << "\n";
            }
          }
        }
      }
    }
    else if (sType == PARAM_DIJKSTRA_DISTANCE)
    {
      CDijkstraDistanceLayer *pDijkstraDistanceLayer = dynamic_cast<CDijkstraDistanceLayer *>(pNumericLayer);
      std::cout << "from_" << PARAM_ROW << CONFIG_SPACE_SEPARATOR << "from_" << PARAM_COLUMN << CONFIG_SPACE_SEPARATOR
                << "to_" << PARAM_ROW << CONFIG_SPACE_SEPARATOR << "to_" << PARAM_COLUMN << CONFIG_SPACE_SEPARATOR
                << PARAM_DISTANCE << "\n";
      for (int i = 0; i < pDijkstraDistanceLayer->getHeight(); ++i)
      {
        for (int j = 0; j < pDijkstraDistanceLayer->getWidth(); ++j)
        {
          for (int k = 0; k < pDijkstraDistanceLayer->getHeight(); ++k)
          {
            for (int l = 0; l < pDijkstraDistanceLayer->getWidth(); ++l)
            {
              std::cout << i + 1 << " " << j + 1 << " "
                        << k + 1 << " " << l + 1 << " "
                        << pDijkstraDistanceLayer->getValue(i, j, k, l) << "\n";
            }
          }
        }
      }
    }
    else if (sType == PARAM_LAT_LONG_DIJKSTRA_DISTANCE)
    {
      CLatLongDijkstraDistanceLayer *pLatLongDijkstraDistanceLayer = dynamic_cast<CLatLongDijkstraDistanceLayer *>(pNumericLayer);
      std::cout << "from_" << PARAM_ROW << CONFIG_SPACE_SEPARATOR << "from_" << PARAM_COLUMN << CONFIG_SPACE_SEPARATOR
                << "to_" << PARAM_ROW << CONFIG_SPACE_SEPARATOR << "to_" << PARAM_COLUMN << CONFIG_SPACE_SEPARATOR
                << PARAM_DISTANCE << "\n";
      for (int i = 0; i < pLatLongDijkstraDistanceLayer->getHeight(); ++i)
      {
        for (int j = 0; j < pLatLongDijkstraDistanceLayer->getWidth(); ++j)
        {
          for (int k = 0; k < pLatLongDijkstraDistanceLayer->getHeight(); ++k)
          {
            for (int l = 0; l < pLatLongDijkstraDistanceLayer->getWidth(); ++l)
            {
              std::cout << pLatLongDijkstraDistanceLayer->getLong(i, j) << " " << pLatLongDijkstraDistanceLayer->getLat(i, j) << " " << pLatLongDijkstraDistanceLayer->getLong(k, l) << " " << pLatLongDijkstraDistanceLayer->getLat(k, l) << " " << pLatLongDijkstraDistanceLayer->getValue(i, j, k, l) << "\n";
            }
          }
        }
      }
    }
    else if (sType == PARAM_STRING)
    {
      for (int i = 0; i < pCategoricalLayer->getHeight(); ++i)
      {
        for (int j = 0; j < pCategoricalLayer->getWidth(); ++j)
        {
          std::cout << pCategoricalLayer->getValue(i, j) << (j < ((int)pCategoricalLayer->getWidth() - 1) ? CONFIG_SPACE_SEPARATOR : "\n");
        }
      }
    }

    std::cout << CONFIG_END_REPORT << "\n"
              << endl;

    this->end();
  }
  catch (string &Ex)
  {
    Ex = "CLayerReport.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CLayerReport::~CLayerReport()
// Destructor
//**********************************************************************
CLayerReport::~CLayerReport()
{
}
