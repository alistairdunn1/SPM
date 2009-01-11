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
#include <vector>
#include <string>
#include <boost/thread/condition.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/xtime.hpp>
#include <boost/thread/barrier.hpp>

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
  static CConfiguration*    Instance();
  static void               Destroy();

  // Functions
  void                       setQuietMode(bool value) { bQuietMode = value; }
  bool                       getQuietMode() { return bQuietMode; }
  void                       setPopulateWithDummyData(bool value) { bPopulateWithDummyData = value; }
  bool                       getPopulateWithDummyData() { return bPopulateWithDummyData; }
  void                       setConfigFile(string value) { sConfigFile = value; }
  string                     getConfigFile() { return sConfigFile; }
  void                       setInputValuesFile(string value) { sInputValuesFile = value; }
  string                     getInputValuesFile() { return sInputValuesFile; }
  void                       setNumberOfYearsToRun(int value) { iNumberOfYearsToRun = value; }
  int                        getNumberOfYearsToRun() { return iNumberOfYearsToRun; }
  void                       setNumberOfYearsToProject(int value) { iNumberOfYearsToProject = value; }
  int                        getNumberOfYearsToProject() { return iNumberOfYearsToProject; }
  void                       setNumberOfTimeSteps(int value) { iNumberOfTimeSteps = value; }
  int                        getNumberOfTimeSteps() { return iNumberOfTimeSteps; }
  void                       setMinAge(int value) { iMinAge = value; }
  int                        getMinAge() { return iMinAge; }
  void                       setMaxAge(int value) { iMaxAge = value; }
  int                        getMaxAge() { return iMaxAge; }
  void                       setUseAgePlus(bool value) { bUseAgePlus = value; }
  bool                       getUseAgePlus() { return bUseAgePlus; }
  void                       setHumanStartYear(int value) { iHumanStartYear = value; }
  int                        getHumanStartYear() { return iHumanStartYear; }
  void                       setNumberOfThreads(int value) { iNumberOfThreads = value; }
  int                        getNumberOfThreads() { return iNumberOfThreads; }
  void                       addCategory(string value);
  int                        getCategoryCount() { return (int)vCategoryList.size(); }
  string                     getCategoryNameForIndex(int Index);
  int                        getCategoryIndexForName(string Name);
  int                        getAgeForColIndex(int ColIndex);
  int                        getColIndexForAge(int Age);
  void                       setUseEstimateValues(bool value) { bUseEstimateValues = value; }
  bool                       getUseEstimateValues() { return bUseEstimateValues; }
  void                       addInitializationPhase(string value);
  int                        getInitilizationPhaseCount() { return vInitializationList.size(); }
  string                     getInitializationPhase(int index);
  void                       setRandomSeed(int value) { iRandomSeed = value; }
  int                        getRandomSeed() { return iRandomSeed; }
  void                       addCommandLineParameter(string value);
  int                        getCommandLineParameterCount() { return (int)vCommandLineParameters.size(); }
  string                     getCommandLineParameter(int index);
  void                       validate();

protected:
  // Functions
	CConfiguration();
	virtual                    ~CConfiguration();

	// Variables
  bool                       bQuietMode;
  bool                       bPopulateWithDummyData;
  string                     sConfigFile;
  string                     sInputValuesFile;
  int                        iNumberOfYearsToRun;
  int                        iNumberOfYearsToProject;
  int                        iNumberOfTimeSteps;
  int                        iMinAge;
  int                        iMaxAge;
  bool                       bUseAgePlus;
  int                        iHumanStartYear;
  int                        iNumberOfThreads;
  vector<string>             vCategoryList;
  bool                       bUseEstimateValues;
  vector<string>             vInitializationList;
  int                        iRandomSeed;
  vector<string>             vCommandLineParameters;

private:
  static CConfiguration*     clInstance;
  boost::mutex               configLock;
};

#endif /*CCONFIGURATION_H_*/
