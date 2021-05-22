//============================================================================
// Name        : CProportionsAtAgeObservation.h
// Author      : S.Rasmussen
// Date        : 17/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CPROPORTIONSATAGE_H_
#define CPROPORTIONSATAGE_H_

// Local Headers
#include "../CObservation.h"
#include "../../RandomNumberGenerator/CRandomNumberGenerator.h"

// Forward Declaration
class CAgeingError;
class CCompoundCategories;

//**********************************************************************
//
//
//**********************************************************************
class CProportionsAtAgeObservation : public CObservation
{
public:
  // Functions
  CProportionsAtAgeObservation();
  virtual ~CProportionsAtAgeObservation();
  CObservation *clone() { return new CProportionsAtAgeObservation(*this); }
  void validate();
  void build();
  void execute();
  int getMinAge() { return iMinAge; }
  int getMaxAge() { return iMaxAge; }
  bool getAgePlusGroup() { return bAgePlus; }
  string getType() { return (PARAM_PROPORTIONS_AT_AGE); }

protected:
  // Variables
  map<string, vector<double>> mvObservationMatrix;
  map<string, vector<double>> mvErrorMatrix;
  double dDelta;
  double *pAgeResults;
  int iMinAge;
  int iMaxAge;
  int iAgeSpread;
  bool bAgePlus;
  bool bRescale;
  double dTolerance;
  double dProcessError;
  string sAgeingError;
  CAgeingError *pAgeingError;
  CCompoundCategories *pCategories;
};

#endif /*CPROPORTIONSATAGE_H_*/
