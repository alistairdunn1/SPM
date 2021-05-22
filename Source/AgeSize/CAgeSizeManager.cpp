//============================================================================
// Name        : CAgeSizeManager.cpp
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global headers
#include <iostream>

// Local headers
#include "CAgeSizeManager.h"
#include "CAgeSize.h"
#include "../Helpers/ForEach.h"
#include "../Helpers/CError.h"

// Using
using std::cout;
using std::endl;

// Singleton Variable
boost::thread_specific_ptr<CAgeSizeManager> CAgeSizeManager::clInstance;

//**********************************************************************
// CAgeSizeManager::CAgeSizeManager()
// Default Constructor
//**********************************************************************
CAgeSizeManager::CAgeSizeManager()
{
}

//**********************************************************************
// CAgeSizeManager* CAgeSizeManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CAgeSizeManager *CAgeSizeManager::Instance()
{
  if (clInstance.get() == 0)
    clInstance.reset(new CAgeSizeManager());
  return clInstance.get();
}

//**********************************************************************
// void CAgeSizeManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CAgeSizeManager::Destroy()
{
  if (clInstance.get() != 0)
  {
    clInstance.reset();
  }
}

//**********************************************************************
// void CAgeSizeManager::clone(CAgeSizeManager *Manager)
// Clone our Ageing Errors
//**********************************************************************
void CAgeSizeManager::clone(CAgeSizeManager *Manager)
{

  foreach (CAgeSize *ageSize, Manager->vAgeSizes)
  {
    vAgeSizes.push_back(ageSize->clone());
  }
}

//**********************************************************************
// void CAgeSizeManager::addAgeSize(CAgeSize *AgeSize)
// Add Ageing Error to the List
//**********************************************************************
void CAgeSizeManager::addAgeSize(CAgeSize *AgeSize)
{
  vAgeSizes.push_back(AgeSize);
}

//**********************************************************************
// CAgeSize* CAgeSizeManager::getAgeSize(string label)
// Get our Ageing Error
//**********************************************************************
CAgeSize *CAgeSizeManager::getAgeSize(string label)
{
  try
  {
    foreach (CAgeSize *AgeSize, vAgeSizes)
    {
      if (AgeSize->getLabel() == label)
        return AgeSize;
    }

    CError::errorUnknown(PARAM_AGE_SIZE, label);
  }
  catch (string &Ex)
  {
    Ex = "CAgeSizeManager.getAgeSize(" + label + ")->" + Ex;
    throw Ex;
  }

  return 0;
}

//**********************************************************************
// void CAgeSizeManager::validate()
// Validate our Ageing Errors
//**********************************************************************
void CAgeSizeManager::validate()
{
  try
  {
    foreach (CAgeSize *AgeSize, vAgeSizes)
    {
      AgeSize->validate();
    }

    // Look for Duplicate Labels
    map<string, int> mLabelList;
    foreach (CAgeSize *AgeSize, vAgeSizes)
    {
      // Increase Count for this label
      mLabelList[AgeSize->getLabel()] += 1;

      // Check if we have more than 1
      if (mLabelList[AgeSize->getLabel()] > 1)
        CError::errorDuplicate(PARAM_AGE_SIZE, AgeSize->getLabel());
    }
  }
  catch (string &Ex)
  {
    Ex = "CAgeSizeManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAgeSizeManager::build()
// Build our AgeSizes
//**********************************************************************
void CAgeSizeManager::build()
{
  try
  {
    foreach (CAgeSize *AgeSize, vAgeSizes)
    {
      AgeSize->build();
    }
  }
  catch (string &Ex)
  {
    Ex = "CAgeSizeManager.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAgeSizeManager::rebuild()
// Rebuild our ageing errors
//**********************************************************************
void CAgeSizeManager::rebuild()
{
  try
  {
    foreach (CAgeSize *AgeSize, vAgeSizes)
    {
      AgeSize->rebuild();
    }
  }
  catch (string &Ex)
  {
    Ex = "CAgeSizeManager.rebuild()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CAgeSizeManager::~CAgeSizeManager()
// Destructor
//**********************************************************************
CAgeSizeManager::~CAgeSizeManager()
{
  foreach (CAgeSize *AgeSize, vAgeSizes)
  {
    delete AgeSize;
  }
}
