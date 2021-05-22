//============================================================================
// Name        : CEstimateFactory.h
// Author      : S.Rasmussen
// Date        : 12/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description : This is the factory for creating different types of estimates.
//      It uses a basic factory design pattern to make it easier to add new types
//      of estimates later
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CMCMCFACTORY_H_
#define CMCMCFACTORY_H_

// Global headers
#include <string>

// Local Headers
#include "../CMCMC.h"

// Using
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CMCMCFactory
{
public:
  // Functions
  static CMCMC *buildMCMC(const string &type, bool registerWithManager = true);

private:
  // Functions
  CMCMCFactory() = delete;
  virtual ~CMCMCFactory() = delete;
};

#endif /* CESTIMATEFACTORY_H_ */
