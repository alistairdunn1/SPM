//============================================================================
// Name        : DESolverEngine.cpp
// Author      : Lester E. Godwin
// Copyright   : Lester E. Godwin, godwin@pushcorp.com
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global Headers
#include <memory.h>
#include <iostream>
#include <math.h>

// Local Headers
#include "DESolverEngine.h"
#include "../../../CConfiguration.h"
#include "../../../Helpers/CComparer.h"
// Local headers
#include "../../../RandomNumberGenerator/CRandomNumberGenerator.h"

// Namespaces
using std::cerr;
using std::endl;

// Macro
#ifdef WIN32
inline double fmax(double a, double b)
{
  return (a > b) ? a : b;
}
inline double fmin(double a, double b)
{
  return (a < b) ? a : b;
}
#endif

//**********************************************************************
// DESolverEngine::DESolverEngine(int dim,int popSize)
// Constructor
//**********************************************************************
DESolverEngine::DESolverEngine(int vectorSize, int populationSize, double tolerance)
{

  // Variables
  iVectorSize = vectorSize;
  iPopulationSize = populationSize;
  iGenerations = 0;
  dScale = 0.7;
  dProbability = 0.5;
  dBestEnergy = 1.0E20;
  dStepSize = 1e-6;
  dTolerance = tolerance;

  // Build our Vectors so they are correct size
  vCurrentValues.resize(iVectorSize);
  vScaledValues.resize(iVectorSize);
  vLowerBounds.resize(iVectorSize);
  vUpperBounds.resize(iVectorSize);
  vBestSolution.resize(iVectorSize);
  vGradientValues.resize(iVectorSize);
  vPopulationEnergy.resize(iPopulationSize);

  for (int i = 0; i < iVectorSize; ++i)
    vBestSolution[i] = 0.0;

  for (int i = 0; i < iPopulationSize; ++i)
    mvPopulation[i].resize(iVectorSize);
}

//**********************************************************************
// DESolverEngine::~DESolverEngine()
// Default De-Constructor
//**********************************************************************
DESolverEngine::~DESolverEngine()
{
}

//**********************************************************************
// void DESolverEngine::Setup(double *min,double *max,
//                            int deStrategy,double diffScale,double crossoverProb)
// Setup
//**********************************************************************
void DESolverEngine::Setup(vector<double> startValues, vector<double> lowerBounds, vector<double> upperBounds,
                           int deStrategy, double diffScale, double crossoverProb)
{
  CRandomNumberGenerator *pRandom = CRandomNumberGenerator::Instance();

  switch (deStrategy)
  {
  case stBest1Exp:
    calcTrialSolution = &DESolverEngine::Best1Exp;
    iNumberOfParents = 2;
    break;

  case stRand1Exp:
    calcTrialSolution = &DESolverEngine::Rand1Exp;
    iNumberOfParents = 3;
    break;

  case stRandToBest1Exp:
    calcTrialSolution = &DESolverEngine::RandToBest1Exp;
    iNumberOfParents = 2;
    break;

  case stBest2Exp:
    calcTrialSolution = &DESolverEngine::Best2Exp;
    iNumberOfParents = 4;
    break;

  case stRand2Exp:
    calcTrialSolution = &DESolverEngine::Rand2Exp;
    iNumberOfParents = 5;
    break;

  case stBest1Bin:
    calcTrialSolution = &DESolverEngine::Best1Bin;
    iNumberOfParents = 2;
    break;

  case stRand1Bin:
    calcTrialSolution = &DESolverEngine::Rand1Bin;
    iNumberOfParents = 3;
    break;

  case stRandToBest1Bin:
    calcTrialSolution = &DESolverEngine::RandToBest1Bin;
    iNumberOfParents = 2;
    break;

  case stBest2Bin:
    calcTrialSolution = &DESolverEngine::Best2Bin;
    iNumberOfParents = 4;
    break;

  case stRand2Bin:
    calcTrialSolution = &DESolverEngine::Rand2Bin;
    iNumberOfParents = 5;
    break;
  }

  dScale = diffScale;
  dProbability = crossoverProb;

  for (int i = 0; i < iPopulationSize; ++i)
  {
    for (int j = 0; j < iVectorSize; ++j)
      mvPopulation[i][j] = pRandom->getRandomUniform(lowerBounds[j], upperBounds[j]);

    vPopulationEnergy[i] = 1.0E20;
  }

  vCurrentValues.assign(startValues.begin(), startValues.end());
  vBestSolution.assign(startValues.begin(), startValues.end());
  vLowerBounds.assign(lowerBounds.begin(), lowerBounds.end());
  vUpperBounds.assign(upperBounds.begin(), upperBounds.end());
}

