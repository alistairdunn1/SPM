//============================================================================
// Name        : CCategoricalMonotonicPreferenceFunction.h
// Author      : S.Rasmussen
// Date        : 16/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CCATEGORICALMONOTONICPREFERENCEFUNCTION_H_
#define CCATEGORICALMONOTONICPREFERENCEFUNCTION_H_

// Local Headers
#include "../CPreferenceFunction.h"

// Classes
class CCategoricalLayer;

//**********************************************************************
//
//
//**********************************************************************
class CCategoricalMonotonicPreferenceFunction : public CPreferenceFunction
{
public:
  // Functions
  CCategoricalMonotonicPreferenceFunction();
  virtual ~CCategoricalMonotonicPreferenceFunction();
  CPreferenceFunction *clone() { return new CCategoricalMonotonicPreferenceFunction(*this); }
  vector<double> getValues() { return vValues; }
  vector<string> getLabels() { return vLabels; }
  double getResult(int RIndex, int CIndex, int TRIndex, int TCIndex);
  void validate();
  void build();
  bool getIsStatic();

protected:
  // Variables
  vector<double> vValues;
  vector<string> vLabels;
  vector<string> vCategories;
  vector<string> vSelectivities;
  string sLayerValue;
  CCategoricalLayer *pLayer;
};

#endif /*CCATEGORICALMONOTONICPREFERENCEFUNCTION_H_*/
