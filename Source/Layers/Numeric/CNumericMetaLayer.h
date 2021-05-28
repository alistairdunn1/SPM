//============================================================================
// Name        : CNumericMetaLayer.h
// Author      : S.Rasmussen
// Date        : 16/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CNUMERICMETALAYER_H_
#define CNUMERICMETALAYER_H_

// Global Headers
#include <vector>

// Local headers
#include "../../InitializationPhases/CInitializationPhaseManager.h"
#include "Base/CNumericLayer.h"

// Classes
class CTimeStepManager;

// Using
using std::vector;

//**********************************************************************
//
//
//**********************************************************************
class CNumericMetaLayer : public CNumericLayer {
public:
  // Functions
  CNumericMetaLayer();
  virtual ~CNumericMetaLayer();
  CLayer* clone() { return new CNumericMetaLayer(*this); }
  void    validate();
  void    build();
  double  getValue(int RowIndex, int ColIndex, int TargetRow, int TargetCol);

protected:
  // Variables
  string                       sDefaultLayer;
  vector<int>                  vYears;
  vector<string>               vLayerNames;
  vector<string>               vInitialisationPhases;
  vector<string>               vInitialisationLayers;
  vector<CNumericLayer*>       vPhaseLayers;
  vector<int>                  vYearsIndex;
  vector<CNumericLayer*>       vYearsLayers;
  bool                         bHasYears;
  bool                         bHasInitialisation;
  CInitializationPhaseManager* pInitializationPhaseManager;
  CTimeStepManager*            pTimeStepManager;
};

#endif /* CMETALAYER_H_ */
