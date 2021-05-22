//============================================================================
// Name        : CPreferenceMovementProcess.h
// Author      : S.Rasmussen
// Date        : 15/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef COPENMPPREFERENCEMOVEMENTPROCESS_H_
#define COPENMPPREFERENCEMOVEMENTPROCESS_H_

// Local headers
#include "Base/CMovementProcess.h"

// Classes
class CPreferenceFunction;
class CNumericLayer;

//**********************************************************************
//
//
//**********************************************************************
class COpenMPPreferenceMovementProcess : public CMovementProcess
{
public:
  // Typedefs
  typedef vector<vector<vector<vector<double>>>> Vector4D;

  // Functions
  COpenMPPreferenceMovementProcess();
  virtual ~COpenMPPreferenceMovementProcess();
  CProcess *clone() { return (new COpenMPPreferenceMovementProcess(*this)); }
  void validate();
  void build();
  void rebuild();
  void execute();

protected:
  // Variables
  vector<string> vDirectedProcessList;
  vector<CPreferenceFunction *> vDirectedProcessIndex;
  double dRunningTotal;
  CNumericLayer *pLayer;
  Vector4D vPreferenceCache;
  vector<vector<double>> vRunningTotalCache;
  bool bIsStatic;
  int iProcs;
};

#endif /* COPENMPPREFERENCEMOVEMENTPROCESS_H_ */
