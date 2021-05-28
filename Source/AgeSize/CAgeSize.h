//============================================================================
// Name        : CAgeSize.h
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CAGESIZE_H_
#define CAGESIZE_H_

// Local headers
#include "../BaseClasses/CBaseBuild.h"
#include "../Distributions/CLogNormalDistribution.h"
#include "../Distributions/CNormalDistribution.h"
#include "../SizeWeight/CSizeWeightManager.h"

//**********************************************************************
//
//
//**********************************************************************
class CAgeSize : public CBaseBuild {
public:
  // Functions
  CAgeSize();
  virtual ~CAgeSize();
  virtual CAgeSize* clone() = 0;
  void              validate();
  void              build();
  virtual void      rebuild();
  virtual double    getMeanSize(double& age)                                                  = 0;
  virtual double    getMeanWeight(double& age)                                                = 0;
  virtual double    getMeanWeightFromSize(double& size, double& cv)                           = 0;
  virtual double    getCV(double& age)                                                        = 0;
  virtual double    getCVFromSize(double& size)                                               = 0;
  virtual double    getProportionInLengthBin(double& age, double& LowerBin, double& UpperBin) = 0;
  virtual double    getGrowthProportion()                                                     = 0;
  virtual bool      getByLength()                                                             = 0;
};

#endif /* CAGESIZE_H_ */
