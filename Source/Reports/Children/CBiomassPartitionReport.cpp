//============================================================================
// Name        : CBiomassPartitionReport.cpp
// Author      : S.Rasmussen
// Date        : 29/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Headers
#include "CBiomassPartitionReport.h"

#include <boost/lexical_cast.hpp>

#include "../../Helpers/CConvertor.h"
#include "../../Helpers/CError.h"
#include "../../TimeSteps/CTimeStepManager.h"

//**********************************************************************
// CBiomassPartitionReport::CBiomassPartitionReport()
// Default Constructor
//**********************************************************************
CBiomassPartitionReport::CBiomassPartitionReport() {
  // Variables
  eExecutionState  = STATE_MODELLING;
  pTimeStepManager = CTimeStepManager::Instance();

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_YEARS);
  pParameterList->registerAllowed(PARAM_TIME_STEP);
}

//**********************************************************************
// void CBiomassPartitionReport::validate()
// Validate this reporter
//**********************************************************************
void CBiomassPartitionReport::validate() {
  try {
    // Assign Variables
    if (pParameterList->hasParameter(PARAM_YEARS)) {
      pParameterList->fillVector(vYear, PARAM_YEARS);
    } else {
      for (int i = pWorld->getInitialYear(); i <= pWorld->getCurrentYear(); ++i) vYear.push_back(i);
    }

    sTimeStep = pParameterList->getString(PARAM_TIME_STEP, true, "");

    // Validate parent
    CFileReport::validate();

    // Local validation
    // Validate Year Range
    for (int i = 0; i < (int)vYear.size(); ++i) {
      if (vYear[i] < pWorld->getInitialYear())
        CError::errorLessThan(PARAM_YEARS, PARAM_INITIAL_YEAR);
      else if (vYear[i] > pWorld->getCurrentYear())
        CError::errorGreaterThan(PARAM_YEARS, PARAM_CURRENT_YEAR);
    }
  } catch (string& Ex) {
    Ex = "CBiomassPartitionReport.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CBiomassPartitionReport::build()
// Build this reporter
//**********************************************************************
void CBiomassPartitionReport::build() {
  try {
    // Base
    CFileReport::build();

    // Populate TimeStepIndex
    if (sTimeStep != "")
      iTimeStep = pTimeStepManager->getTimeStepOrderIndex(sTimeStep);
    else {
      iTimeStep = 0;
      sTimeStep = pTimeStepManager->getFirstTimeStepLabel();
    }
  } catch (string& Ex) {
    Ex = "CBiomassPartitionReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CBiomassPartitionReport::execute()
// Execute reporter
//**********************************************************************
void CBiomassPartitionReport::execute() {
  try {
    // Check for correct state
    if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
      if (pRuntimeController->getRunMode() != RUN_MODE_PROFILE)
        return;

    this->start();
    for (int i = 0; i < (int)vYear.size(); ++i) {
      if (vYear[i] == pTimeStepManager->getCurrentYear()) {
        if (iTimeStep == pTimeStepManager->getCurrentTimeStep()) {
          // Variables
          int iSquareHeight = -1;
          int iSquareWidth  = -1;

          // Print Out
          cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
          cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";
          cout << PARAM_YEAR << CONFIG_RATIO_SEPARATOR << " " << boost::lexical_cast<string>(vYear[i]) << "\n";
          cout << PARAM_TIME_STEP << CONFIG_RATIO_SEPARATOR << " " << sTimeStep << "\n";

          cout << PARAM_ROW << CONFIG_SPACE_SEPARATOR;
          cout << PARAM_COLUMN << CONFIG_SPACE_SEPARATOR, cout << PARAM_CATEGORY;
          for (int i = pWorld->getMinAge(); i < pWorld->getMaxAge() + 1; i++) {
            cout << CONFIG_SPACE_SEPARATOR << PARAM_AGE;
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
                cout << i + 1 << CONFIG_SPACE_SEPARATOR << j + 1 << CONFIG_SPACE_SEPARATOR << pWorld->getCategoryNameForIndex(k);
                for (int l = 0; l < iSquareWidth; ++l) {
                  cout << CONFIG_SPACE_SEPARATOR << pBaseSquare->getValue(k, l) * pWorld->getMeanWeight(l, k);
                  ;
                }
                cout << "\n";
              }
            }
          }
          cout << CONFIG_END_REPORT << "\n" << endl;
        }
      }
    }
    this->end();
  } catch (string& Ex) {
    Ex = "CBiomassPartitionReport.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CBiomassPartitionReport::~CBiomassPartitionReport()
// Destructor
//**********************************************************************
CBiomassPartitionReport::~CBiomassPartitionReport() {}
