//============================================================================
// Name        : CDerivedQuantityByCellFactory.h
// Author      : S.Rasmussen
// Date        : 23/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
//============================================================================
#ifndef CDERIVEDQUANTITYBYCELLFACTORY_H_
#define CDERIVEDQUANTITYBYCELLFACTORY_H_

// Global Includes
#include <string>

// Local includes
#include "../CDerivedQuantityByCell.h"

// Using
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CDerivedQuantityByCellFactory
{
public:
  static CDerivedQuantityByCell *buildDerivedQuantityByCell(string type, bool registerWithManager = true);

private:
  // Functions
  CDerivedQuantityByCellFactory(){};
  virtual ~CDerivedQuantityByCellFactory(){};
};

#endif /* CDERIVEDQUANTITYBYCELLFACTORY_H_ */
