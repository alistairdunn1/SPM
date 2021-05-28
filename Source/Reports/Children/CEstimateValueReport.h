//============================================================================
// Name        : CEstimateValueReport.h
// Author      : S.Rasmussen
// Date        : 4/03/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CESTIMATEVALUEREPORT_H_
#define CESTIMATEVALUEREPORT_H_

// Local headers
#include "Base/CFileReport.h"

//**********************************************************************
//
//
//**********************************************************************
class CEstimateValueReport : public CFileReport {
public:
  CEstimateValueReport();
  virtual ~CEstimateValueReport();
  CReport* clone() { return new CEstimateValueReport(*this); }
  void     validate();
  void     execute();

protected:
  bool bWrittenHeader;
  bool bStandardHeader;
};

#endif /* CESTIMATEVALUEREPORT_H_ */
