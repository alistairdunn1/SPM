// Name        : CRuntimeController.cpp
// Author      : S.Rasmussen
// Date        : 29/04/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global Headers
#include <boost/program_options.hpp>
#include <sstream>
#include <iostream>
#include <time.h>

// Local Headers
#include "CConfiguration.h"
#include "CRuntimeController.h"
#include "ConfigurationLoaders/CConfigurationLoader.h"
#include "Estimates/CEstimateManager.h"
#include "Helpers/CError.h"
#include "MCMC/CMCMC.h"
#include "Minimizers/CMinimizerManager.h"
#include "Profiles/CProfileManager.h"
#include "Reports/Factory/CReportFactory.h"
#include "RuntimeThread/CRuntimeThread.h"
#include "Translations/Translations.h"

// Singleton Variable
CRuntimeController *CRuntimeController::clInstance = 0;

// Typedefs
typedef boost::mutex::scoped_lock lock;

// Namespaces
using namespace boost::program_options;
using std::cout;
using std::endl;
using std::ostringstream;

//**********************************************************************
// CRuntimeController::CRuntimeController()
// Default Constructor
//**********************************************************************
CRuntimeController::CRuntimeController()
{
  // Setup Variables
  bDisableHeader = false;
  eRunMode = RUN_MODE_INVALID;
  iCurrentEstimateValue = 0;
  runtimeBarrier = new boost::barrier(2);
  sCommandLineOptions = "Undefined";
  pBaseThread = 0;
}

//**********************************************************************
// CRuntimeController* CRuntimeController::Instance()
// Instance Method - Singleton
//**********************************************************************
CRuntimeController *CRuntimeController::Instance()
{
  if (clInstance == 0)
    clInstance = new CRuntimeController();

  return clInstance;
}

//**********************************************************************
// void CRuntimeController::Destroy()
// Destroy Method - Singleton
//**********************************************************************
void CRuntimeController::Destroy()
{
  if (clInstance != 0)
  {
    delete clInstance;
    clInstance = 0;
  }
}

//**********************************************************************
// bool CRuntimeController::parseCommandLine(int argc, const char* argv[])
// Parse out command line
//**********************************************************************
void CRuntimeController::parseCommandLine(int argc, const char *argv[])
{

  // Build some hidden options
  options_description oHidden("Hidden");
  oHidden.add_options()("disable_reports,D", "Disable all reports")("disable_header,d", "Disable standard header");

  // Build Options menu
  options_description oDesc("Usage");
  oDesc.add_options()("help,h", "Print help")("license,l", "Display SPM license")("version,v", "Display version information")("config,c", value<string>(), "Input configuration file")("run,r", "Basic model run")("estimate,e", "Point estimation")("profile,p", "Likelihood profiles")("mcmc,m", "MCMC")
      //("forward,f", "Forward projections")
      ("simulate,s", value<int>(), "Simulate observations")("input,i", value<string>(), "Load free parameter values from file")("estimates,o", value<string>(), "Create estimate values report")("threads,t", value<int>(), "Maximum number of threads to use in multi-threaded processes")("quiet,q", "Run in quiet mode")("seed,g", value<int>(), "Random number seed")("suffix,u", "Modify output file names using a unique suffix for each run when using (-r -i)");

  options_description oAllOptions("All");
  oAllOptions.add(oDesc);
  oAllOptions.add(oHidden);

  ostringstream o;
  o << oDesc;
  sCommandLineOptions = o.str();

  // Read our Parameters
  variables_map vmParams;
  try
  {
    store(parse_command_line(argc, argv, oAllOptions), vmParams);
    notify(vmParams);
  }
  catch (std::exception &ex)
  {
    throw string(ex.what());
  }

  // Check for Help Command
  if ((vmParams.count("help")) || (vmParams.size() == 0))
  {
    setRunMode(RUN_MODE_HELP);
    return;
  }

  // Check for Version
  if (vmParams.count("version"))
  {
    setRunMode(RUN_MODE_VERSION);
    return;
  }

  // Check For License
  if (vmParams.count("license"))
  {
    setRunMode(RUN_MODE_LICENSE);
    return;
  }

  // Count how many modes are present.
  int iCount = 0;
  iCount += vmParams.count("run");
  iCount += vmParams.count("estimate");
  iCount += vmParams.count("profile");
  iCount += vmParams.count("mcmc");
  iCount += vmParams.count("forward");
  iCount += vmParams.count("simulate");

  if (iCount == 0)
    throw string("Missing run mode command line option");
  if (iCount > 1)
    throw string("More than one run mode parameter supplied");

  if (vmParams.count("run"))
    setRunMode(RUN_MODE_BASIC);
  else if (vmParams.count("estimate"))
    setRunMode(RUN_MODE_ESTIMATION);
  else if (vmParams.count("profile"))
    setRunMode(RUN_MODE_PROFILE);
  else if (vmParams.count("mcmc"))
    setRunMode(RUN_MODE_MONTE_CARLO_MARKOV_CHAIN);
  else if (vmParams.count("forward"))
    setRunMode(RUN_MODE_FORWARD_PROJECTION);
  else if (vmParams.count("simulate"))
    setRunMode(RUN_MODE_SIMULATION);

  // Variables
  CConfiguration *pConfig = CConfiguration::Instance();

  // Estimates
  if (vmParams.count("input"))
    pConfig->setEstimateValuesFile(vmParams["input"].as<string>());

  // Threads
  if (vmParams.count("threads"))
    pConfig->setNumberOfThreads(vmParams["threads"].as<int>());

  // Quiet
  if (vmParams.count("quiet"))
    pConfig->setQuietMode(true);

  // Random Seed
  if (vmParams.count("seed"))
  {
    pConfig->setRandomSeed(vmParams["seed"].as<int>());
  }
  else
  {
    long iSeed = time(0);
    iSeed = (long)(iSeed - (floor((double)iSeed / 100000) * 100000));
    pConfig->setRandomSeed(iSeed);
  }

  // Configuration File
  if (vmParams.count("config"))
    pConfig->setConfigFile(vmParams["config"].as<string>());

  // Set number of simulation candidates to generate
  if (vmParams.count("simulate"))
    pConfig->setSimulationCandidates(vmParams["simulate"].as<int>());

  if (vmParams.count("estimates"))
  {
    string sReportName = vmParams["estimates"].as<string>();

    CReport *report = CReportFactory::buildReport(PARAM_ESTIMATE_VALUE, true);
    report->addParameter(PARAM_LABEL, string(""));
    report->addParameter(PARAM_TYPE, PARAM_ESTIMATE_VALUE);
    report->addParameter(PARAM_FILE_NAME, sReportName);
  }

  if (vmParams.count("suffix"))
  {
    pConfig->setSuffixFileOutput(true);
  }

  if (vmParams.count("disable_reports"))
  {
    pConfig->setDisableReports(true);
  }

  if (vmParams.count("disable_header"))
  {
    bDisableHeader = true;
  }
}

