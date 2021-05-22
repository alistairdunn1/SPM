//============================================================================
// Name        : CWorld_Fixture.cpp
// Author      : S.Rasmussen
// Date        : 12/02/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST

// Global Headers
#include <boost/test/unit_test.hpp>

// Local Headers
#include "CWorld_Fixture.h"
#include "../World/CWorld.h"

//**********************************************************************
// CWorld_Fixture::CWorld_Fixture()
// Default Constructor
//**********************************************************************
CWorld_Fixture::CWorld_Fixture()
{

  CWorld *pWorld = CWorld::Instance();

  pWorld->addParameter(PARAM_CELL_LENGTH, "1");
  pWorld->addParameter(PARAM_NROWS, "5");
  pWorld->addParameter(PARAM_NCOLS, "5");
  pWorld->addParameter(PARAM_LAYER, "base_layer");
  pWorld->addParameter(PARAM_MIN_AGE, "1");
  pWorld->addParameter(PARAM_MAX_AGE, "20");
  pWorld->addParameter(PARAM_AGE_PLUS_GROUP, "true");
  pWorld->addParameter(PARAM_INITIAL_YEAR, "1990");
  pWorld->addParameter(PARAM_CURRENT_YEAR, "2000");
  //pWorld->addParameter(PARAM_FINAL_YEAR, "2010");

  pWorld->addParameter(PARAM_CATEGORIES, "immature");
  pWorld->addParameter(PARAM_CATEGORIES, "mature");
  pWorld->addParameter(PARAM_CATEGORIES, "spawning");

  pWorld->addParameter(PARAM_INITIALIZATION_PHASES, "initial_phase_one");
  pWorld->addParameter(PARAM_INITIALIZATION_PHASES, "initial_phase_two");

  pWorld->addParameter(PARAM_TIME_STEPS, "time_step_one");
  pWorld->addParameter(PARAM_TIME_STEPS, "time_step_two");

  pWorld->addParameter(PARAM_AGE_SIZE, "vonB");
  pWorld->addParameter(PARAM_AGE_SIZE, "vonB");
  pWorld->addParameter(PARAM_AGE_SIZE, "vonB");

  pWorld->validate();
}

//**********************************************************************
// CWorld_Fixture::~CWorld_Fixture()
// Destructor
//**********************************************************************
CWorld_Fixture::~CWorld_Fixture()
{
  CWorld::Destroy();
}

#endif
