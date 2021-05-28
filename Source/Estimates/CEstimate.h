//============================================================================
// Name        : CEstimate.h
// Author      : S.Rasmussen
// Date        : 27/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CESTIMATE_H_
#define CESTIMATE_H_

// Local Headers
#include "../BaseClasses/CBaseBuild.h"

//**********************************************************************
//
//
//**********************************************************************
class CEstimate : public CBaseBuild {
public:
  CEstimate();
  virtual ~CEstimate();
  void           fillSameVector(vector<string>& sames);
  string         getParameter() { return sParameter; }
  double         getLowerBound() { return dLowerBound; }
  double         getUpperBound() { return dUpperBound; }
  bool           getMCMCFixed() { return bMCMCFixed; }
  int            getEstimationPhase() { return iEstimationPhase; }
  void           setValue(double value);
  double         getValue();
  void           setEnabled(bool value) { bEnabled = value; }
  bool           getEnabled() { return bEnabled; }
  void           addValue(double value);
  int            getValueCount() { return (int)vValueList.size(); }
  void           loadValue(int index);
  void           setTarget(double* newTarget) { pTarget = newTarget; }
  virtual void   validate();
  void           build();
  virtual double getScore() = 0;
  string         getType() { return sType; }

protected:
  // Variables
  string          sType;
  string          sParameter;
  double          dLowerBound;
  double          dUpperBound;
  bool            bMCMCFixed;
  double*         pTarget;
  bool            bEnabled;
  int             iEstimationPhase;
  vector<string>  vSameList;
  vector<double*> vSameIndex;
  vector<double>  vValueList;
};

#endif /*CESTIMATE_H_*/
