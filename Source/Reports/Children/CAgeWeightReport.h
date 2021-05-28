//============================================================================
// Name        : CAgeWeightReport.h
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CAGEWEIGHTREPORT_H_
#define CAGEWEIGHTREPORT_H_

// Local headers
#include "Base/CFileReport.h"

// Forward-Declaration
class CAgeSize;

//**********************************************************************
//
//
//**********************************************************************
class CAgeWeightReport : public CFileReport {
public:
  CAgeWeightReport();
  virtual ~CAgeWeightReport();
  CReport* clone() { return new CAgeWeightReport(*this); }
  void     validate();
  void     build();
  void     execute();

protected:
  string         sAgeSize;
  CAgeSize*      pAgeSize;
  vector<double> vAgeList;
};

#endif /* CAGEWEIGHTREPORT_H_ */
