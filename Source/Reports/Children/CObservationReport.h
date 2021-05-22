//============================================================================
// Name        : CObservationReport.h
// Author      : S.Rasmussen
// Date        : 26/03/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef COBSERVATIONREPORT_H_
#define COBSERVATIONREPORT_H_

// Local Headers
#include "Base/CFileReport.h"

// Forward-Dec
class CObservation;

//**********************************************************************
//
//
//**********************************************************************
class CObservationReport : public CFileReport
{
public:
  // Functions
  CObservationReport();
  virtual ~CObservationReport();
  CReport *clone() { return new CObservationReport(*this); }
  void validate();
  void build();
  void execute();

protected:
  // Variables
  string sObservation;
  CObservation *pObservation;
};

#endif /* COBSERVATIONREPORT_H_ */
