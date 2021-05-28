//============================================================================
// Name        : CStandardHeaderReport.cpp
// Author      : S.Rasmussen
// Date        : 5/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global Headers
#include <math.h>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Local Headers
#include "../../Version.h"
#include "CStandardHeaderReport.h"

// Namespaces
using std::cerr;
using std::cout;
using std::endl;
using std::ostringstream;

//**********************************************************************
// CStandardHeaderReport::CStandardHeaderReport()
// Default Constructor
//**********************************************************************
CStandardHeaderReport::CStandardHeaderReport() {
  // Variables
  tmeStart = time(NULL);

  // Linux Vars
#ifndef __MINGW32__
  times(&cpu_start);
#endif

  // Start building our Header
  sVersion = "";
  sHeader  = "SPM (Spatial Population Model)";
#ifndef OPTIMIZE
  sHeader += " (UNOPTIMISED)\n";
#else
  sHeader += "\n";
#endif
}

//**********************************************************************
// void CStandardHeaderReport::start()
// Start the printing of this header
//**********************************************************************
void CStandardHeaderReport::start() {
  // Build Command Line
  sHeader += "Call: ";
  for (int i = 0; i < pConfig->getCommandLineParameterCount(); ++i) sHeader += pConfig->getCommandLineParameter(i) + string(" ");

  // Build Date
  sHeader += "\nDate: " + string(ctime(&tmeStart));

  // Build Version
  std::stringstream sRevisionNumber;
  sRevisionNumber << SOURCE_CONTROL_VERSION;
  sVersion = "v" + string(VERSION) + "-" + string(SOURCE_CONTROL_DATE) + " (rev. " + sRevisionNumber.str() + ").";

  sHeader += sVersion + " Copyright (c) 2008-" + SOURCE_CONTROL_YEAR + ", NIWA\n";

  // Build User/Computer Info
#ifdef __MINGW32__
  sHeader += "User name: " + string(getenv("USERNAME")) + "\n";
  sHeader += "Machine name: " + string(getenv("COMPUTERNAME")) + " (";
  sHeader += string(getenv("OS")) + ", ";
  ostringstream PID;
  PID << _getpid();
  sHeader += "PID=" + PID.str() + ")\n";
#else
  char* cUsername = getenv("LOGNAME");
  if (cUsername != NULL)
    sHeader += "User name: " + string(cUsername) + "\n";
  else {
    sHeader += "User name: -----\n";
  }
  sHeader += "\nMachine name: ";
  struct utsname names;
  uname(&names);
  sHeader += static_cast<string>(names.nodename) + " (" + static_cast<string>(names.sysname) + " " + static_cast<string>(names.release) + " " + static_cast<string>(names.machine);
  ostringstream PID;
  PID << getpid();
  sHeader += "PID=" + PID.str() + ")\n";
#endif

  // Print Header
  cout << sHeader << endl;
}

//**********************************************************************
// void CStandardHeaderReport::execute()
//
//**********************************************************************
void CStandardHeaderReport::execute() {}

//**********************************************************************
// void CStandardHeaderReport::end()
// End our Printing of this Header
//**********************************************************************
void CStandardHeaderReport::end() {
#ifndef __MINGW32__
  times(&cpu_stop);
  double cpu_time
      = (static_cast<double>(cpu_stop.tms_utime) + static_cast<double>(cpu_stop.tms_stime)) - (static_cast<double>(cpu_start.tms_utime) + static_cast<double>(cpu_start.tms_stime));
  // Turn into seconds
  cpu_time /= static_cast<double>(sysconf(_SC_CLK_TCK));
  // Turn into hours
  cpu_time = cpu_time / 3600.0;
  int P    = (int)floor(log10(cpu_time)) + 4;
  cerr << "Total CPU time: " << std::setprecision(P) << cpu_time << (cpu_time == 1 ? " hour" : " hours") << ".\n";
#endif

  double elapsed_time = static_cast<double>(time(NULL) - tmeStart);
  if (elapsed_time < 60) {
    int P = (int)floor(log10(elapsed_time)) + 4;
    cerr << "Total elapsed time: " << std::setprecision(P) << fmax(1, elapsed_time) << (elapsed_time <= 1 ? " second" : " seconds") << endl;
  } else if ((elapsed_time / 60.0) < 60) {
    elapsed_time /= 60.0;
    int P = (int)floor(log10(elapsed_time)) + 4;
    cerr << "Total elapsed time: " << std::setprecision(P) << elapsed_time << (elapsed_time == 1 ? " minute" : " minutes") << endl;
  } else {
    elapsed_time /= 3600.0;
    int P = (int)floor(log10(elapsed_time)) + 4;
    cerr << "Total elapsed time: " << std::setprecision(P) << elapsed_time << (elapsed_time == 1 ? " hour" : " hours") << endl;
  }
  cout << "Completed" << endl;
}

//**********************************************************************
// CStandardHeaderReport::~CStandardHeaderReport()
// Destructor
//**********************************************************************
CStandardHeaderReport::~CStandardHeaderReport() {}
