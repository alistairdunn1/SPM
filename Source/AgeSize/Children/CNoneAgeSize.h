//============================================================================
// Name        : CNoneAgeSize.h
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CNONEAGESIZE_H_
#define CNONEAGESIZE_H_

#include "../CAgeSize.h"

//**********************************************************************
//
//
//**********************************************************************
class CNoneAgeSize : public CAgeSize {
public:
  // Functions
  CNoneAgeSize();
  virtual ~CNoneAgeSize();
  CAgeSize* clone() { return new CNoneAgeSize(*this); }
  void      validate();
  void      build();
  void      rebuild();
  double    getMeanSize(double& size) { return 1; };
  double    getMeanWeight(double& age) { return 1; };
  double    getCV(double& age) { return 0; };
  double    getCVFromSize(double& size) { return 0; };
  double    getProportionInLengthBin(double& age, double& LowerBin, double& UpperBin);
  bool      getByLength() { return 0; };

protected:
  string       sSizeWeight;
  CSizeWeight* pSizeWeight;
  double       getMeanWeightFromSize(double& size, double& cv) { return 1; };
  double       getGrowthProportion() { return 0; };
};

#endif /* CNONEAGESIZE_H_ */
