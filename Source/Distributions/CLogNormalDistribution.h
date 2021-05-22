//============================================================================
// Name        : CLogNormalDistribution.h
// Author      :
// Date        :
// Copyright   :
// Description :
//============================================================================
#ifndef CLOGNORMALDISTRIBUTION_H_
#define CLOGNORMALDISTRIBUTION_H_

//**********************************************************************
//
//
//**********************************************************************
class CLogNormalDistribution
{
public:
  static double getCDF(double x, double mu, double sigma);
  static double getQuantile(double x, double mu, double sigma);

protected:
  // Functions
  CLogNormalDistribution(){};
  virtual ~CLogNormalDistribution(){};
};

#endif /* CLOGNORMALDISTRIBUTION_H_ */
