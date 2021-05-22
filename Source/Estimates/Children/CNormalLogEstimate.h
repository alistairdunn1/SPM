//============================================================================
// Name        : CNormalLogEstimate.h
// Author      : S.Rasmussen
// Date        : 8/09/2014
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
// Description :
//============================================================================
#ifndef CNORMALLOGESTIMATE_H_
#define CNORMALLOGESTIMATE_H_

#include "../CEstimate.h"

/**
 * Class definition
 */
class CNormalLogEstimate : public CEstimate
{
public:
  // methods
  CNormalLogEstimate();
  virtual ~CNormalLogEstimate() = default;
  void validate();
  double getScore();

protected:
  // Variables
  double dMu;
  double dSigma;
};

#endif /* CNORMALLOGESTIMATE_H_ */
