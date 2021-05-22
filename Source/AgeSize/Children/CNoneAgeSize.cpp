//============================================================================
// Name        : CNoneAgeSize.cpp
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CNoneAgeSize.h"
#include "../../Helpers/CError.h"
#include "../../SizeWeight/CSizeWeight.h"

//**********************************************************************
// CNoneAgeSize::CNoneAgeSize()
// Default Constructor
//**********************************************************************
CNoneAgeSize::CNoneAgeSize()
{

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_SIZE_WEIGHT);
}

//**********************************************************************
// void CNoneAgeSize::validate()
// Validate the age-size relationship
//**********************************************************************
void CNoneAgeSize::validate()
{

  try
  {

    // Get our variables
    sSizeWeight = pParameterList->getString(PARAM_SIZE_WEIGHT);
    CSizeWeightManager *pSizeWeightManager = CSizeWeightManager::Instance();
    pSizeWeight = pSizeWeightManager->getSizeWeight(sSizeWeight);

    // Validate parent
    CAgeSize::validate();

    // Local validation
    if (pSizeWeight->getType() != PARAM_NONE)
      CError::errorTypeNotSupported(PARAM_SIZE_WEIGHT, string(PARAM_AGE_SIZE + string(" type=") + PARAM_NONE));
  }
  catch (string &Ex)
  {
    Ex = "CNoneAgeSize.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CNoneAgeSize::build()
// Validate the age-size relationship
//**********************************************************************
void CNoneAgeSize::build()
{
  try
  {

    // Base
    CAgeSize::build();

    sSizeWeight = pParameterList->getString(PARAM_SIZE_WEIGHT);
    CSizeWeightManager *pSizeWeightManager = CSizeWeightManager::Instance();
    pSizeWeight = pSizeWeightManager->getSizeWeight(sSizeWeight);

    // Rebuild
    rebuild();
  }
  catch (string &Ex)
  {
    Ex = "CNoneAgeSize.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CNoneAgeSize::rebuild()
// Validate the age-size relationship
//**********************************************************************
void CNoneAgeSize::rebuild()
{
  try
  {
  }
  catch (string &Ex)
  {
    Ex = "CNoneAgeSize.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// double getProportionInLengthBin(double &age, double &LowerBin, double&UpperBin);
// Get the proportion within the length bin
//**********************************************************************
double CNoneAgeSize::getProportionInLengthBin(double &age, double &LowerBin, double &UpperBin)
{

  if ((LowerBin < 1.0) && (1.0 <= UpperBin))
  {
    return (1.0);
  }
  else
  {
    return (0.0);
  }
}

//**********************************************************************
// CNoneAgeSize::~CNoneAgeSize()
// Destructor
//**********************************************************************
CNoneAgeSize::~CNoneAgeSize()
{
}
