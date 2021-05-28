//============================================================================
// Name        : CNormalEstimate.h
// Author      : S.Rasmussen
// Date        : 8/09/2014
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
// Description :
//============================================================================
#ifndef CNORMALESTIMATE_H_
#define CNORMALESTIMATE_H_

// headers
#include "../CEstimate.h"

/**
 *
 */
class CNormalEstimate : public CEstimate {
public:
  // methods
  CNormalEstimate();
  virtual ~CNormalEstimate() = default;
  void   validate();
  double getScore();

protected:
  // Variables
  double dMu;
  double dCv;
};

#endif /* CNORMALESTIMATE_H_ */
