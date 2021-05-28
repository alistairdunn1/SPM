//============================================================================
// Name        : CLatLongDistance.Test.cpp
// Author      : A.Dunn
// Date        : 10/08/2014
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/lexical_cast.hpp>
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "../../TestFixtures/CLayer_Fixture.h"
#include "CDoubleLayer.h"
#include "CLatLongDistanceLayer.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE(LatLongDistance_Layer, CLayer_Fixture) {
  // Build the lat long distance layer
  CLatLongDistanceLayer* pLayer = new CLatLongDistanceLayer();
  // Add parameters
  pLayer->addParameter(PARAM_LABEL, "lat_long_distance");
  pLayer->addParameter(PARAM_LAT_LAYER, "latitude");
  pLayer->addParameter(PARAM_LONG_LAYER, "longitude");
  // Validate and build
  pLayer->validate();
  pLayer->build();

  // Check results

  BOOST_CHECK_EQUAL(pLayer->getValue(0, 0, 1, 1), 989.40550543489439);   // DistanceLongLat(170,180,-40,-45,metres=T)/1000 =  989.4055
  BOOST_CHECK_EQUAL(pLayer->getValue(0, 1, 0, 1), 0.00000000000000);     // DistanceLongLat(170,170,-40,-40,metres=T)/1000 =    0
  BOOST_CHECK_EQUAL(pLayer->getValue(1, 0, 1, 1), 785.76722084226333);   // DistanceLongLat(170,180,-45,-45,metres=T)/1000 =  785.7672
  BOOST_CHECK_EQUAL(pLayer->getValue(1, 1, 2, 2), 933.28726207986108);   // DistanceLongLat(180,190,-45,-50,metres=T)/1000 =  933.2873
  BOOST_CHECK_EQUAL(pLayer->getValue(0, 0, 4, 4), 3533.70387764972750);  // DistanceLongLat(170,210,-40,-60,metres=T)/1000 = 3533.704
  BOOST_CHECK_EQUAL(pLayer->getValue(0, 0, 0, 4), 3377.86266447358180);  // DistanceLongLat(170,210,-40,-40,metres=T)/1000 = 3377.863
  BOOST_CHECK_EQUAL(pLayer->getValue(0, 4, 0, 0), 3377.86266447358180);  // DistanceLongLat(210,170,-40,-40,metres=T)/1000 = 3377.863

  // clear memory
  delete pLayer;
}
#endif /* TEST */