//**********************************************************************
// bool DESolverEngine::Solve(int maxGenerations)
//
//**********************************************************************
bool DESolverEngine::Solve(int maxGenerations)
{

  // Variables
  bool bNewBestEnergy = false;
  CConfiguration *pConfig = CConfiguration::Instance();

  // Execute it.
  dTrialEnergy = EnergyFunction(vCurrentValues);

  if (dTrialEnergy < dBestEnergy)
  {
    bNewBestEnergy = true;
    // Copy the solution to our best.
    dBestEnergy = dTrialEnergy;
    vBestSolution.assign(vCurrentValues.begin(), vCurrentValues.end());
    if (!(pConfig->getQuietMode()))
    {
      cerr << "Current estimates: ";
      for (int k = 0; k < (int)vBestSolution.size(); ++k)
        cerr << vBestSolution[k] << " ";
      cerr << "\n";
      cerr << "Objective function value: " << dTrialEnergy << "\n\n";
    }
  }

  for (int i = 0; i < maxGenerations; ++i)
  {
    if (!(pConfig->getQuietMode()))
      cerr << DESOLVER_CURRENT_GENERATION << (i + 1) << "\n";
    for (int j = 0; j < iPopulationSize; ++j)
    {
      // Build our Trial Solution
      (this->*calcTrialSolution)(j);

      // Execute it.
      dTrialEnergy = EnergyFunction(vCurrentValues);

      // Check if this is a new low for this population
      if (dTrialEnergy < vPopulationEnergy[j])
      {

        // Copy solution to our Population
        vPopulationEnergy[j] = dTrialEnergy;
        mvPopulation[j].assign(vCurrentValues.begin(), vCurrentValues.end());

        // Is this a new all-time low for our search?
        if (dTrialEnergy < dBestEnergy)
        {
          bNewBestEnergy = true;
          // Copy the solution to our best.
          dBestEnergy = dTrialEnergy;
          vBestSolution.assign(vCurrentValues.begin(), vCurrentValues.end());

          if (!(pConfig->getQuietMode()))
          {
            cerr << "Current estimates: ";
            for (int k = 0; k < (int)vBestSolution.size(); ++k)
              cerr << vBestSolution[k] << " ";
            cerr << endl;
            cerr << "Objective function value: " << dTrialEnergy << "\n";
          }
        }
      }
    } // end for()

    // If we have a new Best, lets generate a gradient.
    if (bNewBestEnergy)
      if (generateGradient())
      {
        iGenerations = i;
        return true; // Convergence!
      }

    // Reset value
    bNewBestEnergy = false;
  }

  return false;
}

//**********************************************************************
// bool DESolverEngine::generateGradient()
// Generate our Gradient
//**********************************************************************
bool DESolverEngine::generateGradient()
{

  CConfiguration *pConfig = CConfiguration::Instance();

  double dConvergenceCheck = 0;
  for (int i = 0; i < iVectorSize; ++i)
  {
    // Create Vars
    double dMin = 1.0E20;
    double dMax = -1.0E20;

    for (int j = 0; j < iPopulationSize; ++j)
    {
      double scaled = scaleValue(mvPopulation[j][i], vLowerBounds[i], vUpperBounds[i]);

      if (scaled < dMin)
        dMin = scaled;
      if (scaled > dMax)
        dMax = scaled;
    }

    dConvergenceCheck = dMax - dMin;

    if (dConvergenceCheck > dTolerance)
    {
      if (!(pConfig->getQuietMode()))
      {
        cerr << DESOLVER_CONVERGENCE_CHECK << dConvergenceCheck << "\n";
        cerr << DESOLVER_CONVERGENCE_THRESHOLD << dTolerance << "\n"
             << endl;
      }
      return false; // No Convergence
    }
  }
  if (!(pConfig->getQuietMode()))
  {
    cerr << DESOLVER_CONVERGENCE_CHECK << dConvergenceCheck << "\n";
    cerr << DESOLVER_CONVERGENCE_THRESHOLD << dTolerance << "\n"
         << endl;
  }
  return true; // Convergence
}

