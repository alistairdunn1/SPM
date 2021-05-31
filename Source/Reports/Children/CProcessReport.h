//============================================================================
// Name        : CProcessReport.h
// Author      : S.Rasmussen
// Date        : 23/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
//============================================================================
#ifndef CPROCESSREPORT_H_
#define CPROCESSREPORT_H_

// Local headers
#include "../../Processes/CProcess.h"
#include "Base/CFileReport.h"

typedef vector<vector<double>> Data;

// Forward Dec
class CNumericLayer;
class CLayerManager;

//**********************************************************************
//
//
//**********************************************************************
class CProcessReport : public CFileReport {
public:
  CProcessReport();
  virtual ~CProcessReport();
  CReport* clone() { return new CProcessReport(*this); }
  void     validate();
  void     build();
  void     execute();

protected:
  string         sParameter;
  CProcess*      pTarget;
  CNumericLayer* pCatchLayer;
  CNumericLayer* pRemovalLayer;
  CLayerManager* pLayerManager;

private:
  bool bReportRemovals;
};

#endif /* CPROCESSREPORT_H_ */
