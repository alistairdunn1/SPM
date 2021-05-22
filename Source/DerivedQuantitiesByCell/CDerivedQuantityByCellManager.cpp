//============================================================================
// Name        : CDerivedQuantityByCellManager.cpp
// Author      : S.Rasmussen
// Date        : 30/03/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
//============================================================================

// Headers
#include <iostream>

#include "CDerivedQuantityByCellManager.h"
#include "CDerivedQuantityByCell.h"
#include "../Helpers/ForEach.h"
#include "../Helpers/CError.h"

// Using
using std::cout;
using std::endl;

// Singleton Variable
boost::thread_specific_ptr<CDerivedQuantityByCellManager> CDerivedQuantityByCellManager::clInstance;

//**********************************************************************
// CDerivedQuantityByCellManager::CDerivedQuantityByCellManager()
// Default Constructor
//**********************************************************************
CDerivedQuantityByCellManager::CDerivedQuantityByCellManager()
{
}

//**********************************************************************
// CDerivedQuantityByCellManager* CDerivedQuantityByCellManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CDerivedQuantityByCellManager *CDerivedQuantityByCellManager::Instance()
{
  if (clInstance.get() == 0)
    clInstance.reset(new CDerivedQuantityByCellManager());
  return clInstance.get();
}

//**********************************************************************
// void CDerivedQuantityByCellManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CDerivedQuantityByCellManager::Destroy()
{
  if (clInstance.get() != 0)
  {
    clInstance.reset();
  }
}

//**********************************************************************
// void CDerivedQuantityByCellManager::addDerivedQuantityByCell(CDerivedQuantityByCell *DerivedQuantityByCell)
// Add Derived Layer to our list
//**********************************************************************
void CDerivedQuantityByCellManager::addDerivedQuantityByCell(CDerivedQuantityByCell *DerivedQuantityByCell)
{
  vDerivedQuantityByCells.push_back(DerivedQuantityByCell);
}

//**********************************************************************
// CDerivedQuantityByCell* CDerivedQuantityByCellManager::getDerivedQuantityByCell(string label)
// Get our Derived Layer
//**********************************************************************
CDerivedQuantityByCell *CDerivedQuantityByCellManager::getDerivedQuantityByCell(string label)
{
  try
  {
    foreach (CDerivedQuantityByCell *DerivedQuantityByCell, vDerivedQuantityByCells)
    {
      if (DerivedQuantityByCell->getLabel() == label)
        return DerivedQuantityByCell;
    }

    CError::errorUnknown(PARAM_DERIVED_QUANTITY_BY_CELL, label);
  }
  catch (string &Ex)
  {
    Ex = "CDerivedQuantityByCellManager.validate()->" + Ex;
    throw Ex;
  }

  return 0;
}

//**********************************************************************
// void CDerivedQuantityByCellManager::validate()
// Validate our Derived Layers
//**********************************************************************
void CDerivedQuantityByCellManager::validate()
{
  try
  {

    foreach (CDerivedQuantityByCell *DerivedQuantityByCell, vDerivedQuantityByCells)
    {
      DerivedQuantityByCell->validate();
    }

    // Look for Duplicate Labels
    map<string, int> mLabelList;
    foreach (CDerivedQuantityByCell *DerivedQuantityByCell, vDerivedQuantityByCells)
    {
      // Increase Count for this label
      mLabelList[DerivedQuantityByCell->getLabel()] += 1;

      // Check if we have more than 1
      if (mLabelList[DerivedQuantityByCell->getLabel()] > 1)
        CError::errorDuplicate(PARAM_DERIVED_QUANTITY_BY_CELL, DerivedQuantityByCell->getLabel());
    }
  }
  catch (string &Ex)
  {
    Ex = "CDerivedQuantityByCellManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CDerivedQuantityByCellManager::build()
// Build our Derived Layers
//**********************************************************************
void CDerivedQuantityByCellManager::build()
{
  try
  {

    foreach (CDerivedQuantityByCell *DerivedQuantityByCell, vDerivedQuantityByCells)
    {
      DerivedQuantityByCell->build();
    }
  }
  catch (string &Ex)
  {
    Ex = "CDerivedQuantityByCellManager.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CDerivedQuantityByCellManager::rebuild()
// ReBuild our Derived Layers
//**********************************************************************
void CDerivedQuantityByCellManager::rebuild()
{
  try
  {

    foreach (CDerivedQuantityByCell *DerivedQuantityByCell, vDerivedQuantityByCells)
    {
      DerivedQuantityByCell->rebuild();
    }
  }
  catch (string &Ex)
  {
    Ex = "CDerivedQuantityByCellManager.rebuild()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CDerivedQuantityByCellManager::calculate()
// Calculate Derived Layers
//**********************************************************************
void CDerivedQuantityByCellManager::calculate()
{
  foreach (CDerivedQuantityByCell *DerivedQuantityByCell, vDerivedQuantityByCells)
  {
    DerivedQuantityByCell->calculate();
  }
}

//**********************************************************************
// void CDerivedQuantityByCellManager::calculate(bool initialisationPhase)
// Calculate Derived Layers
//**********************************************************************
void CDerivedQuantityByCellManager::calculate(int initialisationPhase)
{

  foreach (CDerivedQuantityByCell *DerivedQuantityByCell, vDerivedQuantityByCells)
  {
    DerivedQuantityByCell->calculate(initialisationPhase);
  }
}

//**********************************************************************
// CDerivedQuantityByCellManager::~CDerivedQuantityByCellManager()
// Destructor
//**********************************************************************
CDerivedQuantityByCellManager::~CDerivedQuantityByCellManager()
{
  foreach (CDerivedQuantityByCell *DerivedQuantityByCell, vDerivedQuantityByCells)
  {
    delete DerivedQuantityByCell;
  }
  vDerivedQuantityByCells.clear();
}