void DESolverEngine::scaleValues()
{

  // Build some Scaled Values
  for (int i = 0; i < iVectorSize; ++i)
  {
    // Boundary-Pinning
    if (CComparer::isEqual(vLowerBounds[i], vUpperBounds[i]))
      vScaledValues[i] = 0.0;
    else
      vScaledValues[i] = scaleValue(vCurrentValues[i], vLowerBounds[i], vUpperBounds[i]);
  }
}

void DESolverEngine::unScaleValues()
{
  for (int i = 0; i < iVectorSize; ++i)
  {
    if (CComparer::isEqual(vLowerBounds[i], vUpperBounds[i]))
      vCurrentValues[i] = vLowerBounds[i];
    else
      vCurrentValues[i] = unScaleValue(vScaledValues[i], vLowerBounds[i], vUpperBounds[i]);
  }
}

//**********************************************************************
// double DESolverEngine::scaleValue(double value, double min, double max)
// Scale our Value from -1.0 to 1.0
//**********************************************************************
double DESolverEngine::scaleValue(double value, double min, double max)
{
  if (CComparer::isEqual(value, min))
    return -1;
  else if (CComparer::isEqual(value, max))
    return 1;

  return asin(2 * (value - min) / (max - min) - 1) / 1.57079633;
}

//**********************************************************************
// double DESolverEngine::unScaleValue(const double& value, double min, double max)
// Un-Scale our value back to Original Value
//**********************************************************************
double DESolverEngine::unScaleValue(const double &value, double min, double max)
{
  // courtesy of AUTODIF - modified to correct error -
  // penalty on values outside [-1,1] multiplied by 100 as of 14/1/02.
  double t = 0.0;
  double y = 0.0;

  t = min + (max - min) * (sin(value * 1.57079633) + 1) / 2;
  this->condAssign(y, -.9999 - value, (value + .9999) * (value + .9999), 0);
  dPenalty += y;
  this->condAssign(y, value - .9999, (value - .9999) * (value - .9999), 0);
  dPenalty += y;
  this->condAssign(y, -1 - value, 1e5 * (value + 1) * (value + 1), 0);
  dPenalty += y;
  this->condAssign(y, value - 1, 1e5 * (value - 1) * (value - 1), 0);
  dPenalty += y;

  return (t);
}

//**********************************************************************
// void DESolverEngine::condAssign(double &res, const double &cond, const double &arg1, const double &arg2)
// Conditional Assignment
//**********************************************************************
void DESolverEngine::condAssign(double &res, const double &cond, const double &arg1, const double &arg2)
{
  res = (cond) > 0 ? arg1 : arg2;
}

//**********************************************************************
// void DESolverEngine::condAssign(double &res, const double &cond, const double &arg)
// Conditional Assignment
//**********************************************************************
void DESolverEngine::condAssign(double &res, const double &cond, const double &arg)
{
  res = (cond) > 0 ? arg : res;
}

//**********************************************************************
// void DESolverEngine::Best1Exp(int candidate)
// Generate A Solution from our Best Score
//**********************************************************************
void DESolverEngine::Best1Exp(int candidate)
{
  CRandomNumberGenerator *pRandom = CRandomNumberGenerator::Instance();

  // Select our Previous Generations to Sample From
  SelectSamples(candidate);

  // Build our Current values from Target Generation
  vCurrentValues.assign(mvPopulation[candidate].begin(), mvPopulation[candidate].end());

  // Generate new values for our Current by using probability and scale and then
  // making a slight adjustment to the vBestSolution.
  for (int i = 0; i < iVectorSize; ++i)
  {
    if (pRandom->getRandomUniform_01() < dProbability)
    {
      vCurrentValues[i] = vBestSolution[i] + (dScale * (mvPopulation[iR1][i] - mvPopulation[iR2][i]));

      if (vCurrentValues[i] < vLowerBounds[i])
        vCurrentValues[i] = vLowerBounds[i];
      if (vCurrentValues[i] > vUpperBounds[i])
        vCurrentValues[i] = vUpperBounds[i];
    }
  }
}

