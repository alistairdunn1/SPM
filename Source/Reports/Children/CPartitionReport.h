//============================================================================
// Name        : CPartitionReport.h
// Author      : S.Rasmussen
// Date        : 29/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CPARTITIONREPORT_H_
#define CPARTITIONREPORT_H_

// Local headers
#include "Base/CFileReport.h"

// Forward Dec
class CTimeStepManager;

//**********************************************************************
//
//
//**********************************************************************
class CPartitionReport : public CFileReport
{
public:
  // Functions
  CPartitionReport();
  virtual ~CPartitionReport();
  CReport *clone() { return new CPartitionReport(*this); }
  void validate();
  void build();
  void execute();

protected:
  // Variables
  vector<int> vYear;
  int iTimeStep;
  string sTimeStep;
  CTimeStepManager *pTimeStepManager;
};

#endif /* CPARTITIONREPORT_H_ */
