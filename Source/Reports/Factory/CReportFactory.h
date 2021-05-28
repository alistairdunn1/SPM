//============================================================================
// Name        : CReportFactory.h
// Author      : S.Rasmussen
// Date        : 9/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CREPORTFACTORY_H_
#define CREPORTFACTORY_H_

// Global Headers
#include <string>

// Local headers
#include "../CReport.h"

// Using
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CReportFactory {
public:
  // Functions
  static CReport* buildReport(string type, bool registerWithManager = true);

private:
  // Functions
  CReportFactory();
  virtual ~CReportFactory();
};

#endif /* CREPORTFACTORY_H_ */
