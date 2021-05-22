//============================================================================
// Name        : CAgeSize.cpp
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CAgeSize.h"

//**********************************************************************
// CAgeSize::CAgeSize()
// Default Constructor
//**********************************************************************
CAgeSize::CAgeSize()
{
}

//**********************************************************************
// void CLayer::validate()
// Validate
//**********************************************************************
void CAgeSize::validate()
{
  try
  {

    CBaseBuild::validate();
  }
  catch (string &Ex)
  {
    Ex = "CAgeSize.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAgeSize::build()
// Build our age-size relationship
//**********************************************************************
void CAgeSize::build()
{
  try
  {
  }
  catch (string &Ex)
  {
    Ex = "CAgeSize.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAgeSize::rebuild()
// Rebuild our age-size relationship
//**********************************************************************
void CAgeSize::rebuild()
{
  try
  {
  }
  catch (string &Ex)
  {
    Ex = "CAgeSize.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CAgeSize::~CAgeSize()
// Destructor
//**********************************************************************
CAgeSize::~CAgeSize()
{
}
