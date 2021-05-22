//============================================================================
// Name        : CHMC.h
// Author      :
// Date        :
// Copyright   :
// Description : Based on Keith O'Hara MCMC C++ library
//============================================================================

#ifndef CHMC_H_
#define CHMC_H_

// Global Headers
#include <boost/numeric/ublas/matrix.hpp>

// Local Headers
#include "../CMCMC.h"
#include "../../Minimizers/CMinimizerManager.h"
#include "../../Minimizers/CMinimizer.h"

// Classes
class CRuntimeThread;

using namespace boost::numeric;

//**********************************************************************
//
//
//**********************************************************************
class CHMC : public CMCMC
{
public:
  // Methods
  CHMC();
  virtual ~CHMC();
  void validate() final;
  void build() final;
  void execute() final;
  void leapfrog();
  void generateNewCandidate();

protected:
};

#endif /*CHMC_H_*/
