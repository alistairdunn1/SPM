//============================================================================
// Name        : CNoneSizeWeight.cpp
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CNoneSizeWeight.h"
#include "../../Helpers/CError.h"

//**********************************************************************
// CNoneSizeWeight::CNoneSizeWeight()
// Default Constructor
//**********************************************************************
CNoneSizeWeight::CNoneSizeWeight()
{

  sType = PARAM_NONE;

  // Register user allowed parameters
}

//**********************************************************************
// voidCNoneSizeWeight::validate()
// Validate the size-weight relationship
//**********************************************************************
void CNoneSizeWeight::validate()
{
  try
  {

    // Base
    CSizeWeight::validate();

    // Local validations
  }
  catch (string &Ex)
  {
    Ex = "CNoneSizeWeight.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// voidCNoneSizeWeight::build()
// Validate the size-weight relationship
//**********************************************************************
void CNoneSizeWeight::build()
{
  try
  {
    // Base
    CSizeWeight::build();

    // Rebuild
    rebuild();
  }
  catch (string &Ex)
  {
    Ex = "CNoneSizeWeight.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// voidCNoneSizeWeight::rebuild()
// Validate the size-weight relationship
//**********************************************************************
void CNoneSizeWeight::rebuild()
{
  try
  {
    // Base
    CSizeWeight::rebuild();
  }
  catch (string &Ex)
  {
    Ex = "CNoneSizeWeight.rebuild(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CNoneSizeWeight::~CNoneSizeWeight()
// Destructor
//**********************************************************************
CNoneSizeWeight::~CNoneSizeWeight()
{
}
