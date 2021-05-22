//============================================================================
// Name        : CObservation.h
// Author      : S.Rasmussen
// Date        : 19/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef COBSERVATION_H_
#define COBSERVATION_H_

// Local Headers
#include "../BaseClasses/CBaseExecute.h"
#include "../World/WorldView/CLayerDerivedWorldView.h"
#include "../Likelihoods/CLikelihood.h"

// structures
struct SComparison
{
  string sKey;
  int iBin;
  string sGroup;
  double dExpectedValue;
  double dObservedValue;
  double dErrorValue;
  double dProcessError;
  double dTotalError;
  double dMultiplier;
  double dScore;
};

// Classes
class CCategoricalLayer;
class CSelectivity;

//**********************************************************************
//
//
//**********************************************************************
class CObservation : public CBaseExecute
{
public:
  // Functions
  CObservation();
  virtual ~CObservation();
  virtual CObservation *clone() = 0;
  int getYear() { return iYear; }
  int getTimeStep() { return iTimeStep; }
  string getTimeStepString() { return sTimeStep; }
  string getLayer() { return sLayer; }
  string getCategory(int index);
  string getSelectivity(int index);
  double getScore() { return dScore; }
  void fillComparisons(vector<SComparison *> &comparisons);
  virtual void validate();
  virtual void build();
  void prepare();
  virtual void execute();
  string getType();

protected:
  // Functions
  void saveComparison(string key, int age, string group, double expected, double observed, double errorValue, double processError, double totalError, double multiplier, double score);
  void saveComparison(string key, int age, double expected, double observed, double errorValue, double processError, double totalError, double multiplier, double score);
  void saveComparison(string key, double expected, double observed, double errorValue, double processError, double totalError, double multiplier, double score);

  // Variables
  double dScore;
  double dMultiplier;
  int iYear;
  string sTimeStep;
  int iTimeStep;
  double dProportionTimeStep;
  string sProportionMethod;
  string sLayer;
  CCategoricalLayer *pLayer;
  vector<string> vCategoryNames;
  vector<int> vCategories;
  vector<string> vSelectivityNames;
  vector<CSelectivity *> vSelectivities;
  vector<SComparison *> vComparisons;
  CLayerDerivedWorldView *pStartWorldView;
  CLayerDerivedWorldView *pWorldView;
  string sLikelihood;
  string sSimulationLikelihood;
  CLikelihood *pLikelihood;
  bool bSimulationRunMode;
};

#endif /*COBSERVATION_H_*/
