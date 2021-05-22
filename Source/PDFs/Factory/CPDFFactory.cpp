//============================================================================
// Name        : CPDFFactory.cpp
// Author      : S.Rasmussen
// Date        : 7/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CPDFFactory.h"
#include "../../Helpers/CError.h"
#include "../../Translations/Translations.h"
#include "../CPDFManager.h"
#include "../Children/CExponentialPDF.h"
#include "../Children/CLogNormalPDF.h"
#include "../Children/CNormalPDF.h"
#include "../Children/CUniformPDF.h"

//**********************************************************************
// CPDF* CPDFFactory::buildPDF(string type, bool registerWithManager)
// Build our buildPDF
//**********************************************************************
CPDF *CPDFFactory::buildPDF(string type, bool registerWithManager)
{

  CPDF *pFunction = 0;

  if (type == PARAM_NORMAL)
    pFunction = new CNormalPDF();
  else if (type == PARAM_LOGNORMAL)
    pFunction = new CLogNormalPDF();
  else if (type == PARAM_EXPONENTIAL)
    pFunction = new CExponentialPDF();
  else if (type == PARAM_UNIFORM)
    pFunction = new CUniformPDF();
  else
    CError::errorUnknown(PARAM_TYPE, type);
  if (registerWithManager)
    CPDFManager::Instance()->addPDF(pFunction);

  return pFunction;
}
