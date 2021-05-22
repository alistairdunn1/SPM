//============================================================================
// Name        : CBaseValidate.cpp
// Author      : S.Rasmussen
// Date        : 28/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global headers
#include <boost/lexical_cast.hpp>

// Local headers
#include "CBaseValidate.h"
#include "../Helpers/CError.h"
#include "../Helpers/CConvertor.h"

//**********************************************************************
// CBaseValidate::CBaseValidate()
// Default Constructor
//**********************************************************************
CBaseValidate::CBaseValidate()
{

  // Default sLabel
  sLabel = "";

  // Register Variable
  pParameterList->registerAllowed(PARAM_LABEL);
  pParameterList->registerAllowed(PARAM_TYPE);
}

//**********************************************************************
// void CBaseValidate::validate()
// Validate
//**********************************************************************
void CBaseValidate::validate()
{
  try
  {
    // Populate our variable
    sLabel = pParameterList->getString(PARAM_LABEL);

    string temp = CConvertor::stringToLowercase(sLabel);
    bool invalid_label = temp.find_first_not_of("abcdefghijklmnopqrstuvwxyz0123456789[]-_.()") != std::string::npos;
    if (invalid_label)
    {
      CError::error("The label " + sLabel + " contains invalid characters. Please ensure it is alphanumeric with the following special characters: []-_.()");
    }

    // Validate known parameters against bad ones
    pParameterList->checkInvalidParameters();
  }
  catch (string &Ex)
  {
    Ex = "CBaseValidate.validate(" + getLabel() + ")->" + Ex; // No label defined yet.
    throw Ex;
  }
}

//**********************************************************************
// CBaseValidate::~CBaseValidate()
// Destructor
//**********************************************************************
CBaseValidate::~CBaseValidate()
{
}
