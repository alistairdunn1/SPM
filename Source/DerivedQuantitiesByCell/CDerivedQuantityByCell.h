//============================================================================
// Name        : CDerivedQuantityByCell.h
// Author      : S.Rasmussen
// Date        : 15/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
//============================================================================
#ifndef CDERIVEDQUANTITYBYCELL_H_
#define CDERIVEDQUANTITYBYCELL_H_

// Global Headers
#include <boost/shared_ptr.hpp>

// Local headers
#include "../BaseClasses/CBaseExecute.h"
#include "../Layers/Numeric/CDoubleLayer.h"

// Namespace
using boost::shared_ptr;

typedef vector<vector<double>> Data;

//**********************************************************************
//
//
//**********************************************************************
class CDerivedQuantityByCell : public CBaseBuild {
public:
  // Functions
  CDerivedQuantityByCell();
  virtual ~CDerivedQuantityByCell();
  vector<vector<double>> getValue(int offset);
  double                 getValue(int offset, int RowIndex, int ColIndex);
  vector<vector<double>> getValueFromIndex(int index) { return vValues[index]; };
  int                    getTimeStep() { return iTimeStep; };
  void                   incrementInitialisationPhase() { iCurrentInitialisationPhase++; }
  int                    getValuesSize() { return vValues.size(); }
  virtual void           calculate()                        = 0;
  virtual void           calculate(int initialisationPhase) = 0;
  int                    getInitialisationSize() { return vvInitialisationValues.size(); }
  int                    getInitialisationValuesSize(int initialisationPhase = 0) { return vvInitialisationValues[initialisationPhase].size(); }
  vector<vector<double>> getInitialisationValue(int initialisationPhase = 0, int index = 0) { return vvInitialisationValues[initialisationPhase][index]; }
  int                    getWidth() { return iWidth; }
  int                    getHeight() { return iHeight; }
  void                   build();
  void                   rebuild();

protected:
  // Members
  string                 sLayer;
  CNumericLayer*         pLayer;
  vector<vector<double>> vBlankData;
  int                    iHeight;
  int                    iWidth;
  int                    iCurrentInitialisationPhase;
  vector<vector<Data>>   vvInitialisationValues;
  vector<Data>           vValues;
  int                    iTimeStep;
};

#endif /* CDERIVEDQUANTITYBYCELL_H_ */
