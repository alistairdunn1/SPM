//============================================================================
// Name        : CFileReport.h
// Author      : S.Rasmussen
// Date        : 29/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CFILEREPORT_H_
#define CFILEREPORT_H_

// Global Headers
#include <string>
#include <iostream>
#include <fstream>

// Local headers
#include "../../CReport.h"

// Using
using std::cout;
using std::endl;
using std::ios_base;
using std::ofstream;
using std::streambuf;

//**********************************************************************
//
//
//**********************************************************************
class CFileReport : public CReport
{
public:
  // Functions
  CFileReport();
  virtual ~CFileReport();
  virtual void validate();
  virtual void build() { CReport::build(); };
  void start();
  void end();

protected:
  // Variable
  string sFileName;
  string sFullFileName;
  string sLastSuffix;
  bool bOverwrite;
  streambuf *sCoutBackup;
  ofstream *fFile;
  bool bStartedWrite;
};

#endif /* CFILEREPORT_H_ */
