//============================================================================
// Name        : CInitializationReport.h
// Author      : S.Rasmussen
// Date        : 26/03/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CINITIALIZATIONREPORT_H_
#define CINITIALIZATIONREPORT_H_

// Local headers
#include "Base/CFileReport.h"

// Forward-Dec
class CInitializationPhaseManager;
class CInitializationPhase;

//**********************************************************************
//
//
//**********************************************************************
class CInitializationReport : public CFileReport
{
public:
  CInitializationReport();
  virtual ~CInitializationReport();
  CReport *clone() { return new CInitializationReport(*this); }
  void validate();
  void build();
  void execute();

protected:
  // Variables
  CInitializationPhaseManager *pInitializationPhaseManager;
  string sInitializationPhase;
  int iInitializationPhaseIndex;
  CInitializationPhase *pInitializationPhase;
};

#endif /* CINITIALIZATIONREPORT_H_ */
