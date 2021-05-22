//============================================================================
// Name        : CProportionalRecruitmentProcess.cpp
// Author      : A.Dunn
// Date        : June 2013
// Copyright   : Copyright NIWA Science �2013 - www.niwa.co.nz
//============================================================================

// Global headers
#include <iostream>
#include <limits>

// Local Headers
#include "../../DerivedQuantities/CDerivedQuantity.h"
#include "../../Helpers/CComparer.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/ForEach.h"
#include "../../InitializationPhases/CInitializationPhaseManager.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../TimeSteps/CTimeStepManager.h"
#include "CProportionalRecruitmentProcess.h"

// Using
using std::cout;
using std::endl;
using std::numeric_limits;

//**********************************************************************
// CProportionalRecruitmentProcess::CProportionalRecruitmentProcess(CProportionalRecruitmentProcess *Process)
// Default Constructor
//**********************************************************************
CProportionalRecruitmentProcess::CProportionalRecruitmentProcess()
{
  // Default Vars

  pInitializationPhaseManager = CInitializationPhaseManager::Instance();

  // Default Vars
  pLayer = 0;
  sType = PARAM_PROPORTIONAL_RECRUITMENT;
  bRequiresMerge = false;

  // Register allowed estimables
  registerEstimable(PARAM_LAMBDA, &dLambda);
  registerEstimable(PARAM_R0, &dR0);

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_LAMBDA);
  pParameterList->registerAllowed(PARAM_CATEGORIES);
  pParameterList->registerAllowed(PARAM_PROPORTIONS);
  pParameterList->registerAllowed(PARAM_SSB);
  pParameterList->registerAllowed(PARAM_R0);
  pParameterList->registerAllowed(PARAM_B0);
  pParameterList->registerAllowed(PARAM_SSB_OFFSET);
  pParameterList->registerAllowed(PARAM_AGE);
  pParameterList->registerAllowed(PARAM_LAYER);
}

