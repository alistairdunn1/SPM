//============================================================================
// Name        : CCatchabilityManager.cpp
// Author      : S.Rasmussen
// Date        : 28/04/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CCatchabilityManager.h"
#include "CCatchability.h"
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"

// Singleton Variable
boost::thread_specific_ptr<CCatchabilityManager> CCatchabilityManager::clInstance;

//**********************************************************************
// CCatchabilityManager::CCatchabilityManager()
// Default Constructor
//**********************************************************************
CCatchabilityManager::CCatchabilityManager()
{
}

//**********************************************************************
// CCatchabilityManager* CCatchabilityManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CCatchabilityManager *CCatchabilityManager::Instance()
{
  if (clInstance.get() == 0)
    clInstance.reset(new CCatchabilityManager());
  return clInstance.get();
}

//**********************************************************************
// void CCatchabilityManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CCatchabilityManager::Destroy()
{
  if (clInstance.get() != 0)
  {
    clInstance.reset();
  }
}

//**********************************************************************
// void CCatchabilityManager::addQ(CCatchability *Q)
// Add a Q (I hate this short name) to our List
//**********************************************************************
void CCatchabilityManager::addCatchability(CCatchability *Q)
{
  vCatchabilities.push_back(Q);
}

//**********************************************************************
// CCatchability* CCatchabilityManager::getQ(string label)
// Get a pointer to our Q from the vector
//**********************************************************************
CCatchability *CCatchabilityManager::getCatchability(string label)
{
#ifndef OPTIMIZE
  try
  {
#endif
    // Loop through and find our Q
    foreach (CCatchability *Q, vCatchabilities)
    {
      if (Q->getLabel() == label)
        return Q;
    }

    // Couldn't find it.
    CError::errorUnknown(PARAM_CATCHABILITY, label);

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CCatchabilityManager.getQ()->" + Ex;
    throw Ex;
  }
#endif

  return 0;
}

//**********************************************************************
// void CCatchabilityManager::clone(CCatchabilityManager *Manager)
// Clone the manager with param
//**********************************************************************
void CCatchabilityManager::clone(CCatchabilityManager *Manager)
{
  try
  {
    foreach (CCatchability *Catchability, Manager->vCatchabilities)
    {
      vCatchabilities.push_back(Catchability->clone());
    }
  }
  catch (string &Ex)
  {
    Ex = "CCatchabilityManager.clone()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CCatchabilityManager::validate()
// Validate our catchabilities
//**********************************************************************
void CCatchabilityManager::validate()
{
  try
  {
    foreach (CCatchability *Catchability, vCatchabilities)
    {
      Catchability->validate();
    }

    // Look for Duplicate Labels
    map<string, int> mLabelList;
    foreach (CCatchability *Catchability, vCatchabilities)
    {
      // Increase Count for this label
      mLabelList[Catchability->getLabel()] += 1;

      // Check if we have more than 1
      if (mLabelList[Catchability->getLabel()] > 1)
        CError::errorDuplicate(PARAM_CATCHABILITY, Catchability->getLabel());
    }
  }
  catch (string &Ex)
  {
    Ex = "CCatchabilityManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CCatchabilityManager::~CCatchabilityManager()
// Default De-Constructor
//**********************************************************************
CCatchabilityManager::~CCatchabilityManager()
{
}
