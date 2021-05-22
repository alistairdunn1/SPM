//============================================================================
// Name        : CEstimateSummaryReport.h
// Author      : S.Rasmussen
// Date        : 30/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CESTIMATESUMMARYREPORT_H_
#define CESTIMATESUMMARYREPORT_H_

// Local headers
#include "Base/CFileReport.h"

//**********************************************************************
//
//
//**********************************************************************
class CEstimateSummaryReport : public CFileReport
{
public:
  CEstimateSummaryReport();
  virtual ~CEstimateSummaryReport();
  CReport *clone() { return new CEstimateSummaryReport(*this); }
  void execute();
};

#endif /* CESTIMATESUMMARYREPORT_H_ */
