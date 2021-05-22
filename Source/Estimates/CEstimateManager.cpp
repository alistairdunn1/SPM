//============================================================================
// Name        : CEstimateManager.cpp
// Author      : S.Rasmussen
// Date        : 25/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description : << See CEstimateManager.h >>
// $Date$
//============================================================================

// Global Header
#include <fstream>
#include <iostream>
#include <boost/lexical_cast.hpp>

// Local Headers
#include "CEstimateManager.h"
#include "CEstimate.h"
#include "CEstimateInfo.h"
#include "../Helpers/CError.h"
#include "../Helpers/CConvertor.h"
#include "../Helpers/ForEach.h"

// Using
using std::cout;
using std::endl;
using std::ifstream;

// Singleton Variable
boost::thread_specific_ptr<CEstimateManager> CEstimateManager::clInstance;

//**********************************************************************
// CEstimateManager::CEstimateManager()
// Default Constructor
//**********************************************************************
CEstimateManager::CEstimateManager()
{
}

//**********************************************************************
// CEstimateManager* CEstimateManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CEstimateManager *CEstimateManager::Instance()
{
  if (clInstance.get() == 0)
    clInstance.reset(new CEstimateManager());
  return clInstance.get();
}

//**********************************************************************
// void CEstimateManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CEstimateManager::Destroy()
{
  if (clInstance.get() != 0)
  {
    clInstance.reset();
  }
}

//**********************************************************************
// void CEstimateManager::addEstimate(CEstimate *Estimate)
// Add Estimate to our List
//**********************************************************************
void CEstimateManager::addEstimateInfo(CEstimateInfo *info)
{
  vEstimateInfoList.push_back(info);
}

//**********************************************************************
// void CEstimateManager::addEstimate(CEstimate *Estimate)
// Add Estimate to our List
//**********************************************************************
void CEstimateManager::addEstimate(CEstimate *Estimate)
{
  vEstimateList.push_back(Estimate);
}

//**********************************************************************
// void CEstimateManager::fillVector(vector<CEstimate*> &list)
// Fill list with our Estimate pointers
//**********************************************************************
void CEstimateManager::fillVector(vector<CEstimate *> &list)
{
  list.clear();

  foreach (CEstimate *Estimate, vEstimateList)
  {
    list.push_back(Estimate);
  }
}

//**********************************************************************
// int CEstimateManager::getEnabledEstimateCount()
// Get the count for enabled Estimates
//**********************************************************************
int CEstimateManager::getEnabledEstimateCount()
{
  try
  {
    // vars
    int iEnabled = 0;
    vector<CEstimate *>::iterator vPtr = vEstimateList.begin();

    // Loop
    while (vPtr != vEstimateList.end())
    {
      if ((*vPtr)->getEnabled())
        iEnabled++;
      vPtr++;
    }

    return iEnabled;
  }
  catch (string &Ex)
  {
    Ex = "CEstimateManager.getEnabledEstimateCount()->" + Ex;
    throw Ex;
  }

  return 0;
}

//**********************************************************************
// CEstimate* CEstimateManager::getEnabledEstimate(int Index)
// Get Estimate
//**********************************************************************
CEstimate *CEstimateManager::getEnabledEstimate(int Index)
{
  try
  {
    if ((Index + 1) > (int)vEstimateList.size())
      CError::errorGreaterThan(PARAM_INDEX, PARAM_ESTIMATES);
    if (Index < 0)
      CError::errorLessThan(PARAM_INDEX, PARAM_ZERO);
    if (Index > getEnabledEstimateCount())
      CError::errorGreaterThan(PARAM_INDEX, PARAM_ENABLED_ESTIMATES);

    int iCurrentIndex = -1;

    // Loop through incrementing our index based on the enabled ones
    for (int i = 0; i < (int)vEstimateList.size(); ++i)
    {
      if (vEstimateList[i]->getEnabled())
        iCurrentIndex++;

      if (iCurrentIndex == Index)
        return vEstimateList[i];
    }

    throw string(ERROR_INVALID_IDX + boost::lexical_cast<string>(Index));
  }
  catch (string &Ex)
  {
    Ex = "CEstimateManager.getEnabledEstimate()->" + Ex;
    throw Ex;
  }

  return 0;
}

//**********************************************************************
// CEstimate* CEstimateManager::getEstimate(int Index)
// Get Estimate Index
//**********************************************************************
CEstimate *CEstimateManager::getEstimate(int Index)
{
  try
  {
    if ((Index + 1) > (int)vEstimateList.size())
      CError::errorGreaterThan(PARAM_INDEX, PARAM_ESTIMATES);
    if (Index < 0)
      CError::errorLessThan(PARAM_INDEX, PARAM_ZERO);
  }
  catch (string &Ex)
  {
    Ex = "CEstimateManager.getEnabledEstimate()->" + Ex;
    throw Ex;
  }

  return vEstimateList[Index];
}

//**********************************************************************
// bool CEstimateManager::hasEstimate(string Parameter)
// Check if estimate exists
//**********************************************************************
bool CEstimateManager::hasEstimate(string Parameter)
{
  // Variables
  vector<CEstimate *>::iterator vPtr = vEstimateList.begin();
  string sParam = Parameter;
  string sParam2 = "";

  // Loop Through
  while (vPtr != vEstimateList.end())
  {
    // Make sure both commands are relative
    sParam2 = (*vPtr)->getParameter();

    // Check For Match (ignore case)
    if (CConvertor::stringToLowercase(sParam) == CConvertor::stringToLowercase(sParam2))
      return true;

    vPtr++;
  }

  return false;
}

