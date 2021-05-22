//============================================================================
// Name        : CPreferenceFunctionManager.cpp
// Author      : S.Rasmussen
// Date        : 28/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description : << See CPreferenceFunctionManager.h >>
// $Date: 2009-01-12 11:44:49 +1300 (Mon, 12 Jan 2009) $
//============================================================================

// Local Headers
#include "CPreferenceFunctionManager.h"
#include "CPreferenceFunction.h"
#include "../Helpers/ForEach.h"
#include "../Helpers/CError.h"

// Singleton Instance
boost::thread_specific_ptr<CPreferenceFunctionManager> CPreferenceFunctionManager::clInstance;

//**********************************************************************
// CPreferenceFunctionManager::CPreferenceFunctionManager()
// Default Constructor
//**********************************************************************
CPreferenceFunctionManager::CPreferenceFunctionManager()
{
}

//**********************************************************************
// CPreferenceFunctionManager* CPreferenceFunctionManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CPreferenceFunctionManager *CPreferenceFunctionManager::Instance()
{
  if (clInstance.get() == 0)
    clInstance.reset(new CPreferenceFunctionManager());
  return clInstance.get();
}

//**********************************************************************
// void CPreferenceFunctionManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CPreferenceFunctionManager::Destroy()
{
  if (clInstance.get() != 0)
  {
    clInstance.reset();
  }
}

//**********************************************************************
// void CPreferenceFunctionManager::addPreferenceFunction(CPreferenceFunction *Function)
// Add Preference Functions to our list
//**********************************************************************
void CPreferenceFunctionManager::addPreferenceFunction(CPreferenceFunction *Function)
{
  vPreferenceFunctions.push_back(Function);
}

//**********************************************************************
// CPreferenceFunction* CPreferenceFunctionManager::getPreferenceFunction(int index)
// Get A PreferenceFunction by Index
//**********************************************************************
CPreferenceFunction *CPreferenceFunctionManager::getPreferenceFunction(int index)
{
  try
  {
    if (index < 0)
      CError::errorLessThan(PARAM_INDEX, PARAM_ZERO);
    if (index >= (int)vPreferenceFunctions.size())
      CError::errorGreaterThanEqualTo(PARAM_INDEX, PARAM_PREFERENCE_FUNCTIONS);

    return vPreferenceFunctions[index];
  }
  catch (string &Ex)
  {
    Ex = "CPreferenceFunctionManager.getPreferenceFunction()->" + Ex;
  }

  return 0;
}

//**********************************************************************
// CPreferenceFunction* CPreferenceFunctionManager::getPreferenceFunction(string Label)
// get The PreferenceFunction Pointer For Label
//**********************************************************************
CPreferenceFunction *CPreferenceFunctionManager::getPreferenceFunction(string Label)
{
  try
  {
    // Loop Through And Find
    foreach (CPreferenceFunction *PreferenceFunction, vPreferenceFunctions)
    {
      if (PreferenceFunction->getLabel() == Label)
        return PreferenceFunction;
    }

    CError::errorUnknown(PARAM_PREFERENCE_FUNCTION, Label);
  }
  catch (string &Ex)
  {
    Ex = "CPreferenceFunctionManager.getPreferenceFunction()->" + Ex;
    throw Ex;
  }
  return 0;
}

//**********************************************************************
// void CPreferenceFunctionManager::clone(CPreferenceFunctionManager *Manager)
// Load our Preference Function Manager From Another One. Multi-Threaded Thing
//**********************************************************************
void CPreferenceFunctionManager::clone(CPreferenceFunctionManager *Manager)
{

  foreach (CPreferenceFunction *preferenceFunction, Manager->vPreferenceFunctions)
  {
    vPreferenceFunctions.push_back(preferenceFunction->clone());
  }
}

//**********************************************************************
// void CPreferenceFunctionManager::validate()
// validate
//**********************************************************************
void CPreferenceFunctionManager::validate()
{

  try
  {
    // Loop through and Validate
    vector<CPreferenceFunction *>::iterator vPtr = vPreferenceFunctions.begin();
    while (vPtr != vPreferenceFunctions.end())
    {
      (*vPtr)->validate();
      vPtr++;
    }

    // Look for Duplicate Labels
    map<string, int> mLabelList;
    vPtr = vPreferenceFunctions.begin();
    while (vPtr != vPreferenceFunctions.end())
    {
      // Increase Count for this label
      mLabelList[(*vPtr)->getLabel()] += 1;
      // Check if we have more than 1
      if (mLabelList[(*vPtr)->getLabel()] > 1)
        CError::errorDuplicate(PARAM_PREFERENCE_FUNCTION, (*vPtr)->getLabel());
      vPtr++;
    }
  }
  catch (string &Ex)
  {
    Ex = "CPreferenceFunctionManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPreferenceFunctionManager::build()
// build
//**********************************************************************
void CPreferenceFunctionManager::build()
{
  try
  {
    // Loop through and build
    vector<CPreferenceFunction *>::iterator vPtr = vPreferenceFunctions.begin();
    while (vPtr != vPreferenceFunctions.end())
    {
      (*vPtr)->build();
      vPtr++;
    }
  }
  catch (string &Ex)
  {
    Ex = "CPreferenceFunctionManager.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CPreferenceFunctionManager::~CPreferenceFunctionManager()
// Default De-Constructor
//**********************************************************************
CPreferenceFunctionManager::~CPreferenceFunctionManager()
{
  vector<CPreferenceFunction *>::iterator vPtr;
  vPtr = vPreferenceFunctions.begin();
  while (vPtr != vPreferenceFunctions.end())
  {
    delete (*vPtr);
    vPtr++;
  }
  vPreferenceFunctions.clear();
}
