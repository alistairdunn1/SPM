//============================================================================
// Name        : CParameterList.h
// Author      : S.Rasmussen
// Date        : 8/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CPARAMETERLIST_H_
#define CPARAMETERLIST_H_

// Global Headers
#include <map>
#include <string>
#include <vector>

// Using
using std::map;
using std::string;
using std::vector;

//**********************************************************************
//
//
//**********************************************************************
class CParameterList {
public:
  // Functions
  CParameterList();
  virtual ~CParameterList();
  void   copyFrom(CParameterList* parameterList);
  void   addParameter(string name, string value);
  void   setParameter(string name, string value);
  void   registerAllowed(string name);
  void   unregisterAllowed(string name);
  string getString(string name, bool optional = false, string defaultValue = "");
  double getDouble(string name, bool optional = false, double defaultValue = 0.0);
  int    getInt(string name, bool optional = false, int defaultValue = 0);
  bool   getBool(string name, bool optional = false, bool defaultValue = true);
  int    countMatches(string name);
  int    countParameterValues(string name);
  string getMatchFullName(string name, int matchNumber);
  void   fillVector(vector<string>& list, string name, bool optional = false);
  void   fillVector(vector<double>& list, string name, bool optional = false);
  void   fillVector(vector<int>& list, string name, bool optional = false);
  void   fillArray(double* array, int length, string name, int offset = 0);
  void   fillArray(string* array, int length, string name, int offset = 0);
  void   fillDefinedParameterVector(vector<string>& list);
  void   checkInvalidParameters();
  bool   hasParameter(string name);
  void   print();

protected:
  // Variables
  map<string, vector<string>> mParameters;
  vector<string>              vAllowedParameters;
};

#endif /* CPARAMETERLIST_H_ */
