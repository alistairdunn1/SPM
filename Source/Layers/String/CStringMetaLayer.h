//============================================================================
// Name        : CStringMetaLayer.h
// Author      : S.Rasmussen
// Date        : 16/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CSTRINGMETALAYER_H_
#define CSTRINGMETALAYER_H_

// Global Headers
#include <vector>

// Local headers
#include "Base/CCategoricalLayer.h"
#include "../../InitializationPhases/CInitializationPhaseManager.h"

// Classes
class CTimeStepManager;

// Using
using std::vector;

//**********************************************************************
//
//
//**********************************************************************
class CStringMetaLayer : public CCategoricalLayer
{
public:
  // Functions
  CStringMetaLayer();
  virtual ~CStringMetaLayer();
  CLayer *clone() { return new CStringMetaLayer(*this); }
  void validate();
  void build();
  string getValue(int RowIndex, int ColIndex);

protected:
  // Variables
  string sDefaultLayer;
  vector<int> vYears;
  vector<string> vLayerNames;
  vector<string> vInitialisationPhases;
  vector<string> vInitialisationLayers;
  vector<CCategoricalLayer *> vPhaseLayers;
  vector<int> vYearsIndex;
  vector<CCategoricalLayer *> vYearsLayers;
  bool bHasYears;
  bool bHasInitialisation;
  CInitializationPhaseManager *pInitializationPhaseManager;
  CTimeStepManager *pTimeStepManager;
};

#endif /* CSTRINGMETALAYER_H_ */
