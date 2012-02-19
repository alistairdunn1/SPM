//============================================================================
// Name        : CConfigurationLoader.cpp
// Author      : S.Rasmussen
// Date        : 6/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global Headers
#include <fstream>
#include <iostream>

// Local Headers
#include "CConfigurationLoader.h"
#include "../CConfiguration.h"
#include "../World/CWorld.h"
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"
#include "../Helpers/CConvertor.h"
#include "../Translations/Translations.h"
#include "../BaseClasses/CBaseObject.h"
#include "../AgeingError/Factory/CAgeingErrorFactory.h"
#include "../SizeWeight/Factory/CSizeWeightFactory.h"
#include "../AgeSize/Factory/CAgeSizeFactory.h"
#include "../Catchabilities/Factory/CCatchabilityFactory.h"
#include "../DerivedQuantities/Factory/CDerivedQuantityFactory.h"
#include "../Estimates/Factory/CEstimateFactory.h"
#include "../InitializationPhases/Factory/CInitializationPhaseFactory.h"
#include "../Layers/Factory/CLayerFactory.h"
#include "../Minimizers/Factory/CMinimizerFactory.h"
#include "../Observations/Factory/CObservationFactory.h"
#include "../Penalties/Factory/CPenaltyFactory.h"
#include "../PreferenceFunctions/Factory/CPreferenceFunctionFactory.h"
#include "../Priors/Factory/CPriorFactory.h"
#include "../Processes/Factory/CProcessFactory.h"
#include "../Profiles/Factory/CProfileFactory.h"
#include "../Selectivities/Factory/CSelectivityFactory.h"
#include "../TimeSteps/Factory/CTimeStepFactory.h"
#include "../Minimizers/CMinimizerManager.h"
#include "../Reports/Factory/CReportFactory.h"
#include "../Estimates/CEstimateManager.h"
#include "../MCMC/CMCMC.h"

// Using
using std::ifstream;
using std::cout;
using std::endl;

//**********************************************************************
// CConfigurationLoader::CConfigurationLoader()
// Default Constructor
//**********************************************************************
CConfigurationLoader::CConfigurationLoader() {
}

//**********************************************************************
// void CConfigurationLoader::loadIntoCache(vector<string> &lines)
// Load a vector into cache, we use this instead of file for Unit tests
//**********************************************************************
void CConfigurationLoader::loadIntoCache(vector<string> &lines) {
  vLines.clear();
  foreach(string Line, lines) {
    vLines.push_back(Line);
  }
}

