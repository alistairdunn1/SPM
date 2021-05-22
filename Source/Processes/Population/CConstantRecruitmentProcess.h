//============================================================================
// Name        : CConstantRecruitmentProcess.h
// Author      : S.Rasmussen
// Date        : 13/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CCONSTANTRECRUITMENTPROCESS_H_
#define CCONSTANTRECRUITMENTPROCESS_H_

// Local Headers
#include "../CProcess.h"

// Forward Declaration
class CNumericLayer;

//**********************************************************************
//
//
//**********************************************************************
class CConstantRecruitmentProcess : public CProcess
{
public:
  // Functions
  CConstantRecruitmentProcess();
  virtual ~CConstantRecruitmentProcess();
  CProcess *clone() { return new CConstantRecruitmentProcess(*this); }
  void validate();
  void build();
  void execute();

protected:
  // Variables
  double dR0;
  vector<double> vProportions;
  int iAge;
  int iAgeIndex;
  string sLayer;
  CNumericLayer *pLayer;
};

#endif /*CCONSTANTRECRUITMENTPROCESS_H_*/
