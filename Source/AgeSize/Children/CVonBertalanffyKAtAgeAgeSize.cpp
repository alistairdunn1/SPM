//============================================================================
// Name        : CVonBertalanffyKAtAgeAgeSize.cpp
// Author      :
// Date        :
// Copyright   :
// Description :
//============================================================================

// Local headers
#include "CVonBertalanffyKAtAgeAgeSize.h"

#include "../../Helpers/CError.h"
#include "../../InitializationPhases/CInitializationPhase.h"
#include "../../InitializationPhases/CInitializationPhaseManager.h"
#include "../../SizeWeight/CSizeWeight.h"
#include "../../TimeSteps/CTimeStep.h"
#include "../../TimeSteps/CTimeStepManager.h"

//**********************************************************************
// CVonBertalanffyKAtAgeAgeSize::CVonBertalanffyKAtAgeAgeSize()
// Default Constructor
//**********************************************************************
CVonBertalanffyKAtAgeAgeSize::CVonBertalanffyKAtAgeAgeSize() {
  pTimeStepManager = CTimeStepManager::Instance();

  // Register estimables
  registerEstimable(PARAM_LINF, &dLinf);
  registerEstimable(PARAM_LMIN, &dLmin);
  registerEstimable(PARAM_B, &dB);
  registerEstimable(PARAM_CV, &dCV);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_LINF);
  pParameterList->registerAllowed(PARAM_LMIN);
  pParameterList->registerAllowed(PARAM_K);
  pParameterList->registerAllowed(PARAM_B);
  pParameterList->registerAllowed(PARAM_CV);
  pParameterList->registerAllowed(PARAM_DISTRIBUTION);
  pParameterList->registerAllowed(PARAM_BY_LENGTH);
  pParameterList->registerAllowed(PARAM_SIZE_WEIGHT);
}

