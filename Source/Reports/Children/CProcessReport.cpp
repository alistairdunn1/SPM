//============================================================================
// Name        : CProcessReport.cpp
// Author      : S.Rasmussen
// Date        : 23/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
//============================================================================

// Headers
#include "CProcessReport.h"

#include <boost/lexical_cast.hpp>

#include "../../Estimates/CEstimate.h"
#include "../../Estimates/CEstimateManager.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Processes/CProcess.h"
#include "../../Processes/CProcessManager.h"
#include "../../Processes/Population/CBHRecruitmentProcess.h"
#include "../../Processes/Population/CBHRecruitmentProcess2.h"
#include "../../Processes/Population/CBiomassEventMortalityProcess.h"
#include "../../Processes/Population/CEventMortalityProcess.h"
#include "../../Processes/Population/CHollingMortalityRateProcess.h"
#include "../../Processes/Population/CLocalBHRecruitmentProcess.h"
#include "../../Processes/Population/CPreySuitabilityPredationProcess.h"
#include "../../Processes/Population/CProportionalRecruitmentProcess.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Selectivities/CSelectivityManager.h"

//**********************************************************************
// CProcessReport::CProcessReport()
// Constructor
//**********************************************************************
CProcessReport::CProcessReport() {
  // Variables
  eExecutionState        = STATE_FINALIZATION;
  pLayerManager          = CLayerManager::Instance();
  bReportRemovals        = false;
  bReportRemovalsAsLayer = false;

  // Reg
  pParameterList->registerAllowed(PARAM_PROCESS);
  pParameterList->registerAllowed(PARAM_REMOVALS);
  pParameterList->registerAllowed(PARAM_REMOVALS_AS_LAYER);
}

