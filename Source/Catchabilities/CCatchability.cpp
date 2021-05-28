//============================================================================
// Name        : CCatchability.cpp
// Author      : S.Rasmussen
// Date        : 28/04/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CCatchability.h"

//**********************************************************************
// CCatchability::CCatchability()
// Default Constructor
//**********************************************************************
CCatchability::CCatchability() {
  // Register estimables
  registerEstimable(PARAM_Q, &dQ);

  // Register user allowed params
  pParameterList->registerAllowed(PARAM_Q);
}

//**********************************************************************
// void CCatchability::validate()
// Validate the Catchability
//**********************************************************************
void CCatchability::validate() {
  try {
    // Base
    CBaseValidate::validate();

    // Populate Vars
    dQ = pParameterList->getDouble(PARAM_Q);
  } catch (string& Ex) {
    Ex = "CCatchability.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CCatchability::~CCatchability()
// Default De-Constructor
//**********************************************************************
CCatchability::~CCatchability() {}
