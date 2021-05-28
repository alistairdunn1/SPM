//============================================================================
// Name        : CBaseObject.cpp
// Author      : S.Rasmussen
// Date        : 30/04/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Headers
#include "CBaseObject.h"

#include <boost/lexical_cast.hpp>

#include "../Helpers/CComparer.h"
#include "../Helpers/CConvertor.h"
#include "../Helpers/CError.h"

//**********************************************************************
// CBaseObject::CBaseObject()
// Default Constructor
//**********************************************************************
CBaseObject::CBaseObject() {
  // Assign Pointers
  pConfig            = CConfiguration::Instance();
  pRuntimeController = CRuntimeController::Instance();
  pParameterList     = new CParameterList();
}

//**********************************************************************
// void CBaseObject::registerEstimable(string name, double *variable)
// Register a Variable as Estimable.
//**********************************************************************
void CBaseObject::registerEstimable(string name, double* variable) {
  mEstimables[name] = variable;
}

//**********************************************************************
// void CBaseObject::registerEstimable(string name, int index, double *variable)
// Register variable as estimable with an index (used for Vectors)
//**********************************************************************
void CBaseObject::registerEstimable(string name, int index, double* variable) {
  // Note index +1 is to allow user input using natural counting from 1 rather
  // than the C++ standard of counting from 0
  string newName       = name + string("(") + boost::lexical_cast<string>(index + 1) + string(")");
  mEstimables[newName] = variable;
}

//**********************************************************************
// double* CBaseObject::getEstimableVariable(string name)
// Get Our Estimable Variable
//**********************************************************************
double* CBaseObject::getEstimableVariable(string name, string longName) {
  try {
    name = CConvertor::stringToLowercase(name);

    if (mEstimables[name] == 0)
      CError::errorUnknown(PARAM_ESTIMABLE, longName);
  } catch (string& Ex) {
    Ex = "CBaseObject.getEstimableVariable()->" + Ex;
    throw Ex;
  }

  return mEstimables[name];
}

//**********************************************************************
// bool CBaseObject::isEstimableAVector(string name)
// This method will return true if the name we've given is for a vector
//**********************************************************************
bool CBaseObject::isEstimableAVector(string name) {
  /**
   * name will be something like 'r0'. What we need to check for
   * is the presence of an estimation 'r0' or 'r0(1)'. If
   * 'r0' exists, then it's not a vector. If 'r0(1)' exists
   * then it's a vector
   */
  name = name + "(1)";
  if (mEstimables.find(name) != mEstimables.end())
    return true;

  return false;
}

//**********************************************************************
// int CBaseObject::getEstimableVectorSize(string name)
// This method iterates over estimables looking for the highest index
//**********************************************************************
int CBaseObject::getEstimableVectorSize(string name) {
  /**
   * This method is a very crude method. It'll go through all of the
   * registered estimables with 'name' and find the highest registered
   * index.
   */
  int size = 1;

  for (size = 1; size < 9999; ++size) {
    string temp = name + "(" + boost::lexical_cast<string>(size) + ")";

    if (mEstimables.find(temp) == mEstimables.end())
      break;
  }

  return (size - 1);
}

//**********************************************************************
// void CBaseObject::addParameter(string name, string value)
// Add A Parameters
//**********************************************************************
void CBaseObject::addParameter(string name, string value) {
  pParameterList->addParameter(name, value);
}

//**********************************************************************
// CBaseObject::~CBaseObject()
// Default De-Constructor
//**********************************************************************
CBaseObject::~CBaseObject() {
  // Blank Pointers
  pConfig            = 0;
  pRuntimeController = 0;

  delete pParameterList;
  pParameterList = 0;
}
