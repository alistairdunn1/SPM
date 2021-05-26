//============================================================================
// Name        : CConfiguration.cpp
// Author      : S.Rasmussen
// Date        : 30/04/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CConfiguration.h"
#include "Translations/Translations.h"

// Singleton Variable
CConfiguration *CConfiguration::clInstance = 0;

//**********************************************************************
// CConfiguration::CConfiguration()
// Default Constructor
//**********************************************************************
CConfiguration::CConfiguration()
{
  // Variables
  bQuietMode = false;
  bPopulateWithDummyData = false;
  sConfigFile = "config.spm";
  sEstimateValuesFile = "";
  iNumberOfThreads = 0;
  bUseEstimateValues = false;
  iSimulationCandidates = 0;
  bSuffixFileOutput = false;
  bDisableReports = false;
  iRandomSeed = 123;
  iNumberSuppliedEstimateValues = 0;
  bWasInputFileSupplied = false;
}

//**********************************************************************
// CConfiguration* CConfiguration::Instance()
// Instance Method - Singleton
//**********************************************************************
CConfiguration *CConfiguration::Instance()
{
  if (clInstance == 0)
    clInstance = new CConfiguration();

  return clInstance;
}

//**********************************************************************
// void CConfiguration::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CConfiguration::Destroy()
{
  if (clInstance != 0)
  {
    delete clInstance;
    clInstance = 0;
  }
}

//**********************************************************************
//
//
//**********************************************************************
void CConfiguration::addCommandLineParameter(string value)
{
  vCommandLineParameters.push_back(value);
}

//**********************************************************************
//
//
//**********************************************************************
string CConfiguration::getCommandLineParameter(int index)
{
  return vCommandLineParameters[index];
}

//**********************************************************************
//
//
//**********************************************************************
void CConfiguration::setNumberOfThreads(int value)
{
  if (value < 1)
    iNumberOfThreads = 1;
  else
    iNumberOfThreads = value;
}

//**********************************************************************
// CConfiguration::~CConfiguration()
// Default De-Constructor
//**********************************************************************
CConfiguration::~CConfiguration()
{
}
