//============================================================================
// Name        : CAgeSizeReport.h
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CAGESIZEREPORT_H_
#define CAGESIZEREPORT_H_

// Local headers
#include "Base/CFileReport.h"

// Forward-Declaration
class CAgeSize;

//**********************************************************************
//
//
//**********************************************************************
class CAgeSizeReport : public CFileReport {
public:
  CAgeSizeReport();
  virtual ~CAgeSizeReport();
  CReport* clone() { return new CAgeSizeReport(*this); }
  void     validate();
  void     build();
  void     execute();

protected:
  string         sAgeSize;
  CAgeSize*      pAgeSize;
  vector<double> vAgeList;
};

#endif /* CAGESIZEREPORT_H_ */
