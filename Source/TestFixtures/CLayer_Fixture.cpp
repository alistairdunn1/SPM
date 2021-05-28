//============================================================================
// Name        : CLayer_Fixture.cpp
// Author      : S.Rasmussen
// Date        : 18/02/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Global Headers
#include <boost/lexical_cast.hpp>
#include <boost/test/unit_test.hpp>
#include <iostream>

// Local headers
#include "../Helpers/CConvertor.h"
#include "../Layers/CLayerManager.h"
#include "../Layers/Factory/CLayerFactory.h"
#include "CLayer_Fixture.h"

// Using
using std::cout;
using std::endl;

//**********************************************************************
// CLayer_Fixture::CLayer_Fixture()
// Constructor
//**********************************************************************
CLayer_Fixture::CLayer_Fixture() {
  // Create a Double Layer
  CLayer* pLayer = CLayerFactory::buildLayer(PARAM_DOUBLE);
  pLayer->addParameter(PARAM_LABEL, "double_layer");
  for (int i = 0; i < 25; ++i) pLayer->addParameter(PARAM_DATA, boost::lexical_cast<string>(i + 1));
  pLayer->validate();
  pLayer->build();

  // Create a Distance Layer
  pLayer = CLayerFactory::buildLayer(PARAM_DISTANCE);
  pLayer->addParameter(PARAM_LABEL, "distance_layer");
  pLayer->validate();
  pLayer->build();

  // Create a latitude Layer
  pLayer = CLayerFactory::buildLayer(PARAM_DOUBLE);
  pLayer->addParameter(PARAM_LABEL, "longitude");
  pLayer->addParameter(PARAM_DATA, "170");
  pLayer->addParameter(PARAM_DATA, "180");
  pLayer->addParameter(PARAM_DATA, "190");
  pLayer->addParameter(PARAM_DATA, "200");
  pLayer->addParameter(PARAM_DATA, "210");
  pLayer->addParameter(PARAM_DATA, "170");
  pLayer->addParameter(PARAM_DATA, "180");
  pLayer->addParameter(PARAM_DATA, "190");
  pLayer->addParameter(PARAM_DATA, "200");
  pLayer->addParameter(PARAM_DATA, "210");
  pLayer->addParameter(PARAM_DATA, "170");
  pLayer->addParameter(PARAM_DATA, "180");
  pLayer->addParameter(PARAM_DATA, "190");
  pLayer->addParameter(PARAM_DATA, "200");
  pLayer->addParameter(PARAM_DATA, "210");
  pLayer->addParameter(PARAM_DATA, "170");
  pLayer->addParameter(PARAM_DATA, "180");
  pLayer->addParameter(PARAM_DATA, "190");
  pLayer->addParameter(PARAM_DATA, "200");
  pLayer->addParameter(PARAM_DATA, "210");
  pLayer->addParameter(PARAM_DATA, "170");
  pLayer->addParameter(PARAM_DATA, "180");
  pLayer->addParameter(PARAM_DATA, "190");
  pLayer->addParameter(PARAM_DATA, "200");
  pLayer->addParameter(PARAM_DATA, "210");
  pLayer->validate();
  pLayer->build();

  // Create a longitude Layer
  pLayer = CLayerFactory::buildLayer(PARAM_DOUBLE);
  pLayer->addParameter(PARAM_LABEL, "latitude");
  pLayer->addParameter(PARAM_DATA, "-40");
  pLayer->addParameter(PARAM_DATA, "-40");
  pLayer->addParameter(PARAM_DATA, "-40");
  pLayer->addParameter(PARAM_DATA, "-40");
  pLayer->addParameter(PARAM_DATA, "-40");
  pLayer->addParameter(PARAM_DATA, "-45");
  pLayer->addParameter(PARAM_DATA, "-45");
  pLayer->addParameter(PARAM_DATA, "-45");
  pLayer->addParameter(PARAM_DATA, "-45");
  pLayer->addParameter(PARAM_DATA, "-45");
  pLayer->addParameter(PARAM_DATA, "-50");
  pLayer->addParameter(PARAM_DATA, "-50");
  pLayer->addParameter(PARAM_DATA, "-50");
  pLayer->addParameter(PARAM_DATA, "-50");
  pLayer->addParameter(PARAM_DATA, "-50");
  pLayer->addParameter(PARAM_DATA, "-55");
  pLayer->addParameter(PARAM_DATA, "-55");
  pLayer->addParameter(PARAM_DATA, "-55");
  pLayer->addParameter(PARAM_DATA, "-55");
  pLayer->addParameter(PARAM_DATA, "-55");
  pLayer->addParameter(PARAM_DATA, "-60");
  pLayer->addParameter(PARAM_DATA, "-60");
  pLayer->addParameter(PARAM_DATA, "-60");
  pLayer->addParameter(PARAM_DATA, "-60");
  pLayer->addParameter(PARAM_DATA, "-60");
  pLayer->validate();
  pLayer->build();
}

//**********************************************************************
// CLayer_Fixture::~CLayer_Fixture()
// Destructor
//**********************************************************************
CLayer_Fixture::~CLayer_Fixture() {
  CLayerManager::Destroy();
}

#endif
