//============================================================================
// Name        : CCovarianceReport.h
// Author      : S.Rasmussen
// Date        : 6/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CCOVARIANCEREPORT_H_
#define CCOVARIANCEREPORT_H_

// Local headers
#include "Base/CFileReport.h"

//**********************************************************************
//
//
//**********************************************************************
class CCovarianceReport : public CFileReport
{
public:
  // Functions
  CCovarianceReport();
  virtual ~CCovarianceReport();
  CReport *clone() { return new CCovarianceReport(*this); }
  void execute();
};

#endif /* CCOVARIANCEREPORT_H_ */
