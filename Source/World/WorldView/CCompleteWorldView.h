//============================================================================
// Name        : CCompleteWorldView.h
// Author      : S.Rasmussen
// Date        : 15/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CCOMPLETEWORLDVIEW_H_
#define CCOMPLETEWORLDVIEW_H_

// Local headers
#include "../../BaseClasses/CBaseExecute.h"

// Forward-Declaration
class CWorldSquare;

//**********************************************************************
//
//
//**********************************************************************
class CCompleteWorldView : public CBaseExecute {
public:
  CCompleteWorldView();
  virtual ~CCompleteWorldView();
  CWorldSquare* getSquare() { return pWorldSquare; }
  void          build();
  void          execute();

protected:
  // Variables
  CWorldSquare*         pWorldSquare;
  vector<CWorldSquare*> vWorldSquares;
};

#endif /* CCOMPLETEWORLDVIEW_H_ */