//**********************************************************************
// voidCVonBertalanffyKAtAgeAgeSize::validate()
// Validate the age-size relationship
//**********************************************************************
void CVonBertalanffyKAtAgeAgeSize::validate() {
  try {
    CBaseBuild::validate();

    // Get our variables
    dLinf         = pParameterList->getDouble(PARAM_LINF);
    dLmin         = pParameterList->getDouble(PARAM_LMIN);
    dB            = pParameterList->getDouble(PARAM_B, true, 0);
    dCV           = pParameterList->getDouble(PARAM_CV, true, 0);
    sDistribution = pParameterList->getString(PARAM_DISTRIBUTION, true, PARAM_NORMAL);
    bByLength     = pParameterList->getBool(PARAM_BY_LENGTH, true, 1);

    iNAges = pWorld->getAgeSpread();

    pParameterList->fillVector(vKs, PARAM_K);
    // Register the Ks as estimable
    for (int i = 0; i < (int)vKs.size(); ++i) registerEstimable(PARAM_K, i, &vKs[i]);

    // Validate parent
    CAgeSize::validate();

    // Local validation
    if (dLinf <= 0)
      CError::errorLessThanEqualTo(PARAM_LINF, PARAM_ZERO);
    if (dCV < 0)
      CError::errorLessThan(PARAM_CV, PARAM_ZERO);
    if (dB < 0)
      CError::errorLessThanEqualTo(PARAM_B, PARAM_ZERO);
    if ((int)vKs.size() < iNAges)
      CError::errorListNotSize(PARAM_K, iNAges);
    if ((sDistribution != PARAM_NORMAL) && (sDistribution != PARAM_LOGNORMAL))
      CError::errorUnknown(PARAM_DISTRIBUTION, sDistribution);
  } catch (string& Ex) {
    Ex = "CVonBertalanffyKAtAgeAgeSize.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// voidCVonBertalanffyKAtAgeAgeSize::build()
// Validate the age-size relationship
//**********************************************************************
void CVonBertalanffyKAtAgeAgeSize::build() {
  CAgeSize::build();

  pInitializationPhaseManager = CInitializationPhaseManager::Instance();

  sSizeWeight                            = pParameterList->getString(PARAM_SIZE_WEIGHT);
  CSizeWeightManager* pSizeWeightManager = CSizeWeightManager::Instance();
  pSizeWeight                            = pSizeWeightManager->getSizeWeight(sSizeWeight);

  vSize.resize(iNAges);

  for (int i = 0; i < iNAges; ++i) {
    if (i == 0) {
      vSize[i] = dLmin + dB * pWorld->getMinAge();
    } else {
      vSize[i] = dLinf + (vSize[i - 1] - dLinf) * (exp(-vKs[i - 1]));
    }
  }

  // Rebuild
  rebuild();
}

//**********************************************************************
// voidCVonBertalanffyKAtAgeAgeSize::rebuild()
// Validate the age-size relationship
//**********************************************************************
void CVonBertalanffyKAtAgeAgeSize::rebuild() {
  CAgeSize::rebuild();
}

//**********************************************************************
// voidCVonBertalanffyKAtAgeAgeSize::getGrowthProportion()
// Get the growth proportion for this state and time step
//**********************************************************************
double CVonBertalanffyKAtAgeAgeSize::getGrowthProportion() {
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
// double CVonBertalanffyKAtAgeAgeSize::getMeanSize(double &age)
// Apply age-size relationship
//**********************************************************************
double CVonBertalanffyKAtAgeAgeSize::getMeanSize(double& age) {
  double dSize   = vSize[age - pWorld->getMinAge()];
  double dGrowth = getGrowthProportion();

  if (dGrowth > 0 && age < pWorld->getMaxAge())
    dSize += (vSize[age - pWorld->getMinAge() + 1] - dSize) * dGrowth;

  if (dSize < 0)
    return 0.0;

  return dSize;
}

//**********************************************************************
// double CVonBertalanffyKAtAgeAgeSize::getMeanWeight(double &age)
// Apply size-weight relationship
//**********************************************************************
double CVonBertalanffyKAtAgeAgeSize::getMeanWeight(double& age) {
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
// double CVonBertalanffyKAtAgeAgeSize::getMeanWeightFromSize(double &size, double &cv)
// Apply size-weight relationship
//**********************************************************************
double CVonBertalanffyKAtAgeAgeSize::getMeanWeightFromSize(double& size, double& cv) {
  double dWeight;
  dWeight = pSizeWeight->getMeanWeight(size, sDistribution, cv);
  return dWeight;
}

//**********************************************************************
// double CVonBertalanffyKAtAgeAgeSize::getCV(double &age)
// get the cv at age
//**********************************************************************
double CVonBertalanffyKAtAgeAgeSize::getCV(double& age) {
  if (bByLength) {
    return (dCV);
  } else {
    double dSize = this->getMeanSize(age);
    return ((age * dCV) / dSize);
  }
}

//**********************************************************************
// double CVonBertalanffyKAtAgeAgeSize::getCVFromSize(double &size)
// get the cv at size
//**********************************************************************
double CVonBertalanffyKAtAgeAgeSize::getCVFromSize(double& size) {
  if (bByLength) {
    return (dCV);
  } else {
    CError::error("age_size.by_length = false is not supported for cvs at size");
    return (0);
  }
}

//**********************************************************************
// double CVonBertalanffyKAtAgeAgeSize::getSd(double &age)
// get the cv at age
//**********************************************************************
double CVonBertalanffyKAtAgeAgeSize::getSd(double& age) {
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
double CVonBertalanffyKAtAgeAgeSize::getProportionInLengthBin(double& age, double& LowerBin, double& UpperBin) {
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
// CVonBertalanffyKAtAgeAgeSize::~CVonBertalanffyKAtAgeAgeSize()
// Destructor
//**********************************************************************
CVonBertalanffyKAtAgeAgeSize::~CVonBertalanffyKAtAgeAgeSize() {}
