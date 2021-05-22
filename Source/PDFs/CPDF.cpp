//============================================================================
// Name        : CPDF.cpp
// Author      : A.Dunn
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
//============================================================================

// Local headers
#include "CPDF.h"
#include "../Helpers/CError.h"

//**********************************************************************
// CPDF::CPDF()
// Default Constructor
//**********************************************************************
CPDF::CPDF()
{

  sType = "";
  // Register our Estimables

  // Register User Allowed Parameters
}

//**********************************************************************
// void CPDF::validate()
// Validate
//**********************************************************************
void CPDF::validate()
{
  try
  {
    // Base Validation
    CBaseBuild::validate();

    // Populate our Parameters.
  }
  catch (string &Ex)
  {
    Ex = "CPDF.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CPDF::build()
// Build our Object
//**********************************************************************
void CPDF::build()
{
  try
  {
  }
  catch (string &Ex)
  {
    Ex = "CPDF.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CPDF::~CPDF()
// Destructor
//**********************************************************************
CPDF::~CPDF()
{
}
