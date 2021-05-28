//============================================================================
// Name        : CObservationReport.cpp
// Author      : S.Rasmussen
// Date        : 8/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CObservationReport.h"

#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"
#include "../../Observations/CObservation.h"
#include "../../Observations/CObservationManager.h"
#include "../../Observations/Children/CAbundanceObservation.h"
#include "../../Observations/Children/CBiomassObservation.h"
#include "../../Observations/Children/CPresenceObservation.h"
#include "../../Observations/Children/CProportionsAtAgeObservation.h"
#include "../../Observations/Children/CProportionsAtLengthByCategoryObservation.h"
#include "../../Observations/Children/CProportionsAtLengthObservation.h"
#include "../../Observations/Children/CProportionsByCategoryObservation.h"

//**********************************************************************
// CObservationReport::CObservationReport()
// Constructor
//**********************************************************************
CObservationReport::CObservationReport() {
  // Variables
  eExecutionState = STATE_FINALIZATION;

  // Register Allowed
  pParameterList->registerAllowed(PARAM_OBSERVATION);
}

//**********************************************************************
// void CObservationReport::validate()
// Validate our Observation Report
//**********************************************************************
void CObservationReport::validate() {
  try {
    // Get Params
    sObservation = pParameterList->getString(PARAM_OBSERVATION);

    // Validate parent
    CFileReport::validate();

    // Local validation
  } catch (string& Ex) {
    Ex = "CObservationReport.validate(" + sLabel + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CObservationReport::build()
// Build our Observation Report
//**********************************************************************
void CObservationReport::build() {
  try {
    // Base
    CFileReport::build();

    // Get our Obs
    pObservation = CObservationManager::Instance()->getObservation(sObservation);
  } catch (string& Ex) {
    Ex = "CObservationReport.build(" + sLabel + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CObservationReport::execute()
// Execute our Print State
//**********************************************************************
void CObservationReport::execute() {
  try {
    // Check for correct state
    if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
      if (pRuntimeController->getRunMode() != RUN_MODE_PROFILE)
        // if (pRuntimeController->getRunMode() != RUN_MODE_SIMULATION)
        return;

    CProportionsAtAgeObservation*              pProportionsAtAge              = dynamic_cast<CProportionsAtAgeObservation*>(pObservation);
    CProportionsByCategoryObservation*         pProportionsByCategory         = dynamic_cast<CProportionsByCategoryObservation*>(pObservation);
    CProportionsAtLengthObservation*           pProportionsAtLength           = dynamic_cast<CProportionsAtLengthObservation*>(pObservation);
    CProportionsAtLengthByCategoryObservation* pProportionsAtLengthByCategory = dynamic_cast<CProportionsAtLengthByCategoryObservation*>(pObservation);
    CAbundanceObservation*                     pAbundance                     = dynamic_cast<CAbundanceObservation*>(pObservation);
    CBiomassObservation*                       pBiomass                       = dynamic_cast<CBiomassObservation*>(pObservation);
    CPresenceObservation*                      pPresence                      = dynamic_cast<CPresenceObservation*>(pObservation);

    this->start();

    cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
    cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";

    vector<SComparison*> vComparisons;
    pObservation->fillComparisons(vComparisons);

    if (pProportionsAtAge != 0) {
      cout << PARAM_LABEL << CONFIG_RATIO_SEPARATOR << " " << pProportionsAtAge->getLabel() << "\n";
      cout << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pProportionsAtAge->getType() << "\n";
      cout << PARAM_YEAR << CONFIG_RATIO_SEPARATOR << " " << pProportionsAtAge->getYear() << "\n";
      cout << PARAM_TIME_STEP << CONFIG_RATIO_SEPARATOR << " " << pProportionsAtAge->getTimeStepString() << "\n";
      cout << PARAM_MIN_AGE << CONFIG_RATIO_SEPARATOR << " " << pProportionsAtAge->getMinAge() << "\n";
      cout << PARAM_MAX_AGE << CONFIG_RATIO_SEPARATOR << " " << pProportionsAtAge->getMaxAge() << "\n";
      cout << PARAM_AGE_PLUS_GROUP << CONFIG_RATIO_SEPARATOR << " " << string(pProportionsAtAge->getAgePlusGroup() ? CONFIG_TRUE : CONFIG_FALSE) << "\n";
      cout << "area" << CONFIG_SPACE_SEPARATOR << "category" << CONFIG_SPACE_SEPARATOR << "age" << CONFIG_SPACE_SEPARATOR << "observed" << CONFIG_SPACE_SEPARATOR << "expected"
           << CONFIG_SPACE_SEPARATOR << "residual" << CONFIG_SPACE_SEPARATOR << "errorvalue" << CONFIG_SPACE_SEPARATOR << "processerror" << CONFIG_SPACE_SEPARATOR << "totalerror"
           << CONFIG_SPACE_SEPARATOR << "score\n";
    } else if (pProportionsByCategory != 0) {
      cout << PARAM_LABEL << CONFIG_RATIO_SEPARATOR << " " << pProportionsByCategory->getLabel() << "\n";
      cout << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pProportionsByCategory->getType() << "\n";
      cout << PARAM_YEAR << CONFIG_RATIO_SEPARATOR << " " << pProportionsByCategory->getYear() << "\n";
      cout << PARAM_TIME_STEP << CONFIG_RATIO_SEPARATOR << " " << pProportionsByCategory->getTimeStepString() << "\n";
      cout << PARAM_MIN_AGE << CONFIG_RATIO_SEPARATOR << " " << pProportionsByCategory->getMinAge() << "\n";
      cout << PARAM_MAX_AGE << CONFIG_RATIO_SEPARATOR << " " << pProportionsByCategory->getMaxAge() << "\n";
      cout << PARAM_AGE_PLUS_GROUP << CONFIG_RATIO_SEPARATOR << " " << string(pProportionsByCategory->getAgePlusGroup() ? CONFIG_TRUE : CONFIG_FALSE) << "\n";
      cout << "area" << CONFIG_SPACE_SEPARATOR << "age" << CONFIG_SPACE_SEPARATOR << "observed" << CONFIG_SPACE_SEPARATOR << "expected" << CONFIG_SPACE_SEPARATOR << "residual"
           << CONFIG_SPACE_SEPARATOR << "errorvalue" << CONFIG_SPACE_SEPARATOR << "processerror" << CONFIG_SPACE_SEPARATOR << "totalerror" << CONFIG_SPACE_SEPARATOR << "score\n";
    } else if (pProportionsAtLength != 0) {
      cout << PARAM_LABEL << CONFIG_RATIO_SEPARATOR << " " << pProportionsAtLength->getLabel() << "\n";
      cout << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pProportionsAtLength->getType() << "\n";
      cout << PARAM_YEAR << CONFIG_RATIO_SEPARATOR << " " << pProportionsAtLength->getYear() << "\n";
      cout << PARAM_TIME_STEP << CONFIG_RATIO_SEPARATOR << " " << pProportionsAtLength->getTimeStepString() << "\n";
      int iNBins = pProportionsAtLength->getNBins();
      cout << PARAM_NBINS << CONFIG_RATIO_SEPARATOR << " " << iNBins << "\n";
      cout << PARAM_LENGTH_BINS << CONFIG_RATIO_SEPARATOR << " ";
      for (int i = 0; i < (iNBins + 1); ++i) cout << pProportionsAtLength->getLengthBinValue(i) << " ";
      cout << "\n";
      cout << "area" << CONFIG_SPACE_SEPARATOR << "category" << CONFIG_SPACE_SEPARATOR << PARAM_LENGTH_BINS << CONFIG_SPACE_SEPARATOR << "observed" << CONFIG_SPACE_SEPARATOR
           << "expected" << CONFIG_SPACE_SEPARATOR << "residual" << CONFIG_SPACE_SEPARATOR << "errorvalue" << CONFIG_SPACE_SEPARATOR << "processerror" << CONFIG_SPACE_SEPARATOR
           << "totalerror" << CONFIG_SPACE_SEPARATOR << "score\n";
    } else if (pProportionsAtLengthByCategory != 0) {
      cout << PARAM_LABEL << CONFIG_RATIO_SEPARATOR << " " << pProportionsAtLengthByCategory->getLabel() << "\n";
      cout << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pProportionsAtLengthByCategory->getType() << "\n";
      cout << PARAM_YEAR << CONFIG_RATIO_SEPARATOR << " " << pProportionsAtLengthByCategory->getYear() << "\n";
      cout << PARAM_TIME_STEP << CONFIG_RATIO_SEPARATOR << " " << pProportionsAtLengthByCategory->getTimeStepString() << "\n";
      int iNBins = pProportionsAtLengthByCategory->getNBins();
      cout << PARAM_NBINS << CONFIG_RATIO_SEPARATOR << " " << iNBins << "\n";
      cout << PARAM_LENGTH_BINS << CONFIG_RATIO_SEPARATOR << " ";
      for (int i = 0; i < (iNBins + 1); ++i) cout << pProportionsAtLengthByCategory->getLengthBinValue(i) << " ";
      cout << "\n";
      cout << "area" << CONFIG_SPACE_SEPARATOR << "category" << CONFIG_SPACE_SEPARATOR << PARAM_LENGTH_BINS << CONFIG_SPACE_SEPARATOR << "observed" << CONFIG_SPACE_SEPARATOR
           << "expected" << CONFIG_SPACE_SEPARATOR << "residual" << CONFIG_SPACE_SEPARATOR << "errorvalue" << CONFIG_SPACE_SEPARATOR << "processerror" << CONFIG_SPACE_SEPARATOR
           << "totalerror" << CONFIG_SPACE_SEPARATOR << "score\n";
    } else if (pAbundance != 0) {
      cout << PARAM_LABEL << CONFIG_RATIO_SEPARATOR << " " << pAbundance->getLabel() << "\n";
      cout << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pAbundance->getType() << "\n";
      cout << PARAM_YEAR << CONFIG_RATIO_SEPARATOR << " " << pAbundance->getYear() << "\n";
      cout << PARAM_TIME_STEP << CONFIG_RATIO_SEPARATOR << " " << pAbundance->getTimeStepString() << "\n";
      cout << PARAM_CATCHABILITY << CONFIG_RATIO_SEPARATOR << " " << pAbundance->getCatchability() << "\n";
      cout << "area" << CONFIG_SPACE_SEPARATOR << "observed" << CONFIG_SPACE_SEPARATOR << "expected" << CONFIG_SPACE_SEPARATOR << "residual" << CONFIG_SPACE_SEPARATOR
           << "errorvalue" << CONFIG_SPACE_SEPARATOR << "processerror" << CONFIG_SPACE_SEPARATOR << "totalerror" << CONFIG_SPACE_SEPARATOR << "score\n";
    } else if (pBiomass != 0) {
      cout << PARAM_LABEL << CONFIG_RATIO_SEPARATOR << " " << pBiomass->getLabel() << "\n";
      cout << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pBiomass->getType() << "\n";
      cout << PARAM_YEAR << CONFIG_RATIO_SEPARATOR << " " << pBiomass->getYear() << "\n";
      cout << PARAM_TIME_STEP << CONFIG_RATIO_SEPARATOR << " " << pBiomass->getTimeStepString() << "\n";
      cout << PARAM_CATCHABILITY << CONFIG_RATIO_SEPARATOR << " " << pBiomass->getCatchability() << "\n";
      cout << "area" << CONFIG_SPACE_SEPARATOR << "observed" << CONFIG_SPACE_SEPARATOR << "expected" << CONFIG_SPACE_SEPARATOR << "residual" << CONFIG_SPACE_SEPARATOR
           << "errorvalue" << CONFIG_SPACE_SEPARATOR << "processerror" << CONFIG_SPACE_SEPARATOR << "totalerror" << CONFIG_SPACE_SEPARATOR << "score\n";
    } else if (pPresence != 0) {
      cout << PARAM_LABEL << CONFIG_RATIO_SEPARATOR << " " << pPresence->getLabel() << "\n";
      cout << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pPresence->getType() << "\n";
      cout << PARAM_YEAR << CONFIG_RATIO_SEPARATOR << " " << pPresence->getYear() << "\n";
      cout << PARAM_TIME_STEP << CONFIG_RATIO_SEPARATOR << " " << pPresence->getTimeStepString() << "\n";
      cout << PARAM_CATCHABILITY << CONFIG_RATIO_SEPARATOR << " " << pPresence->getCatchability() << "\n";
      cout << "area" << CONFIG_SPACE_SEPARATOR << "observed" << CONFIG_SPACE_SEPARATOR << "expected" << CONFIG_SPACE_SEPARATOR << "residual" << CONFIG_SPACE_SEPARATOR
           << "errorvalue" << CONFIG_SPACE_SEPARATOR << "processerror" << CONFIG_SPACE_SEPARATOR << "totalerror" << CONFIG_SPACE_SEPARATOR << "score\n";
    } else {
      CError::errorUnknown(PARAM_OBSERVATION, "");
    }

    foreach (SComparison* Comparison, vComparisons) {
      double dResidual = Comparison->dObservedValue - Comparison->dExpectedValue;
      cout << Comparison->sKey << CONFIG_SPACE_SEPARATOR;
      if (pProportionsAtAge != 0) {
        cout << Comparison->sGroup << CONFIG_SPACE_SEPARATOR;
        cout << Comparison->iBin << CONFIG_SPACE_SEPARATOR;
      } else if (pProportionsByCategory != 0) {
        cout << Comparison->iBin << CONFIG_SPACE_SEPARATOR;
      } else if (pProportionsAtLength != 0) {
        cout << Comparison->sGroup << CONFIG_SPACE_SEPARATOR;
        cout << pProportionsAtLength->getLengthBinValue(Comparison->iBin - 1) << "-" << pProportionsAtLength->getLengthBinValue(Comparison->iBin) << CONFIG_SPACE_SEPARATOR;
      } else if (pProportionsAtLengthByCategory != 0) {
        cout << Comparison->iBin << CONFIG_SPACE_SEPARATOR;
        cout << pProportionsAtLengthByCategory->getLengthBinValue(Comparison->iBin - 1) << "-" << pProportionsAtLengthByCategory->getLengthBinValue(Comparison->iBin)
             << CONFIG_SPACE_SEPARATOR;
      }
      cout << Comparison->dObservedValue << CONFIG_SPACE_SEPARATOR << Comparison->dExpectedValue << CONFIG_SPACE_SEPARATOR << dResidual << CONFIG_SPACE_SEPARATOR
           << Comparison->dErrorValue << CONFIG_SPACE_SEPARATOR << Comparison->dProcessError << CONFIG_SPACE_SEPARATOR << Comparison->dTotalError << CONFIG_SPACE_SEPARATOR
           << Comparison->dScore << "\n";
    }

    cout << CONFIG_END_REPORT << "\n" << endl;

    this->end();
  } catch (string& Ex) {
    Ex = "CObservationReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CObservationReport::~CObservationReport()
// Destructor
//**********************************************************************
CObservationReport::~CObservationReport() {}
