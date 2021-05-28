//============================================================================
// Name        : CLayerReport.h
// Author      : S.Rasmussen
// Date        : 26/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CLAYERREPORT_H_
#define CLAYERREPORT_H_

// Local headers
#include "Base/CFileReport.h"

// Forward Dec
class CTimeStepManager;
class CNumericLayer;
class CCategoricalLayer;
class CLayerManager;

//**********************************************************************
//
//
//**********************************************************************
class CLayerReport : public CFileReport {
public:
  CLayerReport();
  virtual ~CLayerReport();
  CReport* clone() { return new CLayerReport(*this); }
  void     validate();
  void     build();
  void     execute();

protected:
  // Variables
  vector<int>        vYears;
  int                iTimeStep;
  string             sTimeStep;
  CTimeStepManager*  pTimeStepManager;
  string             sLayer;
  string             sLayerType;
  string             sType;
  CNumericLayer*     pNumericLayer;
  CCategoricalLayer* pCategoricalLayer;
  CLayerManager*     pLayerManager;
};

#endif /* CLAYERREPORT_H_ */
