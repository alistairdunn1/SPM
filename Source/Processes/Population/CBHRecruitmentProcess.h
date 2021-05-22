//============================================================================
// Name        : CBHRecruitmentProcess.h
// Author      : S.Rasmussen
// Date        : 13/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description : This is a Beverton-Hold stock recruitment
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CBHRECRUITMENTPROCESS_H_
#define CBHRECRUITMENTPROCESS_H_

// Local Headers
#include "../CProcess.h"
#include "../../DerivedQuantities/CDerivedQuantity.h"
#include "../../DerivedQuantities/CDerivedQuantityManager.h"
#include "../../InitializationPhases/CInitializationPhaseManager.h"

// Classes
class CTimeStepManager;
class CDerivedQuantity;

//**********************************************************************
//
//
//**********************************************************************
class CBHRecruitmentProcess : public CProcess
{
public:
  CBHRecruitmentProcess();
  virtual ~CBHRecruitmentProcess();
  CProcess *clone() { return new CBHRecruitmentProcess(*this); }
  void validate();
  void build();
  void rebuild();
  void execute();
  vector<double> getTrueYCSValues() { return vTrueYCSValues; }
  vector<double> getRecruitmentValues() { return vRecruitmentValues; }
  vector<int> getYCSYears() { return vYCSYears; }
  vector<double> getSSBValues() { return vSSBValues; }
  double getB0Value() { return dB0; }

protected:
  // Variables
  double dR0;
  int iPhaseB0;
  double dB0;
  vector<double> vProportions;
  int iAge;
  int iAgeIndex;
  double dSteepness;
  //double                    dSigmaR;
  //double                    dRho;
  string sSSB;
  string sB0;
  vector<double> vYCSValues;
  vector<int> vYCSYears;
  vector<int> vStandardiseYCSYears;
  vector<double> vTrueYCSValues;
  vector<double> vRecruitmentValues;
  vector<double> vSSBValues;
  int iSSBOffset;
  int iActualOffset;
  string sLayer;
  CNumericLayer *pLayer;
  CTimeStepManager *pTimeStepManager;
  CDerivedQuantity *pDerivedQuantity;
  CInitializationPhaseManager *pInitializationPhaseManager;

private:
  double dAmountPer;
};

#endif /* CBHRECRUITMENTPROCESS_H_ */
