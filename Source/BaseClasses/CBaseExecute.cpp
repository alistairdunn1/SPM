//============================================================================
// Name        : CBaseExecute.cpp
// Author      : S.Rasmussen
// Date        : 28/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CBaseExecute.h"

//**********************************************************************
// CBaseExecute::CBaseExecute()
// Default Constructor
//**********************************************************************
CBaseExecute::CBaseExecute()
{
  // Get Singletone Instance
  pWorld = CWorld::Instance();
}

//**********************************************************************
// CBaseExecute::~CBaseExecute()
// Destructor
//**********************************************************************
CBaseExecute::~CBaseExecute()
{
}
