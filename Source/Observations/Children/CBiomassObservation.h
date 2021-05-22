//============================================================================
// Name        : CBiomassObservation.h
// Author      : S.Rasmussen
// Date        : 4/04/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CBIOMASSOBSERVATION_H_
#define CBIOMASSOBSERVATION_H_

// Local Headers
#include "../CObservation.h"

// Classes
class CCatchability;

//**********************************************************************
//
//
//**********************************************************************
class CBiomassObservation : public CObservation
{
public:
  // Functions
  CBiomassObservation();
  virtual ~CBiomassObservation();
  CObservation *clone() { return new CBiomassObservation(*this); }
  void validate();
  void build();
  void execute();
  string getType() { return (PARAM_BIOMASS); }
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

#endif /*CBIOMASSOBSERVATION_H_*/
