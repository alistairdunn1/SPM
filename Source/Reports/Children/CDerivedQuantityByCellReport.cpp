//============================================================================
// Name        : CDerivedQuantityByCellReport.cpp
// Author      : S.Rasmussen
// Date        : 26/03/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// headers
#include <boost/lexical_cast.hpp>

// Local headers
#include "CDerivedQuantityByCellReport.h"
#include "../../DerivedQuantitiesByCell/CDerivedQuantityByCellManager.h"
#include "../../DerivedQuantitiesByCell/CDerivedQuantityByCell.h"

//**********************************************************************
// CDerivedQuantityByCellReport::CDerivedQuantityByCellReport()
// Constructor
//**********************************************************************
CDerivedQuantityByCellReport::CDerivedQuantityByCellReport()
{
  // Variables
  eExecutionState = STATE_FINALIZATION;
  pDerivedQuantityByCell = 0;

  // Register allowed
  pParameterList->registerAllowed(PARAM_DERIVED_QUANTITY_BY_CELL);
  pParameterList->registerAllowed(PARAM_INITIALIZATION);
}

//**********************************************************************
// void CDerivedQuantityByCellReport::validate()
// Validate our report
//**********************************************************************
void CDerivedQuantityByCellReport::validate()
{
  try
  {

    sDerivedQuantityByCell = pParameterList->getString(PARAM_DERIVED_QUANTITY_BY_CELL);
    bPrintInitialisation = pParameterList->getBool(PARAM_INITIALIZATION, true, false);

    // Validate parent
    CFileReport::validate();

    // Local validation
  }
  catch (string &ex)
  {
    ex = "CDerivedQuantityByCellReport.validate(" + getLabel() + ")->" + ex;
    throw ex;
  }
}

//**********************************************************************
// void CDerivedQuantityByCellReport::build()
// Build our Report
//**********************************************************************
void CDerivedQuantityByCellReport::build()
{
  try
  {

    // Get our derived quantity
    CDerivedQuantityByCellManager *pManager = CDerivedQuantityByCellManager::Instance();
    pDerivedQuantityByCell = pManager->getDerivedQuantityByCell(sDerivedQuantityByCell);
  }
  catch (string &Ex)
  {
    Ex = "CDerivedQuantityByCellReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CDerivedQuantityByCellReport::execute()
// Execute
//**********************************************************************
void CDerivedQuantityByCellReport::execute()
{

  try
  {
    // Check for correct state
    if (pRuntimeController->getRunMode() != RUN_MODE_BASIC)
      if (pRuntimeController->getRunMode() != RUN_MODE_PROFILE)
        return;

    this->start();

    // Output Header
    cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
    cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";
    cout << PARAM_LABEL << CONFIG_RATIO_SEPARATOR << " " << sDerivedQuantityByCell << "\n";
    cout << PARAM_ROW << "." << PARAM_COLUMN << CONFIG_RATIO_SEPARATOR << " " << pDerivedQuantityByCell->getHeight() << " " << pDerivedQuantityByCell->getWidth() << "\n";
    if (bPrintInitialisation)
    {
      // Output initialisation values
      for (int i = 0; i < pDerivedQuantityByCell->getInitialisationSize(); ++i)
      {
        for (int j = 0; j < pDerivedQuantityByCell->getInitialisationValuesSize(i); ++j)
        {
          vector<vector<double>> vvDerivedQuantityByCell = pDerivedQuantityByCell->getInitialisationValue(i, j);
          cout << PARAM_INITIALIZATION_PHASE << CONFIG_ARRAY_START << boost::lexical_cast<string>(i + 1) << CONFIG_ARRAY_END
               << "." << PARAM_YEAR << CONFIG_RATIO_SEPARATOR << " " << j + 1 << "\n";
          for (int k = 0; k < pDerivedQuantityByCell->getHeight(); ++k)
          {
            for (int l = 0; l < pDerivedQuantityByCell->getWidth(); ++l)
            {
              cout << vvDerivedQuantityByCell[k][l] << (l < ((int)pDerivedQuantityByCell->getWidth() - 1) ? CONFIG_SPACE_SEPARATOR : "\n");
            }
          }
        }
      }
    }
    // Output values for each year
    for (int i = pWorld->getInitialYear(); i <= pWorld->getCurrentYear(); ++i)
    {
      int iIndex = i - pWorld->getInitialYear();
      vector<vector<double>> vvDerivedQuantityByCell = pDerivedQuantityByCell->getValueFromIndex(iIndex);
      cout << PARAM_YEAR << CONFIG_RATIO_SEPARATOR << " " << i << "\n";
      for (int k = 0; k < pDerivedQuantityByCell->getHeight(); ++k)
      {
        for (int l = 0; l < pDerivedQuantityByCell->getWidth(); ++l)
        {
          cout << vvDerivedQuantityByCell[k][l] << (l < ((int)pDerivedQuantityByCell->getWidth() - 1) ? CONFIG_SPACE_SEPARATOR : "\n");
        }
      }
    }
    cout << CONFIG_END_REPORT << "\n"
         << endl;

    this->end();
  }
  catch (string &Ex)
  {
    Ex = "CDerivedQuantityByCellReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CDerivedQuantityByCellReport::~CDerivedQuantityByCellReport()
// Destructor
//**********************************************************************
CDerivedQuantityByCellReport::~CDerivedQuantityByCellReport()
{
}
