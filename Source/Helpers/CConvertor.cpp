//============================================================================
// Name        : CConvertor.cpp
// Author      : S.Rasmussen
// Date        : 6/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
//============================================================================

// Global Headers
#include <iomanip>
#include <iostream>
#include <sstream>

// Local Headers
#include "CConvertor.h"

// Namespace
using std::cout;
using std::endl;
using std::ostringstream;
using std::stringstream;

//**********************************************************************
// int CConvertor::stringToBool(string value)
// Convert from string to boolean
//**********************************************************************
bool CConvertor::stringToBool(string value) {
  bool   bRet   = false;
  string sValue = value;

  for (unsigned i = 0; i < sValue.length(); ++i) sValue[i] = tolower(sValue[i]);

  if ((sValue == "true") || (sValue == "t"))
    bRet = true;
  else if ((sValue == "false") || (sValue == "f"))
    bRet = false;
  else
    throw string("Unknown boolean (true/false): " + value);

  return bRet;
}

//**********************************************************************
// void CConvertor::stringToVectorByNewline(string value, vector<string> &lines)
// Convert a string to a vector, split by \n
//**********************************************************************
void CConvertor::stringToVectorByNewline(string value, vector<string>& lines) {
  // Variables
  string sLine       = value;
  int    iFirstSpace = -1;

  // Lowercase sline
  //  for (unsigned i = 0; i < sLine.length(); ++i)
  //    sLine[i] = tolower(sLine[i]);

  iFirstSpace = sLine.find_first_of('\n');
  if (iFirstSpace == -1) {
    lines.push_back(sLine);
    return;
  }

  while (iFirstSpace >= 0) {
    // Check Difference Between Our Spaces
    if (iFirstSpace > 0)
      lines.push_back(sLine.substr(0, iFirstSpace));

    sLine       = sLine.erase(0, iFirstSpace + 1);
    iFirstSpace = sLine.find_first_of('\n', 0);
  }
  // If anything is remaining, add it to the list
  if (sLine.length() > 0)
    lines.push_back(sLine);
}

//**********************************************************************
// string CConvertor::stringToLowercase(string value)
// Convert a string to lowercase
//**********************************************************************
string CConvertor::stringToLowercase(string value) {
  for (unsigned i = 0; i < value.length(); ++i) value[i] = tolower(value[i]);

  return value;
}
