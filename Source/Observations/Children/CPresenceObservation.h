//============================================================================
// Name        : CPresenceObservation.h
// Author      : C.Marsh, A. Dunn
// Copyright   : Copyright NIWA Science �2015 - www.niwa.co.nz
//============================================================================
#ifndef CPRESENCEOBSERVATION_H_
#define CPRESENCEOBSERVATION_H_

// Local Headers
#include "../CObservation.h"

// Classes
class CCatchability;

//**********************************************************************
//
//
//**********************************************************************
class CPresenceObservation : public CObservation
{
public:
  // Functions
  CPresenceObservation();
  virtual ~CPresenceObservation();
  CObservation *clone() { return new CPresenceObservation(*this); }
  void validate();
  void build();
  void execute();
  string getType() { return (PARAM_PRESENCE); }
  double getCatchability();

protected:
  // Variables
  map<string, double> mProportionMatrix;
  map<string, double> mErrorValue;
  string sCatchability;
  CCatchability *pCatchability;
  double dDelta;
  double dProcessError;
};

#endif /*CPRESENCEOBSERVATION_H_*/