//**********************************************************************
// void CConfigurationLoader::loadConfigFile(bool skipLoadingFile = false)
// Entry Point to load our configuration file
//**********************************************************************
void CConfigurationLoader::loadConfigFile(bool skipLoadingFile) {
  try {
    // Load file to memory
    CConfiguration *pConfig = CConfiguration::Instance();

    if (!skipLoadingFile) {
      vLines.clear();
      string sFileName = pConfig->getConfigFile();
      loadConfigIntoCache(sFileName);
    }

    // Verify file had contents
    if ((int)vLines.size() == 0)
      throw string("Empty configuration file");

    if (vLines[0].substr(0, 1) != CONFIG_SECTION_SYMBOL)
      throw string("First statement (excluding comments) must be an @command");

    vCurrentSection.push_back(vLines[0]);
    for (int i = 1; i < (int)vLines.size(); ++i) {

      // New Section? Process It
      if (vLines[i].substr(0,1) == CONFIG_SECTION_SYMBOL) {
        processSection();
        vCurrentSection.clear();
      }

      vCurrentSection.push_back(vLines[i]);
    }

    processSection();
  } catch (string &Ex) {
    Ex = "CConfigurationLoad.loadConfigFile()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CConfigurationLoader::processSection()
// Process Our Section
//**********************************************************************
void CConfigurationLoader::processSection() {

  // See what section it is.
  string sSection = vCurrentSection[0].substr(1, vCurrentSection[0].length()-1);

  int iSpaceLocation = sSection.find_first_of(' '); // Check for space
  if (iSpaceLocation > 0)
    sSection = sSection.substr(0, iSpaceLocation);

  // Based on the @section, we want to get a Base Object
  CBaseObject *pBaseObject    = 0;

  string sType = getTypeFromCurrentSection();
  try {
    if (sSection == PARAM_MODEL)
      pBaseObject = CWorld::Instance();
    else if (sSection == PARAM_AGEING_ERROR)
      pBaseObject = CAgeingErrorFactory::buildAgeingError(sType);
    else if (sSection == PARAM_SIZE_WEIGHT)
      pBaseObject = CSizeWeightFactory::buildSizeWeight(sType);
    else if (sSection == PARAM_AGE_SIZE)
      pBaseObject = CAgeSizeFactory::buildAgeSize(sType);
    else if (sSection == PARAM_CATCHABILITY)
      pBaseObject = CCatchabilityFactory::buildCatchability(sType);
    else if (sSection == PARAM_DERIVED_QUANTITY)
      pBaseObject = CDerivedQuantityFactory::buildDerivedQuantity(sType);
    else if (sSection == PARAM_ESTIMATE)
      pBaseObject = CEstimateFactory::buildEstimate(sType);
    else if (sSection == PARAM_INITIALIZATION_PHASE)
      pBaseObject = CInitializationPhaseFactory::buildInitializationPhase(sType);
    else if (sSection == PARAM_LAYER)
      pBaseObject = CLayerFactory::buildLayer(sType);
    else if (sSection == PARAM_MINIMIZER)
      pBaseObject = CMinimizerFactory::buildMinimizer(sType);
    else if (sSection == PARAM_OBSERVATION)
      pBaseObject = CObservationFactory::buildObservation(sType);
    else if (sSection == PARAM_PENALTY)
      pBaseObject = CPenaltyFactory::buildPenalty(sType);
    else if (sSection == PARAM_PREFERENCE_FUNCTION)
      pBaseObject = CPreferenceFunctionFactory::buildPreferenceFunction(sType);
    else if (sSection == PARAM_PRIOR)
      pBaseObject = CPriorFactory::buildPrior(sType);
    else if (sSection == PARAM_PROCESS)
      pBaseObject = CProcessFactory::buildProcess(sType);
    else if (sSection == PARAM_PROFILE)
      pBaseObject = CProfileFactory::buildProfile(sType);
    else if (sSection == PARAM_REPORT)
      pBaseObject = CReportFactory::buildReport(sType);
    else if (sSection == PARAM_SELECTIVITY)
      pBaseObject = CSelectivityFactory::buildSelectivity(sType);
    else if (sSection == PARAM_TIME_STEP)
      pBaseObject = CTimeStepFactory::buildTimeStep(sType);
    else if (sSection == PARAM_ESTIMATION)
      pBaseObject = CMinimizerManager::Instance();
    else if (sSection == PARAM_MCMC)
      pBaseObject = CMCMC::Instance();
    else
      CError::errorUnknown(PARAM_SECTION, sSection);

  } catch (string &Ex) {
    Ex += string(" - ") + sSection;
    throw Ex;
  }

  assignParameters(pBaseObject);
}

//**********************************************************************
// string CConfigurationLoader::getTypeFromCurrentSection()
// Find the type variable in our current section
//**********************************************************************
string CConfigurationLoader::getTypeFromCurrentSection() {

  for (int i = 0; i < (int)vCurrentSection.size(); ++i) {
    int iTypeLocation = vCurrentSection[i].find(PARAM_TYPE);

    if (iTypeLocation == 0) {
      int iSpaceLocation = vCurrentSection[i].find_first_of(' ');
      return vCurrentSection[i].substr(iSpaceLocation+1, vCurrentSection[i].length()-iSpaceLocation);
    }
  }

  return "";
}

//**********************************************************************
// void CConfigurationLoader::assignParameters(CBaseObject *Object)
// Assign our parameters to the object
//**********************************************************************
void CConfigurationLoader::assignParameters(CBaseObject *Object) {
  try {
    // Extra Label
    int iSpaceLocation = vCurrentSection[0].find(" ");
    if (iSpaceLocation > 0) {
      string sLabel = vCurrentSection[0].substr(iSpaceLocation+1, vCurrentSection[0].length()-iSpaceLocation);
      Object->addParameter(PARAM_LABEL, sLabel);
    }

    // Loop through rest of parameters
    for (int i = 1; i < (int)vCurrentSection.size(); ++i) {
      string sCurrentLine = vCurrentSection[i];

      iSpaceLocation = sCurrentLine.find_first_of(' ');

      if (iSpaceLocation == -1) {
        Object->addParameter(sCurrentLine, "");
        continue;
      }

      // Get variable name
      string sName = sCurrentLine.substr(0, iSpaceLocation);

      // Setup variables
      int iNxtSpace = 0;
      iSpaceLocation++;

      do {
        // Extract value, setup for next run
        iNxtSpace = sCurrentLine.find(' ', iSpaceLocation);
        string sValue = sCurrentLine.substr(iSpaceLocation, iNxtSpace-iSpaceLocation);
        iSpaceLocation = iNxtSpace + 1;

        // Add the parameter
        if (sValue != "")
          Object->addParameter(sName, sValue);
      } while (iNxtSpace > 0);
    }
  } catch (string &Ex) {
    Ex = "CConfigurationLoader.assignParameters()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CConfigurationLoader::loadConfigIntoCache()
// Load the configuration file into memory
//**********************************************************************
void CConfigurationLoader::loadConfigIntoCache(string FileName) {
  // TODO: (Scott) Re-Write this function

  try {
    if (FileName == "")
      throw string(ERROR_INVALID_FILE_NAME);

    ifstream fConfig(FileName.c_str());
    if (!fConfig)
     throw string(ERROR_OPEN_FILE + FileName);

    string sLine = "";
    bool   bInMultiLineComment = false;

    while (getline(fConfig, sLine)) {
      if (sLine.length() == 0)
        continue;

      // Var
      int iIndex = -1;

      // In ML Comment?
      if (bInMultiLineComment) {
        // Check For }
        iIndex = (int)sLine.find_first_of(CONFIG_MULTI_COMMENT_END);
        if (iIndex >= 0) {
         bInMultiLineComment = false; // End Comment Run
         sLine = sLine.substr(iIndex+1, sLine.length()-iIndex); // Remove upto }
        } else
          continue; // Get Next Line and ignore this one
      }

      if (sLine.length() == 0)
        continue;

      // Remove Any # Single Line Comments
      iIndex = (int)sLine.find_first_of(CONFIG_SINGLE_COMMENT);
      if (iIndex >= 0)
        sLine = sLine.substr(0, iIndex);

      // Remove Any { } Multiline Comments
      iIndex = (int)sLine.find_first_of(CONFIG_MULTI_COMMENT_START);
      if (iIndex >= 0) {
        bInMultiLineComment = true;
        sLine = sLine.substr(0, iIndex);
      }

      // Replace \t (Tabs) with Spaces
      iIndex = (int)sLine.find_first_of("\t");
      while (iIndex != -1) {
        sLine.replace(iIndex, 1, " ");
        iIndex = (int)sLine.find_first_of("\t");
      }

      // look for @include commands
      iIndex = (int)sLine.find_first_of(" ");
      if ( (iIndex != -1) && (sLine.substr(0, iIndex) == CONFIG_INCLUDE)) { //command is '@include'
        // Find First "
        iIndex = (int)sLine.find_first_of("\"");
        if (iIndex == -1)
          throw string("@include file name should be surrounded by quotes");
        // get line from First " (+1) onwards
        string sIncludeFile = sLine.substr(iIndex+1, sLine.length()-iIndex);

        // Remove last "
        iIndex = (int)sIncludeFile.find_first_of("\"");
        if (iIndex == -1)
          throw string("@include file name is missing a closing quote");
        sIncludeFile = sIncludeFile.substr(0, iIndex);

        // Check if it's absolute or relative
        if ( (sIncludeFile.substr(0, 1) == "/") || (sIncludeFile.substr(1, 1) == ":") )
          loadConfigIntoCache(sIncludeFile); // Absolute
        else {
          int iLastLoc = FileName.find_last_of('/');
          if (iLastLoc == -1)
            iLastLoc = FileName.find_last_of('\\');

          if (iLastLoc == -1) {
            loadConfigIntoCache(sIncludeFile);
          } else {
           string sDirectory = FileName.substr(0, iLastLoc+1);
           loadConfigIntoCache(sDirectory + (sDirectory==""?"":"//") + sIncludeFile); // Relative
          }
        }

        // Blank line so it's not added
        sLine = "";
      }

      // // Lowercase line
      for (unsigned i = 0; i < sLine.length(); ++i)
        sLine[i] = tolower(sLine[i]);
      // Remove trailing spaces caused by Comments
      int iLastNotSpace = sLine.find_last_not_of(" ");
      sLine = sLine.substr(0, (iLastNotSpace+1));

      if (sLine.length() > 0)
        vLines.push_back(sLine);
    }
    fConfig.close();
  } catch (string &Ex) {
    Ex = "CConfigurationLoader.loadConfigIntoCache(" + FileName +")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CConfigurationLoader::loadEstimateValuesFile(bool skipLoadingFile = false)
//
//**********************************************************************
void CConfigurationLoader::loadEstimateValuesFile(bool skipLoadingFile) {
  try {
    CConfiguration *pConfig = CConfiguration::Instance();

    if (!skipLoadingFile) {
      string sFileName = pConfig->getEstimateValuesFile();
      if (sFileName == "")
        return;
      vLines.clear();
      loadConfigIntoCache(sFileName);
    }

    // Verify file had contents
    if ((int)vLines.size() == 0)
      throw string("Empty configuration file");

    // Get the First Line and load Estimate names
    // Then delete from Vector
    string sFirstLine = vLines[0];
    vector<string> vEstimates;
    splitLineIntoVector(sFirstLine, vEstimates);
    vLines.erase(vLines.begin());

    // Loop through remaining lines and set values through estimate manager
    CEstimateManager *pEstimateManager = CEstimateManager::Instance();
    vector<string> vValues;

    foreach(string Line, vLines) {
      splitLineIntoVector(Line, vValues);

      if (vValues.size() != vEstimates.size())
        CError::errorListSameSize(PARAM_VALUE, PARAM_ESTIMATE);

      for(int i = 0; i < (int)vValues.size(); ++i)
        pEstimateManager->addEstimateValue(vEstimates[i], CConvertor::stringToDouble(vValues[i]));
    }

    // Now we've loaded correctly. Flag Configuration
    pConfig->setUseEstimateValues(true);

  } catch (string &Ex) {
    Ex = "CConfigurationLoader.loadEstimateValuesFile()->" + Ex;
    throw Ex;
  }

}

//**********************************************************************
// void CConfigurationLoader::splitLineIntoVector(string line, vector<string> &parameters)
// Split a Line into Vectors
//**********************************************************************
void CConfigurationLoader::splitLineIntoVector(string line, vector<string> &parameters) {
  try {
    // Clear Our Old Parameters
    parameters.clear();

    // Variables
    string  sLine         = line;
    int     iFirstSpace   = -1;

    // // Lowercase sline
    // for (unsigned i = 0; i < sLine.length(); ++i)
    //  sLine[i] = tolower(sLine[i]);

    iFirstSpace = sLine.find_first_of(CONFIG_SEPERATOR_ESTIMATE_VALUES);
    if (iFirstSpace == -1) {
      parameters.push_back( sLine );
      return;
    }

    while (iFirstSpace >= 0) {
      // Check Difference Between Our Spaces
      if (iFirstSpace > 0)
        parameters.push_back( sLine.substr(0, iFirstSpace));

      sLine = sLine.erase(0, iFirstSpace+1);
      iFirstSpace = sLine.find_first_of(CONFIG_SEPERATOR_ESTIMATE_VALUES, 0);
    }
    // If anything is remaining, add it to the list
    if (sLine.length() > 0)
      parameters.push_back(sLine);

  } catch (string &Ex) {
    Ex = "CConfigurationLoader.splitLineIntoVector()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CConfigurationLoader::~CConfigurationLoader()
// Destructor
//**********************************************************************
CConfigurationLoader::~CConfigurationLoader() {

}
