//============================================================================
// Name        : CObjectiveFunctionReport.h
// Author      : S.Rasmussen
// Date        : 30/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef COBJECTIVEFUNCTIONREPORT_H_
#define COBJECTIVEFUNCTIONREPORT_H_

// Local Headers
#include "Base/CFileReport.h"

//**********************************************************************
//
//
//**********************************************************************
class CObjectiveFunctionReport : public CFileReport
{
public:
  CObjectiveFunctionReport();
  virtual ~CObjectiveFunctionReport();
  CReport *clone() { return new CObjectiveFunctionReport(*this); }
  void execute();
};

#endif /* COBJECTIVEFUNCTIONREPORT_H_ */
