//============================================================================
// Name        : CCategoryTransitionByAgeProcess.cpp
// Author      : A. Dunn
// Date        : 18/04/2014
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
//============================================================================

// Headers
#include <boost/lexical_cast.hpp>

#include "../../Helpers/CComparer.h"
#include "../../Helpers/CConvertor.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/ForEach.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../Penalties/CPenalty.h"
#include "../../Penalties/CPenaltyManager.h"
#include "../../Selectivities/CSelectivity.h"
#include "../../Selectivities/CSelectivityManager.h"
#include "../../TimeSteps/CTimeStepManager.h"
#include "CCategoryTransitionByAgeProcess.h"

//**********************************************************************
// CCategoryTransitionByAgeProcess::CCategoryTransitionByAgeProcess()
// Default Constructor
//**********************************************************************
CCategoryTransitionByAgeProcess::CCategoryTransitionByAgeProcess()
{

  // Variables
  pWorldView = 0;
  iMinAge = -1;
  iMaxAge = -1;
  pTimeStepManager = CTimeStepManager::Instance();
  sType = PARAM_CATEGORY_TRANSITION_BY_AGE;
  bRequiresMerge = false;
  pPenalty = 0;

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_FROM);    //categories
  pParameterList->registerAllowed(PARAM_TO);      //categories
  pParameterList->registerAllowed(PARAM_YEAR);    //year for layer
  pParameterList->registerAllowed(PARAM_LAYER);   //layer
  pParameterList->registerAllowed(PARAM_MIN_AGE); // min age
  pParameterList->registerAllowed(PARAM_MAX_AGE); // max age
  pParameterList->registerAllowed(PARAM_DATA);    // N to move (vector, by age)
  pParameterList->registerAllowed(PARAM_PENALTY);
  pParameterList->registerAllowed(PARAM_U_MAX);
}

//**********************************************************************
// string CCategoryTransitionByAgeProcess::getCategoryTo(int index)
// Get category from vector at index
//**********************************************************************
string CCategoryTransitionByAgeProcess::getCategoryTo(int index)
{
  return vCategoryToList[index];
}

