//============================================================================
// Name        : CMCMCObjectivesReport.cpp
// Author      : A. Dunn
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
//============================================================================

// Headers
#include <boost/lexical_cast.hpp>

#include "CMCMCObjectivesReport.h"
#include "../../Helpers/CConvertor.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"
#include "../../MCMC/CMCMC.h"
#include "../../MCMC/CMCMCManager.h"
#include "../../TimeSteps/CTimeStepManager.h"

//**********************************************************************
// CMCMCObjectivesReport::CMCMCObjectivesReport()
// Default Constructor
//**********************************************************************
CMCMCObjectivesReport::CMCMCObjectivesReport()
{
  // Variables
  eExecutionState = STATE_ITERATION_COMPLETE;
  bWrittenHeader = false;

  pParameterList->registerAllowed(PARAM_MCMC);
}

//**********************************************************************
// void CMCMCObjectivesReport::validate()
// Validate this reporter
//**********************************************************************
void CMCMCObjectivesReport::validate()
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
    Ex = "CMCMCObjectivesReport.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMCMCObjectivesReport::build()
// Build this reporter
//**********************************************************************
void CMCMCObjectivesReport::build()
{
  try
  {
    // Base
    CFileReport::build();

    pMCMC = CMCMCManager::Instance()->getMCMC();
  }
  catch (string &Ex)
  {
    Ex = "CMCMCObjectivesReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMCMCObjectivesReport::execute()
// Execute reporter
//**********************************************************************
void CMCMCObjectivesReport::execute()
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

      ublas::matrix<double> mxCovariance = pMCMC->getCovariance();
      ublas::matrix<double> mxOriginalCovariance = pMCMC->getOriginalCovariance();
      ublas::matrix<double> mxCovarianceLT = pMCMC->getCovarianceLT();
      vector<string> vEstimateNames = pMCMC->getEstimateNames();

      cout << CONFIG_ARRAY_START << sLabel << CONFIG_ARRAY_END << "\n";
      cout << PARAM_REPORT << "." << PARAM_TYPE << CONFIG_RATIO_SEPARATOR << " " << pParameterList->getString(PARAM_TYPE) << "\n";

      cout << "Original " << PARAM_COVARIANCE << " " << PARAM_MATRIX << CONFIG_RATIO_SEPARATOR << endl;
      for (int i = 0; i < (int)mxOriginalCovariance.size1(); ++i)
      {
        for (int j = 0; j < (int)mxOriginalCovariance.size2(); ++j)
        {
          cout << mxOriginalCovariance(i, j) << ((j < (int)mxOriginalCovariance.size2() - 1) ? CONFIG_SPACE_SEPARATOR : "\n");
        }
      }
      cout << "Proposal distribution " PARAM_COVARIANCE << " " << PARAM_MATRIX << CONFIG_RATIO_SEPARATOR << endl;
      for (int i = 0; i < (int)mxCovariance.size1(); ++i)
      {
        for (int j = 0; j < (int)mxCovariance.size2(); ++j)
        {
          cout << mxCovariance(i, j) << ((j < (int)mxCovariance.size2() - 1) ? CONFIG_SPACE_SEPARATOR : "\n");
        }
      }
      cout << "Cholesky decomposition " << PARAM_MATRIX << CONFIG_RATIO_SEPARATOR << endl;
      for (int i = 0; i < (int)mxCovarianceLT.size1(); ++i)
      {
        for (int j = 0; j < (int)mxCovarianceLT.size2(); ++j)
        {
          cout << mxCovarianceLT(i, j) << ((j < (int)mxCovarianceLT.size2() - 1) ? CONFIG_SPACE_SEPARATOR : "\n");
        }
      }

      cout << "MCMC objective function values:\n";
      cout << "iteration" << CONFIG_SPACE_SEPARATOR << "score" << CONFIG_SPACE_SEPARATOR
           << PARAM_PENALTY << CONFIG_SPACE_SEPARATOR << PARAM_PRIOR << CONFIG_SPACE_SEPARATOR
           << "likelihood" << CONFIG_SPACE_SEPARATOR << "acceptance_rate" << CONFIG_SPACE_SEPARATOR
           << "acceptance_rate_since_adapt" << CONFIG_SPACE_SEPARATOR << "stepsize\n";

      bWrittenHeader = true;
    }

    //Print out the most recent set of numbers
    cout << vChain.iIteration << CONFIG_SPACE_SEPARATOR << vChain.dScore;
    cout << CONFIG_SPACE_SEPARATOR << vChain.dPenalty << CONFIG_SPACE_SEPARATOR;
    cout << vChain.dPrior << CONFIG_SPACE_SEPARATOR << vChain.dLikelihood;
    cout << CONFIG_SPACE_SEPARATOR << vChain.dAcceptanceRate << CONFIG_SPACE_SEPARATOR;
    cout << vChain.dAcceptanceRateSinceAdapt << CONFIG_SPACE_SEPARATOR << vChain.dStepSize << "\n";

    if (pMCMC->isLastItem())
    {
      cout << CONFIG_END_REPORT << "\n"
           << endl;
    }

    this->end();
  }
  catch (string &Ex)
  {
    Ex = "CMCMCObjectivesReport.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CMCMCObjectivesReport::~CMCMCObjectivesReport()
// Destructor
//**********************************************************************
CMCMCObjectivesReport::~CMCMCObjectivesReport()
{
}
