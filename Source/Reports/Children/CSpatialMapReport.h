//============================================================================
// Name        : CSpatialMapReport.h
// Author      : S.Rasmussen
// Date        : 15/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CSPATIALMAPREPORT_H_
#define CSPATIALMAPREPORT_H_

// Local headers
#include "Base/CFileReport.h"

//**********************************************************************
//
//
//**********************************************************************
class CSpatialMapReport : public CFileReport {
public:
  CSpatialMapReport();
  virtual ~CSpatialMapReport();
  CReport* clone() { return new CSpatialMapReport(*this); }
  void     execute();
};

#endif /* CSPATIALMAPREPORT_H_ */
