//============================================================================
// Name        : CInitializationReport.cpp
// Author      : S.Rasmussen
// Date        : 26/03/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CInitializationReport.h"
#include "../../InitializationPhases/CInitializationPhaseManager.h"
#include "../../InitializationPhases/CInitializationPhase.h"

//**********************************************************************
// CInitializationReport::CInitializationReport()
// Constructor
//**********************************************************************
CInitializationReport::CInitializationReport() {
  // Variables
  eExecutionState             = STATE_INITIALIZATION;
  pInitializationPhaseManager = CInitializationPhaseManager::Instance();

  // Register user allowed parameter
  pParameterList->registerAllowed(PARAM_INITIALIZATION_PHASE);
}

//**********************************************************************
// void CInitializationReport::validate()
// Validate the report
//**********************************************************************
void CInitializationReport::validate() {
  try {

    // Populate vars
    sInitializationPhase = pParameterList->getString(PARAM_INITIALIZATION_PHASE);

    // Validate parent
    CFileReport::validate();

    // Local validation

  } catch (string &Ex) {
    Ex = "CInitializationReport.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CInitializationReport::build()
// Build the report
//**********************************************************************
void CInitializationReport::build() {
  try {
    // Base
    CFileReport::build();

    pInitializationPhaseManager = CInitializationPhaseManager::Instance();
    iInitializationPhaseIndex   = pInitializationPhaseManager->getInitializationPhaseOrderIndex(sInitializationPhase);

  } catch (string &Ex) {
    Ex = "CInitializationReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CInitializationReport::execute()
// Execute
//**********************************************************************
void CInitializationReport::execute() {
  try {
    // Check for correct state
    if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
      return;
    if (iInitializationPhaseIndex != pInitializationPhaseManager->getLastExecutedInitializationPhase())
      return;

    this->start();

    // Variables
    int         iSquareHeight   = -1;
    int         iSquareWidth    = -1;

    // Print Out
    cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
    cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";
    cout << PARAM_INITIALIZATION << "." << PARAM_INITIALIZATION_PHASE << CONFIG_RATIO_SEPARATOR << " " << sInitializationPhase << "\n";

    cout << PARAM_ROW << CONFIG_SEPERATOR_ESTIMATE_VALUES;
    cout << PARAM_COLUMN << CONFIG_SEPERATOR_ESTIMATE_VALUES,
    cout << PARAM_CATEGORY;
    for(int i = pWorld->getMinAge(); i < pWorld->getMaxAge()+1; i++) {
      cout << CONFIG_SEPERATOR_ESTIMATE_VALUES << PARAM_AGE;
      cout << CONFIG_ARRAY_START << i << CONFIG_ARRAY_END;
    }
    cout << "\n";

    for (int i = 0; i < iWorldHeight; ++i) {
      for (int j = 0; j < iWorldWidth; ++j) {
        // Get Current Square
        pBaseSquare = pWorld->getBaseSquare(i, j);

        // If not set, Set our SquareHeight/Width
        if (iSquareHeight == -1) {
          iSquareHeight = pBaseSquare->getHeight();
          iSquareWidth  = pBaseSquare->getWidth();
        }

        if (!pBaseSquare->getEnabled())
          continue;

        // Loop Through
        for (int k = 0; k < iSquareHeight; ++k) {
          cout << i+1 << CONFIG_SEPERATOR_ESTIMATE_VALUES << j+1 << "," << pWorld->getCategoryNameForIndex(k);
          for (int l = 0; l < iSquareWidth; ++l) {
            cout << CONFIG_SEPERATOR_ESTIMATE_VALUES << pBaseSquare->getValue(k, l);
          }
          cout << "\n";
        }
      }
    }

  cout << CONFIG_END_REPORT << "\n" << endl;

    this->end();
  } catch (string &Ex) {
    Ex = "CInitialisationReport.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CInitializationReport::~CInitializationReport()
// Destructor
//**********************************************************************
CInitializationReport::~CInitializationReport() {
}
