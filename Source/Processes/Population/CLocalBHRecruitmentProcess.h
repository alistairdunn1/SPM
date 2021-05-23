//============================================================================
// Name        : CLocalBHRecruitmentProcess.h
// Author      : S.Rasmussen
// Date        : 13/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description : This is a Beverton-Holt stock recruitment
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CLOCALBHRECRUITMENTPROCESS_H_
#define CLOCALBHRECRUITMENTPROCESS_H_

// Local Headers
#include "../CProcess.h"
#include "../../DerivedQuantitiesByCell/CDerivedQuantityByCell.h"
#include "../../DerivedQuantitiesByCell/CDerivedQuantityByCellManager.h"
#include "../../InitializationPhases/CInitializationPhaseManager.h"

// Classes
class CTimeStepManager;
class CDerivedQuantityByCell;

typedef vector<vector<double>> Data;

//**********************************************************************
//
//
//**********************************************************************
class CLocalBHRecruitmentProcess : public CProcess
{
public:
  CLocalBHRecruitmentProcess();
  virtual ~CLocalBHRecruitmentProcess();
  CProcess *clone() { return new CLocalBHRecruitmentProcess(*this); }
  void validate();
  void build();
  void rebuild();
  void execute();
  vector<Data> getTrueYCSValues() { return vTrueYCSValues; }
  vector<Data> getRecruitmentValues() { return vRecruitmentValues; }
  vector<int> getYCSYears() { return vYCSYears; }
  vector<Data> getSSBValues() { return vSSBValues; }
  Data getB0Value() { return dB0; }

protected:
  // Variables
  double dR0;
  int iPhaseB0;
  Data dB0;
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
  vector<Data> vTrueYCSValues;
  vector<Data> vRecruitmentValues;
  vector<Data> vSSBValues;
  int iSSBOffset;
  int iActualOffset;
  string sR0Layer;
  CNumericLayer *pR0Layer;
  vector<vector<double>> *pSSB;
  CTimeStepManager *pTimeStepManager;
  CDerivedQuantityByCell *pDerivedQuantityByCell;
  CInitializationPhaseManager *pInitializationPhaseManager;

private:
  Data dAmountPer;
  Data dTrueYCS;
};

#endif /* CLOCALBHRECRUITMENTPROCESS_H_ */
