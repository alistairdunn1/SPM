//============================================================================
// Name        : CAgeingError.cpp
// Author      : S.Rasmussen
// Date        : 18/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CAgeingError.h"

//**********************************************************************
// CAgeingError::CAgeingError()
// Default Constructor
//**********************************************************************
CAgeingError::CAgeingError()
{
}

//**********************************************************************
// void CLayer::validate()
// Validate
//**********************************************************************
void CAgeingError::validate()
{
  try
  {
    CBaseBuild::validate();

    // Get Variables from World
    iMinAge = pWorld->getMinAge();
    iMaxAge = pWorld->getMaxAge();
    bAgePlusGroup = pWorld->getAgePlusGroup();
    iNAges = pWorld->getAgeSpread();
  }
  catch (string &Ex)
  {
    Ex = "CAgeingError.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAgeingError::build()
// Build our Ageing Error
//**********************************************************************
void CAgeingError::build()
{
  try
  {

    // Build 2D Matrix
    mMisMatrix.resize(iNAges);

    for (int i = 0; i < iNAges; ++i)
      mMisMatrix[i].resize(iNAges, 0);
  }
  catch (string &Ex)
  {
    Ex = "CAgeingError.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAgeingError::rebuild()
// Rebuild our Ageing Error
//**********************************************************************
void CAgeingError::rebuild()
{
  try
  {
    for (int i = 0; i < (int)mMisMatrix.size(); ++i)
      for (int j = 0; j < (int)mMisMatrix[i].size(); ++j)
        mMisMatrix[i][j] = 0;
  }
  catch (string &Ex)
  {
    Ex = "CAgeingError.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CAgeingError::~CAgeingError()
// Destructor
//**********************************************************************
CAgeingError::~CAgeingError()
{
}