//**********************************************************************
// CEstimate* CEstimateManager::getEstimate(string Parameter)
// Get Estimate
//**********************************************************************
CEstimate *CEstimateManager::getEstimate(string Parameter)
{
  try
  {
    // Variables
    vector<CEstimate *>::iterator vPtr = vEstimateList.begin();
    string sParam = Parameter;
    string sParam2 = "";

    // Loop Through
    while (vPtr != vEstimateList.end())
    {
      // Make sure both commands are relative
      sParam2 = (*vPtr)->getParameter();

      // Check For Match (ignore case)
      if (CConvertor::stringToLowercase(sParam) == CConvertor::stringToLowercase(sParam2))
        return (*vPtr);

      vPtr++;
    }

    CError::errorUnknown(PARAM_ESTIMATE, Parameter);
  }
  catch (string &Ex)
  {
    Ex = "CEstimateManager.getEstimate()->" + Ex;
    throw Ex;
  }

  return 0;
}

//**********************************************************************
// void CEstimateManager::addEstimateValue(string estimate, double value)
// Add An Estimate Value to Be Used
//**********************************************************************
void CEstimateManager::addEstimateValue(string estimate, double value)
{
  mvEstimateValues[estimate].push_back(value);
}

//**********************************************************************
// int CEstimateManager::getEstimateValueCount()
// Get The Number of Estimates Loaded
//**********************************************************************
int CEstimateManager::getEstimateValueCount()
{
  try
  {
    if (vEstimateList.size() == 0)
      CError::errorMissing(PARAM_ESTIMATES);
  }
  catch (string &Ex)
  {
    Ex = "CEstimateManager.getEstimateValueCount()->" + Ex;
    throw Ex;
  }

  return vEstimateList[0]->getValueCount();
}

//**********************************************************************
// void CEstimateManager::loadEstimateValues(int index)
// Load The Estimate Values
//**********************************************************************
void CEstimateManager::loadEstimateValues(int index)
{
  try
  {
    foreach (CEstimate *Estimate, vEstimateList)
    {
      Estimate->loadValue(index);
    }
  }
  catch (string &Ex)
  {
    Ex = "CEstimateManager.loadEstimateValues()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CEstimateManager::setCurrentPhase(int phase)
// This method will enable all estimates that have estimate_phase <= phase
//**********************************************************************
void CEstimateManager::setCurrentPhase(int phase)
{
  foreach (CEstimate *estimate, vEstimateList)
  {
    if (estimate->getEstimationPhase() <= phase)
      estimate->setEnabled(true);
    else
      estimate->setEnabled(false);
  }
}

//**********************************************************************
// void CEstimateManager::validate()
// Validate
//**********************************************************************
void CEstimateManager::validate()
{
  try
  {
    /**
     * Remove any existing Estimates
     */
    if (vEstimateInfoList.size() > 0)
    {
      foreach (CEstimate *estimate, vEstimateList)
      {
        delete estimate;
      }

      vEstimateList.clear();
    }

    /**
     * Convert from EstimateInfo objects into Estimate objects
     */
    foreach (CEstimateInfo *info, vEstimateInfoList)
    {
      info->generateEstimates();
    }
    vEstimateInfoList.clear();

    /**
     * Now, start the real validation of the CEstimateObjects
     */
    // Validate Each Estimate
    foreach (CEstimate *Estimate, vEstimateList)
    {
      Estimate->validate();
    }

    // Variables
    map<string, int> mParameters;

    // Check for Duplicate Estimates
    foreach (CEstimate *Estimate, vEstimateList)
    {
      string sParameter = Estimate->getParameter();
      mParameters[sParameter]++;

      if (mParameters[sParameter] > 1)
        CError::errorDuplicate(PARAM_PARAMETER, sParameter);
    }

    // Check For Duplicate Sames Across Estimates
    map<string, int> mSames;
    vector<string> vSames;

    // Get Sames and Check Against Map
    foreach (CEstimate *Estimate, vEstimateList)
    {
      Estimate->fillSameVector(vSames);

      foreach (string Same, vSames)
      {
        mSames[Same]++;
        if (mSames[Same] > 1)
          CError::errorDuplicate(PARAM_SAME, Same);
      }
    }
  }
  catch (string &Ex)
  {
    Ex = "CEstimateManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CEstimateManager::build()
// Build
//**********************************************************************
void CEstimateManager::build()
{
  try
  {
    // Build Estimates
    vector<CEstimate *>::iterator vPtr = vEstimateList.begin();
    while (vPtr != vEstimateList.end())
    {
      (*vPtr)->build();
      vPtr++;
    }

    // Now set the estimate values on Them
    foreach (CEstimate *estimate, vEstimateList)
    {
      string parameter = estimate->getParameter();

      for (unsigned i = 0; i < mvEstimateValues[parameter].size(); ++i)
      {
        estimate->addValue(mvEstimateValues[parameter][i]);
      }
    }
  }
  catch (string &Ex)
  {
    Ex = "CEstimateManager.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CEstimateManager::~CEstimateManager()
// Default De-Constructor
//**********************************************************************
CEstimateManager::~CEstimateManager()
{
  foreach (CEstimate *Estimate, vEstimateList)
  {
    delete Estimate;
  }

  foreach (CEstimateInfo *info, vEstimateInfoList)
  {
    delete info;
  }
}
