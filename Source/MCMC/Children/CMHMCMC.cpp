//============================================================================
// Name        : CMHMCMC.cpp
// Author      :
// Date        :
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
//============================================================================

// Headers
#include "CMHMCMC.h"

#include <limits>
#include <numeric>
#include <iostream>
#include <boost/random.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/lu.hpp>

#include "../CMCMC.h"
#include "../../Estimates/CEstimate.h"
#include "../../Estimates/CEstimateManager.h"
#include "../../Helpers/CComparer.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/ForEach.h"
#include "../../Minimizers/CMinimizer.h"
#include "../../Minimizers/CMinimizerManager.h"
#include "../../ObjectiveFunction/CObjectiveFunction.h"
#include "../../RandomNumberGenerator/CRandomNumberGenerator.h"
#include "../../Reports/CReportManager.h"
#include "../../RuntimeThread/CRuntimeThread.h"

// Namespaces
using namespace boost::numeric;
using std::cout;
using std::endl;

//**********************************************************************
// CMHMCMC::CMHMCMC()
// Default Constructor
//**********************************************************************
CMHMCMC::CMHMCMC()
{
}

//**********************************************************************
// void CMHMCMC::validate()
// Validate our MCMC
//**********************************************************************
void CMHMCMC::validate()
{
  try
  {

    CMCMC::validate();
  }
  catch (string &Ex)
  {
    Ex = "CMHMCMC.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMHMCMC::build()
// Build our MCMC
//**********************************************************************
void CMHMCMC::build()
{
  try
  {

    CMCMC::build();
  }
  catch (string &Ex)
  {
    Ex = "CMHMCMC.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMHMCMC::execute()
// Execute our MCMC
//**********************************************************************
void CMHMCMC::execute()
{
  try
  {

    CMCMC::execute();

    // Get the initial objective function value
    CRuntimeThread *pThread = pRuntimeController->getCurrentThread();
    pThread->rebuild();
    pThread->startModel();

    // Workout our objective function value
    CObjectiveFunction *pObjectiveFunction = CObjectiveFunction::Instance();
    pObjectiveFunction->execute();

    // record it as the old one as well
    CObjectiveFunction *pOldObjectiveFunction = CObjectiveFunction::Instance();

    double dScore = pObjectiveFunction->getScore();
    // Keep the location as the first point in our chain
    {
      SChainItem newItem;
      newItem.iIteration = 0;
      newItem.dPenalty = pObjectiveFunction->getPenalties();
      newItem.dScore = pObjectiveFunction->getScore();
      newItem.dPrior = pObjectiveFunction->getPriors();
      newItem.dLikelihood = pObjectiveFunction->getLikelihoods();
      ;
      newItem.dAcceptanceRate = 0;
      newItem.dAcceptanceRateSinceAdapt = 0;
      newItem.dStepSize = dStepSize;
      newItem.vValues = vCandidates;
      vChain.push_back(newItem);
    }

    //===============================================================
    // Now, do our MCMC
    //===============================================================
    // Iterate over length of MCMC

    do
    {

      if (!(pConfig->getQuietMode()))
      {
        if (((iJumps) % iKeep) == 0)
        {
          std::cerr << ".";
        }
      }

      // Generate a candidate value
      vector<double> vOldCandidates = vCandidates;
      updateStepSize(iJumps);
      generateNewCandidate();
      for (int j = 0; j < iEstimateCount; ++j)
      {
        CEstimateManager::Instance()->getEnabledEstimate(j)->setValue(vCandidates[j]);
      }

      // Run model with these parameters to get objective function score
      CRuntimeThread *pThread = pRuntimeController->getCurrentThread();
      pThread->rebuild();
      pThread->startModel();
      // Workout our Objective Score
      pOldObjectiveFunction = pObjectiveFunction;
      pObjectiveFunction->execute();

      // Preserve our score for later
      double dOldScore = dScore;
      dScore = pObjectiveFunction->getScore();
      double dRatio = 1.0;

      // Evaluate if the old value was better, and decide whether to jump
      if (dScore > dOldScore)
      {
        dRatio = exp(-dScore + dOldScore);
      }
      //Update number of jumps and jumps since last adapt
      iJumps++;
      iJumpsSinceAdapt++;
      if (dRatio == 1.0 || CRandomNumberGenerator::Instance()->getRandomUniform_01() < dRatio)
      {
        // accept the proposed candidate point
        iSuccessfulJumps++;
        iSuccessfulJumpsSinceAdapt++;
        // keep the score, and its component parts
        if (((iJumps) % iKeep) == 0)
        {
          newItem.iIteration = iJumps;
          newItem.dPenalty = pObjectiveFunction->getPenalties();
          newItem.dScore = pObjectiveFunction->getScore();
          newItem.dPrior = pObjectiveFunction->getPriors();
          newItem.dLikelihood = pObjectiveFunction->getLikelihoods();
          newItem.dAcceptanceRateSinceAdapt = (double)iSuccessfulJumpsSinceAdapt / (double)iJumpsSinceAdapt;
          newItem.dAcceptanceRate = (double)iSuccessfulJumps / (double)(iJumps);
          newItem.dStepSize = dStepSize;
          newItem.vValues = vCandidates;
          vChain.push_back(newItem);
          if (iSuccessfulJumps >= iLength)
          {
            bLastItem = true;
          }
          CReportManager::Instance()->execute(STATE_ITERATION_COMPLETE);
        }
      }
      else
      {
        // reject the new proposed candidate point and use the point from the previous iteration
        dScore = dOldScore;
        vCandidates = vOldCandidates;
        pObjectiveFunction = pOldObjectiveFunction;
        if (((iJumps) % iKeep) == 0)
        {
          newItem.iIteration = iJumps;
          newItem.dPenalty = pOldObjectiveFunction->getPenalties();
          newItem.dScore = dScore;
          newItem.dPrior = pOldObjectiveFunction->getPriors();
          newItem.dLikelihood = pOldObjectiveFunction->getLikelihoods();
          newItem.dAcceptanceRateSinceAdapt = (double)iSuccessfulJumpsSinceAdapt / (double)iJumpsSinceAdapt;
          newItem.dAcceptanceRate = (double)iSuccessfulJumps / (double)(iJumps);
          newItem.dStepSize = dStepSize;
          newItem.vValues = vCandidates;
          vChain.push_back(newItem);
          if (iSuccessfulJumps >= iLength)
          {
            bLastItem = true;
          }
          CReportManager::Instance()->execute(STATE_ITERATION_COMPLETE);
        }
      }

    } while (iJumps < iLength);

    if (!(pConfig->getQuietMode()))
    {
      std::cerr << "\n";
    }
  }
  catch (string &Ex)
  {
    Ex = "CMHMCMC.execute()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CMHMCMC::~CMHMCMC()
// Default De-Constructor
//**********************************************************************
CMHMCMC::~CMHMCMC()
{
}
