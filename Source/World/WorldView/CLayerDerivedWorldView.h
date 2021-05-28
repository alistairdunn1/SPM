//============================================================================
// Name        : CLayerDerivedWorldView.h
// Author      : S.Rasmussen
// Date        : 7/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description : This class gives us an organised snapshot of the world based
//            on a categorical layer. This allows us to organise the world into
//            categorical based pockets.
//
//            The primary use for this is observations that use string layers or
//            reporters.
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CLAYERDERIVEDWORLDVIEW_H_
#define CLAYERDERIVEDWORLDVIEW_H_

// Local headers
#include "../../BaseClasses/CBaseExecute.h"

// Forward-Declaration
class CCategoricalLayer;
class CWorldSquare;

//**********************************************************************
//
//
//**********************************************************************
class CLayerDerivedWorldView : public CBaseExecute {
public:
  CLayerDerivedWorldView(CCategoricalLayer* sourceLayer);
  virtual ~CLayerDerivedWorldView();
  CWorldSquare*         getSquare(string area);
  vector<CWorldSquare*> getWorldSquares(string area);
  void                  cleanUp();
  void                  build();
  void                  execute();

protected:
  // Variables
  CCategoricalLayer*                 pSourceLayer;
  map<string, vector<CWorldSquare*>> mvAreas;
  map<string, CWorldSquare*>         mView;
};

#endif /* CLAYERDERIVEDWORLDVIEW_H_ */