//**********************************************************************
// void CProcessReport::validate()
// Validate our Parameter List
//**********************************************************************
void CProcessReport::validate() {
  try {
    // Get var
    sParameter             = pParameterList->getString(PARAM_PROCESS);
    bReportRemovals        = pParameterList->getBool(PARAM_REMOVALS, true, false);
    bReportRemovalsAsLayer = pParameterList->getBool(PARAM_REMOVALS_AS_LAYER, true, false);

    // Validate parent
    CFileReport::validate();

    // Local validation
  } catch (string& Ex) {
    Ex = "CProcessReport.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
//
//
//**********************************************************************
void CProcessReport::build() {
  try {
    // Base
    CFileReport::build();

    // Now grab our variable
    pTarget = CProcessManager::Instance()->getProcess(sParameter);
  } catch (string& Ex) {
    Ex = "CProcessReport.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProcessReport::execute()
// Execute our Report
//**********************************************************************
void CProcessReport::execute() {
  try {
    // Check for correct state
    if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
      if (pRuntimeController->getRunMode() != RUN_MODE_PROFILE)
        return;

    this->start();

    CEstimateManager* pEstimateManager = CEstimateManager::Instance();

    CParameterList* pList = pTarget->getParameterList();

    cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
    cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR << pParameterList->getString(PARAM_TYPE) << "\n";

    vector<string> vDefinedParameters;
    pList->fillDefinedParameterVector(vDefinedParameters);

    vector<string> vValues;
    foreach (string Parameter, vDefinedParameters) {
      pList->fillVector(vValues, Parameter);

      cout << Parameter << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;

      /**
       * Check if this parameter is estimated
       * First check if there is only 1 value
       */
      if (vValues.size() == 1) {
        string estimableName = "process[" + pTarget->getLabel() + "]." + Parameter;

        if (pEstimateManager->hasEstimate(estimableName)) {
          CEstimate* pEstimate = pEstimateManager->getEstimate(estimableName);
          cout << pEstimate->getValue();
        } else {
          cout << vValues[0];
        }
      } else if (vValues.size() > 1) {
        for (int i = 0; i < (int)vValues.size(); ++i) {
          string estimableName = "process[" + pTarget->getLabel() + "]." + Parameter + "(" + boost::lexical_cast<string>(i + 1) + ")";

          if (pEstimateManager->hasEstimate(estimableName)) {
            CEstimate* pEstimate = pEstimateManager->getEstimate(estimableName);
            cout << pEstimate->getValue() << (i < (int)vValues.size() ? CONFIG_SPACE_SEPARATOR : "");
          } else {
            cout << vValues[i] << (i < ((int)vValues.size() - 1) ? CONFIG_SPACE_SEPARATOR : "");
          }
        }
      } else {
        foreach (string Value, vValues) { cout << Value << CONFIG_SPACE_SEPARATOR; }
      }

      cout << endl;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // Specific private reporting for individual processes
    ///////////////////////////////////////////////////////////////////////////////

    // BH Recruitment
    CBHRecruitmentProcess* pRecruit = dynamic_cast<CBHRecruitmentProcess*>(pTarget);
    if (pRecruit != 0) {
      // B0
      cout << PARAM_B0_VALUE << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR << pRecruit->getB0Value() << "\n";
      // YCS years
      vector<int> vYCSYears = pRecruit->getYCSYears();
      cout << PARAM_YCS_YEARS << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
      for (int i = 0; i < (int)vYCSYears.size(); ++i) {
        cout << vYCSYears[i] << (i < ((int)vYCSYears.size() - 1) ? CONFIG_SPACE_SEPARATOR : "");
      }
      cout << "\n";
      // SSBs
      vector<double> vSSBValues = pRecruit->getSSBValues();
      cout << PARAM_SSB_VALUES << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
      for (int i = 0; i < (int)vSSBValues.size(); ++i) {
        cout << vSSBValues[i] << (i < ((int)vSSBValues.size() - 1) ? CONFIG_SPACE_SEPARATOR : "");
      }
      cout << "\n";
      // Recruitments
      vector<double> vRecruitmentValues = pRecruit->getRecruitmentValues();
      cout << PARAM_RECRUITMENT_VALUES << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
      for (int i = 0; i < (int)vRecruitmentValues.size(); ++i) {
        cout << vRecruitmentValues[i] << (i < ((int)vRecruitmentValues.size() - 1) ? CONFIG_SPACE_SEPARATOR : "");
      }
      cout << "\n";
      // True YCS
      vector<double> vTrueYCSValues = pRecruit->getTrueYCSValues();
      cout << PARAM_TRUE_YCS_VALUES << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
      for (int i = 0; i < (int)vTrueYCSValues.size(); ++i) {
        cout << vTrueYCSValues[i] << (i < ((int)vTrueYCSValues.size() - 1) ? CONFIG_SPACE_SEPARATOR : "");
      }
      cout << "\n";
    }

    // BH Recruitment2
    CBHRecruitmentProcess2* pRecruit2 = dynamic_cast<CBHRecruitmentProcess2*>(pTarget);
    if (pRecruit2 != 0) {
      // B0 & R0
      cout << PARAM_B0_VALUE << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR << pRecruit2->getB0Value() << "\n";
      cout << PARAM_R0_VALUE << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR << pRecruit2->getR0Value() << "\n";
      // Recruitment years
      vector<int> vAllRecruitmentYears = pRecruit2->getAllRecruitmentYears();
      cout << PARAM_RECRUITMENT_YEARS << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
      for (int i = 0; i < (int)vAllRecruitmentYears.size(); ++i) {
        cout << vAllRecruitmentYears[i] << (i < ((int)vAllRecruitmentYears.size() - 1) ? CONFIG_SPACE_SEPARATOR : "");
      }
      cout << "\n";
      // Standardising years
      vector<int> vStandardiseRecruitmentYears = pRecruit2->getStandariseRecruitmentYears();
      cout << PARAM_STANDARDISE_RECRUITMENT_YEARS << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
      for (int i = 0; i < (int)vStandardiseRecruitmentYears.size(); ++i) {
        cout << vStandardiseRecruitmentYears[i] << (i < ((int)vStandardiseRecruitmentYears.size() - 1) ? CONFIG_SPACE_SEPARATOR : "");
      }
      cout << "\n";
      // SSBs
      vector<double> vSSBValues = pRecruit2->getSSBValues();
      cout << PARAM_SSB_VALUES << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
      for (int i = 0; i < (int)vSSBValues.size(); ++i) {
        cout << vSSBValues[i] << (i < ((int)vSSBValues.size() - 1) ? CONFIG_SPACE_SEPARATOR : "");
      }
      cout << "\n";
      // Recruitment
      vector<double> vAllRecruitmentValues = pRecruit2->getAllRecruitmentValues();
      cout << PARAM_RECRUITMENT_VALUES << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
      for (int i = 0; i < (int)vAllRecruitmentValues.size(); ++i) {
        cout << vAllRecruitmentValues[i] << (i < ((int)vAllRecruitmentValues.size() - 1) ? CONFIG_SPACE_SEPARATOR : "");
      }
      cout << "\n";
      // Actual Recruitment
      vector<double> vTrueRecruitmentValues = pRecruit2->getTrueRecruitmentValues();
      cout << PARAM_TRUE_RECRUITMENT_VALUES << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
      for (int i = 0; i < (int)vTrueRecruitmentValues.size(); ++i) {
        cout << vTrueRecruitmentValues[i] << (i < ((int)vTrueRecruitmentValues.size() - 1) ? CONFIG_SPACE_SEPARATOR : "");
      }
      cout << "\n";
      // YCS
      vector<double> vYCSValues = pRecruit2->getYCSValues();
      cout << PARAM_YCS_VALUES << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
      for (int i = 0; i < (int)vYCSValues.size(); ++i) {
        cout << vYCSValues[i] << (i < ((int)vYCSValues.size() - 1) ? CONFIG_SPACE_SEPARATOR : "");
      }
      cout << "\n";
      // True YCS
      vector<double> vTrueYCSValues = pRecruit2->getTrueYCSValues();
      cout << PARAM_TRUE_YCS_VALUES << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
      for (int i = 0; i < (int)vTrueYCSValues.size(); ++i) {
        cout << vTrueYCSValues[i] << (i < ((int)vTrueYCSValues.size() - 1) ? CONFIG_SPACE_SEPARATOR : "");
      }
      cout << "\n";
    }

    // Local BH Recruitment
    CLocalBHRecruitmentProcess* pLocalRecruit = dynamic_cast<CLocalBHRecruitmentProcess*>(pTarget);
    if (pLocalRecruit != 0) {
      // YCS years
      vector<int> vYCSYears = pLocalRecruit->getYCSYears();
      cout << PARAM_YCS_YEARS << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
      for (int i = 0; i < (int)vYCSYears.size(); ++i) {
        cout << vYCSYears[i] << (i < ((int)vYCSYears.size() - 1) ? CONFIG_SPACE_SEPARATOR : "\n");
      }
      // B0
      Data dB0 = pLocalRecruit->getB0Value();
      cout << PARAM_B0_VALUE << CONFIG_RATIO_SEPARATOR << "\n";
      for (int i = 0; i < (int)dB0.size(); ++i) {
        for (int j = 0; j < (int)dB0[i].size(); ++j) {
          cout << dB0[i][j] << (j < ((int)dB0[i].size() - 1) ? CONFIG_SPACE_SEPARATOR : "\n");
        }
      }
      // SSBs
      vector<Data> vSSBValues = pLocalRecruit->getSSBValues();
      for (int i = 0; i < (int)vSSBValues.size(); ++i) {
        cout << PARAM_SSB_VALUES << " for " << PARAM_YEAR << "=" << vYCSYears[i] << ":\n";
        for (int j = 0; j < (int)vSSBValues[i].size(); ++j) {
          for (int k = 0; k < (int)vSSBValues[i][j].size(); ++k) {
            cout << vSSBValues[i][j][k] << (k < ((int)vSSBValues[i][j].size() - 1) ? CONFIG_SPACE_SEPARATOR : "\n");
          }
        }
      }
      // Recruitments
      vector<Data> vRecruitmentValues = pLocalRecruit->getRecruitmentValues();
      for (int i = 0; i < (int)vRecruitmentValues.size(); ++i) {
        cout << PARAM_RECRUITMENT_VALUES << " for " << PARAM_YEAR << "=" << vYCSYears[i] << ":\n";
        for (int j = 0; j < (int)vRecruitmentValues[i].size(); ++j) {
          for (int k = 0; k < (int)vRecruitmentValues[i][j].size(); ++k) {
            cout << vRecruitmentValues[i][j][k] << (k < ((int)vRecruitmentValues[i][j].size() - 1) ? CONFIG_SPACE_SEPARATOR : "\n");
          }
        }
      }
      // True YCS
      vector<Data> vTrueYCSValues = pLocalRecruit->getTrueYCSValues();
      for (int i = 0; i < (int)vTrueYCSValues.size(); ++i) {
        cout << PARAM_TRUE_YCS_VALUES << " for " << PARAM_YEAR << "=" << vYCSYears[i] << ":\n";
        for (int j = 0; j < (int)vTrueYCSValues[i].size(); ++j) {
          for (int k = 0; k < (int)vTrueYCSValues[i][j].size(); ++k) {
            cout << vTrueYCSValues[i][j][k] << (k < ((int)vTrueYCSValues[i][j].size() - 1) ? CONFIG_SPACE_SEPARATOR : "\n");
          }
        }
      }
    }

    // Proportional Recruitment
    CProportionalRecruitmentProcess* pProportionalRecruit = dynamic_cast<CProportionalRecruitmentProcess*>(pTarget);
    if (pProportionalRecruit != 0) {
      // SSBs
      vector<double> vSSBValues = pProportionalRecruit->getSSBValues();
      cout << PARAM_SSB_VALUES << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
      for (int i = 0; i < (int)vSSBValues.size(); ++i) {
        cout << vSSBValues[i] << (i < ((int)vSSBValues.size() - 1) ? CONFIG_SPACE_SEPARATOR : "");
      }
      cout << "\n";
      // Recruitments
      vector<double> vRecruitmentValues = pProportionalRecruit->getRecruitmentValues();
      cout << PARAM_RECRUITMENT_VALUES << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
      for (int i = 0; i < (int)vRecruitmentValues.size(); ++i) {
        cout << vRecruitmentValues[i] << (i < ((int)vRecruitmentValues.size() - 1) ? CONFIG_SPACE_SEPARATOR : "");
      }
      cout << "\n";
    }

    // EventMortalityProcess
    CEventMortalityProcess* pEventMortalityProcess = dynamic_cast<CEventMortalityProcess*>(pTarget);
    if (pEventMortalityProcess != 0 && bReportRemovals) {
      vector<int> vYears = pEventMortalityProcess->getYears();
      std::cout << PARAM_VALUES << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
      for (int i = 0; i < (int)vYears.size(); ++i) {
        std::cout << pEventMortalityProcess->getRecordedRemovals(i) << (i < ((int)vYears.size() - 1) ? CONFIG_SPACE_SEPARATOR : "");
      }
      cout << "\n";
      std::cout << PARAM_REMOVALS << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
      for (int i = 0; i < (int)vYears.size(); ++i) {
        std::cout << pEventMortalityProcess->getActualRemovals(i) << (i < ((int)vYears.size() - 1) ? CONFIG_SPACE_SEPARATOR : "");
      }
      cout << "\n";
    }
    if (pEventMortalityProcess != 0 && bReportRemovalsAsLayer) {
      vector<int> vYears = pEventMortalityProcess->getYears();
      std::cout << PARAM_YEAR << CONFIG_SPACE_SEPARATOR << PARAM_ROW << CONFIG_SPACE_SEPARATOR << PARAM_COLUMN;
      std::cout << CONFIG_SPACE_SEPARATOR << PARAM_VALUE << CONFIG_SPACE_SEPARATOR << PARAM_REMOVALS << "\n";
      for (int i = 0; i < (int)vYears.size(); ++i) {
        pCatchLayer   = pEventMortalityProcess->getRemovalsLayer(i);
        pRemovalLayer = pEventMortalityProcess->getActualRemovalsLayer(i);
        for (int j = 0; j < pRemovalLayer->getHeight(); ++j) {
          for (int k = 0; k < pRemovalLayer->getWidth(); ++k) {
            std::cout << vYears[i] << CONFIG_SPACE_SEPARATOR << j + 1 << CONFIG_SPACE_SEPARATOR << k + 1;
            std::cout << CONFIG_SPACE_SEPARATOR << pCatchLayer->getValue(j, k);
            std::cout << CONFIG_SPACE_SEPARATOR << pRemovalLayer->getValue(j, k) << "\n";
          }
        }
      }
    }

    // BiomassEventMortalityProcess
    CBiomassEventMortalityProcess* pBiomassEventMortalityProcess = dynamic_cast<CBiomassEventMortalityProcess*>(pTarget);
    if (pBiomassEventMortalityProcess != 0 && bReportRemovals) {
      vector<int> vYears = pBiomassEventMortalityProcess->getYears();
      std::cout << PARAM_VALUES << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
      for (int i = 0; i < (int)vYears.size(); ++i) {
        std::cout << pBiomassEventMortalityProcess->getRecordedRemovals(i) << (i < ((int)vYears.size() - 1) ? CONFIG_SPACE_SEPARATOR : "");
      }
      cout << "\n";
      std::cout << PARAM_REMOVALS << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
      for (int i = 0; i < (int)vYears.size(); ++i) {
        std::cout << pBiomassEventMortalityProcess->getActualRemovals(i) << (i < ((int)vYears.size() - 1) ? CONFIG_SPACE_SEPARATOR : "");
      }
      cout << "\n";
    }
    if (pBiomassEventMortalityProcess != 0 && bReportRemovalsAsLayer) {
      vector<int> vYears = pBiomassEventMortalityProcess->getYears();
      std::cout << PARAM_YEAR << CONFIG_SPACE_SEPARATOR << PARAM_ROW << CONFIG_SPACE_SEPARATOR << PARAM_COLUMN;
      std::cout << CONFIG_SPACE_SEPARATOR << PARAM_VALUE << CONFIG_SPACE_SEPARATOR << PARAM_REMOVALS << "\n";
      for (int i = 0; i < (int)vYears.size(); ++i) {
        pCatchLayer   = pBiomassEventMortalityProcess->getRemovalsLayer(i);
        pRemovalLayer = pBiomassEventMortalityProcess->getActualRemovalsLayer(i);
        for (int j = 0; j < pRemovalLayer->getHeight(); ++j) {
          for (int k = 0; k < pRemovalLayer->getWidth(); ++k) {
            std::cout << vYears[i] << CONFIG_SPACE_SEPARATOR << j + 1 << CONFIG_SPACE_SEPARATOR << k + 1;
            std::cout << CONFIG_SPACE_SEPARATOR << pCatchLayer->getValue(j, k);
            std::cout << CONFIG_SPACE_SEPARATOR << pRemovalLayer->getValue(j, k) << "\n";
          }
        }
      }
    }

    // Holling mortality rates
    CHollingMortalityRateProcess* pHolling = dynamic_cast<CHollingMortalityRateProcess*>(pTarget);
    if (pHolling != 0) {
      vector<int>    vMortalityYears  = pHolling->getMortalityYears();
      vector<double> vMortalityRate   = pHolling->getMortalityRate();
      vector<double> vMortalityN      = pHolling->getMortalityN();
      vector<double> vPredatorBiomass = pHolling->getPredatorBiomass();

      cout << PARAM_YEARS << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
      for (int i = 0; i < (int)vMortalityYears.size(); ++i) cout << vMortalityYears[i] << (i < ((int)vMortalityYears.size() - 1) ? CONFIG_SPACE_SEPARATOR : "");
      cout << "\n";
      cout << PARAM_PROPORTIONS << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
      for (int i = 0; i < (int)vMortalityRate.size(); ++i) cout << vMortalityRate[i] << (i < ((int)vMortalityRate.size() - 1) ? CONFIG_SPACE_SEPARATOR : "");
      cout << "\n";
      cout << PARAM_ABUNDANCE << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
      for (int i = 0; i < (int)vMortalityN.size(); ++i) cout << vMortalityN[i] << (i < ((int)vMortalityN.size() - 1) ? CONFIG_SPACE_SEPARATOR : "");
      cout << "\n";
      if (!(pHolling->isAbundance())) {
        vector<double> vMortalityBiomass = pHolling->getMortalityBiomass();
        cout << PARAM_BIOMASS << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
        for (int i = 0; i < (int)vMortalityBiomass.size(); ++i) cout << vMortalityBiomass[i] << (i < ((int)vMortalityBiomass.size() - 1) ? CONFIG_SPACE_SEPARATOR : "");
        cout << "\n";
      }
      if (pHolling->isAbundance()) {
        cout << PARAM_PREDATOR_ABUNDANCE << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
      } else {
        cout << PARAM_PREDATOR_BIOMASS << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
      }
      for (int i = 0; i < (int)vPredatorBiomass.size(); ++i) cout << vPredatorBiomass[i] << (i < ((int)vPredatorBiomass.size() - 1) ? CONFIG_SPACE_SEPARATOR : "");
      cout << "\n";
    }

    // Prey-Suitability predation
    CPreySuitabilityPredationProcess* pPreySuitabilityPredation = dynamic_cast<CPreySuitabilityPredationProcess*>(pTarget);
    if (pPreySuitabilityPredation != 0) {
      vector<string>         vPreyGroups      = pPreySuitabilityPredation->getPreyGroups();
      vector<int>            vMortalityYears  = pPreySuitabilityPredation->getMortalityYears();
      vector<double>         vPredatorBiomass = pPreySuitabilityPredation->getPredatorBiomass();
      vector<vector<double>> vMortalityRate   = pPreySuitabilityPredation->getMortalityRate();
      vector<vector<double>> vMortalityN      = pPreySuitabilityPredation->getMortalityN();

      cout << PARAM_YEARS << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
      for (int i = 0; i < (int)vMortalityYears.size(); ++i) cout << vMortalityYears[i] << (i < ((int)vMortalityYears.size() - 1) ? CONFIG_SPACE_SEPARATOR : "");
      cout << "\n";
      for (int m = 0; m < (int)vMortalityRate.size(); ++m) {
        cout << PARAM_PREY_GROUP << "[" << vPreyGroups[m] << "]." << PARAM_PROPORTIONS << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
        for (int i = 0; i < (int)vMortalityRate[m].size(); ++i) cout << vMortalityRate[m][i] << (i < ((int)vMortalityRate[m].size() - 1) ? CONFIG_SPACE_SEPARATOR : "");
        cout << "\n";

        cout << PARAM_PREY_GROUP << "[" << vPreyGroups[m] << "]." << PARAM_ABUNDANCE << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
        for (int i = 0; i < (int)vMortalityN[m].size(); ++i) cout << vMortalityN[m][i] << (i < ((int)vMortalityN[m].size() - 1) ? CONFIG_SPACE_SEPARATOR : "");
        cout << "\n";
        if (!(pPreySuitabilityPredation->isAbundance())) {
          vector<vector<double>> vMortalityBiomass = pPreySuitabilityPredation->getMortalityBiomass();
          cout << PARAM_PREY_GROUP << "[" << vPreyGroups[m] << "]." << PARAM_BIOMASS << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
          for (int i = 0; i < (int)vMortalityBiomass[m].size(); ++i) cout << vMortalityBiomass[m][i] << (i < ((int)vMortalityBiomass[m].size() - 1) ? CONFIG_SPACE_SEPARATOR : "");
          cout << "\n";
        }
      }
      if (pPreySuitabilityPredation->isAbundance()) {
        cout << PARAM_PREDATOR_ABUNDANCE << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
      } else {
        cout << PARAM_PREDATOR_BIOMASS << CONFIG_RATIO_SEPARATOR << CONFIG_SPACE_SEPARATOR;
      }
      for (int i = 0; i < (int)vPredatorBiomass.size(); ++i) cout << vPredatorBiomass[i] << (i < ((int)vPredatorBiomass.size() - 1) ? CONFIG_SPACE_SEPARATOR : "");
      cout << "\n";
    }

    cout << CONFIG_END_REPORT << "\n" << endl;

    this->end();
  } catch (string& Ex) {
    Ex = "CProcessReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CProcessReport::~CProcessReport()
// Destructor
//**********************************************************************
CProcessReport::~CProcessReport() {}
