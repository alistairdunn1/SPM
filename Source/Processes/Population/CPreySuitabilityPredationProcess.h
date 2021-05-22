//============================================================================
// Name        : CPreySuitabilityPredationProcess.h
// Author      : S.Rasmussen
// Date        : 15/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CPRESUITABILITYPREDATIONPROCESS_H_
#define CPRESUITABILITYPREDATIONPROCESS_H_

// Local headers
#include "../CProcess.h"

// Forward-Dec
class CPenalty;
class CTimeStepManager;
class CCompoundCategories;

//**********************************************************************
//
//
//**********************************************************************
class CPreySuitabilityPredationProcess : public CProcess
{
public:
  // Functions
  CPreySuitabilityPredationProcess();
  virtual ~CPreySuitabilityPredationProcess();
  CProcess *clone() { return new CPreySuitabilityPredationProcess(*this); }
  void validate();
  void build();
  void rebuild();
  void execute();
  vector<int> getMortalityYears() { return vMortalityYears; }
  vector<vector<double>> getMortalityRate() { return vMortalityRate; }
  vector<vector<double>> getMortalityN() { return vMortalityN; }
  vector<vector<double>> getMortalityBiomass() { return vMortalityBiomass; }
  vector<double> getPredatorBiomass() { return vPredatorBiomass; }
  bool isAbundance() { return bIsAbundance; }
  int getPredatorCategoryCount() { return vPredatorCategoryList.size(); }
  int getPredatorSelectivityCount() { return vPredatorSelectivityList.size(); }
  vector<string> getPreyGroups();

protected:
  // Variables
  bool bIsAbundance;
  double dCR;
  string sCRLayer;
  CNumericLayer *pCRLayer;
  double dUMax;
  vector<double> vMortality;
  vector<double> vExploitation;
  vector<double> vVulnerable;
  double dPredatorVulnerable;
  vector<double> vElectivityList;
  vector<string> vPreyCategoryList;
  vector<string> vPreySelectivityList;
  vector<vector<CSelectivity *>> vvPreySelectivityIndex;
  vector<string> vPredatorCategoryList;
  vector<int> vPredatorCategoryIndex;
  vector<string> vPredatorSelectivityList;
  vector<CSelectivity *> vPredatorSelectivityIndex;

  double dPredatorCurrent;
  vector<int> vMortalityYears;
  vector<vector<double>> vMortalityRate;
  vector<vector<double>> vMortalityN;
  vector<vector<double>> vMortalityBiomass;
  vector<double> vPredatorBiomass;
  string sPenalty;
  CPenalty *pPenalty;
  CTimeStepManager *pTimeStepManager;
  CCompoundCategories *pPreyCategories;
};

#endif /* CPRESUITABILITYPREDATIONPROCESS_H_ */
