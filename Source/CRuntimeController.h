//============================================================================
// Name        : CRuntimeController.h
// Author      : S.Rasmussen
// Date        : 29/04/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CRUNTIMECONTROLLER_H_
#define CRUNTIMECONTROLLER_H_

// Global Headers
#include <boost/thread/barrier.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/xtime.hpp>
#include <string>

// Namespaces
using std::string;

// Forward Prototyping our Classes
// Use this instead of #include to prevent
// Cyclic-Dependencies
class CRuntimeThread;

// Enums
typedef enum {
  RUN_MODE_INVALID,
  RUN_MODE_LICENSE,
  RUN_MODE_VERSION,
  RUN_MODE_HELP,
  RUN_MODE_BASIC,
  RUN_MODE_ESTIMATION,
  RUN_MODE_PROFILE,
  RUN_MODE_MONTE_CARLO_MARKOV_CHAIN,
  RUN_MODE_FORWARD_PROJECTION,
  RUN_MODE_SIMULATION
} ERunMode;

typedef enum { STATE_INVALID, STATE_VALIDATION, STATE_CONSTRUCTION, STATE_INITIALIZATION, STATE_MODELLING, STATE_ITERATION_COMPLETE, STATE_FINALIZATION } EState;

//**********************************************************************
//
//
//**********************************************************************
class CRuntimeController {
public:
  static CRuntimeController* Instance();
  static void                Destroy();

  // Functions
  void            parseCommandLine(int argc, const char* argv[]);
  string          getCommandLineOptions() { return sCommandLineOptions; }
  void            setRunMode(ERunMode value) { eRunMode = value; }
  ERunMode        getRunMode() { return eRunMode; }
  bool            getDisableHeader() { return bDisableHeader; }
  EState          getCurrentState();
  CRuntimeThread* getCurrentThread();
  void            loadConfiguration();
  void            run();

protected:
  // Functions
  CRuntimeController();
  virtual ~CRuntimeController();
  void        startEstimation();
  static void initEstimationThread();
  void        startMCMC();
  static void initMCMCThread();

  // Variables
  ERunMode        eRunMode;
  bool            bDisableHeader;
  int             iCurrentEstimateValue;
  CRuntimeThread* pBaseThread;
  string          sCommandLineOptions;

private:
  // Variables
  static CRuntimeController* clInstance;
  boost::mutex               runtimeLock;
  boost::barrier*            runtimeBarrier;
};

#endif /*CRUNTIMECONTROLLER_H_*/
