// Differential Evolution Solver Class
// Based on algorithms developed by Dr. Rainer Storn & Kenneth Price
// Written By: Lester E. Godwin
//             PushCorp, Inc.
//             Dallas, Texas
//             972-840-0208 x102
//             godwin@pushcorp.com
// Created: 6/8/98
// Last Modified: 6/8/98
// Revision: 1.0

#ifndef _DESOLVERENGINE_H
#define _DESOLVERENGINE_H

// Global Headers
#include <vector>
#include <map>

using std::map;
using std::vector;

// Defines
#define stBest1Exp 0
#define stRand1Exp 1
#define stRandToBest1Exp 2
#define stBest2Exp 3
#define stRand2Exp 4
#define stBest1Bin 5
#define stRand1Bin 6
#define stRandToBest1Bin 7
#define stBest2Bin 8
#define stRand2Bin 9

class DESolverEngine;
typedef void (DESolverEngine::*StrategyFunction)(int);

//**********************************************************************
//
//
//**********************************************************************
class DESolverEngine
{
public:
  DESolverEngine(int vectorSize, int populationsize, double tolerance);
  virtual ~DESolverEngine(void);
  void Setup(vector<double> startValues, vector<double> lowerBounds,
             vector<double> upperBounds, int deStrategy, double diffScale, double crossoverProb);
  virtual bool Solve(int maxGenerations);
  virtual double EnergyFunction(vector<double> testSolution) = 0;
  double getEnergy() { return dBestEnergy; }
  int getGenerations() { return iGenerations; }

protected:
  // Functions
  void SelectSamples(int candidate);
  bool generateGradient();
  void scaleValues();
  void unScaleValues();
  double scaleValue(double value, double min, double max);
  double unScaleValue(const double &value, double min, double max);
  void condAssign(double &res, const double &cond, const double &arg1, const double &arg2);
  void condAssign(double &res, const double &cond, const double &arg);

  // Variables
  int iVectorSize;
  vector<double> vCurrentValues;
  vector<double> vScaledValues;
  vector<double> vLowerBounds;
  vector<double> vUpperBounds;
  map<int, vector<double>> mvPopulation;
  vector<double> vPopulationEnergy;
  vector<double> vBestSolution;
  vector<double> vGradientValues;
  int iPopulationSize;
  int iNumberOfParents;
  int iGenerations;
  double dScale;
  double dProbability;
  double dBestEnergy;
  double dTrialEnergy;
  StrategyFunction calcTrialSolution;
  int iR1;
  int iR2;
  int iR3;
  int iR4;
  int iR5;
  double dStepSize;
  double dPenalty;
  double dTolerance;

private:
  // Functions
  void Best1Exp(int candidate);
  void Rand1Exp(int candidate);
  void RandToBest1Exp(int candidate);
  void Best2Exp(int candidate);
  void Rand2Exp(int candidate);
  void Best1Bin(int candidate);
  void Rand1Bin(int candidate);
  void RandToBest1Bin(int candidate);
  void Best2Bin(int candidate);
  void Rand2Bin(int candidate);
};

#endif // _DESOLVERENGINE_H
