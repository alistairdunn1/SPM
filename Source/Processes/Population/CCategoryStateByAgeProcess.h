//============================================================================
// Name        : CCategoryStateByAgeProcess.cpp
// Author      : A. Dunn
// Date        : 18/04/2014
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
//============================================================================
#ifndef CCATEGORYSTATEBYAGEPROCESS_H_
#define CCATEGORYSTATEBYAGEPROCESS_H_

// Local Headers
#include "../CProcess.h"
#include "../../World/WorldView/CLayerDerivedWorldView.h"

// Classes
class CTimeStepManager;
class CPenalty;
//class CCategoricalLayer;

//**********************************************************************
//
//
//**********************************************************************
class CCategoryStateByAgeProcess : public CProcess
{
public:
  // Functions
  CCategoryStateByAgeProcess();
  virtual ~CCategoryStateByAgeProcess();
  CProcess *clone() { return new CCategoryStateByAgeProcess(*this); }
  string getCategories(int index);
  void validate();
  void build();
  void execute();

protected:
  // Variables
  double dN;
  int iMinAge;
  int iMaxAge;
  int iAgeSpread;
  string sCategory;
  int iCategoryIndex;
  string sLayer;
  CCategoricalLayer *pLayer;
  CLayerDerivedWorldView *pWorldView;
  double *pAgeResults;
  map<string, vector<double>> mvNMatrix;
  CTimeStepManager *pTimeStepManager;
};

#endif /*CCATEGORYSTATEBYAGEPROCESS_H_*/
