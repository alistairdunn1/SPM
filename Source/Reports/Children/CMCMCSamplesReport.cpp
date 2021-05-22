//============================================================================
// Name        : CMCMCSamplesReport.cpp
// Author      : A. Dunn
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
//============================================================================

// Headers
#include <boost/lexical_cast.hpp>

#include "CMCMCSamplesReport.h"
#include "../../Helpers/CConvertor.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"
#include "../../MCMC/CMCMC.h"
#include "../../MCMC/CMCMCManager.h"
#include "../../TimeSteps/CTimeStepManager.h"

//**********************************************************************
// CMCMCSamplesReport::CMCMCSamplesReport()
// Default Constructor
//**********************************************************************
CMCMCSamplesReport::CMCMCSamplesReport()
{
  // Variables
  eExecutionState = STATE_ITERATION_COMPLETE;
  bWrittenHeader = false;

  pParameterList->registerAllowed(PARAM_MCMC);
}

//**********************************************************************
// void CMCMCSamplesReport::validate()
// Validate this reporter
//**********************************************************************
void CMCMCSamplesReport::validate()
{
  try
  {

    // Validate parent
    CFileReport::validate();

    sFileName = pParameterList->getString(PARAM_FILE_NAME);
    //sMCMC       = pParameterList->getString(PARAM_MCMC);
  }
  catch (string &Ex)
  {
    Ex = "CMCMCSamplesReport.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMCMCSamplesReport::build()
// Build this reporter
//**********************************************************************
void CMCMCSamplesReport::build()
{
  try
  {
    // Base
    CFileReport::build();

    pMCMC = CMCMCManager::Instance()->getMCMC();
  }
  catch (string &Ex)
  {
    Ex = "CMCMCSamplesReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMCMCSamplesReport::execute()
// Execute reporter
//**********************************************************************
void CMCMCSamplesReport::execute()
{
  try
  {

    // Check for correct state
    if (pRuntimeController->getRunMode() != RUN_MODE_MONTE_CARLO_MARKOV_CHAIN)
      return;

    vChain = pMCMC->getLastChainItem();

    this->start();

    // Print Out
    if (!bWrittenHeader)
    {
      cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
      cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";

      cout << PARAM_MCMC_SAMPLES << CONFIG_RATIO_SEPARATOR << "\n";
      vector<string> vEstimateNames = pMCMC->getEstimateNames();
      for (int i = 0; i < (int)vEstimateNames.size(); ++i)
      {
        cout << vEstimateNames[i] << ((i < (int)vEstimateNames.size() - 1) ? CONFIG_SPACE_SEPARATOR : "\n");
      }
      bWrittenHeader = true;
    }

    //Print out the most recent set of numbers
    for (int j = 0; j < (int)vChain.vValues.size(); ++j)
    {
      cout << vChain.vValues[j] << ((j < (int)vChain.vValues.size() - 1) ? CONFIG_SPACE_SEPARATOR : "\n");
    }

    if (pMCMC->isLastItem())
    {
      cout << CONFIG_END_REPORT << "\n"
           << endl;
    }

    this->end();
  }
  catch (string &Ex)
  {
    Ex = "CMCMCSamplesReport.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CMCMCSamplesReport::~CMCMCSamplesReport()
// Destructor
//**********************************************************************
CMCMCSamplesReport::~CMCMCSamplesReport()
{
}
