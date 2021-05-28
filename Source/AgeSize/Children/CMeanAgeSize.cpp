//============================================================================
// Name        : CMeanAgeSize.cpp
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CMeanAgeSize.h"

#include "../../Helpers/CError.h"
#include "../../InitializationPhases/CInitializationPhase.h"
#include "../../InitializationPhases/CInitializationPhaseManager.h"
#include "../../SizeWeight/CSizeWeight.h"
#include "../../TimeSteps/CTimeStep.h"
#include "../../TimeSteps/CTimeStepManager.h"

//**********************************************************************
// CMeanAgeSize::CMeanAgeSize()
// Default Constructor
//**********************************************************************
CMeanAgeSize::CMeanAgeSize() {
  pTimeStepManager = CTimeStepManager::Instance();

  // Register estimables
  registerEstimable(PARAM_CV, &dCV);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_SIZES);
  pParameterList->registerAllowed(PARAM_CV);
  pParameterList->registerAllowed(PARAM_DISTRIBUTION);
  pParameterList->registerAllowed(PARAM_BY_LENGTH);
  pParameterList->registerAllowed(PARAM_SIZE_WEIGHT);
}

//**********************************************************************
// voidCMeanAgeSize::validate()
// Validate the age-size relationship
//**********************************************************************
void CMeanAgeSize::validate() {
  try {
    CBaseBuild::validate();

    // Get our variables
    dCV           = pParameterList->getDouble(PARAM_CV, true, 0);
    sDistribution = pParameterList->getString(PARAM_DISTRIBUTION, true, PARAM_NORMAL);
    bByLength     = pParameterList->getBool(PARAM_BY_LENGTH, true, 1);

    iNAges = pWorld->getAgeSpread();

    pParameterList->fillVector(vSizes, PARAM_SIZES);
    // Register the Sizes as estimable
    for (int i = 0; i < (int)vSizes.size(); ++i) registerEstimable(PARAM_SIZES, i, &vSizes[i]);

    // Validate parent
    CAgeSize::validate();

    // Local validation
    if (dCV < 0)
      CError::errorLessThan(PARAM_CV, PARAM_ZERO);
    if ((int)vSizes.size() != iNAges)
      CError::errorListNotSize(PARAM_SIZES, iNAges);
    if ((sDistribution != PARAM_NORMAL) && (sDistribution != PARAM_LOGNORMAL))
      CError::errorUnknown(PARAM_DISTRIBUTION, sDistribution);
  } catch (string& Ex) {
    Ex = "CMeanAgeSize.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// voidCMeanAgeSize::build()
// Validate the age-size relationship
//**********************************************************************
void CMeanAgeSize::build() {
  CAgeSize::build();

  pInitializationPhaseManager = CInitializationPhaseManager::Instance();

  sSizeWeight                            = pParameterList->getString(PARAM_SIZE_WEIGHT);
  CSizeWeightManager* pSizeWeightManager = CSizeWeightManager::Instance();
  pSizeWeight                            = pSizeWeightManager->getSizeWeight(sSizeWeight);

  // Rebuild
  rebuild();
}

//**********************************************************************
// voidCMeanAgeSize::rebuild()
// Validate the age-size relationship
//**********************************************************************
void CMeanAgeSize::rebuild() {
  CAgeSize::rebuild();
}

//**********************************************************************
// voidCMeanAgeSize::getGrowthProportion()
// Get the growth proportion for this state and time step
//**********************************************************************
double CMeanAgeSize::getGrowthProportion() {
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
// double CMeanAgeSize::getMeanSize(double &age)
// Apply age-size relationship
//**********************************************************************
double CMeanAgeSize::getMeanSize(double& age) {
  double dSize   = vSizes[age - pWorld->getMinAge()];
  double dGrowth = getGrowthProportion();

  if (dGrowth > 0 && age < pWorld->getMaxAge())
    dSize += (vSizes[age - pWorld->getMinAge() + 1] - dSize) * dGrowth;

  if (dSize < 0)
    return 0.0;

  return dSize;
}

//**********************************************************************
// double CMeanAgeSize::getMeanWeight(double &age)
// Apply size-weight relationship
//**********************************************************************
double CMeanAgeSize::getMeanWeight(double& age) {
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
// double CMeanAgeSize::getMeanWeightFromSize(double &size)
// Apply size-weight relationship
//**********************************************************************
double CMeanAgeSize::getMeanWeightFromSize(double& size, double& cv) {
  double dWeight;
  dWeight = pSizeWeight->getMeanWeight(size, sDistribution, cv);
  return dWeight;
}

//**********************************************************************
// double CMeanAgeSize::getCV(double &age)
// get the cv at age
//**********************************************************************
double CMeanAgeSize::getCV(double& age) {
  if (bByLength) {
    return (dCV);
  } else {
    double dSize = this->getMeanSize(age);
    return ((age * dCV) / dSize);
  }
}

//**********************************************************************
// double CMeanAgeSize::getCVFromSize(double &size)
// get the cv at size
//**********************************************************************
double CMeanAgeSize::getCVFromSize(double& size) {
  if (bByLength) {
    return (dCV);
  } else {
    CError::error("age_size.by_length = false is not supported for cvs at size");
    return (0);
  }
}

//**********************************************************************
// double CMeanAgeSize::getSd(double &age)
// get the cv at age
//**********************************************************************
double CMeanAgeSize::getSd(double& age) {
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
double CMeanAgeSize::getProportionInLengthBin(double& age, double& LowerBin, double& UpperBin) {
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
// CMeanAgeSize::~CMeanAgeSize()
// Destructor
//**********************************************************************
CMeanAgeSize::~CMeanAgeSize() {}
