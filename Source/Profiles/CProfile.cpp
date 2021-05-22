//============================================================================
// Name        : CProfile.cpp
// Author      : S.Rasmussen
// Date        : 2/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local Headers
#include "CProfile.h"
#include "../World/CWorld.h"
#include "../Estimates/CEstimateManager.h"
#include "../Estimates/CEstimate.h"
#include "../Helpers/CError.h"
#include "../Helpers/CComparer.h"

//**********************************************************************
// CProfile::CProfile()
// Default Constructor
//**********************************************************************
CProfile::CProfile()
{

  // Vars
  iSteps = 0;
  dStepSize = 0.0;
  dLowerBound = 0.0;
  dUpperBound = 0.0;
  dCurrent = 0.0;
  sParameter = "";
  pTarget = 0;

  // Register Params
  pParameterList->registerAllowed(PARAM_LOWER_BOUND);
  pParameterList->registerAllowed(PARAM_UPPER_BOUND);
  pParameterList->registerAllowed(PARAM_STEPS);
  pParameterList->registerAllowed(PARAM_PARAMETER);
}

//**********************************************************************
// bool CProfile::doStep()
// Do A Step
//**********************************************************************
bool CProfile::doStep()
{
  try
  {
    // Increase Current Value
    if (CComparer::isZero(dCurrent) && (!CComparer::isZero(dLowerBound)))
      dCurrent = dLowerBound;
    else
      dCurrent += dStepSize;

    // Check
    if (dCurrent > dUpperBound)
      return false; // Finished

    // Set Value
    pTarget->setValue(dCurrent);
  }
  catch (string &Ex)
  {
    Ex = "CProfile.doStep(" + getParameter() + ")->" + Ex;
    throw Ex;
  }

  return true;
}

//**********************************************************************
// void CProfile::setEnabled(bool value)
// set Enabled
//**********************************************************************
void CProfile::setEnabled(bool value)
{
  try
  {
    // If this is enabled, we want to disable the estimation
    // of our target
    pTarget->setEnabled(!value);
  }
  catch (string &Ex)
  {
    Ex = "CProfile.setEnabled(" + getParameter() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProfile::validate()
// validate
//**********************************************************************
void CProfile::validate()
{
  try
  {
    // Base
    CBaseBuild::validate();

    // Get our Parameters
    dLowerBound = pParameterList->getDouble(PARAM_LOWER_BOUND);
    dUpperBound = pParameterList->getDouble(PARAM_UPPER_BOUND);
    iSteps = pParameterList->getInt(PARAM_STEPS, true, 10);
    sParameter = pParameterList->getString(PARAM_PARAMETER);

    if ((dLowerBound - dUpperBound) > ZERO) // Lower Bound Must be < Upper Bound
      CError::errorGreaterThan(PARAM_UPPER_BOUND, PARAM_LOWER_BOUND);
    if (iSteps <= 1)
      CError::errorLessThanEqualTo(PARAM_STEPS, PARAM_ONE);

    dStepSize = (dUpperBound - dLowerBound) / ((double)(iSteps - 1));
  }
  catch (string &Ex)
  {
    Ex = "CProfile.validate(" + getParameter() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProfile::build()
// Build
//**********************************************************************
void CProfile::build()
{
  try
  {
    // Get our Target
    if (pTarget == 0)
    {
      CEstimateManager *pEstimateManager = CEstimateManager::Instance();
      pTarget = pEstimateManager->getEstimate(sParameter);
    }
  }
  catch (string &Ex)
  {
    Ex = "CProfile.build(" + getParameter() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CProfile::~CProfile()
// Default De-Constructor
//**********************************************************************
CProfile::~CProfile()
{
}
