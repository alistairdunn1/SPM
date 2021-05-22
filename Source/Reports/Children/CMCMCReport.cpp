//============================================================================
// Name        : CMCMCReport.cpp
// Author      : S.Rasmussen
// Date        : 26/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Headers
#include <boost/lexical_cast.hpp>

#include "CMCMCReport.h"
#include "../../Helpers/CConvertor.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"
#include "../../MCMC/CMCMC.h"
#include "../../MCMC/CMCMCManager.h"
#include "../../TimeSteps/CTimeStepManager.h"

//**********************************************************************
// CMCMCReport::CMCMCReport()
// Default Constructor
//**********************************************************************
CMCMCReport::CMCMCReport()
{
  // Variables
  eExecutionState = STATE_FINALIZATION;

  pParameterList->registerAllowed(PARAM_MCMC);
}

//**********************************************************************
// void CMCMCReport::validate()
// Validate this reporter
//**********************************************************************
void CMCMCReport::validate()
{
  try
  {
    // Validate parent
    CFileReport::validate();

    //sMCMC = pParameterList->getString(PARAM_MCMC);
  }
  catch (string &Ex)
  {
    Ex = "CMCMCReport.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMCMCReport::build()
// Build this reporter
//**********************************************************************
void CMCMCReport::build()
{
  try
  {
    // Base
    CFileReport::build();

    pMCMC = CMCMCManager::Instance()->getMCMC();
  }
  catch (string &Ex)
  {
    Ex = "CMCMCReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMCMCReport::execute()
// Execute reporter
//**********************************************************************
void CMCMCReport::execute()
{
  try
  {
    // Check for correct state
    if (pRuntimeController->getRunMode() != RUN_MODE_MONTE_CARLO_MARKOV_CHAIN)
      return;

    vChain = pMCMC->getMCMCChain();
    ublas::matrix<double> mxCovariance = pMCMC->getCovariance();
    ublas::matrix<double> mxOriginalCovariance = pMCMC->getOriginalCovariance();
    ublas::matrix<double> mxCovarianceLT = pMCMC->getCovarianceLT();
    vector<string> vEstimateNames = pMCMC->getEstimateNames();

    this->start();

    // Print Out
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

    for (int i = 0; i < (int)vChain.size(); ++i)
    {
      cout << vChain[i].iIteration << CONFIG_SPACE_SEPARATOR << vChain[i].dScore;
      cout << CONFIG_SPACE_SEPARATOR << vChain[i].dPenalty << CONFIG_SPACE_SEPARATOR;
      cout << vChain[i].dPrior << CONFIG_SPACE_SEPARATOR << vChain[i].dLikelihood;
      cout << CONFIG_SPACE_SEPARATOR << vChain[i].dAcceptanceRate << CONFIG_SPACE_SEPARATOR;
      cout << vChain[i].dAcceptanceRateSinceAdapt << CONFIG_SPACE_SEPARATOR << vChain[i].dStepSize << "\n";
    }
    cout << "MCMC samples:\n";
    for (int i = 0; i < (int)vEstimateNames.size(); ++i)
    {
      cout << vEstimateNames[i] << ((i < (int)vEstimateNames.size() - 1) ? CONFIG_SPACE_SEPARATOR : "\n");
    }
    for (int i = 0; i < (int)vChain.size(); ++i)
    {
      for (int j = 0; j < (int)vChain[i].vValues.size(); ++j)
      {
        cout << vChain[i].vValues[j] << ((j < (int)vChain[i].vValues.size() - 1) ? CONFIG_SPACE_SEPARATOR : "\n");
      }
    }

    cout << CONFIG_END_REPORT << "\n"
         << endl;

    this->end();
  }
  catch (string &Ex)
  {
    Ex = "CMCMCReport.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CMCMCReport::~CMCMCReport()
// Destructor
//**********************************************************************
CMCMCReport::~CMCMCReport()
{
}
