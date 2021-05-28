//============================================================================
// Name        : CVonBertalanffyKAtAgeAgeSize.h
// Author      :
// Date        :
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
//============================================================================
#ifndef CVONBERTALANFFYKATAGEAGESIZE_H_
#define CVONBERTALANFFYKATAGEAGESIZE_H_

#include "../../InitializationPhases/CInitializationPhaseManager.h"
#include "../CAgeSize.h"

// Classes
class CTimeStepManager;
class CTimeStep;
class CInitializationPhase;

//**********************************************************************
//
//
//**********************************************************************
class CVonBertalanffyKAtAgeAgeSize : public CAgeSize {
public:
  // Functions
  CVonBertalanffyKAtAgeAgeSize();
  virtual ~CVonBertalanffyKAtAgeAgeSize();
  CAgeSize* clone() { return new CVonBertalanffyKAtAgeAgeSize(*this); }
  void      validate();
  void      build();
  void      rebuild();
  double    getMeanSize(double& age);
  double    getMeanWeight(double& age);
  double    getCV(double& age);
  double    getCVFromSize(double& size);
  double    getProportionInLengthBin(double& age, double& LowerBin, double& UpperBin);
  bool      getByLength() { return bByLength; };

protected:
  double                       dLmin;
  double                       dLinf;
  vector<double>               vKs;
  vector<double>               vSize;
  double                       dB;
  double                       dCV;
  int                          iNAges;
  double                       getGrowthProportion();
  std::string                  sDistribution;
  bool                         bByLength;
  string                       sSizeWeight;
  CSizeWeight*                 pSizeWeight;
  double                       getMeanWeightFromSize(double& size, double& cv);
  double                       getSd(double& age);
  CTimeStepManager*            pTimeStepManager;
  CInitializationPhaseManager* pInitializationPhaseManager;
  CInitializationPhase*        pInitializationPhase;
};

#endif /* CVONBERTALANFFYKATAGEAGESIZE_H_ */
