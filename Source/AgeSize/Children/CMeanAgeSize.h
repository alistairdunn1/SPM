//============================================================================
// Name        : CMeanAgeSize.h
// Author      :
// Date        :
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
//============================================================================
#ifndef CMEANAGESIZE_H_
#define CMEANAGESIZE_H_

#include "../CAgeSize.h"
#include "../../InitializationPhases/CInitializationPhaseManager.h"

// Classes
class CTimeStepManager;
class CTimeStep;
class CInitializationPhase;

//**********************************************************************
//
//
//**********************************************************************
class CMeanAgeSize : public CAgeSize
{
public:
  // Functions
  CMeanAgeSize();
  virtual ~CMeanAgeSize();
  CAgeSize *clone() { return new CMeanAgeSize(*this); }
  void validate();
  void build();
  void rebuild();
  double getMeanSize(double &age);
  double getMeanWeight(double &age);
  double getCV(double &age);
  double getCVFromSize(double &size);
  double getProportionInLengthBin(double &age, double &LowerBin, double &UpperBin);
  bool getByLength() { return bByLength; };

protected:
  vector<double> vSizes;
  double dCV;
  int iNAges;
  double getGrowthProportion();
  std::string sDistribution;
  bool bByLength;
  string sSizeWeight;
  CSizeWeight *pSizeWeight;
  double getMeanWeightFromSize(double &size, double &cv);
  double getSd(double &age);
  CTimeStepManager *pTimeStepManager;
  CInitializationPhaseManager *pInitializationPhaseManager;
  CInitializationPhase *pInitializationPhase;
};

#endif /* CMEANAGESIZE_H_ */
