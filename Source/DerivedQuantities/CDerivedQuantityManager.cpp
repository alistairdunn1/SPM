//============================================================================
// Name        : CDerivedQuantityManager.cpp
// Author      : S.Rasmussen
// Date        : 30/03/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Headers
#include <iostream>

#include "CDerivedQuantityManager.h"
#include "CDerivedQuantity.h"
#include "../Helpers/ForEach.h"
#include "../Helpers/CError.h"

// Using
using std::cout;
using std::endl;

// Singleton Variable
boost::thread_specific_ptr<CDerivedQuantityManager> CDerivedQuantityManager::clInstance;

//**********************************************************************
// CDerivedQuantityManager::CDerivedQuantityManager()
// Default Constructor
//**********************************************************************
CDerivedQuantityManager::CDerivedQuantityManager()
{
}

//**********************************************************************
// CDerivedQuantityManager* CDerivedQuantityManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CDerivedQuantityManager *CDerivedQuantityManager::Instance()
{
  if (clInstance.get() == 0)
    clInstance.reset(new CDerivedQuantityManager());
  return clInstance.get();
}

//**********************************************************************
// void CDerivedQuantityManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CDerivedQuantityManager::Destroy()
{
  if (clInstance.get() != 0)
  {
    clInstance.reset();
  }
}

//**********************************************************************
// void CDerivedQuantityManager::addDerivedQuantity(CDerivedQuantity *DerivedQuantity)
// Add Derived Quantity to our list
//**********************************************************************
void CDerivedQuantityManager::addDerivedQuantity(CDerivedQuantity *DerivedQuantity)
{
  vDerivedQuantities.push_back(DerivedQuantity);
}

//**********************************************************************
// CDerivedQuantity* CDerivedQuantityManager::getDerivedQuantity(string label)
// Get our Derived Quantity
//**********************************************************************
CDerivedQuantity *CDerivedQuantityManager::getDerivedQuantity(string label)
{
  try
  {
    foreach (CDerivedQuantity *DerivedQuantity, vDerivedQuantities)
    {
      if (DerivedQuantity->getLabel() == label)
        return DerivedQuantity;
    }

    CError::errorUnknown(PARAM_DERIVED_QUANTITY, label);
  }
  catch (string &Ex)
  {
    Ex = "CDerivedQuantityManager.validate()->" + Ex;
    throw Ex;
  }

  return 0;
}

//**********************************************************************
// void CDerivedQuantityManager::validate()
// Validate our Derived Quantities
//**********************************************************************
void CDerivedQuantityManager::validate()
{
  try
  {

    foreach (CDerivedQuantity *DerivedQuantity, vDerivedQuantities)
    {
      DerivedQuantity->validate();
    }

    // Look for Duplicate Labels
    map<string, int> mLabelList;
    foreach (CDerivedQuantity *DerivedQuantity, vDerivedQuantities)
    {
      // Increase Count for this label
      mLabelList[DerivedQuantity->getLabel()] += 1;

      // Check if we have more than 1
      if (mLabelList[DerivedQuantity->getLabel()] > 1)
        CError::errorDuplicate(PARAM_DERIVED_QUANTITY, DerivedQuantity->getLabel());
    }
  }
  catch (string &Ex)
  {
    Ex = "CDerivedQuantityManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CDerivedQuantityManager::build()
// Build our Derived Quantities
//**********************************************************************
void CDerivedQuantityManager::build()
{
  try
  {

    foreach (CDerivedQuantity *DerivedQuantity, vDerivedQuantities)
    {
      DerivedQuantity->build();
    }
  }
  catch (string &Ex)
  {
    Ex = "CDerivedQuantityManager.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CDerivedQuantityManager::rebuild()
// ReBuild our Derived Quantities
//**********************************************************************
void CDerivedQuantityManager::rebuild()
{
  try
  {

    foreach (CDerivedQuantity *DerivedQuantity, vDerivedQuantities)
    {
      DerivedQuantity->rebuild();
    }
  }
  catch (string &Ex)
  {
    Ex = "CDerivedQuantityManager.rebuild()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CDerivedQuantityManager::calculate()
// Calculate Derived Quantities
//**********************************************************************
void CDerivedQuantityManager::calculate()
{
  foreach (CDerivedQuantity *DerivedQuantity, vDerivedQuantities)
  {
    DerivedQuantity->calculate();
  }
}

//**********************************************************************
// void CDerivedQuantityManager::calculate(bool initialisationPhase)
// Calculate Derived Quantities
//**********************************************************************
void CDerivedQuantityManager::calculate(int initialisationPhase)
{

  foreach (CDerivedQuantity *DerivedQuantity, vDerivedQuantities)
  {
    DerivedQuantity->calculate(initialisationPhase);
  }
}

//**********************************************************************
// CDerivedQuantityManager::~CDerivedQuantityManager()
// Destructor
//**********************************************************************
CDerivedQuantityManager::~CDerivedQuantityManager()
{
  foreach (CDerivedQuantity *DerivedQuantity, vDerivedQuantities)
  {
    delete DerivedQuantity;
  }
  vDerivedQuantities.clear();
}
