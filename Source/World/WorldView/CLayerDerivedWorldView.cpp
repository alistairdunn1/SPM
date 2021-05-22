//============================================================================
// Name        : CLayerDerivedWorldView.cpp
// Author      : S.Rasmussen
// Date        : 7/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CLayerDerivedWorldView.h"
#include "../../Layers/String/Base/CCategoricalLayer.h"
#include "../../Helpers/ForEach.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/DefinedValues.h"
#include "../CWorldSquare.h"

//**********************************************************************
// CLayerDerivedWorldView::CLayerDerivedWorldView(CCategoricalLayer *sourceLayer)
// Default Constructor
//**********************************************************************
CLayerDerivedWorldView::CLayerDerivedWorldView(CCategoricalLayer *sourceLayer)
{
  // Variables
  pSourceLayer = sourceLayer;

  pParameterList->addParameter(PARAM_LABEL, "0");
}

//**********************************************************************
// CWorldSquare* CLayerDerivedWorldView::getSquare(string area)
// Get A Square From our Map of Areas.
//**********************************************************************
CWorldSquare *CLayerDerivedWorldView::getSquare(string area)
{
#ifndef OPTIMIZE
  try
  {
#endif
    if (mView[area] == 0)
      CError::errorUnknown(PARAM_AREA, area);

#ifndef OPTIMIZE
  }
  catch (string &Ex)
  {
    Ex = "CLayerDerivedWorldView.getSquare(" + area + ")->" + Ex;
    throw Ex;
  }
#endif

  return mView[area];
}

//**********************************************************************
// vector<CWorldSquare*> CLayerDerivedWorldView::getWorldSquares(string area)
// Get the vector of world squares from an area in our map
//**********************************************************************
vector<CWorldSquare *> CLayerDerivedWorldView::getWorldSquares(string area)
{
  try
  {
    if (mView[area] == 0)
      CError::errorUnknown(PARAM_AREA, area);

    return mvAreas[area];
  }
  catch (string &Ex)
  {
    Ex = "CLayerDerivedWorldView.getWorldSquares(" + area + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CLayerDerivedWorldView::cleanUp()
// Clean up Our Area-Cache
//**********************************************************************
void CLayerDerivedWorldView::cleanUp()
{
  // Free Memory
  map<string, CWorldSquare *>::iterator mViewPtr = mView.begin();
  while (mViewPtr != mView.end())
  {
    delete (*mViewPtr).second;
    mViewPtr++;
  }
  mView.clear();
}

//**********************************************************************
// void CLayerDerivedWorldView::build()
// Build our Derived View of the World
//**********************************************************************
void CLayerDerivedWorldView::build()
{
  try
  {

    // Populate our map with the different squares we have
    for (int i = 0; i < iWorldHeight; ++i)
      for (int j = 0; j < iWorldWidth; ++j)
      {
        CWorldSquare *pSquare = pWorld->getBaseSquare(i, j);
        //if (pSquare->getEnabled())
        mvAreas[pSourceLayer->getValue(i, j)].push_back(pSquare);
      }
  }
  catch (string &Ex)
  {
    Ex = "CLayerDerivedWorldView.build()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CLayerDerivedWorldView::execute()
// Execute layer derived value
//**********************************************************************
void CLayerDerivedWorldView::execute()
{
  // Free any memory that has been allocated.
  cleanUp();

  // Populate some variables
  int iRows = pWorld->getCategoryCount();
  int iAgeSpread = (pWorld->getMaxAge() + 1) - pWorld->getMinAge();

  // Loop through the areas.
  map<string, vector<CWorldSquare *>>::iterator mvAreaPtr = mvAreas.begin();
  while (mvAreaPtr != mvAreas.end())
  {
    CWorldSquare *pNewSquare = new CWorldSquare();
    pNewSquare->build();

    // Loop through the squares in this area.
    foreach (CWorldSquare *Square, (*mvAreaPtr).second)
    {
      for (int i = 0; i < iRows; ++i)
        for (int j = 0; j < iAgeSpread; ++j)
          pNewSquare->addValue(i, j, Square->getValue(i, j));
    }

    // Assign Square.
    mView[(*mvAreaPtr).first] = pNewSquare;
    mvAreaPtr++;
  }
}

//**********************************************************************
// CLayerDerivedWorldView::~CLayerDerivedWorldView()
// Destructor
//**********************************************************************
CLayerDerivedWorldView::~CLayerDerivedWorldView()
{
  // Clear Memory
  cleanUp();
}
