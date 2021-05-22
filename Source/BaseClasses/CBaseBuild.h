//============================================================================
// Name        : CBaseBuild.h
// Author      : S.Rasmussen
// Date        : 28/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CBASEBUILD_H_
#define CBASEBUILD_H_

// Local headers
#include "CBaseValidate.h"
#include "../World/CWorld.h"
#include "../World/CWorldSquare.h"

//**********************************************************************
//
//
//**********************************************************************
class CBaseBuild : public CBaseValidate
{
public:
  CBaseBuild();
  virtual ~CBaseBuild();
  virtual void validate();
  virtual void build() = 0;
  virtual void rebuild(){};

protected:
  // Variables
  CWorld *pWorld;
  CWorldSquare *pBaseSquare;
  int iWorldWidth;
  int iWorldHeight;
};

#endif /* CBASEBUILD_H_ */