//**********************************************************************
// void CProportionalRecruitmentProcess::validate()
// Validate Our Parameters
//**********************************************************************
void CProportionalRecruitmentProcess::validate()
{
  try
  {

    // Populate our Variables
    dLambda = pParameterList->getDouble(PARAM_LAMBDA);
    iAge = pParameterList->getInt(PARAM_AGE, pWorld->getMinAge());
    sLayer = pParameterList->getString(PARAM_LAYER, true, "");
    sSSB = pParameterList->getString(PARAM_SSB);
    dR0 = pParameterList->getDouble(PARAM_R0);
    sB0 = pParameterList->getString(PARAM_B0, true, "");
    iSSBOffset = pParameterList->getInt(PARAM_SSB_OFFSET);
    pParameterList->fillVector(vCategoryList, PARAM_CATEGORIES);
    pParameterList->fillVector(vProportions, PARAM_PROPORTIONS);

    // Base Validation
    CProcess::validate();

    // Local validation
    // iAge must be a valid age
    if (iAge < pWorld->getMinAge())
      CError::errorLessThan(PARAM_AGE, PARAM_MIN_AGE);
    if (iAge > pWorld->getMaxAge())
      CError::errorGreaterThan(PARAM_AGE, PARAM_MAX_AGE);

    // The 2 Vectors must be same size
    if (getCategoryCount() != (int)vProportions.size())
      CError::errorListSameSize(PARAM_CATEGORIES, PARAM_PROPORTIONS);

    // Register our Proportions as Estimable
    for (int i = 0; i < (int)vProportions.size(); ++i)
      registerEstimable(PARAM_PROPORTIONS, i, &vProportions[i]);

    // Loop Through Proportions. Make Sure They Equal 1.0
    double dRunningTotal = 0.0;
    foreach (double Prop, vProportions)
    {
      dRunningTotal += Prop;
    }
    // See If It is close enough to 1.0
    if (!CComparer::isEqual(dRunningTotal, 1.0))
      CError::errorNotEqual(PARAM_PROPORTIONS, PARAM_ONE);

    //Check SSBOffset is a non-negative int
    if (iSSBOffset < 0)
      CError::errorLessThan(PARAM_SSB_OFFSET, PARAM_ZERO);
  }
  catch (string &Ex)
  {
    Ex = "CRecruitmentProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProportionalRecruitmentProcess::build()
// Build Our Relationships and Indexes
//**********************************************************************
void CProportionalRecruitmentProcess::build()
{
  try
  {
    // Base Build
    CProcess::build();

    // Get our Layer
    if (sLayer != "")
      pLayer = CLayerManager::Instance()->getNumericLayer(sLayer);

    // Get our derived quantity (SSB)
    pDerivedQuantity = CDerivedQuantityManager::Instance()->getDerivedQuantity(sSSB);

    // Get B0 phase
    if (sB0 == "")
    {
      iPhaseB0 = pInitializationPhaseManager->getNumberInitializationPhases() - 1;
    }
    else
    {
      iPhaseB0 = pInitializationPhaseManager->getInitializationPhaseOrderIndex(sB0);
    }

    // Populate Our Age Index
    iAgeIndex = pWorld->getColIndexForAge(iAge);

    // Validate our Vectors are all same size
    if (getCategoryCount() != (int)vProportions.size())
      CError::errorListSameSize(PARAM_CATEGORIES, PARAM_PROPORTIONS);

    rebuild();
  }
  catch (string &Ex)
  {
    Ex = "CRecruitmentProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CProportionalRecruitmentProcess::rebuild()
// Build the process
//**********************************************************************
void CProportionalRecruitmentProcess::rebuild()
{
#ifndef OPTIMIZE
  try
  {
#endif

    // Base rebuild
    CProcess::rebuild();

    // reset values
    vSSBValues.resize(0);
    vRecruitmentValues.resize(0);

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CProportionalRecruitmentProcess.rebuild(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// void CProportionalRecruitmentProcess::execute()
// Execute
//**********************************************************************
void CProportionalRecruitmentProcess::execute()
{
#ifndef OPTIMIZE
  try
  {
#endif
    // Base Execute
    CProcess::execute();

    if (pRuntimeController->getCurrentState() == STATE_INITIALIZATION)
    {
      // We are in an initialisation phase
      if (pInitializationPhaseManager->getLastExecutedInitializationPhase() <= iPhaseB0)
      {
        // If in a phase before we have defined B0, then just assume a constant recruitment of dR0
        dAmountPer = dR0;
      }
      else
      {
        // Get our B0 (assumed to be the LAST value in the defined initialisation)
        dB0 = pDerivedQuantity->getInitialisationValue(iPhaseB0, (pDerivedQuantity->getInitialisationValuesSize(iPhaseB0)) - 1);
        dAmountPer = dLambda * pDerivedQuantity->getValue(iSSBOffset);
      }
    }
    else
    {
      // We are not in an initialisation phase
      // Get SSB
      dB0 = pDerivedQuantity->getInitialisationValue(iPhaseB0, (pDerivedQuantity->getInitialisationValuesSize(iPhaseB0)) - 1);
      dAmountPer = dLambda * pDerivedQuantity->getValue(iSSBOffset);
      vRecruitmentValues.push_back(dAmountPer);
      vSSBValues.push_back(pDerivedQuantity->getValue(iSSBOffset));
    }

    //Allocate our recruitment across the cells
    if (pLayer != 0)
    {
      double dTotal = 0.0;

      for (int i = 0; i < iWorldHeight; ++i)
      {
        for (int j = 0; j < iWorldWidth; ++j)
        {
          pBaseSquare = pWorld->getBaseSquare(i, j);
          if (pBaseSquare->getEnabled())
          {
            dTotal += pLayer->getValue(i, j);
          }
        }
      }

      if (CComparer::isPositive(dTotal))
      {
        dAmountPer /= dTotal;
      }
      else
      {
        CError::errorLessThanEqualTo(PARAM_LAYER, PARAM_ZERO);
      }
    }
    else
      dAmountPer /= pWorld->getEnabledSquareCount();

    // Loop Through The World Grid (i,j)
    for (int i = 0; i < iWorldHeight; ++i)
    {
      for (int j = 0; j < iWorldWidth; ++j)
      {
        // Get Current Square, and Difference Equal
        pBaseSquare = pWorld->getBaseSquare(i, j);
        // Check if this square is enabled or not.
        if (!pBaseSquare->getEnabled())
          continue;

        double value = dAmountPer;
        if (pLayer != 0)
          value *= pLayer->getValue(i, j);

        // Loop Through the Categories and Ages we have and Recruit
        for (int k = 0; k < getCategoryCount(); ++k)
          pBaseSquare->addValue(vCategoryIndex[k], iAgeIndex, (value * vProportions[k]));
      }
    }

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CRecruitmentProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CProportionalRecruitmentProcess::~CProportionalRecruitmentProcess()
// Default De-Constructor
//**********************************************************************
CProportionalRecruitmentProcess::~CProportionalRecruitmentProcess()
{
  vProportions.clear();
}
