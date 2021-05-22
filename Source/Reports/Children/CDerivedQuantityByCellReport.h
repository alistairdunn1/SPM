//============================================================================
// Name        : CDerivedQuantityReport.h
// Author      : S.Rasmussen
// Date        : 26/03/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CDERIVEDQUANTITYBYCELLREPORT_H_
#define CDERIVEDQUANTITYBYCELLREPORT_H_

// Local headers
#include "Base/CFileReport.h"

// Forward-Declaration
class CDerivedQuantityByCell;

//**********************************************************************
//
//
//**********************************************************************
class CDerivedQuantityByCellReport : public CFileReport
{
public:
  CDerivedQuantityByCellReport();
  virtual ~CDerivedQuantityByCellReport();
  CReport *clone() { return new CDerivedQuantityByCellReport(*this); }
  void validate();
  void build();
  void execute();

protected:
  string sDerivedQuantityByCell;
  CDerivedQuantityByCell *pDerivedQuantityByCell;
  bool bPrintInitialisation;
};

#endif /* CDERIVEDQUANTITYBYCELLREPORT_H_ */
