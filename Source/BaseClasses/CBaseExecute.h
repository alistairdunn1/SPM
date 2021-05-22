//============================================================================
// Name        : CBaseExecute.h
// Author      : S.Rasmussen
// Date        : 28/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CBASEEXECUTE_H_
#define CBASEEXECUTE_H_

// Local Headers
#include "CBaseBuild.h"

//**********************************************************************
//
//
//**********************************************************************
class CBaseExecute : public CBaseBuild
{
public:
  CBaseExecute();
  virtual ~CBaseExecute();
  virtual void validate() { CBaseBuild::validate(); }
  virtual void execute() = 0;
};

#endif /* CBASEEXECUTE_H_ */
