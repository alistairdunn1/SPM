//============================================================================
// Name        : CLogNormalEstimate.h
// Author      : S.Rasmussen
// Date        : 8/09/2014
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
// Description :
//============================================================================
#ifndef CLOGNORMALESTIMATE_H_
#define CLOGNORMALESTIMATE_H_

// headers
#include "../CEstimate.h"

/**
 *
 */
class CLogNormalEstimate : public CEstimate
{
public:
  // methods
  CLogNormalEstimate();
  virtual ~CLogNormalEstimate() = default;
  void validate();
  double getScore();

protected:
  // Variables
  double dMu;
  double dCv;

private:
  // Variables
  double dSigma;
};

#endif /* CLOGNORMALESTIMATE_H_ */
