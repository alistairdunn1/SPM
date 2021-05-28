//============================================================================
// Name        : CDerivedQuantityReport.cpp
// Author      : S.Rasmussen
// Date        : 26/03/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// headers
#include <boost/lexical_cast.hpp>

// Local headers
#include "../../DerivedQuantities/CDerivedQuantity.h"
#include "../../DerivedQuantities/CDerivedQuantityManager.h"
#include "CDerivedQuantityReport.h"

//**********************************************************************
// CDerivedQuantityReport::CDerivedQuantityReport()
// Constructor
//**********************************************************************
CDerivedQuantityReport::CDerivedQuantityReport() {
  // Variables
  eExecutionState  = STATE_FINALIZATION;
  pDerivedQuantity = 0;

  // Register allowed
  pParameterList->registerAllowed(PARAM_DERIVED_QUANTITY);
}

//**********************************************************************
// void CDerivedQuantityReport::validate()
// Validate our report
//**********************************************************************
void CDerivedQuantityReport::validate() {
  try {
    sDerivedQuantity = pParameterList->getString(PARAM_DERIVED_QUANTITY);

    // Validate parent
    CFileReport::validate();

    // Local validation
  } catch (string& ex) {
    ex = "CDerivedQuantityReport.validate(" + getLabel() + ")->" + ex;
    throw ex;
  }
}

//**********************************************************************
// void CDerivedQuantityReport::build()
// Build our Report
//**********************************************************************
void CDerivedQuantityReport::build() {
  try {
    // Get our derived quantity
    CDerivedQuantityManager* pManager = CDerivedQuantityManager::Instance();
    pDerivedQuantity                  = pManager->getDerivedQuantity(sDerivedQuantity);
  } catch (string& Ex) {
    Ex = "CDerivedQuantityReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CDerivedQuantityReport::execute()
// Execute
//**********************************************************************
void CDerivedQuantityReport::execute() {
  try {
    // Check for correct state
    if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
      if (pRuntimeController->getRunMode() != RUN_MODE_PROFILE)
        return;

    this->start();

    // Output Header
    cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
    cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";
    cout << PARAM_LABEL << CONFIG_RATIO_SEPARATOR << " " << sDerivedQuantity << "\n";

    // Output initialisation values
    for (int i = 0; i < pDerivedQuantity->getInitialisationSize(); ++i) {
      cout << PARAM_INITIALIZATION_PHASE << CONFIG_ARRAY_START << boost::lexical_cast<string>(i + 1) << CONFIG_ARRAY_END << CONFIG_RATIO_SEPARATOR << " ";
      for (int j = 0; j < pDerivedQuantity->getInitialisationValuesSize(i); ++j) {
        cout << pDerivedQuantity->getInitialisationValue(i, j) << (j == (pDerivedQuantity->getInitialisationValuesSize(i) - 1) ? "" : CONFIG_SPACE_SEPARATOR);
      }
      cout << "\n";
    }

    // Output values for each year
    cout << PARAM_YEARS << CONFIG_RATIO_SEPARATOR << " ";
    for (int i = pWorld->getInitialYear(); i <= pWorld->getCurrentYear(); ++i) {
      cout << boost::lexical_cast<string>(i) << (i == (pWorld->getCurrentYear()) ? "" : CONFIG_SPACE_SEPARATOR);
    }
    cout << "\n" << PARAM_VALUES << CONFIG_RATIO_SEPARATOR << " ";
    for (int i = 0; i < pDerivedQuantity->getValuesSize(); ++i) {
      cout << pDerivedQuantity->getValueFromIndex(i) << (i == (pDerivedQuantity->getValuesSize() - 1) ? "" : CONFIG_SPACE_SEPARATOR);
    }

    cout << "\n";
    cout << CONFIG_END_REPORT << "\n" << endl;

    this->end();
  } catch (string& Ex) {
    Ex = "CDerivedQuantityReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CDerivedQuantityReport::~CDerivedQuantityReport()
// Destructor
//**********************************************************************
CDerivedQuantityReport::~CDerivedQuantityReport() {}
