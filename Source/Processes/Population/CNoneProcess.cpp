//============================================================================
// Name        : CNoneProcess.cpp
// Author      :
// Date        :
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
//============================================================================

// Local Headers
#include "CNoneProcess.h"

#include "../../Helpers/CComparer.h"
#include "../../Helpers/CError.h"

//**********************************************************************
// CNoneProcess::CNoneProcess()
// Default Constructor
//**********************************************************************
CNoneProcess::CNoneProcess() {
  // Variables
  sType          = PARAM_NONE;
  bRequiresMerge = false;
}

//**********************************************************************
// void CNoneProcess:validate()
// Validate This
//**********************************************************************
void CNoneProcess::validate() {}

//**********************************************************************
// void CNoneProcess::build()
// Build Our Relationships and Indexes
//**********************************************************************
void CNoneProcess::build() {}

//**********************************************************************
// void CNoneProcess::execute()
// execute this Process
//**********************************************************************
void CNoneProcess::execute() {
  CProcess::execute();
}

//**********************************************************************
// CNoneProcess::~CNoneProcess()
// Default De-Constructor
//**********************************************************************
CNoneProcess::~CNoneProcess() {}
