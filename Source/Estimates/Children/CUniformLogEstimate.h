//============================================================================
// Name        : CUniformLogEstimate.h
// Author      : S.Rasmussen
// Date        : 8/09/2014
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
// Description :
//============================================================================
#ifndef CUNIFORMLOGESTIMATE_H_
#define CUNIFORMLOGESTIMATE_H_

// headers
#include "../CEstimate.h"

/**
 * Class definition
 */
class CUniformLogEstimate : public CEstimate {
public:
  // methods
  CUniformLogEstimate();
  virtual ~CUniformLogEstimate() = default;
  void   validate() { CEstimate::validate(); }
  double getScore();
};

#endif /* CUNIFORMLOGESTIMATE_H_ */
