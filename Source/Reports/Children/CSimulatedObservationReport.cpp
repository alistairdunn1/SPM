//============================================================================
// Name        : CSimulatedObservationReport.cpp
// Author      : S.Rasmussen
// Date        : 13/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Headers
#include "CSimulatedObservationReport.h"

#include <boost/lexical_cast.hpp>

#include "../../Helpers/CConvertor.h"
#include "../../Helpers/ForEach.h"
#include "../../Observations/CObservation.h"
#include "../../Observations/CObservationManager.h"

//**********************************************************************
// CSimulatedObservationReport::CSimulatedObservationReport()
// Default Constructor
//**********************************************************************
CSimulatedObservationReport::CSimulatedObservationReport() {
  // Variables
  eExecutionState = STATE_FINALIZATION;

  // Register Allowed
  pParameterList->registerAllowed(PARAM_OBSERVATION);
}

//**********************************************************************
// void CSimulatedObservationReport::validate()
// Validate our Observation Report
//**********************************************************************
void CSimulatedObservationReport::validate() {
  try {
    // Get Params
    sObservation = pParameterList->getString(PARAM_OBSERVATION);

    // Validate parent
    CFileReport::validate();

    // Local validation
  } catch (string& Ex) {
    Ex = "CSimulatedObservationReport.validate(" + sLabel + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CSimulatedObservationReport::execute()
// Execute our Print State
//**********************************************************************
void CSimulatedObservationReport::execute() {
  try {
    // Check for correct state
    if (pRuntimeController->getRunMode() != RUN_MODE_SIMULATION)
      return;

    this->start();

    cout << CONFIG_SINGLE_COMMENT << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
    cout << CONFIG_SINGLE_COMMENT << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";
    cout << CONFIG_SINGLE_COMMENT << PARAM_OBSERVATION << "." << PARAM_LABEL << CONFIG_RATIO_SEPARATOR << " " << pObservation->getLabel() << "\n";

    CParameterList* pList = pObservation->getParameterList();

    // Get the parameters that have been defined.
    vector<string> vDefinedParameters;
    pList->fillDefinedParameterVector(vDefinedParameters);

    cout << CONFIG_SECTION_SYMBOL << PARAM_OBSERVATION << " " << pList->getString(PARAM_LABEL) << "\n";

    // Loop through and print values
    vector<string> vValues;
    foreach (string Parameter, vDefinedParameters) {
      if (CConvertor::stringToLowercase(Parameter) == PARAM_LIKELIHOOD) {
        if (pList->getString(PARAM_LIKELIHOOD) == PARAM_PSEUDO) {
          cout << PARAM_LIKELIHOOD << " " << pList->getString(PARAM_SIMULATION_LIKELIHOOD) << endl;
          cout << CONFIG_SINGLE_COMMENT << PARAM_SIMULATION_LIKELIHOOD << " " << pList->getString(PARAM_SIMULATION_LIKELIHOOD) << endl;
        } else {
          cout << PARAM_LIKELIHOOD << " " << pList->getString(PARAM_LIKELIHOOD) << endl;
        }

        continue;
      }

      if ((Parameter == PARAM_OBS) || (Parameter == PARAM_ERROR_VALUE) || (Parameter == PARAM_LABEL) || (Parameter == PARAM_SIMULATION_LIKELIHOOD))
        continue;

      pList->fillVector(vValues, Parameter);

      cout << Parameter << " ";
      foreach (string Value, vValues) { cout << Value << " "; }
      cout << endl;
    }

    // Now, Print our Observations
    vector<SComparison*> vComparisons;
    pObservation->fillComparisons(vComparisons);

    // Print OBS
    string sLastKey = "";
    foreach (SComparison* Comparison, vComparisons) {
      if (sLastKey != Comparison->sKey) {
        if (sLastKey != "")
          cout << "\n";
        cout << PARAM_OBS << " " << Comparison->sKey << " ";
        sLastKey = Comparison->sKey;
      }

      cout << boost::lexical_cast<string>(Comparison->dObservedValue) << " ";
    }

    // Print Error Values
    sLastKey              = "";
    bool bWriteErrorValue = false;
    foreach (SComparison* Comparison, vComparisons) {
      if (sLastKey != Comparison->sKey) {
        cout << "\n" << PARAM_ERROR_VALUE << " " << Comparison->sKey << " ";
        sLastKey         = Comparison->sKey;
        bWriteErrorValue = true;
      }

      if (bWriteErrorValue)
        cout << boost::lexical_cast<string>(Comparison->dErrorValue) << " ";

      if (pList->getString(PARAM_TYPE) == PARAM_PROPORTIONS_AT_AGE)
        bWriteErrorValue = false;

      if (pList->getString(PARAM_TYPE) == PARAM_PROPORTIONS_AT_LENGTH)
        bWriteErrorValue = false;
    }

    cout << "\n";
    cout << "#end\n" << endl;

    this->end();
  } catch (string& Ex) {
    Ex = "CSimulatedObservationReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CSimulatedObservationReport::build()
// Build our Observation Report
//**********************************************************************
void CSimulatedObservationReport::build() {
  try {
    // Base
    CFileReport::build();

    // Get our Obs
    pObservation = CObservationManager::Instance()->getObservation(sObservation);
  } catch (string& Ex) {
    Ex = "CSimulatedObservationReport.build(" + sLabel + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CSimulatedObservationReport::~CSimulatedObservationReport()
// Destructor
//**********************************************************************
CSimulatedObservationReport::~CSimulatedObservationReport() {}
