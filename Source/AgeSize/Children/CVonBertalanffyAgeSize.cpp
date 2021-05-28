//============================================================================
// Name        : CVonBertalanffyAgeSize.cpp
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CVonBertalanffyAgeSize.h"

#include "../../Helpers/CError.h"
#include "../../InitializationPhases/CInitializationPhase.h"
#include "../../InitializationPhases/CInitializationPhaseManager.h"
#include "../../SizeWeight/CSizeWeight.h"
#include "../../TimeSteps/CTimeStep.h"
#include "../../TimeSteps/CTimeStepManager.h"

//**********************************************************************
// CVonBertalanffyAgeSize::CVonBertalanffyAgeSize()
// Default Constructor
//**********************************************************************
CVonBertalanffyAgeSize::CVonBertalanffyAgeSize() {
  pTimeStepManager = CTimeStepManager::Instance();

  // Register estimables
  registerEstimable(PARAM_LINF, &dLinf);
  registerEstimable(PARAM_K, &dK);
  registerEstimable(PARAM_T0, &dT0);
  registerEstimable(PARAM_CV, &dCV);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_LINF);
  pParameterList->registerAllowed(PARAM_K);
  pParameterList->registerAllowed(PARAM_T0);
  pParameterList->registerAllowed(PARAM_CV);
  pParameterList->registerAllowed(PARAM_DISTRIBUTION);
  pParameterList->registerAllowed(PARAM_BY_LENGTH);
  pParameterList->registerAllowed(PARAM_SIZE_WEIGHT);
}

