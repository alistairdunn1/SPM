//============================================================================
// Name        : CLayerFactory.Test.cpp
// Author      : S.Rasmussen
// Date        : 23/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description : Unit tests for the CLayer Factory
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Headers
#include "CLayerFactory.h"
#include "../Numeric/CAbundanceDensityLayer.h"
#include "../Numeric/CAbundanceLayer.h"
#include "../Numeric/CBiomassDensityLayer.h"
#include "../Numeric/CBiomassLayer.h"
#include "../Numeric/CDistanceLayer.h"
#include "../Numeric/CDoubleLayer.h"
#include "../String/CStringLayer.h"

// Namespaces
using namespace std;

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_AbundanceDensityLayer)
{

  CLayer *pLayer = 0;
  BOOST_REQUIRE_NO_THROW(pLayer = CLayerFactory::buildLayer(PARAM_ABUNDANCE_DENSITY, false));

  CAbundanceDensityLayer *pPtr = dynamic_cast<CAbundanceDensityLayer *>(pLayer);
  BOOST_ASSERT(pPtr != 0);

  CStringLayer *pPtr2 = dynamic_cast<CStringLayer *>(pLayer);
  BOOST_ASSERT(pPtr2 == 0);

  delete pLayer;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_AbundanceLayer)
{

  CLayer *pLayer = 0;
  BOOST_REQUIRE_NO_THROW(pLayer = CLayerFactory::buildLayer(PARAM_ABUNDANCE, false));

  CAbundanceLayer *pPtr = dynamic_cast<CAbundanceLayer *>(pLayer);
  BOOST_ASSERT(pPtr != 0);

  CAbundanceDensityLayer *pPtr2 = dynamic_cast<CAbundanceDensityLayer *>(pLayer);
  BOOST_ASSERT(pPtr2 == 0);

  delete pLayer;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_BiomassDensityLayer)
{

  CLayer *pLayer = 0;
  BOOST_REQUIRE_NO_THROW(pLayer = CLayerFactory::buildLayer(PARAM_BIOMASS_DENSITY, false));

  CBiomassDensityLayer *pPtr = dynamic_cast<CBiomassDensityLayer *>(pLayer);
  BOOST_ASSERT(pPtr != 0);

  CAbundanceLayer *pPtr2 = dynamic_cast<CAbundanceLayer *>(pLayer);
  BOOST_ASSERT(pPtr2 == 0);

  delete pLayer;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_BiomassLayer)
{

  CLayer *pLayer = 0;
  BOOST_REQUIRE_NO_THROW(pLayer = CLayerFactory::buildLayer(PARAM_BIOMASS, false));

  CBiomassLayer *pPtr = dynamic_cast<CBiomassLayer *>(pLayer);
  BOOST_ASSERT(pPtr != 0);

  CBiomassDensityLayer *pPtr2 = dynamic_cast<CBiomassDensityLayer *>(pLayer);
  BOOST_ASSERT(pPtr2 == 0);

  delete pLayer;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_DistanceLayer)
{

  CLayer *pLayer = 0;
  BOOST_REQUIRE_NO_THROW(pLayer = CLayerFactory::buildLayer(PARAM_DISTANCE, false));

  CDistanceLayer *pPtr = dynamic_cast<CDistanceLayer *>(pLayer);
  BOOST_ASSERT(pPtr != 0);

  CBiomassLayer *pPtr2 = dynamic_cast<CBiomassLayer *>(pLayer);
  BOOST_ASSERT(pPtr2 == 0);

  delete pLayer;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_DoubleLayer)
{

  CLayer *pLayer = 0;
  BOOST_REQUIRE_NO_THROW(pLayer = CLayerFactory::buildLayer(PARAM_DOUBLE, false));

  CDoubleLayer *pPtr = dynamic_cast<CDoubleLayer *>(pLayer);
  BOOST_ASSERT(pPtr != 0);

  CDistanceLayer *pPtr2 = dynamic_cast<CDistanceLayer *>(pLayer);
  BOOST_ASSERT(pPtr2 == 0);

  delete pLayer;
}

//**********************************************************************
//
//
//**********************************************************************
BOOST_AUTO_TEST_CASE(Build_StringLayer)
{

  CLayer *pLayer = 0;
  BOOST_REQUIRE_NO_THROW(pLayer = CLayerFactory::buildLayer(PARAM_STRING, false));

  CStringLayer *pPtr = dynamic_cast<CStringLayer *>(pLayer);
  BOOST_ASSERT(pPtr != 0);

  CDoubleLayer *pPtr2 = dynamic_cast<CDoubleLayer *>(pLayer);
  BOOST_ASSERT(pPtr2 == 0);

  delete pLayer;
}

#endif
