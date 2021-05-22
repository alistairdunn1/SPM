//============================================================================
// Name        : CEstimate.h
// Author      : S.Rasmussen
// Date        : 27/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// $Date: 2012-06-08 17:29:15 +1200 (Fri, 08 Jun 2012) $
//============================================================================

// Headers
#include <iostream>
#include <iomanip>
#include <boost/lexical_cast.hpp>

#include "CEstimateInfo.h"
#include "CEstimate.h"
#include "Factory/CEstimateFactory.h"
#include "../ObjectFinder/CObjectFinder.h"
#include "../Helpers/CError.h"
#include "../Helpers/CConvertor.h"

// Using
using std::cout;
using std::endl;

//**********************************************************************
// CEstimateInfo::CEstimateInfo()
// Default Constructor
//**********************************************************************
CEstimateInfo::CEstimateInfo()
{

  // Add default parameters to be passed to any CEstimate objects
  // we create from here.

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_LABEL);
  pParameterList->registerAllowed(PARAM_TYPE);
  pParameterList->registerAllowed(PARAM_PARAMETER);
  pParameterList->registerAllowed(PARAM_LOWER_BOUND);
  pParameterList->registerAllowed(PARAM_UPPER_BOUND);
  pParameterList->registerAllowed(PARAM_SAME);
  pParameterList->registerAllowed(PARAM_ESTIMATION_PHASE);
  pParameterList->registerAllowed(PARAM_MCMC_FIXED);
}

//**********************************************************************
// CEstimateInfo::~CEstimateInfo()
// Destructor
//**********************************************************************
CEstimateInfo::~CEstimateInfo()
{
}

//**********************************************************************
// void CEstimateInfo::fillSameVector(vector<string> &sames)
// Fill a Vector with our "Same" parameters
//**********************************************************************
void CEstimateInfo::fillSameVector(vector<string> &sames)
{
  sames.assign(vSameList.begin(), vSameList.end());
}

//**********************************************************************
// void CEstimateInfo::generateEstimates()
// Generate all of our estimates
//**********************************************************************
void CEstimateInfo::generateEstimates()
{
  try
  {
    if (!pParameterList->hasParameter(PARAM_PARAMETER))
    {
      string label = pParameterList->getString(PARAM_LABEL);
      pParameterList->addParameter(PARAM_PARAMETER, label);
    }
    else if (!pParameterList->hasParameter(PARAM_LABEL))
    {
      string param = pParameterList->getString(PARAM_PARAMETER);
      pParameterList->addParameter(PARAM_LABEL, param);
    }

    string parameter = pParameterList->getString(PARAM_PARAMETER);
    string type = pParameterList->getString(PARAM_TYPE);

    /**
     * First thing we want to split our parameter
     */
    CObjectFinder::splitParameter(parameter, sObjectType, sObjectLabel, sObjectParameter, iObjectIndex);

    /**
     * Find the target object with the estimable we're interested in.
     */
    CBaseObject *target = CObjectFinder::getObject(parameter);

    // Do we have to create 1 or n Estimates
    if (iObjectIndex != -1 || !target->isEstimableAVector(sObjectParameter))
    {
      // 1 Estimate
      CEstimate *newEstimate = CEstimateFactory::buildEstimate(type);
      newEstimate->getParameterList()->copyFrom(pParameterList);

      if (iObjectIndex != -1)
        sObjectParameter += "(" + boost::lexical_cast<string>(iObjectIndex) + ")";
      newEstimate->setTarget(target->getEstimableVariable(sObjectParameter, parameter));
    }
    else
    {
      // N Estimates
      int size = target->getEstimableVectorSize(sObjectParameter);

      for (int i = 0; i < size; ++i)
      {
        CEstimate *newEstimate = CEstimateFactory::buildEstimate(type);
        newEstimate->getParameterList()->copyFrom(pParameterList);

        string newShortParameter = sObjectParameter + "(" + boost::lexical_cast<string>(i + 1) + ")";
        string newParameter = parameter + "(" + boost::lexical_cast<string>(i + 1) + ")";

        newEstimate->getParameterList()->setParameter(PARAM_PARAMETER, newParameter);
        newEstimate->setTarget(target->getEstimableVariable(newShortParameter, newParameter));
      }
    }
  }
  catch (const string &ex)
  {
    RETHROW_EXCEPTION(ex);
  }
}