//**********************************************************************
//
//
//**********************************************************************
void DESolverEngine::Rand1Exp(int candidate)
{
  /*int r1, r2, r3;
  int n;

  SelectSamples(candidate, &r1, &r2, &r3);
  n = (int) pRandom -> getRandomUniform(0.0, (double) nDim);

  CopyVector(trialSolution,RowVector(population,candidate));
  for (int i = 0; (pRandom -> getRandomUniform_01() < probability) && (i < nDim); i++) {
    trialSolution[n] = Element(population,r1,n) + scale * (Element(population,r2,n) - Element(population,r3,n));
    n = (n + 1) % nDim;
  }*/

  return;
}

//**********************************************************************
//
//
//**********************************************************************
void DESolverEngine::RandToBest1Exp(int candidate)
{
  /*int r1, r2;
  int n;

  SelectSamples(candidate, &r1, &r2);
  n = (int) pRandom -> getRandomUniform(0.0, (double) nDim);

  CopyVector(trialSolution,RowVector(population,candidate));
  for (int i = 0; (pRandom -> getRandomUniform_01() < probability) && (i < nDim); i++) {
    trialSolution[n] += scale * (bestSolution[n] - trialSolution[n]) + scale * (Element(population,r1,n) - Element(population,r2,n));
    n = (n + 1) % nDim;
  }
*/
  return;
}

//**********************************************************************
//
//
//**********************************************************************
void DESolverEngine::Best2Exp(int candidate)
{
  /*int r1, r2, r3, r4;
  int n;

  SelectSamples(candidate, &r1, &r2, &r3, &r4);
  n = (int) pRandom -> getRandomUniform(0.0, (double) nDim);

  CopyVector(trialSolution,RowVector(population,candidate));
  for (int i = 0; (pRandom -> getRandomUniform_01() < probability) && (i < nDim); i++) {
    trialSolution[n] = bestSolution[n] + scale * (Element(population,r1,n) + Element(population,r2,n) - Element(population,r3,n) - Element(population,r4,n));
    n = (n + 1) % nDim;
  }
*/
  return;
}

//**********************************************************************
//
//
//**********************************************************************
void DESolverEngine::Rand2Exp(int candidate)
{
  /*int r1, r2, r3, r4, r5;
  int n;

  SelectSamples(candidate, &r1, &r2, &r3, &r4, &r5);
  n = (int) pRandom -> getRandomUniform(0.0, (double) nDim);

  CopyVector(trialSolution,RowVector(population,candidate));
  for (int i = 0; (pRandom -> getRandomUniform_01() < probability) && (i < nDim); i++) {
    trialSolution[n] = Element(population,r1,n) + scale * (Element(population,r2,n) + Element(population,r3,n) - Element(population,r4,n) - Element(population,r5,n));
    n = (n + 1) % nDim;
  }*/

  return;
}

//**********************************************************************
//
//
//**********************************************************************
void DESolverEngine::Best1Bin(int candidate)
{
  /*int r1, r2;
  int n;

  SelectSamples(candidate, &r1, &r2);
  n = (int) pRandom -> getRandomUniform(0.0, (double) nDim);

  CopyVector(trialSolution,RowVector(population,candidate));
  for (int i = 0; i < nDim; i++) {
    if ((pRandom -> getRandomUniform_01() < probability) || (i == (nDim - 1)))
      trialSolution[n] = bestSolution[n] + scale * (Element(population,r1,n) - Element(population,r2,n));
    n = (n + 1) % nDim;
  }
*/
  return;
}

//**********************************************************************
//
//
//**********************************************************************
void DESolverEngine::Rand1Bin(int candidate)
{
  /*int r1, r2, r3;
  int n;

  SelectSamples(candidate, &r1, &r2, &r3);
  n = (int) pRandom -> getRandomUniform(0.0, (double) nDim);

  CopyVector(trialSolution,RowVector(population,candidate));
  for (int i = 0; i < nDim; i++) {
    if ((pRandom -> getRandomUniform_01() < probability) || (i == (nDim - 1)))
      trialSolution[n] = Element(population,r1,n) + scale * (Element(population,r2,n) - Element(population,r3,n));
    n = (n + 1) % nDim;
  }*/

  return;
}

