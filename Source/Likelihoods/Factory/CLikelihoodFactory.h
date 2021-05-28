//============================================================================
// Name        : CLikelihoodFactory.h
// Author      : S.Rasmussen
// Date        : 14/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CLIKELIHOODFACTORY_H_
#define CLIKELIHOODFACTORY_H_

// Global headers
#include <string>

// Local headers
#include "../CLikelihood.h"

// Using
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CLikelihoodFactory {
public:
  // Functions
  static CLikelihood* buildLikelihood(string observationType, string type);

private:
  // Functions
  CLikelihoodFactory(){};
  virtual ~CLikelihoodFactory(){};
};

#endif /* CLIKELIHOODFACTORY_H_ */
