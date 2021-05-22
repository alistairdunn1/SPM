//============================================================================
// Name        : CBaseBuild.cpp
// Author      : S.Rasmussen
// Date        : 28/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CBaseBuild.h"

//**********************************************************************
// CBaseBuild::CBaseBuild()
// Constructor
//**********************************************************************
CBaseBuild::CBaseBuild()
{
}

//**********************************************************************
// void CBaseBuild::validate()
// Build
//**********************************************************************
void CBaseBuild::validate()
{
  try
  {
    // Base
    CBaseValidate::validate();

    // Assign
    pWorld = CWorld::Instance();
    iWorldWidth = pWorld->getWidth();
    iWorldHeight = pWorld->getHeight();
  }
  catch (string &Ex)
  {
    Ex = "CBaseBuild.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CBaseBuild::~CBaseBuild()
// Destructor
//**********************************************************************
CBaseBuild::~CBaseBuild()
{
}
