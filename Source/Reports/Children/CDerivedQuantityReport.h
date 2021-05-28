//============================================================================
// Name        : CDerivedQuantityReport.h
// Author      : S.Rasmussen
// Date        : 26/03/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CDERIVEDQUANTITYREPORT_H_
#define CDERIVEDQUANTITYREPORT_H_

// Local headers
#include "Base/CFileReport.h"

// Forward-Declaration
class CDerivedQuantity;

//**********************************************************************
//
//
//**********************************************************************
class CDerivedQuantityReport : public CFileReport {
public:
  CDerivedQuantityReport();
  virtual ~CDerivedQuantityReport();
  CReport* clone() { return new CDerivedQuantityReport(*this); }
  void     validate();
  void     build();
  void     execute();

protected:
  string            sDerivedQuantity;
  CDerivedQuantity* pDerivedQuantity;
};

#endif /* CDERIVEDQUANTITYREPORT_H_ */
