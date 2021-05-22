//============================================================================
// Name        : CNormalByStdevEstimate.h
// Author      : S.Rasmussen
// Date        : 8/09/2014
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
// Description :
//============================================================================
#ifndef CNORMALBYSTDEVESTIMATE_H_
#define CNORMALBYSTDEVESTIMATE_H_

#include "../CEstimate.h"

/**
 * Class definition
 */
class CNormalByStdevEstimate : public CEstimate
{
public:
  // methods
  CNormalByStdevEstimate();
  virtual ~CNormalByStdevEstimate() = default;
  void validate();
  double getScore();

protected:
  // Variables
  double dMu;
  double dSigma;
};

#endif /* CNORMALBYSTDEVESTIMATE_H_ */
