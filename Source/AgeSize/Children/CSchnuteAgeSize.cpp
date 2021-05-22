//============================================================================
// Name        : CSchnuteAgeSize.cpp
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CSchnuteAgeSize.h"
#include "../../Helpers/CError.h"
#include "../../SizeWeight/CSizeWeight.h"
#include "../../TimeSteps/CTimeStepManager.h"
#include "../../TimeSteps/CTimeStep.h"
#include "../../InitializationPhases/CInitializationPhase.h"
#include "../../InitializationPhases/CInitializationPhaseManager.h"

//**********************************************************************
// CSchnuteAgeSize::CSchnuteAgeSize()
// Default Constructor
//**********************************************************************
CSchnuteAgeSize::CSchnuteAgeSize()
{

  pTimeStepManager = CTimeStepManager::Instance();

  // regsiter estimables
  registerEstimable(PARAM_Y1, &dY1);
  registerEstimable(PARAM_Y2, &dY2);
  registerEstimable(PARAM_TAU1, &dTau1);
  registerEstimable(PARAM_TAU2, &dTau2);
  registerEstimable(PARAM_A, &dA);
  registerEstimable(PARAM_B, &dB);
  registerEstimable(PARAM_CV, &dCV);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_Y1);
  pParameterList->registerAllowed(PARAM_Y2);
  pParameterList->registerAllowed(PARAM_TAU1);
  pParameterList->registerAllowed(PARAM_TAU2);
  pParameterList->registerAllowed(PARAM_A);
  pParameterList->registerAllowed(PARAM_B);
  pParameterList->registerAllowed(PARAM_CV);
  pParameterList->registerAllowed(PARAM_DISTRIBUTION);
  pParameterList->registerAllowed(PARAM_BY_LENGTH);
  pParameterList->registerAllowed(PARAM_SIZE_WEIGHT);
}

