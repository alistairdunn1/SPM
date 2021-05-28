//============================================================================
// Name        : CBHRecruitmentProcess2.h
// Author      : A.Dunn
// Date        : 23/05/2021
// Copyright   :
// Description : This is a Beverton-Holt stock recruitment, parametersed with absolute annual recruitment
//============================================================================
#ifndef CBHRECRUITMENTPROCESS2_H_
#define CBHRECRUITMENTPROCESS2_H_

// Local Headers
#include "../../DerivedQuantities/CDerivedQuantity.h"
#include "../../DerivedQuantities/CDerivedQuantityManager.h"
#include "../../InitializationPhases/CInitializationPhaseManager.h"
#include "../CProcess.h"

// Classes
class CTimeStepManager;
class CDerivedQuantity;

//**********************************************************************
//
//
//**********************************************************************
class CBHRecruitmentProcess2 : public CProcess {
public:
  CBHRecruitmentProcess2();
  virtual ~CBHRecruitmentProcess2();
  CProcess*      clone() { return new CBHRecruitmentProcess2(*this); }
  void           validate();
  void           build();
  void           rebuild();
  void           execute();
  vector<double> getTrueYCSValues() { return vTrueYCSValues; }
  vector<double> getYCSValues() { return vYCSValues; }
  vector<double> getAllRecruitmentValues() { return vAllRecruitmentValues; }
  vector<int>    getAllRecruitmentYears() { return vAllRecruitmentYears; }
  vector<double> getRecruitmentValues() { return vRecruitmentValues; }
  vector<int>    getRecruitmentYears() { return vRecruitmentYears; }
  vector<int>    getStandariseRecruitmentYears() { return vStandardiseRecruitmentYears; }
  vector<double> getTrueRecruitmentValues() { return vTrueRecruitmentValues; }
  vector<double> getSSBValues() { return vSSBValues; }
  double         getB0Value() { return dB0; }
  double         getR0Value() { return dR0; }

protected:
  // Variables
  double         dR0;
  int            iPhaseB0;
  double         dB0;
  vector<double> vProportions;
  int            iAge;
  int            iAgeIndex;
  double         dSteepness;
  // double dSigmaR;
  // double dRho;
  string                       sSSB;
  string                       sB0;
  vector<double>               vAllRecruitmentValues;
  vector<double>               vTrueRecruitmentValues;
  vector<int>                  vAllRecruitmentYears;
  vector<double>               vRecruitmentValues;
  vector<int>                  vRecruitmentYears;
  vector<int>                  vStandardiseRecruitmentYears;
  vector<double>               vTrueYCSValues;
  vector<double>               vYCSValues;
  vector<double>               vSSBValues;
  int                          iSSBOffset;
  int                          iActualOffset;
  string                       sLayer;
  CNumericLayer*               pLayer;
  CTimeStepManager*            pTimeStepManager;
  CDerivedQuantity*            pDerivedQuantity;
  CInitializationPhaseManager* pInitializationPhaseManager;

private:
  double dAmountPer;
};

#endif /* CBHRECRUITMENTPROCESS2_H_ */
