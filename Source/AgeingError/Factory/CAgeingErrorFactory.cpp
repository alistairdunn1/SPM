//============================================================================
// Name        : CAgeingErrorFactory.cpp
// Author      : S.Rasmussen
// Date        : 18/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CAgeingErrorFactory.h"

#include "../../Helpers/CError.h"
#include "../CAgeingError.h"
#include "../CAgeingErrorManager.h"
#include "../Children/CNormalAgeingError.h"
#include "../Children/COffByOneAgeingError.h"

//**********************************************************************
// CAgeingError* CAgeingErrorFactory::buildAgeingError(string type, bool registerWithManager)
//
//**********************************************************************
CAgeingError* CAgeingErrorFactory::buildAgeingError(string type, bool registerWithManager) {
  CAgeingError* pError = 0;

  if (type == PARAM_NONE)
    pError = new CAgeingError();
  else if (type == PARAM_OFF_BY_ONE)
    pError = new COffByOneAgeingError();
  else if (type == PARAM_NORMAL)
    pError = new CNormalAgeingError();
  else
    CError::errorUnknown(PARAM_AGEING_ERROR, type);

  if (registerWithManager)
    CAgeingErrorManager::Instance()->addAgeingError(pError);

  return pError;
}