//**********************************************************************
// void CCategoryTransitionByAgeProcess::validate()
// Validate This Object
//**********************************************************************
void CCategoryTransitionByAgeProcess::validate()
{
  try
  {

    // Get our Parameters
    pParameterList->fillVector(vCategoryList, PARAM_FROM);
    pParameterList->fillVector(vCategoryToList, PARAM_TO);
    iYear = pParameterList->getInt(PARAM_YEAR);
    sLayer = pParameterList->getString(PARAM_LAYER);
    iMinAge = pParameterList->getInt(PARAM_MIN_AGE);
    iMaxAge = pParameterList->getInt(PARAM_MAX_AGE);
    sPenalty = pParameterList->getString(PARAM_PENALTY, true, "");
    dUMax = pParameterList->getDouble(PARAM_U_MAX, true, 0.99);

    // Base Validation
    CProcess::validate();

    // Local validation
    if (getCategoryCount() != getCategoryToCount())
      CError::errorListSameSize(PARAM_FROM, PARAM_TO);
    if (dUMax > ONE)
      CError::errorGreaterThan(PARAM_U_MAX, PARAM_ONE);
    if (dUMax <= TRUE_ZERO)
      CError::errorLessThanEqualTo(PARAM_U_MAX, PARAM_ZERO);
    if (iMinAge < pWorld->getMinAge())
      CError::errorLessThan(PARAM_MIN_AGE, PARAM_MIN_AGE);
    if (iMaxAge > pWorld->getMaxAge())
      CError::errorGreaterThan(PARAM_MAX_AGE, PARAM_MAX_AGE);

    // Find out the Spread in Ages
    iAgeSpread = (iMaxAge + 1) - iMinAge;

    // Get our Ns
    vector<string> vNs;
    pParameterList->fillVector(vNs, PARAM_DATA);

    if ((vNs.size() % (iAgeSpread + 1)) != 0)
      CError::errorListNotSize(PARAM_OBS, iAgeSpread);

    for (int i = 0; i < (int)vNs.size(); i += (iAgeSpread + 1))
    {
      for (int j = 0; j < iAgeSpread; ++j)
      {
        try
        {
          mvNMatrix[vNs[i]].push_back(boost::lexical_cast<double>(vNs[i + j + 1]));
        }
        catch (boost::bad_lexical_cast &)
        {
          string Ex = string("Non-numeric value in ") + PARAM_DATA + string(" for ") + PARAM_PROCESS + string(" ") + getLabel();
          throw Ex;
        }
      }
    }

    int iCounter = 0;
    for (int i = 0; i < (int)vNs.size(); i += (iAgeSpread + 1))
    {
      for (int j = 0; j < iAgeSpread; ++j)
      {
        registerEstimable(PARAM_DATA, iCounter, &mvNMatrix[vNs[i]][j]);
        iCounter++;
      }
    }
  }
  catch (string &Ex)
  {
    Ex = "CCategoryTransitionByAgeProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CCategoryTransitionByAgeProcess::build()
// Build our Relationships and Indexes
//**********************************************************************
void CCategoryTransitionByAgeProcess::build()
{
  try
  {
    // Base Build
    CProcess::build();

    // Get our Layer Pointer
    CLayerManager *pLayerManager = CLayerManager::Instance();
    pLayer = pLayerManager->getCategoricalLayer(sLayer);

    // Build our World View
    pWorldView = new CLayerDerivedWorldView(pLayer);
    pWorldView->validate();
    pWorldView->build();

    // Build the category to list
    foreach (string Name, vCategoryToList)
    {
      vCategoryToIndex.push_back(pWorld->getCategoryIndexForName(Name));
    }

    // Build Penalty
    if (sPenalty != "")
      pPenalty = CPenaltyManager::Instance()->getPenalty(sPenalty);
  }
  catch (string &Ex)
  {
    Ex = "CCategoryTransitionByAgeProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CCategoryTransitionByAgeProcess::execute()
// Execute This Process
//**********************************************************************
void CCategoryTransitionByAgeProcess::execute()
{
#ifndef OPTIMIZE
  try
  {
#endif
    // See if we are suppose to be executing first
    double iCurrentYear = pTimeStepManager->getCurrentYear();
    if (iYear != iCurrentYear)
    {
      // Not the correct year. Don't Execute
      return;
    }

    int iSquareAgeOffset = iMinAge - pWorld->getMinAge();

    // Base execute
    CProcess::execute();
    // Execute pWorldView
    pWorldView->execute();

    // Loop Through each area
    map<string, vector<double>>::iterator mvNPtr = mvNMatrix.begin();
    while (mvNPtr != mvNMatrix.end())
    {
      // Get Square for this Area
      CWorldSquare *pLayerDerivedSquare = pWorldView->getSquare((*mvNPtr).first);
      // and its list of WorldSquares
      vector<CWorldSquare *> vWorldSquares = pWorldView->getWorldSquares((*mvNPtr).first);

      // Loop through each age
      for (int j = 0; j < iAgeSpread; ++j)
      {

        // Initialise variables
        double dTotal = 0;

        // Loop Through Categories & Work out total stock
        for (int i = 0; i < (int)vCategoryIndex.size(); ++i)
        {
          dTotal += pLayerDerivedSquare->getValue(vCategoryIndex[i], (iSquareAgeOffset + j));
        }

        // Work out exploitation rate to move
        dExploitation = ((*mvNPtr).second)[j] / CMath::zeroFun(dTotal, ZERO);
        if (dExploitation > dUMax)
        {
          dExploitation = dUMax;
          if (pPenalty != 0)
          { // Throw Penalty
            pPenalty->trigger(sLabel, dN, (dTotal * dUMax));
          }
        }
        else if (dExploitation < 0.0)
        {
          dExploitation = 0.0;
        }

        // Loop through the WorldSquares
        for (int k = 0; k < (int)vWorldSquares.size(); ++k)
        {
          // Get Current Square
          if (!((vWorldSquares[k])->getEnabled()))
            continue;
          for (int i = 0; i < (int)vCategoryIndex.size(); ++i)
          {

            // Get Amount to move
            dCurrent = (vWorldSquares[k])->getValue(vCategoryIndex[i], (iSquareAgeOffset + j)) * dExploitation;

            // If is Zero, Continue
            if (dCurrent <= 0.0)
              continue;

            // Add these to the categories to move to
            (vWorldSquares[k])->addValue(vCategoryToIndex[i], (iSquareAgeOffset + j), dCurrent);
            // Subtract these from the categories to move from
            (vWorldSquares[k])->subValue(vCategoryIndex[i], (iSquareAgeOffset + j), dCurrent);
          }
        }
      }
      mvNPtr++;
    }

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CCategoryTransitionByAgeProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CCategoryTransitionByAgeProcess::~CCategoryTransitionByAgeProcess()
// Default De-Constructor
//**********************************************************************
CCategoryTransitionByAgeProcess::~CCategoryTransitionByAgeProcess()
{
  if (pWorldView != 0)
    delete pWorldView;
}
