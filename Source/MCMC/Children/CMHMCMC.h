//============================================================================
// Name        : CMHMCMC.h
// Author      :
// Date        :
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
//============================================================================
#ifndef CMHMCMC_H_
#define CMHMCMC_H_

// Global Headers
#include <boost/numeric/ublas/matrix.hpp>

// Local Headers
#include "../../Minimizers/CMinimizer.h"
#include "../../Minimizers/CMinimizerManager.h"
#include "../CMCMC.h"

// Classes
class CRuntimeThread;

using namespace boost::numeric;

//**********************************************************************
//
//
//**********************************************************************
class CMHMCMC : public CMCMC {
public:
  // Methods
  CMHMCMC();
  virtual ~CMHMCMC();
  void validate() final;
  void build() final;
  void execute() final;

protected:
};

#endif /*CMHMCMC_H_*/
