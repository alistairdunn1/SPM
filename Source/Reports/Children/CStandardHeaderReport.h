//============================================================================
// Name        : CStandardHeaderReport.h
// Author      : S.Rasmussen
// Date        : 5/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CSTANDARDHEADERREPORT_H_
#define CSTANDARDHEADERREPORT_H_

// Global Headers
#include <string>

#ifdef __MINGW32__
#include <process.h>
#else
#include <sys/utsname.h>
#include <sys/times.h>
#include <unistd.h>
#endif

// Local headers
#include "../CReport.h"

// Namespace
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CStandardHeaderReport : public CReport
{
public:
  // Functions
  CStandardHeaderReport();
  virtual ~CStandardHeaderReport();
  CReport *clone() { return new CStandardHeaderReport(*this); }
  void start();
  void execute();
  void end();

protected:
  // Variables
  string sHeader;
  string sVersion;
  time_t tmeStart;

  // Linux Vars
#ifndef __MINGW32__
  tms cpu_start;
  tms cpu_stop;
#endif
};

#endif /* CSTANDARDHEADERREPORT_H_ */
