//============================================================================
// Name        : CProportionsByCategoryObservation.h
// Author      : S.Rasmussen
// Date        : 1/05/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CPROPORTIONSBYCATEGORYOBSERVATION_H_
#define CPROPORTIONSBYCATEGORYOBSERVATION_H_

// Local Headers
#include "../CObservation.h"

//**********************************************************************
//
//
//**********************************************************************
class CProportionsByCategoryObservation : public CObservation
{
public:
  CProportionsByCategoryObservation();
  virtual ~CProportionsByCategoryObservation();
  CObservation *clone() { return new CProportionsByCategoryObservation(*this); }
  void validate();
  void build();
  void execute();
  int getMinAge() { return iMinAge; }
  int getMaxAge() { return iMaxAge; }
  bool getAgePlusGroup() { return bAgePlus; }
  string getType() { return (PARAM_PROPORTIONS_BY_CATEGORY); }

protected:
  // Variables
  map<string, vector<double>> mvProportionMatrix;
  map<string, vector<double>> mvErrorValue;
  vector<string> vTargetCategoryNames;
  vector<int> vTargetCategories;

  double *pAgeResults;
  double *pCombinedAgeResults;
  int iMinAge;
  int iMaxAge;
  int iAgeSpread;
  bool bAgePlus;
  vector<string> vTargetSelectivityNames;
  vector<CSelectivity *> vTargetSelectivities;
  double dDelta;
  double dProcessError;
  double dDetectionProbability;
};

#endif /*CPROPORTIONSBYCATEGORYOBSERVATION_H_*/
