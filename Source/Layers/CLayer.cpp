//============================================================================
// Name        : CLayer.cpp
// Author      : S.Rasmussen
// Date        : 11/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local Headers
#include "CLayer.h"

#include "../World/CWorld.h"

//**********************************************************************
// CLayer::CLayer()
// Default Constructor
//**********************************************************************
CLayer::CLayer() {
  sType     = "";
  bIsStatic = true;
  bIsZero   = false;
}

//**********************************************************************
// void CLayer::validate()
// Validate
//**********************************************************************
void CLayer::validate() {
  try {
    // Base
    CBaseBuild::validate();

    // Get Variables from World
    CWorld* pWorld = CWorld::Instance();
    iWidth         = pWorld->getWidth();
    iHeight        = pWorld->getHeight();
  } catch (string& Ex) {
    Ex = "CLayer.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CLayer::~CLayer()
// Default De-Constructor
//**********************************************************************
CLayer::~CLayer() {}