//**********************************************************************
//
//
//**********************************************************************
void DESolverEngine::RandToBest1Bin(int candidate)
{
  /*int r1, r2;
  int n;

  SelectSamples(candidate, &r1, &r2);
  n = (int) pRandom -> getRandomUniform(0.0, (double) nDim);

  CopyVector(trialSolution,RowVector(population,candidate));
  for (int i = 0; i < nDim; i++) {
    if ((pRandom -> getRandomUniform_01() < probability) || (i == (nDim - 1)))
      trialSolution[n] += scale * (bestSolution[n] - trialSolution[n]) + scale * (Element(population,r1,n) - Element(population,r2,n));
    n = (n + 1) % nDim;
  }
*/
  return;
}

//**********************************************************************
//
//
//**********************************************************************
void DESolverEngine::Best2Bin(int candidate)
{
  /*int r1, r2, r3, r4;
  int n;

  SelectSamples(candidate, &r1, &r2, &r3, &r4);
  n = (int) pRandom -> getRandomUniform(0.0, (double) nDim);

  CopyVector(trialSolution,RowVector(population,candidate));
  for (int i = 0; i < nDim; i++) {
    if ((pRandom -> getRandomUniform_01() < probability) || (i == (nDim - 1)))
      trialSolution[n] = bestSolution[n] + scale * (Element(population,r1,n) + Element(population,r2,n) - Element(population,r3,n) - Element(population,r4,n));
    n = (n + 1) % nDim;
  }
*/
  return;
}

//**********************************************************************
//
//
//**********************************************************************
void DESolverEngine::Rand2Bin(int candidate)
{
  /*int r1, r2, r3, r4, r5;
  int n;

  SelectSamples(candidate, &r1, &r2, &r3, &r4, &r5);
  n = (int) pRandom -> getRandomUniform(0.0, (double) nDim);

  CopyVector(trialSolution,RowVector(population,candidate));
  for (int i = 0; i < nDim; i++) {
    if ((pRandom -> getRandomUniform() < probability) || (i == (nDim - 1)))
      trialSolution[n] = Element(population,r1,n) + scale * (Element(population,r2,n) + Element(population,r3,n) - Element(population,r4,n) - Element(population,r5,n));
    n = (n + 1) % nDim;
  }
*/
  return;
}

//**********************************************************************
// void DESolverEngine::SelectSamples(int candidate)
// Build us some sample values
//**********************************************************************
void DESolverEngine::SelectSamples(int candidate)
{

  CRandomNumberGenerator *pRandom = CRandomNumberGenerator::Instance();

  // Build first Sample
  if (iNumberOfParents >= 1)
  {
    do
    {
      iR1 = (int)pRandom->getRandomUniform(0.0, (double)iPopulationSize);
    } while (iR1 == candidate);
  }
  else
    return;

  // Build Second Sample
  if (iNumberOfParents >= 2)
  {
    do
    {
      iR2 = (int)pRandom->getRandomUniform(0.0, (double)iPopulationSize);
    } while ((iR2 == candidate) || (iR2 == iR1));
  }
  else
    return;

  // Build third sample
  if (iNumberOfParents >= 3)
  {
    do
    {
      iR3 = (int)pRandom->getRandomUniform(0.0, (double)iPopulationSize);
    } while ((iR3 == candidate) || (iR3 == iR2) || (iR3 == iR1));
  }
  else
    return;

  // etc
  if (iNumberOfParents >= 4)
  {
    do
    {
      iR4 = (int)pRandom->getRandomUniform(0.0, (double)iPopulationSize);
    } while ((iR4 == candidate) || (iR4 == iR3) || (iR4 == iR2) || (iR4 == iR1));
  }

  // etc
  if (iNumberOfParents >= 5)
  {
    do
    {
      iR5 = (int)pRandom->getRandomUniform(0.0, (double)iPopulationSize);
    } while ((iR5 == candidate) || (iR5 == iR4) || (iR5 == iR3) || (iR5 == iR2) || (iR5 == iR1));
  }

  return;
}
