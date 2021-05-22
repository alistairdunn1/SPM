//============================================================================
// Name        : CProfileFactory.cpp
// Author      : S.Rasmussen
// Date        : 12/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CProfileFactory.h"
#include "../CProfileManager.h"
#include "../CProfile.h"

//**********************************************************************
// CProfile* CProfileFactory::buildProfile(string type)
// Build a profile based on type
//**********************************************************************
CProfile *CProfileFactory::buildProfile(string type, bool registerWithManager)
{

  CProfile *pProfile = 0;

  if (type == "")
    pProfile = new CProfile();
  else
    throw string("Unknown type: " + type);

  if (registerWithManager)
    CProfileManager::Instance()->addProfile(pProfile);

  return pProfile;
}
