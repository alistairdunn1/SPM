//============================================================================
// Name        : CLayerDerivedWorldViewReport.h
// Author      : S.Rasmussen
// Date        : 9/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CLAYERDERIVEDWORLDVIEWREPORT_H_
#define CLAYERDERIVEDWORLDVIEWREPORT_H_

// Local Headers
#include "Base/CFileReport.h"

// Forward Dec
class CTimeStepManager;
class CLayerManager;
class CCategoricalLayer;
class CLayerDerivedWorldView;

//**********************************************************************
//
//
//**********************************************************************
class CLayerDerivedWorldViewReport : public CFileReport {
public:
  // Functions
  CLayerDerivedWorldViewReport();
  virtual ~CLayerDerivedWorldViewReport();
  CReport* clone() { return new CLayerDerivedWorldViewReport(*this); }
  void     validate();
  void     build();
  void     execute();

protected:
  // Variables
  vector<int>             vYear;
  int                     iTimeStep;
  string                  sTimeStep;
  CTimeStepManager*       pTimeStepManager;
  string                  sLayer;
  CCategoricalLayer*      pLayer;
  CLayerManager*          pLayerManager;
  CLayerDerivedWorldView* pWorldView;
  map<string, int>        mAreas;
};

#endif /* CLAYERDERIVEDWORLDVIEWREPORT_H_ */
