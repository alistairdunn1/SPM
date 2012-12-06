//============================================================================
// Name        : CConvertor.h
// Author      : S.Rasmussen
// Date        : 6/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CCONVERTOR_H_
#define CCONVERTOR_H_

// Global Headers
#include <string>
#include <vector>

// Using
using std::string;
using std::vector;

//**********************************************************************
//
//
//**********************************************************************
class CConvertor {
public:
  // Functions
  static bool           stringToBool(string value);
  static void           stringToVectorByNewline(string value, vector<string> &lines);
  static string         stringToLowercase(string value);

private:
  // Functions
  CConvertor() { }
  virtual ~CConvertor() { }
};

#endif /* CCONVERTOR_H_ */
