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
#include <algorithm>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/trim_all.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/lexical_cast.hpp>

// Local Headers
#include "CConfigurationLoader.h"
#include "../AgeSize/Factory/CAgeSizeFactory.h"
#include "../AgeingError/Factory/CAgeingErrorFactory.h"
#include "../BaseClasses/CBaseObject.h"
#include "../CConfiguration.h"
#include "../Catchabilities/Factory/CCatchabilityFactory.h"
#include "../DerivedQuantities/Factory/CDerivedQuantityFactory.h"
#include "../DerivedQuantitiesByCell/Factory/CDerivedQuantityByCellFactory.h"
#include "../Estimates/CEstimateManager.h"
#include "../Estimates/Factory/CEstimateFactory.h"
#include "../Helpers/CConvertor.h"
#include "../Helpers/CError.h"
#include "../Helpers/ForEach.h"
#include "../InitializationPhases/Factory/CInitializationPhaseFactory.h"
#include "../Layers/Factory/CLayerFactory.h"
#include "../MCMC/Factory/CMCMCFactory.h"
#include "../Minimizers/CMinimizerManager.h"
#include "../Minimizers/Factory/CMinimizerFactory.h"
#include "../Observations/Factory/CObservationFactory.h"
#include "../Penalties/Factory/CPenaltyFactory.h"
#include "../PDFs/Factory/CPDFFactory.h"
#include "../PreferenceFunctions/Factory/CPreferenceFunctionFactory.h"
#include "../Processes/Factory/CProcessFactory.h"
#include "../Profiles/Factory/CProfileFactory.h"
#include "../Reports/Factory/CReportFactory.h"
#include "../Selectivities/Factory/CSelectivityFactory.h"
#include "../SizeWeight/Factory/CSizeWeightFactory.h"
#include "../TimeSteps/Factory/CTimeStepFactory.h"
#include "../Translations/Translations.h"
#include "../World/CWorld.h"

// Using
using std::cout;
using std::endl;
using std::ifstream;

//**********************************************************************
// CConfigurationLoader::CConfigurationLoader()
// Default Constructor
//**********************************************************************
CConfigurationLoader::CConfigurationLoader()
{
  bModelHasBeenDefined = false;
  bEstimationHasBeenDefined = false;
  bMCMCHasBeenDefined = false;
}

//**********************************************************************
// void CConfigurationLoader::loadIntoCache(vector<string> &lines)
// Load a vector into cache, we use this instead of file for Unit tests
//**********************************************************************
void CConfigurationLoader::loadIntoCache(vector<string> &lines)
{
  vLines.clear();
  foreach (string Line, lines)
  {
    if (Line != "")
    {
      boost::replace_all(Line, "\t", " ");
      boost::replace_all(Line, "  ", " ");
      boost::trim_all(Line);
      vLines.push_back(Line);
    }
  }
}