//**********************************************************************
// EState CRuntimeController::getCurrentState()
// Get the current state from the base thread
//**********************************************************************
EState CRuntimeController::getCurrentState()
{
  return pBaseThread->getCurrentState();
}

//**********************************************************************
// CRuntimeThread* CRuntimeController::getCurrentThread()
// Return the Current Thread
//**********************************************************************
CRuntimeThread *CRuntimeController::getCurrentThread()
{
  return pBaseThread;
}

//**********************************************************************
// void CRuntimeController::loadConfiguration()
// Load our Configurations
//**********************************************************************
void CRuntimeController::loadConfiguration()
{
  try
  {
    // Estimation
    CConfigurationLoader clLoader = CConfigurationLoader();

    clLoader.loadConfigFile();
    clLoader.loadEstimateValuesFile();
  }
  catch (string &Ex)
  {
    Ex = "CRuntimeController.loadConfiguration()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CRuntimeController::run()
// Run our Model. Break up Flow into Correct Functions
//**********************************************************************
void CRuntimeController::run()
{
  try
  {
    CConfiguration *pConfig = CConfiguration::Instance();
    CEstimateManager *pEstimateManager = CEstimateManager::Instance();

    // Create our Base Thread
    pBaseThread = new CRuntimeThread();
    pBaseThread->validate();
    pBaseThread->build();

    // Verify (if an input file was given) that the correct number of values was supplied
    if (pConfig->getWasInputFileSupplied())
    {
      if (pConfig->getNumberSuppliedEstimateValues() != pEstimateManager->getEnabledEstimateCount())
      {
        CError::error("Incorrect number of values in the input file supplied with -i");
      }
    }

    // Set a default number of estimate values we want to run
    // the model for. This defaults to 1, because we always
    // want to run atleast 1 iteration of the model
    int iEstimateValueCount = 1;

    // If we are using pre-loaded estimate values, how many?
    if (pConfig->getUseEstimateValues())
      iEstimateValueCount = pEstimateManager->getEstimateValueCount();

    for (int i = 0; i < iEstimateValueCount; ++i)
    {
      // If we are using loaded estimate values, set them now.
      if (pConfig->getUseEstimateValues())
      {
        pEstimateManager->loadEstimateValues(i);
        pBaseThread->rebuild();
      }

      // Run the model.
      switch (eRunMode)
      {
      case RUN_MODE_BASIC:
        pBaseThread->executeBasicRun();
        break;

      case RUN_MODE_ESTIMATION:
        pBaseThread->executeEstimationRun();
        break;
      case RUN_MODE_PROFILE:
        pBaseThread->executeProfileRun();
        break;
      case RUN_MODE_MONTE_CARLO_MARKOV_CHAIN:
        pBaseThread->executeMCMC();
        break;
      case RUN_MODE_SIMULATION:
        pBaseThread->executeSimulationRun();
        break;
      case RUN_MODE_FORWARD_PROJECTION:
        cout << "Forward projections are not yet implemented" << endl;
        break;
      default:
        CError::errorUnknown(PARAM_RUN_MODE, "");
        break;
      }
    }
  }
  catch (string &Ex)
  {
    Ex = "CRuntimeController.run()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CRuntimeController::~CRuntimeController()
// Default De-Constructor
//**********************************************************************
CRuntimeController::~CRuntimeController()
{
  if (pBaseThread != 0)
    delete pBaseThread;

  CConfiguration::Destroy();
}
