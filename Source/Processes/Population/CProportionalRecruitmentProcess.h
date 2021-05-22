//============================================================================
// Name        : CProportionalRecruitmentProcess.h
// Author      : A.Dunn
// Date        : June 2013
// Copyright   : Copyright NIWA Science �2013 - www.niwa.co.nz
//============================================================================
#ifndef CPROPORTIONALRECRUITMENTPROCESS_H_
#define CPROPORTIONALRECRUITMENTPROCESS_H_

// Local Headers
#include "../CProcess.h"
#include "../../DerivedQuantities/CDerivedQuantity.h"
#include "../../DerivedQuantities/CDerivedQuantityManager.h"
#include "../../InitializationPhases/CInitializationPhaseManager.h"

// Forward Declaration
class CNumericLayer;
class CDerivedQuantity;

//**********************************************************************
//
//
//**********************************************************************
class CProportionalRecruitmentProcess : public CProcess
{
public:
  // Functions
  CProportionalRecruitmentProcess();
  virtual ~CProportionalRecruitmentProcess();
  CProcess *clone() { return new CProportionalRecruitmentProcess(*this); }
  void validate();
  void build();
  void rebuild();
  void execute();
  double getLambda() { return dLambda; }
  double getB0() { return dB0; }
  vector<double> getRecruitmentValues() { return vRecruitmentValues; }
  vector<double> getSSBValues() { return vSSBValues; }

protected:
  // Variables
  double dLambda;
  double dB0;
  double dR0;
  int iPhaseB0;
  string sSSB;
  string sB0;
  int iSSBOffset;
  vector<double> vRecruitmentValues;
  vector<double> vSSBValues;
  CTimeStepManager *pTimeStepManager;
  CDerivedQuantity *pDerivedQuantity;
  CInitializationPhaseManager *pInitializationPhaseManager;
  vector<double> vProportions;
  int iAge;
  int iAgeIndex;
  string sLayer;
  CNumericLayer *pLayer;

private:
  double dAmountPer;
};

#endif /*CPROPORTIONALRECRUITMENTPROCESS_H_*/
