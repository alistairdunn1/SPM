//============================================================================
// Name        : CMCMC.h
// Author      : S.Rasmussen
// Date        : 2/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CMCMC_H_
#define CMCMC_H_

// Global Headers
#include <boost/numeric/ublas/matrix.hpp>

// Local Headers
#include "../BaseClasses/CBaseExecute.h"
#include "../Minimizers/CMinimizer.h"
#include "../Minimizers/CMinimizerManager.h"

// Structs
struct SChainItem {
  int            iIteration;
  double         dScore;
  double         dLikelihood;
  double         dPrior;
  double         dPenalty;
  double         dAcceptanceRate;
  double         dAcceptanceRateSinceAdapt;
  double         dStepSize;
  vector<double> vValues;
};

// Classes
class CRuntimeThread;

using namespace boost::numeric;

//**********************************************************************
//
//
//**********************************************************************
class CMCMC : public CBaseExecute {
public:
  // Methods
  void                  validate();
  void                  build();
  void                  execute();
  vector<SChainItem>    getMCMCChain() { return vChain; }
  ublas::matrix<double> getOriginalCovariance() { return mxOriginalCovariance; }
  ublas::matrix<double> getCovariance() { return mxCovariance; }
  ublas::matrix<double> getCovarianceLT() { return mxCovarianceLT; }  // Cholesky decomposition (lower triangle) of mxCovariance
  vector<string>        getEstimateNames() { return vEstimateNames; }
  bool                  isLastItem() { return bLastItem; }
  SChainItem            getLastChainItem() { return newItem; }

protected:
  // Functions
  CMCMC();
  void buildCovarianceMatrix();
  void generateEstimates();
  void generateRandomStart();
  void generateNewCandidate();
  void fillMultivariateNormal(double stepsize);
  void fillMultivariatet(double stepsize);
  bool choleskyDecomposition();
  void updateStepSize(int iteration);
  virtual ~CMCMC();

  // Variables
  string                sType;
  int                   iLength;
  bool                  bLastItem;
  ublas::matrix<double> mxOriginalCovariance;
  ublas::matrix<double> mxCovariance;
  ublas::matrix<double> mxCovarianceLT;
  SChainItem            newItem;
  vector<SChainItem>    vChain;
  vector<string>        vEstimateNames;

  double         dStart;
  int            iKeep;
  int            iEstimateCount;
  int            iJumps;
  int            iSuccessfulJumps;
  int            iJumpsSinceAdapt;
  int            iSuccessfulJumpsSinceAdapt;
  double         dMaxCorrelation;
  string         sCorrelationMethod;
  double         dCorrelationDiff;
  double         dStepSize;
  double         dAcceptanceRatio;
  string         sProposalDistribution;
  int            iDF;
  vector<double> vCandidates;
  vector<bool>   vbIsEnabledEstimate;
  vector<int>    vAdaptStepSize;
  CMinimizer*    pMinimizer;
};

#endif /*CMCMC_H_*/