//**********************************************************************
// voidCSchnuteAgeSize::validate()
// Validate the age-size relationship
//**********************************************************************
void CSchnuteAgeSize::validate()
{
  try
  {

    // Get our variables
    dY1 = pParameterList->getDouble(PARAM_Y1);
    dY2 = pParameterList->getDouble(PARAM_Y2);
    dTau1 = pParameterList->getDouble(PARAM_TAU1);
    dTau2 = pParameterList->getDouble(PARAM_TAU2);
    dA = pParameterList->getDouble(PARAM_A);
    dB = pParameterList->getDouble(PARAM_B);
    dCV = pParameterList->getDouble(PARAM_CV, true, 0);
    sDistribution = pParameterList->getString(PARAM_DISTRIBUTION, true, PARAM_NORMAL);
    bByLength = pParameterList->getBool(PARAM_BY_LENGTH, true, 1);

    // Validate parent
    CAgeSize::validate();

    // Local validation
    if (dA <= 0)
      CError::errorLessThanEqualTo(PARAM_A, PARAM_ZERO);
    if (dB < 1)
      CError::errorLessThanEqualTo(PARAM_B, PARAM_ONE);
    if (dCV < 0)
      CError::errorLessThan(PARAM_CV, PARAM_ZERO);

    if ((sDistribution != PARAM_NORMAL) && (sDistribution != PARAM_LOGNORMAL))
      CError::errorUnknown(PARAM_DISTRIBUTION, sDistribution);
  }
  catch (string &Ex)
  {
    Ex = "CSchnuteAgeSize.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// voidCSchnuteAgeSize::build()
// Validate the age-size relationship
//**********************************************************************
void CSchnuteAgeSize::build()
{
  try
  {
    // Base
    CAgeSize::build();

    pInitializationPhaseManager = CInitializationPhaseManager::Instance();

    sSizeWeight = pParameterList->getString(PARAM_SIZE_WEIGHT);
    CSizeWeightManager *pSizeWeightManager = CSizeWeightManager::Instance();
    pSizeWeight = pSizeWeightManager->getSizeWeight(sSizeWeight);

    // Rebuild
    rebuild();
  }
  catch (string &Ex)
  {
    Ex = "CSchnuteAgeSize.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CSchnuteAgeSize::rebuild()
// Validate the age-size relationship
//**********************************************************************
void CSchnuteAgeSize::rebuild()
{
  try
  {
    // Base
    CAgeSize::rebuild();
  }
  catch (string &Ex)
  {
    Ex = "CSchnuteAgeSize.rebuild(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CSchnuteAgeSize::getGrowthProportion()
// Get the growth proportion for this state and time step
//**********************************************************************
double CSchnuteAgeSize::getGrowthProportion()
{

  int iTimeStep;
  double dGrowth;

  if (pRuntimeController->getCurrentState() == STATE_INITIALIZATION)
  {
    pInitializationPhase = pInitializationPhaseManager->getInitializationPhase(pInitializationPhaseManager->getLastExecutedInitializationPhase());
    iTimeStep = pInitializationPhase->getCurrentTimeStep();
    dGrowth = pInitializationPhase->getTimeStep(iTimeStep)->getGrowthProportion();
  }
  else
  {
    iTimeStep = pTimeStepManager->getCurrentTimeStep();
    dGrowth = pTimeStepManager->getTimeStep(iTimeStep)->getGrowthProportion();
  }

  return (dGrowth);
}

//**********************************************************************
// double CSchnuteAgeSize::getMeanSize(double &age)
// Apply age-size relationship
//**********************************************************************
double CSchnuteAgeSize::getMeanSize(double &age)
{

  double dSize = 0;
  double dTemp = 0;
  double dGrowth = getGrowthProportion();

  if (dA != 0)
  {
    dTemp = (1 - exp(-dA * ((age + dGrowth) - dTau1))) / (1 - exp(-dA * (dTau2 - dTau1)));
  }
  else
  {
    dTemp = ((age + dGrowth) - dTau1) / (dTau2 - dTau1);
  }
  if (dB != 0)
  {
    dSize = pow((pow(dY1, dB) + (pow(dY2, dB) - pow(dY1, dB)) * dTemp), 1 / dB);
  }
  else
  {
    dSize = dY1 * exp(log(dY2 / dY1) * dTemp);
  }

  if (dSize < 0)
    return 0;

  return dSize;
}

//**********************************************************************
// double CSchnuteAgeSize::getMeanWeight(double &age)
// Apply size-weight relationship
//**********************************************************************
double CSchnuteAgeSize::getMeanWeight(double &age)
{

  double dWeight = 0;
  double dSize = this->getMeanSize(age);

  if (bByLength)
  {
    dWeight = getMeanWeightFromSize(dSize, dCV);
  }
  else
  {
    double dGrowth = getGrowthProportion();
    double cv = ((age + dGrowth) * dCV) / dSize;
    dWeight = getMeanWeightFromSize(dSize, cv);
  }

  return dWeight;
}

//**********************************************************************
// double CSchnuteAgeSize::getMeanWeightFromSize(double &size)
// Apply size-weight relationship
//**********************************************************************
double CSchnuteAgeSize::getMeanWeightFromSize(double &size, double &cv)
{

  double dWeight = 0;
  dWeight = pSizeWeight->getMeanWeight(size, sDistribution, cv);
  return dWeight;
}

//**********************************************************************
// double CSchnuteAgeSize::getCV(double &age)
// get the cv at age
//**********************************************************************
double CSchnuteAgeSize::getCV(double &age)
{

  if (bByLength)
  {
    return (dCV);
  }
  else
  {
    double dSize = this->getMeanSize(age);
    return ((age * dCV) / dSize);
  }
}

//**********************************************************************
// double CSchnuteAgeSize::getCVFromSize(double &size)
// get the cv at size
//**********************************************************************
double CSchnuteAgeSize::getCVFromSize(double &size)
{

  if (bByLength)
  {
    return (dCV);
  }
  else
  {
    CError::error("age_size.by_length = false is not supported for cvs at size");
    return (0);
  }
}

//**********************************************************************
// double CSchnuteAgeSize::getSd(double &age)
// get the cv at age
//**********************************************************************
double CSchnuteAgeSize::getSd(double &age)
{

  if (bByLength)
  {
    double dSize = this->getMeanSize(age);
    return (dCV * dSize);
  }
  else
  {
    double dGrowth = getGrowthProportion();
    return ((age + dGrowth) * dCV);
  }
}

//**********************************************************************
// double CSchnuteAgeSize::getProportionInLengthBin(double &age, double &LowerBin, double&UpperBin)
// Get the proportion within the length bin
//**********************************************************************
double CSchnuteAgeSize::getProportionInLengthBin(double &age, double &LowerBin, double &UpperBin)
{

  double dSize = this->getMeanSize(age);
  double dResult = 0;

  if (this->getSd(age) <= 0.0)
  {
    if ((LowerBin < dSize) && (dSize <= UpperBin))
      dResult = 1.0;
    else
      dResult = 0.0;
  }
  else
  {
    if (sDistribution == PARAM_NORMAL)
    {
      double dSd = this->getSd(age);
      dResult = CNormalDistribution::getCDF(UpperBin, dSize, dSd) - CNormalDistribution::getCDF(LowerBin, dSize, dSd);
    }
    else if (sDistribution == PARAM_LOGNORMAL)
    {
      double dVar = log(dCV * dCV + 1.0);
      double dMu = log(dSize) - (dVar / 2.0);
      dResult = CLogNormalDistribution::getCDF(UpperBin, dMu, sqrt(dVar)) - CLogNormalDistribution::getCDF(LowerBin, dMu, sqrt(dVar));
    }
    else
    {
      CError::errorTypeNotSupported(PARAM_DISTRIBUTION, sDistribution);
    }
  }
  return (dResult);
}

//**********************************************************************
// CSchnuteAgeSize::~CSchnuteAgeSize()
// Destructor
//**********************************************************************
CSchnuteAgeSize::~CSchnuteAgeSize()
{
}
