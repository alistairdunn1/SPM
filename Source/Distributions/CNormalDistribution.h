//============================================================================
// Name        : CNormalDistribution.h
// Author      : S.Rasmussen
// Date        : 7/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CNORMALDISTRIBUTION_H_
#define CNORMALDISTRIBUTION_H_

//**********************************************************************
//
//
//**********************************************************************
class CNormalDistribution
{
public:
  static double getCDF(double x, double mu, double sigma);
  static double getQuantile(double x, double mu, double sigma);

protected:
  // Functions
  CNormalDistribution(){};
  virtual ~CNormalDistribution(){};
};

#endif /* CNORMALDISTRIBUTION_H_ */
