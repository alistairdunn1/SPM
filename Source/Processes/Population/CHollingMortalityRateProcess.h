//============================================================================
// Name        : CHollingMortalityRateProcess.h
// Author      : S.Rasmussen
// Date        : 15/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CHOLLINGMORTALITYRATEPROCESS_H_
#define CHOLLINGMORTALITYRATEPROCESS_H_

// Local headers
#include "../CProcess.h"

// Forward-Dec
class CPenalty;
class CSelectivity;
class CTimeStepManager;

//**********************************************************************
//
//
//**********************************************************************
class CHollingMortalityRateProcess : public CProcess
{
public:
  // Functions
  CHollingMortalityRateProcess();
  virtual ~CHollingMortalityRateProcess();
  CProcess *clone() { return new CHollingMortalityRateProcess(*this); }
  void validate();
  void build();
  void rebuild();
  void execute();
  vector<int> getMortalityYears() { return vMortalityYears; }
  vector<double> getMortalityRate() { return vMortalityRate; }
  vector<double> getMortalityN() { return vMortalityN; }
  vector<double> getMortalityBiomass() { return vMortalityBiomass; }
  vector<double> getPredatorBiomass() { return vPredatorBiomass; }
  bool isAbundance() { return bIsAbundance; }
  int getPredatorCategoryCount() { return vPredatorCategoryList.size(); }
  int getPredatorSelectivityCount() { return vPredatorSelectivityList.size(); }

protected:
  // Variables
  bool bIsAbundance;
  double dA;
  double dB;
  double dX;
  double dUMax;
  double dMortality;
  double dExploitation;
  double dVulnerable;
  double dPredatorVulnerable;
  vector<string> vPredatorCategoryList;
  vector<int> vPredatorCategoryIndex;
  vector<string> vPredatorSelectivityList;
  vector<CSelectivity *> vPredatorSelectivityIndex;
  double dPredatorCurrent;
  vector<int> vMortalityYears;
  vector<double> vMortalityRate;
  vector<double> vMortalityN;
  vector<double> vMortalityBiomass;
  vector<double> vPredatorBiomass;
  string sPenalty;
  CPenalty *pPenalty;
  CTimeStepManager *pTimeStepManager;
};

#endif /* CHOLLINGMORTALITYRATEPROCESS_H_ */
