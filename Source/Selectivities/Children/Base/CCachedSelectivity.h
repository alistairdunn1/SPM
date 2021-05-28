//============================================================================
// Name        : CCachedSelectivity.h
// Author      : S.Rasmussen
// Date        : 20/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CCACHEDSELECTIVITY_H_
#define CCACHEDSELECTIVITY_H_

// Global Headers
#include <vector>

// Local headers
#include "../../CSelectivity.h"

// Using
using std::vector;

//**********************************************************************
//
//
//**********************************************************************
class CCachedSelectivity : public CSelectivity {
public:
  CCachedSelectivity();
  virtual ~CCachedSelectivity();
  virtual void   build();
  virtual void   rebuild();
  virtual double getResult(int index);

protected:
  // Functions
  virtual double calculateResult(int Age) = 0;

  // variables
  vector<double> vResults;
};

#endif /* CCACHEDSELECTIVITY_H_ */
