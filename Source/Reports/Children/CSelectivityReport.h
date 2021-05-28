//============================================================================
// Name        : CSelectivityReport.h
// Author      : S.Rasmussen
// Date        : 26/03/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CSELECTIVITYREPORT_H_
#define CSELECTIVITYREPORT_H_

// Local headers
#include "Base/CFileReport.h"

// Forward-Declaration
class CSelectivity;

//**********************************************************************
//
//
//**********************************************************************
class CSelectivityReport : public CFileReport {
public:
  CSelectivityReport();
  virtual ~CSelectivityReport();
  CReport* clone() { return new CSelectivityReport(*this); }
  void     validate();
  void     build();
  void     execute();

protected:
  string        sSelectivity;
  CSelectivity* pSelectivity;
};

#endif /* CSELECTIVITYREPORT_H_ */
