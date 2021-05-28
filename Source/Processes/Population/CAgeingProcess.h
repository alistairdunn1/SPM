//============================================================================
// Name        : CAgeingProcess.h
// Author      : S.Rasmussen
// Date        : 13/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CAGEINGPROCESS_H_
#define CAGEINGPROCESS_H_

// Local Headers
#include "../CProcess.h"

//**********************************************************************
//
//
//**********************************************************************
class CAgeingProcess : public CProcess {
public:
  // Functions
  CAgeingProcess();
  virtual ~CAgeingProcess();
  CProcess* clone() { return new CAgeingProcess(*this); }
  void      validate();
  void      build();
  void      execute();
};

#endif /*CAGEINGPROCESS_H_*/