//**********************************************************************
// void CConfigurationLoader::loadConfigFile(bool skipLoadingFile = false)
// Entry Point to load our configuration file
//**********************************************************************
void CConfigurationLoader::loadConfigFile(bool skipLoadingFile)
{
  try
  {
    // Load file to memory
    CConfiguration *pConfig = CConfiguration::Instance();

    if (!skipLoadingFile)
    {
      vLines.clear();
      string sFileName = pConfig->getConfigFile();
      loadConfigIntoCache(sFileName);
    }

    // Verify file had contents
    if ((int)vLines.size() == 0)
      throw string("Empty configuration file");

    if (vLines[0].substr(0, 1) != CONFIG_SECTION_SYMBOL)
      throw string("The first statement in the input configuration file (excluding comments) must be an @command");

    vCurrentSection.push_back(vLines[0]);
    for (int i = 1; i < (int)vLines.size(); ++i)
    {

      // New Section? Process It
      if (vLines[i].substr(0, 1) == CONFIG_SECTION_SYMBOL)
      {
        processSection();
        vCurrentSection.clear();
      }

      vCurrentSection.push_back(vLines[i]);
    }

    processSection();
  }
  catch (string &Ex)
  {
    Ex = "CConfigurationLoad.loadConfigFile()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CConfigurationLoader::processSection()
// Process Our Section
//**********************************************************************
void CConfigurationLoader::processSection()
{

  // See what section it is.
  string sSection = vCurrentSection[0].substr(1, vCurrentSection[0].length() - 1);

  int iSpaceLocation = sSection.find_first_of(' '); // Check for space
  if (iSpaceLocation > 0)
    sSection = sSection.substr(0, iSpaceLocation);

  sSection = CConvertor::stringToLowercase(sSection);

  // Based on the @section, we want to get a Base Object
  CBaseObject *pBaseObject = 0;

  string sType = getTypeFromCurrentSection();

  try
  {
    if (sSection == PARAM_MODEL)
    {
      if (bModelHasBeenDefined)
        CError::error("Command can only be declared once in the config file");
      pBaseObject = CWorld::Instance();
      bModelHasBeenDefined = true;
    }
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
    else if (sSection == PARAM_DERIVED_QUANTITY_BY_CELL)
      pBaseObject = CDerivedQuantityByCellFactory::buildDerivedQuantityByCell(sType);
    else if (sSection == PARAM_ESTIMATE)
      pBaseObject = CEstimateFactory::buildEstimateInfo();
    else if (sSection == PARAM_INITIALIZATION_PHASE)
      pBaseObject = CInitializationPhaseFactory::buildInitializationPhase(sType);
    else if (sSection == PARAM_LAYER)
      pBaseObject = CLayerFactory::buildLayer(sType);
    else if (sSection == PARAM_MINIMIZER)
      pBaseObject = CMinimizerFactory::buildMinimizer(sType);
    else if (sSection == PARAM_MCMC)
    {
      if (bMCMCHasBeenDefined)
        CError::error("Command can only be declared once in the config file");
      pBaseObject = CMCMCFactory::buildMCMC(sType);
      bMCMCHasBeenDefined = true;
    }
    else if (sSection == PARAM_OBSERVATION)
      pBaseObject = CObservationFactory::buildObservation(sType);
    else if (sSection == PARAM_PENALTY)
      pBaseObject = CPenaltyFactory::buildPenalty(sType);
    else if (sSection == PARAM_PDF)
      pBaseObject = CPDFFactory::buildPDF(sType);
    else if (sSection == PARAM_PREFERENCE_FUNCTION)
      pBaseObject = CPreferenceFunctionFactory::buildPreferenceFunction(sType);
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
    {
      if (bEstimationHasBeenDefined)
        CError::error("Command can only be declared once in the config file");
      pBaseObject = CMinimizerManager::Instance();
      bEstimationHasBeenDefined = true;
    }
    else
      CError::errorUnknown(PARAM_SECTION, "");
  }
  catch (string &Ex)
  {
    Ex += string(": ") + sSection;
    throw Ex;
  }

  assignParameters(pBaseObject);
}

//**********************************************************************
// string CConfigurationLoader::getTypeFromCurrentSection()
// Find the type variable in our current section
//**********************************************************************
string CConfigurationLoader::getTypeFromCurrentSection()
{

  for (int i = 0; i < (int)vCurrentSection.size(); ++i)
  {
    int iTypeLocation = vCurrentSection[i].find(PARAM_TYPE);

    if (iTypeLocation == 0)
    {
      int iSpaceLocation = vCurrentSection[i].find_first_of(' ');
      string sType = vCurrentSection[i].substr(iSpaceLocation + 1, vCurrentSection[i].length() - iSpaceLocation);
      return CConvertor::stringToLowercase(sType);
    }
  }

  return "";
}

//**********************************************************************
// void CConfigurationLoader::assignParameters(CBaseObject *Object)
// Assign our parameters to the object
//**********************************************************************
void CConfigurationLoader::assignParameters(CBaseObject *Object)
{
  try
  {
    /**
     * If we have a label add it as a parameter
     */
    vector<string> pieces;
    boost::split(pieces, vCurrentSection[0], boost::is_any_of(" "));
    for (unsigned i = 1; i < pieces.size(); ++i)
    {
      Object->addParameter(PARAM_LABEL, pieces[i]);
    }

    // Loop through rest of parameters
    for (int i = 1; i < (int)vCurrentSection.size(); ++i)
    {
      string sCurrentLine = vCurrentSection[i];
      boost::replace_all(sCurrentLine, "\t", " ");
      boost::replace_all(sCurrentLine, "  ", " ");
      boost::trim_all(sCurrentLine);
      boost::split(pieces, sCurrentLine, boost::is_any_of(" "));

      // Get variable name
      string sName = CConvertor::stringToLowercase(pieces[0]);

      for (unsigned j = 1; j < pieces.size(); ++j)
      {
        string sValue = pieces[j];

        // Check if the value is a range (e.g 1999-2010)
        int iRangeSpacerIndex = sValue.find('-');
        if (iRangeSpacerIndex > 0)
        {
          // Make sure it's all numerical
          bool isRange = true;
          for (unsigned i = 0; i < sValue.length(); ++i)
          {
            if (!isdigit(sValue[i]) && sValue[i] != '-')
            {
              isRange = false;
              break;
            }
          }

          if (isRange)
          {
            int firstNumber = 0;
            int secondNumber = 0;
            try
            {
              firstNumber = boost::lexical_cast<int>(sValue.substr(0, iRangeSpacerIndex));
              secondNumber = boost::lexical_cast<int>(sValue.substr(iRangeSpacerIndex + 1, sValue.length()));
            }
            catch (boost::bad_lexical_cast &)
            {
              string Ex = string("Non-integer value in ") + sName;
              throw Ex;
            }

            // Now, add our range
            for (int i = firstNumber; i <= secondNumber; ++i)
              Object->addParameter(sName, boost::lexical_cast<string>(i));

            continue;
          }
        }

        Object->addParameter(sName, sValue);
      }
    }
  }
  catch (string &Ex)
  {
    Ex = "CConfigurationLoader.assignParameters()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CConfigurationLoader::loadConfigIntoCache()
// Load the configuration file into memory
//**********************************************************************
void CConfigurationLoader::loadConfigIntoCache(string FileName)
{
  try
  {
    if (FileName == "")
      throw string(ERROR_INVALID_FILE_NAME);

    ifstream fConfig(FileName.c_str());
    if (!fConfig)
      throw string(ERROR_OPEN_FILE + FileName);

    string sLine = "";
    bool bInMultiLineComment = false;

    while (getline(fConfig, sLine))
    {
      if (sLine.length() == 0)
        continue;

      // Var
      int iIndex = -1;

      // In ML Comment?
      if (bInMultiLineComment)
      {
        // Check For }
        iIndex = (int)sLine.find_first_of(CONFIG_MULTI_COMMENT_END);
        if (iIndex >= 0)
        {
          bInMultiLineComment = false;                               // End Comment Run
          sLine = sLine.substr(iIndex + 1, sLine.length() - iIndex); // Remove upto }
        }
        else
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
      if (iIndex >= 0)
      {
        bInMultiLineComment = true;
        sLine = sLine.substr(0, iIndex);
      }

      // Replace \t (Tabs) with Spaces
      iIndex = (int)sLine.find_first_of("\t");
      while (iIndex != -1)
      {
        sLine.replace(iIndex, 1, " ");
        iIndex = (int)sLine.find_first_of("\t");
      }

      // look for @include commands
      iIndex = (int)sLine.find_first_of(" ");
      if ((iIndex != -1) && (sLine.substr(0, iIndex) == CONFIG_INCLUDE))
      { //command is '@include'
        // Find First "
        iIndex = (int)sLine.find_first_of("\"");
        if (iIndex == -1)
          throw string(string(CONFIG_INCLUDE) + string(" file name should be surrounded by quotes"));
        // get line from First " (+1) onwards
        string sIncludeFile = sLine.substr(iIndex + 1, sLine.length() - iIndex);

        // Remove last "
        iIndex = (int)sIncludeFile.find_first_of("\"");
        if (iIndex == -1)
          throw string(string(CONFIG_INCLUDE) + string(" file name is missing a closing quote"));
        sIncludeFile = sIncludeFile.substr(0, iIndex);

        // Check if it's absolute or relative
        if ((sIncludeFile.substr(0, 1) == "/") || (sIncludeFile.substr(1, 1) == ":"))
          loadConfigIntoCache(sIncludeFile); // Absolute
        else
        {
          int iLastLoc = FileName.find_last_of('/');
          if (iLastLoc == -1)
            iLastLoc = FileName.find_last_of('\\');

          if (iLastLoc == -1)
          {
            loadConfigIntoCache(sIncludeFile);
          }
          else
          {
            string sDirectory = FileName.substr(0, iLastLoc + 1);
            loadConfigIntoCache(sDirectory + (sDirectory == "" ? "" : "//") + sIncludeFile); // Relative
          }
        }

        // Blank line so it's not added
        sLine = "";
      }

      // Remove trailing spaces caused by Comments
      int iLastNotSpace = sLine.find_last_not_of(" ");
      sLine = sLine.substr(0, (iLastNotSpace + 1));

      if (sLine.length() > 0)
        vLines.push_back(sLine);
    }
    fConfig.close();
  }
  catch (string &Ex)
  {
    Ex = "CConfigurationLoader.loadConfigIntoCache(" + FileName + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CConfigurationLoader::loadEstimateValuesFile(bool skipLoadingFile = false)
//
//**********************************************************************
void CConfigurationLoader::loadEstimateValuesFile(bool skipLoadingFile)
{
  try
  {
    CConfiguration *pConfig = CConfiguration::Instance();

    if (!skipLoadingFile)
    {
      string sFileName = pConfig->getEstimateValuesFile();
      if (sFileName == "")
        return;
      vLines.clear();
      loadConfigIntoCache(sFileName);
    }

    // Verify file had contents
    if ((int)vLines.size() == 0)
      throw string("Empty input configuration file");

    // Get the First Line and load Estimate names
    // Then delete from Vector
    string sFirstLine = vLines[0];
    vector<string> vEstimates;
    splitLineIntoVector(sFirstLine, vEstimates);
    vLines.erase(vLines.begin());

    // Loop through remaining lines and set values through estimate manager
    CEstimateManager *pEstimateManager = CEstimateManager::Instance();
    vector<string> vValues;

    foreach (string Line, vLines)
    {
      splitLineIntoVector(Line, vValues);

      if (vValues.size() != vEstimates.size())
        CError::errorListSameSize(PARAM_VALUE, PARAM_ESTIMATE);

      for (int i = 0; i < (int)vValues.size(); ++i)
      {
        try
        {
          pEstimateManager->addEstimateValue(vEstimates[i], boost::lexical_cast<double>(vValues[i]));
        }
        catch (boost::bad_lexical_cast &)
        {
          string Ex = string("Non-numeric value in ") + vValues[i] + " of " + PARAM_ESTIMATE;
          throw Ex;
        }
      }
    }

    // Now we've loaded correctly. Flag Configuration
    pConfig->setUseEstimateValues(true);
    pConfig->setNumberSuppliedEstimateValues(vValues.size());
    pConfig->setWasInputFileSupplied(true);
  }
  catch (string &Ex)
  {
    Ex = "CConfigurationLoader.loadEstimateValuesFile()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CConfigurationLoader::splitLineIntoVector(string line, vector<string> &parameters)
// Split a Line into Vectors
//**********************************************************************
void CConfigurationLoader::splitLineIntoVector(string line, vector<string> &parameters)
{
  try
  {
    // Clear Our Old Parameters
    parameters.clear();

    // Variables
    string sLine = line;
    int iFirstSpace = -1;

    iFirstSpace = sLine.find_first_of(CONFIG_SPACE_SEPARATOR);
    if (iFirstSpace == -1)
    {
      parameters.push_back(sLine);
      return;
    }

    while (iFirstSpace >= 0)
    {
      // Check Difference Between Our Spaces
      if (iFirstSpace > 0)
        parameters.push_back(sLine.substr(0, iFirstSpace));

      sLine = sLine.erase(0, iFirstSpace + 1);
      iFirstSpace = sLine.find_first_of(CONFIG_SPACE_SEPARATOR, 0);
    }
    // If anything is remaining, add it to the list
    if (sLine.length() > 0)
      parameters.push_back(sLine);
  }
  catch (string &Ex)
  {
    Ex = "CConfigurationLoader.splitLineIntoVector()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CConfigurationLoader::~CConfigurationLoader()
// Destructor
//**********************************************************************
CConfigurationLoader::~CConfigurationLoader()
{
}
