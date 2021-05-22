//============================================================================
// Name        : CBiomassPartitionReport.h
// Author      : S.Rasmussen
// Date        : 29/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CBIOMASSPARTITIONREPORT_H_
#define CBIOMASSPARTITIONREPORT_H_

// Local headers
#include "Base/CFileReport.h"

// Forward Dec
class CTimeStepManager;

//**********************************************************************
//
//
//**********************************************************************
class CBiomassPartitionReport : public CFileReport
{
public:
  // Functions
  CBiomassPartitionReport();
  virtual ~CBiomassPartitionReport();
  CReport *clone() { return new CBiomassPartitionReport(*this); }
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

#endif /* CBIOMASSPARTITIONREPORT_H_ */
