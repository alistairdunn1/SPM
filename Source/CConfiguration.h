//============================================================================
// Name        : CConfiguration.h
// Author      : S.Rasmussen
// Date        : 30/04/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CCONFIGURATION_H_
#define CCONFIGURATION_H_

// Global Headers
#include <boost/thread/barrier.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/xtime.hpp>
#include <string>
#include <vector>

// Namespaces
using std::string;
using std::vector;

// TypeDefs
typedef boost::mutex::scoped_lock lock;

//**********************************************************************
//
//
//**********************************************************************
class CConfiguration {
public:
  static CConfiguration* Instance();
  static void            Destroy();

  // Functions
  void   setQuietMode(bool value) { bQuietMode = value; }
  bool   getQuietMode() { return bQuietMode; }
  void   setPopulateWithDummyData(bool value) { bPopulateWithDummyData = value; }
  bool   getPopulateWithDummyData() { return bPopulateWithDummyData; }
  void   setConfigFile(string value) { sConfigFile = value; }
  string getConfigFile() { return sConfigFile; }
  void   setEstimateValuesFile(string value) { sEstimateValuesFile = value; }
  string getEstimateValuesFile() { return sEstimateValuesFile; }
  void   setNumberOfThreads(int value);
  int    getNumberOfThreads() { return iNumberOfThreads; }
  void   setUseEstimateValues(bool value) { bUseEstimateValues = value; }
  bool   getUseEstimateValues() { return bUseEstimateValues; }
  void   setWasInputFileSupplied(bool value) { bWasInputFileSupplied = value; }
  bool   getWasInputFileSupplied() { return bWasInputFileSupplied; }
  void   setNumberSuppliedEstimateValues(int value) { iNumberSuppliedEstimateValues = value; }
  int    getNumberSuppliedEstimateValues() { return iNumberSuppliedEstimateValues; }
  void   setRandomSeed(int value) { iRandomSeed = value; }
  int    getRandomSeed() { return iRandomSeed; }
  void   addCommandLineParameter(string value);
  int    getCommandLineParameterCount() { return (int)vCommandLineParameters.size(); }
  string getCommandLineParameter(int index);
  void   setSimulationCandidates(int value) { iSimulationCandidates = value; }
  int    getSimulationCandidates() { return iSimulationCandidates; }
  void   setSuffixFileOutput(bool value) { bSuffixFileOutput = value; }
  bool   getSuffixFileOutput() { return bSuffixFileOutput; }
  void   setDisableReports(bool value) { bDisableReports = value; }
  bool   getDisableReports() { return bDisableReports; }

protected:
  // Functions
  CConfiguration();
  virtual ~CConfiguration();

  // Variables
  bool           bQuietMode;
  bool           bPopulateWithDummyData;
  string         sConfigFile;
  string         sEstimateValuesFile;
  int            iNumberOfThreads;
  bool           bUseEstimateValues;
  int            iRandomSeed;
  vector<string> vCommandLineParameters;
  int            iSimulationCandidates;
  bool           bSuffixFileOutput;
  bool           bDisableReports;
  int            iNumberSuppliedEstimateValues;
  bool           bWasInputFileSupplied;

private:
  static CConfiguration* clInstance;
  boost::mutex           configLock;
};

#endif /*CCONFIGURATION_H_*/
