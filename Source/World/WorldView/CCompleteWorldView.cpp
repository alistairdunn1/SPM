//============================================================================
// Name        : CCompleteWorldView.cpp
// Author      : S.Rasmussen
// Date        : 15/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CCompleteWorldView.h"

#include "../../Helpers/ForEach.h"

//**********************************************************************
// CCompleteWorldView::CCompleteWorldView()
// Default Constructor
//**********************************************************************
CCompleteWorldView::CCompleteWorldView() {
  // Variables
  pWorldSquare = 0;

  // Add Default Label
  pParameterList->addParameter(PARAM_LABEL, "0");
}

//**********************************************************************
// void CCompleteWorldView::build()
// Build our Square
//**********************************************************************
void CCompleteWorldView::build() {
  try {
    // Populate our map with the different squares we have
    for (int i = 0; i < iWorldHeight; ++i)
      for (int j = 0; j < iWorldWidth; ++j) {
        CWorldSquare* pSquare = pWorld->getBaseSquare(i, j);
        if (pSquare->getEnabled())
          vWorldSquares.push_back(pSquare);
      }
  } catch (string& Ex) {
    Ex = "CCompleteWorldView.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CCompleteWorldView::execute()
// Execute
//**********************************************************************
void CCompleteWorldView::execute() {
  if (pWorldSquare != 0)
    delete pWorldSquare;

  // Populate some variables
  int iRows      = pWorld->getCategoryCount();
  int iAgeSpread = (pWorld->getMaxAge() + 1) - pWorld->getMinAge();

  // Build new Square
  pWorldSquare = new CWorldSquare();
  pWorldSquare->build();

  // Loop through the areas.
  foreach (CWorldSquare* Square, vWorldSquares) {
    for (int i = 0; i < iRows; ++i)
      for (int j = 0; j < iAgeSpread; ++j) pWorldSquare->addValue(i, j, Square->getValue(i, j));
  }
}

//**********************************************************************
// CCompleteWorldView::~CCompleteWorldView()
// Destructor
//**********************************************************************
CCompleteWorldView::~CCompleteWorldView() {
  if (pWorldSquare != 0)
    delete pWorldSquare;

  pWorldSquare = 0;
}
