//============================================================================
// Name        : CError.h
// Author      : S.Rasmussen
// Date        : 6/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
//============================================================================
#ifndef CERROR_H_
#define CERROR_H_

// Global Headers
#include <string>
#include <sstream>
#include <iostream>
#include <exception>

// Using
using std::cout;
using std::endl;
using std::exception;
using std::ostringstream;
using std::string;
using std::stringstream;

// Macro
#define THROW_EXCEPTION(X)                   \
  {                                          \
    ostringstream o;                         \
    o << __FILE__ << ":" << __LINE__ << endl \
      << "## " << X << endl;                 \
    throw string(o.str());                   \
  }
#define RETHROW_EXCEPTION(X)                 \
  {                                          \
    ostringstream o;                         \
    o << __FILE__ << ":" << __LINE__ << endl \
      << X;                                  \
    throw string(o.str());                   \
  }
#define RETHROW_LABELLED_EXCEPTION(X)                                                                             \
  {                                                                                                               \
    ostringstream o;                                                                                              \
    o << __FILE__ << ":" << __LINE__ << " (" << pParameterList->getString(PARAM_LABEL, "Unknown") << ") " << endl \
      << X;                                                                                                       \
    throw string(o.str());                                                                                        \
  }

//**********************************************************************
//
//
//**********************************************************************
class CError
{
public:
  // Functions
  static void error(string value);
  static void errorMissing(string value);
  static void errorLessThan(string less, string more);
  static void errorNotLessThan(string less, string more);
  static void errorLessThanEqualTo(string less, string more);
  static void errorGreaterThan(string more, string less);
  static void errorGreaterThanEqualTo(string more, string less);
  static void errorNotEqual(string value1, string value2);
  static void errorEqualTo(string value1, string value2);
  static void errorSupported(string value);
  static void errorTypeNotSupported(string type, string label);
  static void errorUnknown(string type, string label);
  static void errorPairs(string value);
  static void errorNoMatch(string type, string value, string type2);
  static void errorDuplicate(string type, string label);
  static void errorListSameSize(string type, string type2);
  static void errorListNotSize(string type, int size);
  static void errorTooHigh(string type);
  static void errorTooMuch(string type);
  static void errorNotEnough(string type);
  static void errorNotBetween(string middle, string low, string high);
  static void errorElementLessThan(string type, int lessIndex, int moreIndex);
  static void errorSumGreaterThanEqualTo(string val1, string val2, string less);
  static void errorSumGreaterThan(string val1, string val2, string less);
  static void errorInvalidCharacter(string val1, string val2);
  static void errorNotIncreasing(string val1);
  // Functions
  CError() {}
  virtual ~CError() {}
};

#endif /* CERROR_H_ */
