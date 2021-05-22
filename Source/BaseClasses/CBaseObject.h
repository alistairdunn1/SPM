//============================================================================
// Name        : CBaseObject.h
// Author      : S.Rasmussen
// Date        : 30/04/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description : This class is the very BASE of all classes. Every class
//    in the application must inherit from this in some form.
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CBASEOBJECT_H_
#define CBASEOBJECT_H_

// Global Headers
#include <map>
#include <vector>

// Local Headers
#include "ParameterList/CParameterList.h"
#include "../CConfiguration.h"
#include "../CRuntimeController.h"
#include "../Translations/Translations.h"

// Namespaces
using std::map;
using std::vector;

//**********************************************************************
//
//
//**********************************************************************
class CBaseObject
{
public:
  CBaseObject();
  virtual ~CBaseObject();
  double *getEstimableVariable(string name, string longName);
  bool isEstimableAVector(string name);
  int getEstimableVectorSize(string name);
  void addParameter(string name, string value);
  CParameterList *getParameterList() { return pParameterList; }

protected:
  // Functions
  void registerEstimable(string name, double *variable);
  void registerEstimable(string name, int index, double *variable);

  // Variables
  CConfiguration *pConfig;
  CRuntimeController *pRuntimeController;
  CParameterList *pParameterList;
  map<string, double *> mEstimables;
};

#endif /*CBASEOBJECT_H_*/
