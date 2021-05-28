//============================================================================
// Name        : CPDFFactory.h
// Author      : A.Dunn
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
//============================================================================
#ifndef CPDFFACTORY_H_
#define CPDFFACTORY_H_

// Global Includes
#include <string>

// Local headers
#include "../CPDF.h"

// Using
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CPDFFactory {
public:
  // Functions
  static CPDF* buildPDF(string type, bool registerWithManager = true);

private:
  // Functions
  CPDFFactory() {}
  virtual ~CPDFFactory() {}
};

#endif /* CPDFFACTORY_H_ */
