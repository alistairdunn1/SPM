//============================================================================
// Name        : CAgeingProcess.cpp
// Author      : S.Rasmussen
// Date        : 13/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================

// Local Headers
#include "CAgeingProcess.h"

#include "../../Helpers/CComparer.h"
#include "../../Helpers/CError.h"

//**********************************************************************
// CAgeingProcess::CAgeingProcess()
// Default Constructor
//**********************************************************************
CAgeingProcess::CAgeingProcess() {
  // Variables
  sType          = PARAM_AGEING;
  bRequiresMerge = false;

  // Register Allowed Parameters
  pParameterList->registerAllowed(PARAM_CATEGORIES);
}

//**********************************************************************
// void CAgeingProcess:validate()
// Validate This
//**********************************************************************
void CAgeingProcess::validate() {
  try {
    // populate our vector
    pParameterList->fillVector(vCategoryList, PARAM_CATEGORIES);

    // Validate parent
    CProcess::validate();

    // local validation
  } catch (string& Ex) {
    Ex = "CAgeingProcess.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAgeingProcess::build()
// Build Our Relationships and Indexes
//**********************************************************************
void CAgeingProcess::build() {
  try {
    // Call Our Base Build
    CProcess::build();
  } catch (string& Ex) {
    Ex = "CAgeingProcess.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CAgeingProcess::execute()
// execute this Process
//**********************************************************************
void CAgeingProcess::execute() {
#ifndef OPTIMIZE
  try {
#endif
    // Base Execute
    CProcess::execute();
    // Loop through World Grid (i, j)
    for (int i = 0; i < iWorldHeight; ++i) {
      for (int j = 0; j < iWorldWidth; ++j) {
        pBaseSquare = pWorld->getBaseSquare(i, j);
        if (!pBaseSquare->getEnabled())
          continue;

        // Loop Through Categories and Ages (vPtr, k)
        vector<int>::iterator vPtr = vCategoryIndex.begin();
        while (vPtr != vCategoryIndex.end()) {
          if ((iBaseColCount - 1) > 1) {
            if (pBaseSquare->getAgePlus()) {
              pBaseSquare->addValue((*vPtr), iBaseColCount - 1, pBaseSquare->getValue((*vPtr), iBaseColCount - 2));
            } else {
              pBaseSquare->setValue((*vPtr), iBaseColCount - 1, pBaseSquare->getValue((*vPtr), iBaseColCount - 2));
            }
            for (int k = (iBaseColCount - 2); k > 0; --k) {
              pBaseSquare->setValue((*vPtr), k, pBaseSquare->getValue((*vPtr), k - 1));
            }
            pBaseSquare->setValue((*vPtr), 0, 0.0);
          } else {
            if (!pBaseSquare->getAgePlus())
              pBaseSquare->setValue((*vPtr), 0, 0.0);
          }

          vPtr++;
        }
      }
    }
#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CAgeingProcess.execute(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif
}

//**********************************************************************
// CAgeingProcess::~CAgeingProcess()
// Default De-Constructor
//**********************************************************************
CAgeingProcess::~CAgeingProcess() {}
