//============================================================================
// Name        : CDerivedQuantityByCell.Test.cpp
// Author      : S.Rasmussen
// Date        : 23/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
//============================================================================
#ifdef TEST

// Global Includes
#include <boost/test/unit_test.hpp>
#include <string>

// Local Includes
#include "../../Helpers/CComparer.h"
#include "../../TestFixtures/C1x1_Fixture.h"
#include "../../TestFixtures/ConfigurationFiles/AgeSize/AgeSize.h"
#include "../../TestFixtures/ConfigurationFiles/DerivedQuantitiesByCell/DerivedQuantityByCell.h"
#include "../../TestFixtures/ConfigurationFiles/Layers/DoubleLayer.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/Ageing.h"
#include "../../TestFixtures/ConfigurationFiles/Processes/ConstantRecruitment.h"
#include "../../TestFixtures/ConfigurationFiles/Selectivities/Constant.h"
#include "../../TestFixtures/ConfigurationFiles/SizeWeight/SizeWeight.h"
#include "../CDerivedQuantityByCell.h"
#include "../CDerivedQuantityByCellManager.h"
#include "CAbundanceDerivedQuantityByCell.h"

//**********************************************************************
//
//
//**********************************************************************
BOOST_FIXTURE_TEST_CASE(Abundance_Derived_QuantityByCell, C1x1_Fixture) {
  // Add What we need to configuration
  // Then run our model
  addToConfiguration(ageing);
  addToConfiguration(age_size_vonB);
  addToConfiguration(size_weight_none);
  addToConfiguration(constant_recruitment);
  addToConfiguration(derived_quantity_by_cell_abundance);
  addToConfiguration(constant);
  addToConfiguration(numeric);
  addToTimeStep("ageing constant_recruitment");
  loadAndRunEnvironment();

  // Check our Results
  CDerivedQuantityByCellManager* pManager = CDerivedQuantityByCellManager::Instance();
  CDerivedQuantityByCell*        pLayer   = pManager->getDerivedQuantityByCell("derived_quantity_by_cell_abundance");
  //  CWorldSquare         *pSquare   = getSquare();

  // Check Results

  BOOST_CHECK_EQUAL(1, pLayer->getWidth());
  BOOST_CHECK_EQUAL(1, pLayer->getHeight());

  //  int                         getInitialisationSize() { return vvInitialisationValues.size(); }
  //  int                         getInitialisationValuesSize(int initialisationPhase = 0) { return vvInitialisationValues[initialisationPhase].size(); }
  //  vector<vector<double> >     getInitialisationValue(int initialisationPhase = 0, int index = 0) { return vvInitialisationValues[initialisationPhase][index]; }

  BOOST_CHECK_EQUAL(0, pLayer->getInitialisationSize());
  //  BOOST_CHECK_EQUAL(0, pLayer->getInitialisationValuesSize(1));
  //  BOOST_CHECK_EQUAL(0, pLayer->getInitialisationValue(1,1));
  //  BOOST_CHECK_EQUAL(pLayer->getValue(3), 1200.0);
  //  BOOST_CHECK_EQUAL(pLayer->getValue(4), 1100.0);
  //  BOOST_CHECK_EQUAL(pLayer->getValue(5), 1000.0);
  //  BOOST_CHECK_EQUAL(pLayer->getValue(6), 900.0);
  //  BOOST_CHECK_EQUAL(pLayer->getValue(7), 800.0);
  //  BOOST_CHECK_EQUAL(pLayer->getValue(8), 700.0);
  //  BOOST_CHECK_EQUAL(pLayer->getValue(9), 600.0);
  //  BOOST_CHECK_EQUAL(pLayer->getValue(10), 500.0);
  //  BOOST_CHECK_EQUAL(pLayer->getValue(11), 400.0);
  //  BOOST_CHECK_EQUAL(pLayer->getValue(12), 300.0);
  //  BOOST_CHECK_EQUAL(pLayer->getValue(13), 200.0);
  //  BOOST_CHECK_EQUAL(pLayer->getValue(14), 100.0);
  //  BOOST_CHECK_EQUAL(pLayer->getValue(15), 0.0);
  //  BOOST_CHECK_EQUAL(pLayer->getValue(16), 0.0); // Too Large, should return 0.0
  //  BOOST_CHECK_EQUAL(pLayer->getValue(17), 0.0); // ""
}

#endif
