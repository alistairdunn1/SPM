//============================================================================
// Name        : CDerivedQuantity.h
// Author      : S.Rasmussen
// Date        : 15/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CDERIVEDQUANTITY_H_
#define CDERIVEDQUANTITY_H_

// Local headers
#include "../BaseClasses/CBaseExecute.h"

//**********************************************************************
//
//
//**********************************************************************
class CDerivedQuantity : public CBaseBuild
{
public:
  // Functions
  CDerivedQuantity();
  virtual ~CDerivedQuantity();
  double getValue(int offset);
  int getTimeStep() { return iTimeStep; };
  double getValueFromIndex(int index) { return vValues[index]; };
  void incrementInitialisationPhase() { iCurrentInitialisationPhase++; }
  int getValuesSize() { return vValues.size(); }
  virtual void calculate() = 0;
  virtual void calculate(int initialisationPhase) = 0;
  int getInitialisationSize() { return vvInitialisationValues.size(); }
  int getInitialisationValuesSize(int initialisationPhase = 0) { return vvInitialisationValues[initialisationPhase].size(); }
  double getInitialisationValue(int initialisationPhase = 0, int index = 0) { return vvInitialisationValues[initialisationPhase][index]; }
  void rebuild()
  {
    iCurrentInitialisationPhase = 0;
    vvInitialisationValues.clear();
    vValues.clear();
  }

protected:
  // Members
  int iHeight;
  int iWidth;
  int iCurrentInitialisationPhase;
  vector<vector<double>> vvInitialisationValues;
  vector<double> vValues;
  int iTimeStep;
};

#endif /* CDERIVEDQUANTITY_H_ */
