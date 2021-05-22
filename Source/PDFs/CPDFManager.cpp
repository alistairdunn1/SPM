//============================================================================
// Name        : CPDFManager.cpp
// Author      : A.Dunn
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
//============================================================================

// Local Headers
#include "CPDFManager.h"
#include "CPDF.h"
#include "../Helpers/ForEach.h"
#include "../Helpers/CError.h"

// Singleton Instance
boost::thread_specific_ptr<CPDFManager> CPDFManager::clInstance;

//**********************************************************************
// CPDFManager::CPDFManager()
// Default Constructor
//**********************************************************************
CPDFManager::CPDFManager()
{
}

//**********************************************************************
// CPDFManager* CPDFManager::Instance()
// Instance Method - Singleton
//**********************************************************************
CPDFManager *CPDFManager::Instance()
{
  if (clInstance.get() == 0)
    clInstance.reset(new CPDFManager());
  return clInstance.get();
}

//**********************************************************************
// void CPDFManager::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CPDFManager::Destroy()
{
  if (clInstance.get() != 0)
  {
    clInstance.reset();
  }
}

//**********************************************************************
// void CPDFManager::addPDF(CPDF *Function)
// Add Preference Functions to our list
//**********************************************************************
void CPDFManager::addPDF(CPDF *Function)
{
  vPDFs.push_back(Function);
}

//**********************************************************************
// CPDF* CPDFManager::getPDF(int index)
// Get A PDF by Index
//**********************************************************************
CPDF *CPDFManager::getPDF(int index)
{
  try
  {
    if (index < 0)
      CError::errorLessThan(PARAM_INDEX, PARAM_ZERO);
    if (index >= (int)vPDFs.size())
      CError::errorGreaterThanEqualTo(PARAM_INDEX, PARAM_PDF);

    return vPDFs[index];
  }
  catch (string &Ex)
  {
    Ex = "CPDFManager.getPDF()->" + Ex;
  }

  return 0;
}

//**********************************************************************
// CPDF* CPDFManager::getPDF(string Label)
// get The PDF Pointer For Label
//**********************************************************************
CPDF *CPDFManager::getPDF(string Label)
{
  try
  {
    // Loop Through And Find
    foreach (CPDF *PDF, vPDFs)
    {
      if (PDF->getLabel() == Label)
        return PDF;
    }

    CError::errorUnknown(PARAM_PDF, Label);
  }
  catch (string &Ex)
  {
    Ex = "CPDFManager.getPDF()->" + Ex;
    throw Ex;
  }
  return 0;
}

//**********************************************************************
// void CPDFManager::clone(CPDFManager *Manager)
// Load our Preference Function Manager From Another One. Multi-Threaded Thing
//**********************************************************************
void CPDFManager::clone(CPDFManager *Manager)
{

  foreach (CPDF *pdf, Manager->vPDFs)
  {
    vPDFs.push_back(pdf->clone());
  }
}

//**********************************************************************
// void CPDFManager::validate()
// validate
//**********************************************************************
void CPDFManager::validate()
{
  try
  {
    // Loop through and Validate
    vector<CPDF *>::iterator vPtr = vPDFs.begin();
    while (vPtr != vPDFs.end())
    {
      (*vPtr)->validate();
      vPtr++;
    }

    // Look for Duplicate Labels
    map<string, int> mLabelList;
    vPtr = vPDFs.begin();
    while (vPtr != vPDFs.end())
    {
      // Increase Count for this label
      mLabelList[(*vPtr)->getLabel()] += 1;
      // Check if we have more than 1
      if (mLabelList[(*vPtr)->getLabel()] > 1)
        CError::errorDuplicate(PARAM_PDF, (*vPtr)->getLabel());
      vPtr++;
    }
  }
  catch (string &Ex)
  {
    Ex = "CPDFManager.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPDFManager::build()
// build
//**********************************************************************
void CPDFManager::build()
{
  try
  {
    // Loop through and build
    vector<CPDF *>::iterator vPtr = vPDFs.begin();
    while (vPtr != vPDFs.end())
    {
      (*vPtr)->build();
      vPtr++;
    }
  }
  catch (string &Ex)
  {
    Ex = "CPDFManager.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CPDFManager::~CPDFManager()
// Default De-Constructor
//**********************************************************************
CPDFManager::~CPDFManager()
{
  vector<CPDF *>::iterator vPtr;
  vPtr = vPDFs.begin();
  while (vPtr != vPDFs.end())
  {
    delete (*vPtr);
    vPtr++;
  }
  vPDFs.clear();
}
