//============================================================================
// Name        : CProfile.h
// Author      : S.Rasmussen
// Date        : 2/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CPROFILE_H_
#define CPROFILE_H_

// Local Headers
#include "../BaseClasses/CBaseBuild.h"

// Classes
class CEstimate;

//**********************************************************************
//
//
//**********************************************************************
class CProfile : public CBaseBuild {
public:
  CProfile();
  virtual ~CProfile();
  CProfile* clone() { return (new CProfile(*this)); }
  double    getStepSize() { return dStepSize; }
  double    getLowerBound() { return dLowerBound; }
  double    getUpperBound() { return dUpperBound; }
  string    getParameter() { return sParameter; }
  double    getCurrent() { return dCurrent; }
  void      setEnabled();
  bool      doStep();
  void      validate();
  void      build();
  void      setEnabled(bool value);

protected:
  // Variables
  int        iSteps;
  double     dStepSize;
  double     dLowerBound;
  double     dUpperBound;
  double     dCurrent;
  string     sParameter;
  CEstimate* pTarget;
};

#endif /*CPROFILE_H_*/
