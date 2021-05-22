//============================================================================
// Name        : CObjectFinder.cpp
// Author      : S.Rasmussen
// Date        : 25/06/2012
// Copyright   : Copyright NIWA Science �2012 - www.niwa.co.nz
// Description : Unit tests for CEstimateFactory
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Headers
#include <iostream>
#include <iomanip>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>

#include "CObjectFinder.h"
#include "../AgeSize/CAgeSizeManager.h"
#include "../AgeingError/CAgeingErrorManager.h"
#include "../Catchabilities/CCatchabilityManager.h"
#include "../Helpers/CConvertor.h"
#include "../Helpers/CError.h"
#include "../Layers/CLayerManager.h"
#include "../Observations/CObservationManager.h"
#include "../PDFs/CPDFManager.h"
#include "../PreferenceFunctions/CPreferenceFunctionManager.h"
#include "../Processes/CProcessManager.h"
#include "../Selectivities/CSelectivityManager.h"
#include "../SizeWeight/CSizeWeightManager.h"

/**
 * This method will split the absolute name of a system object into it's associated block and return them
 *
 * @param parameter The name to break
 * @param objectType The type of the object (return variable)
 * @param objectLabel The label of the object (return variable)
 * @param objectParameter the actual parameter in the object we want (return variable)
 * @param objectIndex The index of this object into a vector (return variable, default -1)
 */
void CObjectFinder::splitParameter(const string parameter, string &objectType, string &objectLabel, string &objectParameter, int &objectIndex)
{

  /**
    * This snippet of code will split the parameter from
    * objectType[ObjectName].ObjectParam(Index)
    */
  vector<string> tokenList;

  typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
  boost::char_separator<char> seperator(".[]()");
  tokenizer tokens(parameter, seperator);

  for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter)
    tokenList.push_back(*tok_iter);

  /**
   * Now, we've populated vector<string> called tokenList with
   * all of the split objects. We should expect their to be
   * either 3 or 4 (4 if index is specified)
   */
  if (tokenList.size() != 3 && tokenList.size() != 4)
    THROW_EXCEPTION("Failed to split the parameter properly: " + parameter);

  objectType = CConvertor::stringToLowercase(tokenList[0]);
  objectLabel = tokenList[1];
  objectParameter = CConvertor::stringToLowercase(tokenList[2]);
  objectIndex = tokenList.size() == 4 ? boost::lexical_cast<int>(tokenList[3]) : -1;
}

/**
 * This method will find a specific object in our system.
 */
CBaseObject *CObjectFinder::getObject(string objectAbsoluteName)
{

  string sObjectType = "";
  string sObjectLabel = "";
  string sTemp = "";
  int iTemp = -1;

  CObjectFinder::splitParameter(objectAbsoluteName, sObjectType, sObjectLabel, sTemp, iTemp);

  CBaseObject *target = 0;
  if (sObjectType == PARAM_PROCESS)
  {
    target = (CBaseObject *)CProcessManager::Instance()->getProcess(sObjectLabel);
  }
  else if (sObjectType == PARAM_PREFERENCE_FUNCTION)
  {
    target = (CBaseObject *)CPreferenceFunctionManager::Instance()->getPreferenceFunction(sObjectLabel);
  }
  else if (sObjectType == PARAM_SELECTIVITY)
  {
    target = (CBaseObject *)CSelectivityManager::Instance()->getSelectivity(sObjectLabel);
  }
  else if (sObjectType == PARAM_CATCHABILITY)
  {
    target = (CBaseObject *)CCatchabilityManager::Instance()->getCatchability(sObjectLabel);
  }
  else if (sObjectType == PARAM_LAYER)
  {
    target = (CBaseObject *)CLayerManager::Instance()->getNumericLayer(sObjectLabel);
  }
  else if (sObjectType == PARAM_AGE_SIZE)
  {
    target = (CBaseObject *)CAgeSizeManager::Instance()->getAgeSize(sObjectLabel);
  }
  else if (sObjectType == PARAM_AGEING_ERROR)
  {
    target = (CBaseObject *)CAgeingErrorManager::Instance()->getAgeingError(sObjectLabel);
  }
  else if (sObjectType == PARAM_SIZE_WEIGHT)
  {
    target = (CBaseObject *)CSizeWeightManager::Instance()->getSizeWeight(sObjectLabel);
  }
  else if (sObjectType == PARAM_OBSERVATION)
  {
    target = (CBaseObject *)CObservationManager::Instance()->getObservation(sObjectLabel);
  }
  else if (sObjectType == PARAM_PDF)
  {
    target = (CBaseObject *)CPDFManager::Instance()->getPDF(sObjectLabel);
  }
  else
  {
    THROW_EXCEPTION("Failed to find object for: " + objectAbsoluteName);
  }

  return target;
}

/**
 * Find a specific estimable in the system
 */
double *CObjectFinder::getObjectEstimable(string estimableAbsoluteName)
{

  string sObjectType = "";
  string sObjectLabel = "";
  string sObjectParameter = "";
  int iIndex = -1;

  CObjectFinder::splitParameter(estimableAbsoluteName, sObjectType, sObjectLabel, sObjectParameter, iIndex);

  CBaseObject *target = CObjectFinder::getObject(estimableAbsoluteName);

  if (iIndex != -1)
    sObjectParameter += "(" + boost::lexical_cast<string>(iIndex) + ")";

  return target->getEstimableVariable(sObjectParameter, estimableAbsoluteName);
}
