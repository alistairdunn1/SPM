//============================================================================
// Name        : CLayerFactory.cpp
// Author      : S.Rasmussen
// Date        : 7/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description : << See CLayerFactory.h >>
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CLayerFactory.h"
#include "../../Helpers/CError.h"
#include "../../Translations/Translations.h"
#include "../CLayerManager.h"
#include "../Numeric/CAbundanceDensityLayer.h"
#include "../Numeric/CAbundanceLayer.h"
#include "../Numeric/CBiomassDensityLayer.h"
#include "../Numeric/CBiomassLayer.h"
#include "../Numeric/CDerivedQuantityByCellLayer.h"
#include "../Numeric/CDerivedQuantityLayer.h"
#include "../Numeric/CDistanceLayer.h"
#include "../Numeric/CDijkstraDistanceLayer.h"
#include "../Numeric/CLatLongDijkstraDistanceLayer.h"
#include "../Numeric/CDoubleLayer.h"
#include "../Numeric/CLatLongDistanceLayer.h"
#include "../Numeric/CNumericMetaLayer.h"
#include "../Integer/CNotNegIntegerLayer.h"
#include "../String/CStringLayer.h"
#include "../String/CStringMetaLayer.h"

//**********************************************************************
// CLayer* CLayerFactory::buildLayer(string type)
// Build us a layer based on type
//**********************************************************************
CLayer *CLayerFactory::buildLayer(string type, bool registerWithManager)
{

  CLayer *pLayer = 0;

  if (type == PARAM_ABUNDANCE)
    pLayer = new CAbundanceLayer();
  else if (type == PARAM_ABUNDANCE_DENSITY)
    pLayer = new CAbundanceDensityLayer();
  else if (type == PARAM_BIOMASS)
    pLayer = new CBiomassLayer();
  else if (type == PARAM_BIOMASS_DENSITY)
    pLayer = new CBiomassDensityLayer();
  else if (type == PARAM_DERIVED_QUANTITY)
    pLayer = new CDerivedQuantityLayer;
  else if (type == PARAM_DERIVED_QUANTITY_BY_CELL)
    pLayer = new CDerivedQuantityByCellLayer;
  else if (type == PARAM_DIJKSTRA_DISTANCE)
    pLayer = new CDijkstraDistanceLayer();
  else if (type == PARAM_LAT_LONG_DIJKSTRA_DISTANCE)
    pLayer = new CLatLongDijkstraDistanceLayer();
  else if (type == PARAM_DISTANCE)
    pLayer = new CDistanceLayer();
  else if (type == PARAM_DOUBLE)
    pLayer = new CDoubleLayer();
  else if (type == PARAM_NOT_NEG_INT)
    pLayer = new CNotNegIntegerLayer();
  else if (type == PARAM_LAT_LONG_DISTANCE)
    pLayer = new CLatLongDistanceLayer();
  else if (type == PARAM_META_NUMERIC)
    pLayer = new CNumericMetaLayer();
  else if (type == PARAM_META_STRING)
    pLayer = new CStringMetaLayer();
  else if (type == PARAM_STRING)
    pLayer = new CStringLayer();
  else
    CError::errorUnknown(PARAM_TYPE, type);

  // Register the layer with the manager if required
  if (registerWithManager)
    CLayerManager::Instance()->addLayer(pLayer);

  return pLayer;
}