//**********************************************************************
// voidCVonBertalanffyAgeSize::validate()
// Validate the age-size relationship
//**********************************************************************
void CVonBertalanffyAgeSize::validate() {
  try {
    // Get our variables
    dLinf         = pParameterList->getDouble(PARAM_LINF);
    dK            = pParameterList->getDouble(PARAM_K);
    dT0           = pParameterList->getDouble(PARAM_T0);
    dCV           = pParameterList->getDouble(PARAM_CV, true, 0);
    sDistribution = pParameterList->getString(PARAM_DISTRIBUTION, true, PARAM_NORMAL);
    bByLength     = pParameterList->getBool(PARAM_BY_LENGTH, true, 1);

    // Validate parent
    CAgeSize::validate();

    // Local validation
    if (dLinf <= 0)
      CError::errorLessThanEqualTo(PARAM_LINF, PARAM_ZERO);
    if (dK <= 0)
      CError::errorLessThanEqualTo(PARAM_K, PARAM_ZERO);
    if (dCV < 0)
      CError::errorLessThan(PARAM_CV, PARAM_ZERO);

    if ((sDistribution != PARAM_NORMAL) && (sDistribution != PARAM_LOGNORMAL))
      CError::errorUnknown(PARAM_DISTRIBUTION, sDistribution);
  } catch (string& Ex) {
    Ex = "CVonBertalanffyAgeSize.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// voidCVonBertalanffyAgeSize::build()
// Validate the age-size relationship
//**********************************************************************
void CVonBertalanffyAgeSize::build() {
  CAgeSize::build();

  pInitializationPhaseManager = CInitializationPhaseManager::Instance();

  sSizeWeight                            = pParameterList->getString(PARAM_SIZE_WEIGHT);
  CSizeWeightManager* pSizeWeightManager = CSizeWeightManager::Instance();
  pSizeWeight                            = pSizeWeightManager->getSizeWeight(sSizeWeight);

  // Rebuild
  rebuild();
}

//**********************************************************************
// voidCVonBertalanffyAgeSize::rebuild()
// Validate the age-size relationship
//**********************************************************************
void CVonBertalanffyAgeSize::rebuild() {
  CAgeSize::rebuild();
}

//**********************************************************************
// voidCVonBertalanffyAgeSize::getGrowthProportion()
// Get the growth proportion for this state and time step
//**********************************************************************
double CVonBertalanffyAgeSize::getGrowthProportion() {
  int    iTimeStep;
  double dGrowth;

  if (pRuntimeController->getCurrentState() == STATE_INITIALIZATION) {
    pInitializationPhase = pInitializationPhaseManager->getInitializationPhase(pInitializationPhaseManager->getLastExecutedInitializationPhase());
    iTimeStep            = pInitializationPhase->getCurrentTimeStep();
    dGrowth              = pInitializationPhase->getTimeStep(iTimeStep)->getGrowthProportion();
  } else {
    iTimeStep = pTimeStepManager->getCurrentTimeStep();
    dGrowth   = pTimeStepManager->getTimeStep(iTimeStep)->getGrowthProportion();
  }

  return (dGrowth);
}

//**********************************************************************
// double CVonBertalanffyAgeSize::getMeanSize(double &age)
// Apply age-size relationship
//**********************************************************************
double CVonBertalanffyAgeSize::getMeanSize(double& age) {
  double dGrowth = getGrowthProportion();

  if ((-dK * ((age + dGrowth) - dT0)) > 10)
    throw("Fatal error in age-size relationship: exp(-k*(age-t0)) is enormous. The k or t0 parameters are probably wrong.");

  double dSize = dLinf * (1 - exp(-dK * ((age + dGrowth) - dT0)));
  if (dSize < 0)
    return 0.0;

  return dSize;
}

//**********************************************************************
// double CVonBertalanffyAgeSize::getMeanWeight(double &age)
// Apply size-weight relationship
//**********************************************************************
double CVonBertalanffyAgeSize::getMeanWeight(double& age) {
  double dWeight = 0;
  double dSize   = this->getMeanSize(age);

  if (bByLength) {
    dWeight = getMeanWeightFromSize(dSize, dCV);
  } else {
    double dGrowth = getGrowthProportion();
    double cv      = ((age + dGrowth) * dCV) / dSize;
    dWeight        = getMeanWeightFromSize(dSize, cv);
  }
  return dWeight;
}

//**********************************************************************
// double CVonBertalanffyAgeSize::getMeanWeightFromSize(double &size, double &cv)
// Apply size-weight relationship
//**********************************************************************
double CVonBertalanffyAgeSize::getMeanWeightFromSize(double& size, double& cv) {
  double dWeight;
  dWeight = pSizeWeight->getMeanWeight(size, sDistribution, cv);
  return dWeight;
}

//**********************************************************************
// double CVonBertalanffyAgeSize::getCV(double &age)
// get the cv at age
//**********************************************************************
double CVonBertalanffyAgeSize::getCV(double& age) {
  if (bByLength) {
    return (dCV);
  } else {
    double dSize = this->getMeanSize(age);
    return ((age * dCV) / dSize);
  }
}

//**********************************************************************
// double CVonBertalanffyAgeSize::getCVFromSize(double &size)
// get the cv at size
//**********************************************************************
double CVonBertalanffyAgeSize::getCVFromSize(double& size) {
  if (bByLength) {
    return (dCV);
  } else {
    CError::error("age_size.by_length = false is not supported for cvs at size");
    return (0);
  }
}

//**********************************************************************
// double CVonBertalanffyAgeSize::getSd(double &age)
// get the cv at age
//**********************************************************************
double CVonBertalanffyAgeSize::getSd(double& age) {
  if (bByLength) {
    double dSize = this->getMeanSize(age);
    return (dCV * dSize);
  } else {
    double dGrowth = getGrowthProportion();
    return ((age + dGrowth) * dCV);
  }
}

//**********************************************************************
// double getProportionInLengthBin(double &age, double &LowerBin, double&UpperBin)
// Get the proportion within the length bin
//**********************************************************************
double CVonBertalanffyAgeSize::getProportionInLengthBin(double& age, double& LowerBin, double& UpperBin) {
  double dSize   = this->getMeanSize(age);
  double dResult = 0.0;

  if (this->getSd(age) <= 0.0) {
    if ((LowerBin < dSize) && (dSize <= UpperBin))
      dResult = 1.0;
    else
      dResult = 0.0;
  } else {
    if (sDistribution == PARAM_NORMAL) {
      double dSd = this->getSd(age);
      dResult    = CNormalDistribution::getCDF(UpperBin, dSize, dSd) - CNormalDistribution::getCDF(LowerBin, dSize, dSd);
    } else if (sDistribution == PARAM_LOGNORMAL) {
      double dVar = log((dCV * dCV) + 1.0);
      double dMu  = log(dSize) - (dVar / 2.0);
      dResult     = CLogNormalDistribution::getCDF(UpperBin, dMu, sqrt(dVar)) - CLogNormalDistribution::getCDF(LowerBin, dMu, sqrt(dVar));
    } else {
      CError::errorTypeNotSupported(PARAM_DISTRIBUTION, sDistribution);
    }
  }
  return (dResult);
}

//**********************************************************************
// CVonBertalanffyAgeSize::~CVonBertalanffyAgeSize()
// Destructor
//**********************************************************************
CVonBertalanffyAgeSize::~CVonBertalanffyAgeSize() {}
