//============================================================================
// Name        : CProportionsAtLengthObservation.h
// Author      : A. Dunn
// Date        : 02/12/2019
// Copyright   :
// Description :
// $Date$
//============================================================================
#ifndef CPROPORTIONSATLENGTH_H_
#define CPROPORTIONSATLENGTH_H_

// Local Headers
#include "../CObservation.h"
#include "../../RandomNumberGenerator/CRandomNumberGenerator.h"

// Forward Declaration
class CCompoundCategories;
class CAgeSize;

//**********************************************************************
//
//
//**********************************************************************
class CProportionsAtLengthObservation : public CObservation
{
public:
  // Functions
  CProportionsAtLengthObservation();
  virtual ~CProportionsAtLengthObservation();
  CObservation *clone() { return new CProportionsAtLengthObservation(*this); }
  void validate();
  void build();
  void execute();
  double getLengthBinValue(int index) { return vLengthBins[index]; }
  int getNBins() { return iNBins; }
  string getType() { return (PARAM_PROPORTIONS_AT_LENGTH); }

protected:
  // Variables
  map<string, vector<double>> mvObservationMatrix;
  map<string, vector<double>> mvErrorMatrix;
  double dDelta;
  CAgeSize *pAgeSize;
  double *pLengthResults;
  int iNBins;
  vector<double> vLengthBins;
  bool bRescale;
  double dTolerance;
  double dProcessError;
  CCompoundCategories *pCategories;
};

#endif /*CPROPORTIONSATLENGTH_H_*/
