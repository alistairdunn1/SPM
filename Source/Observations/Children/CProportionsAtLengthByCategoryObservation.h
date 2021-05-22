//============================================================================
// Name        : CProportionsAtLengthByCategoryObservation.h
// Author      :
// Date        :
// Copyright   :
// Description :
//============================================================================
#ifndef CPROPORTIONSATLENGTHBYCATEGORYOBSERVATION_H_
#define CPROPORTIONSATLENGTHBYCATEGORYOBSERVATION_H_

// Local Headers
#include "../CObservation.h"

//**********************************************************************
//
//
//**********************************************************************
class CProportionsAtLengthByCategoryObservation : public CObservation
{
public:
  CProportionsAtLengthByCategoryObservation();
  virtual ~CProportionsAtLengthByCategoryObservation();
  CObservation *clone() { return new CProportionsAtLengthByCategoryObservation(*this); }
  void validate();
  void build();
  void execute();
  double getLengthBinValue(int index) { return vLengthBins[index]; }
  int getNBins() { return iNBins; }
  string getType() { return (PARAM_PROPORTIONS_AT_LENGTH_BY_CATEGORY); }

protected:
  // Variables
  map<string, vector<double>> mvObservationMatrix;
  map<string, vector<double>> mvErrorMatrix;
  vector<string> vTargetCategoryNames;
  vector<int> vTargetCategories;
  CAgeSize *pAgeSize;
  double *pLengthResults;
  double *pCombinedLengthResults;
  int iNBins;
  vector<double> vLengthBins;
  vector<string> vTargetSelectivityNames;
  vector<CSelectivity *> vTargetSelectivities;
  double dDelta;
  double dProcessError;
  double dDetectionProbability;
};

#endif /*CPROPORTIONSATLENGTHBYCATEGORYOBSERVATION_H_*/
