//============================================================================
// Name        : CNormalLikelihood.h
// Author      : S.Rasmussen
// Date        : 14/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CNORMALLIKELIHOOD_H_
#define CNORMALLIKELIHOOD_H_

// Local headers
#include "../CLikelihood.h"
#include "../../RandomNumberGenerator/CRandomNumberGenerator.h"

//**********************************************************************
//
//
//**********************************************************************
class CNormalLikelihood : public CLikelihood
{
public:
  // Functions
  CNormalLikelihood();
  virtual ~CNormalLikelihood();
  double adjustErrorValue(const double processError, const double errorValue);
  void getResult(vector<double> &scores, const vector<double> &expected, const vector<double> &observed,
                 const vector<double> &errorValue, const vector<double> &processError, const double delta);
  void simulateObserved(const vector<string> &keys, vector<double> &observed, const vector<double> &expected,
                        const vector<double> &errorValue, const vector<double> &processError, const double delta);
};

#endif /* CNORMALLIKELIHOOD_H_ */
