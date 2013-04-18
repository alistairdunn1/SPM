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
#include "../../TimeSteps/CTimeStepManager.h"
#include "../../MCMC/CMCMC.h"
#include "../../Helpers/CConvertor.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"

//**********************************************************************
// CMCMCReport::CMCMCReport()
// Default Constructor
//**********************************************************************
CMCMCReport::CMCMCReport() {
  // Variables
  eExecutionState     = STATE_FINALIZATION;

}

//**********************************************************************
// void CMCMCReport::validate()
// Validate this reporter
//**********************************************************************
void CMCMCReport::validate() {
  try {

    // Validate parent
    CFileReport::validate();

  } catch (string &Ex) {
    Ex = "CMCMCReport.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMCMCReport::build()
// Build this reporter
//**********************************************************************
void CMCMCReport::build() {
  try {
    // Base
    CFileReport::build();

    pMCMC = CMCMC::Instance();

  } catch (string &Ex) {
    Ex = "CMCMCReport.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMCMCReport::execute()
// Execute reporter
//**********************************************************************
void CMCMCReport::execute() {
  try {
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
    for(int i=0; i < (int)mxOriginalCovariance.size1(); ++i) {
      for(int j=0; j < (int)mxOriginalCovariance.size2(); ++j) {
        cout << mxOriginalCovariance(i,j) << ((j<(int)mxOriginalCovariance.size2()-1) ? CONFIG_SPACE_SEPERATOR : "\n");
      }
    }
    cout << "Proposal distribution " PARAM_COVARIANCE << " " << PARAM_MATRIX << CONFIG_RATIO_SEPARATOR << endl;
    for(int i=0; i < (int)mxCovariance.size1(); ++i) {
      for(int j=0; j < (int)mxCovariance.size2(); ++j) {
        cout << mxCovariance(i,j) << ((j<(int)mxCovariance.size2()-1) ? CONFIG_SPACE_SEPERATOR : "\n");
      }
    }
    cout << "Cholesky decomposition " << PARAM_MATRIX << CONFIG_RATIO_SEPARATOR << endl;
    for(int i=0; i < (int)mxCovarianceLT.size1(); ++i) {
      for(int j=0; j < (int)mxCovarianceLT.size2(); ++j) {
        cout << mxCovarianceLT(i,j) << ((j<(int)mxCovarianceLT.size2()-1) ? CONFIG_SPACE_SEPERATOR : "\n");
      }
    }

    cout << "MCMC objective function values:\n";
    cout << "iteration, score, penalty, prior, likelihood, acceptance_rate, acceptance_rate_since_adapt, step_size\n";
    for(int i=0; i<(int)vChain.size(); ++i) {
      cout << vChain[i].iIteration << CONFIG_SPACE_SEPERATOR << vChain[i].dScore;
      cout << CONFIG_SPACE_SEPERATOR << vChain[i].dPenalty << CONFIG_SPACE_SEPERATOR;
      cout << vChain[i].dPrior << CONFIG_SPACE_SEPERATOR << vChain[i].dLikelihood;
      cout << CONFIG_SPACE_SEPERATOR << vChain[i].dAcceptanceRate << CONFIG_SPACE_SEPERATOR;
      cout << vChain[i].dAcceptanceRateSinceAdapt << CONFIG_SPACE_SEPERATOR << vChain[i].dStepSize << "\n";
    }
    cout << "MCMC samples:\n";
    for (int i =0; i < (int)vEstimateNames.size(); ++i ) {
      cout << vEstimateNames[i] << ((i<(int)vEstimateNames.size()-1) ? CONFIG_SPACE_SEPERATOR : "\n");
    }
    for(int i=0; i<(int)vChain.size(); ++i) {
      for(int j=0; j < (int)vChain[i].vValues.size(); ++j) {
        cout << vChain[i].vValues[j] << ((j<(int)vChain[i].vValues.size()-1) ? CONFIG_SPACE_SEPERATOR : "\n");
      }
    }

    cout << CONFIG_END_REPORT << "\n" << endl;

    this->end();

  } catch (string &Ex) {
    Ex = "CMCMCReport.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CMCMCReport::~CMCMCReport()
// Destructor
//**********************************************************************
CMCMCReport::~CMCMCReport() {
}
