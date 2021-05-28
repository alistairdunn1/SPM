//============================================================================
// Name        : CReportManager.h
// Author      : S.Rasmussen
// Date        : 30/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CREPORTMANAGER_H_
#define CREPORTMANAGER_H_

// Local headers
#include "../BaseClasses/CBaseManager.h"
#include "../CRuntimeController.h"

// Forward-Dec
class CReport;

//**********************************************************************
//
//
//**********************************************************************
class CReportManager : public CBaseManager {
public:
  // Function
  static CReportManager* Instance();
  static void            Destroy();
  virtual ~CReportManager();
  void   addReporter(CReport* value);
  void   setReportSuffix(string newSuffix) { sReportSuffix = newSuffix; }
  string getReportSuffix() { return sReportSuffix; }
  void   clone(CReportManager* Manager);
  void   validate();
  void   build();
  void   execute();
  void   execute(EState state);

protected:
  // Functions
  CReportManager();

  // Variables
  vector<CReport*> vReporters;
  vector<CReport*> vModellingReporters;
  bool             bDisableReports;
  string           sReportSuffix;

private:
  static boost::thread_specific_ptr<CReportManager> clInstance;
};

#endif /* CREPORTMANAGER_H_ */
