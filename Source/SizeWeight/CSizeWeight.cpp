//============================================================================
// Name        : CSizeWeight.cpp
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CSizeWeight.h"

//**********************************************************************
// CSizeWeight::CSizeWeight()
// Default Constructor
//**********************************************************************
CSizeWeight::CSizeWeight() {}

//**********************************************************************
// void CLayer::validate()
// Validate
//**********************************************************************
void CSizeWeight::validate() {
  try {
    CBaseBuild::validate();

    // Get Variables from World
    iMinAge       = pWorld->getMinAge();
    iMaxAge       = pWorld->getMaxAge();
    bAgePlusGroup = pWorld->getAgePlusGroup();
    iNAges        = pWorld->getAgeSpread();
  } catch (string& Ex) {
    Ex = "CSizeWeight.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CSizeWeight::build()
// Build our size-weight relationship
//**********************************************************************
void CSizeWeight::build() {
  try {
  } catch (string& Ex) {
    Ex = "CSizeWeight.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CSizeWeight::rebuild()
// Rebuild our size-weight relationship
//**********************************************************************
void CSizeWeight::rebuild() {
  try {
  } catch (string& Ex) {
    Ex = "CSizeWeight.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CSizeWeight::~CSizeWeight()
// Destructor
//**********************************************************************
CSizeWeight::~CSizeWeight() {}
