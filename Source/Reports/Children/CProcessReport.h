//============================================================================
// Name        : CProcessReport.h
// Author      : S.Rasmussen
// Date        : 23/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CPROCESSREPORT_H_
#define CPROCESSREPORT_H_

// Local headers
#include "Base/CFileReport.h"
#include "../../Processes/CProcess.h"

typedef vector<vector<double>> Data;

//**********************************************************************
//
//
//**********************************************************************
class CProcessReport : public CFileReport
{
public:
  CProcessReport();
  virtual ~CProcessReport();
  CReport *clone() { return new CProcessReport(*this); }
  void validate();
  void build();
  void execute();

protected:
  string sParameter;
  CProcess *pTarget;
};

#endif /* CPROCESSREPORT_H_ */
