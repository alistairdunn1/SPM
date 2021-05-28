//============================================================================
// Name        : CGammaDiffCallback.h
// Author      : S.Rasmussen
// Date        : 8/09/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

#ifndef CGAMMADIFFCALLBACK_H_
#define CGAMMADIFFCALLBACK_H_

// Local Headers
#include "../../BaseClasses/CBaseObject.h"

// Classes
class CEstimateManager;

//**********************************************************************
//
//
//**********************************************************************
class CGammaDiffCallback : public CBaseObject {
public:
  CGammaDiffCallback();
  virtual ~CGammaDiffCallback();
  double operator()(const vector<double>& Parameters);

protected:
  // Variables
  CEstimateManager* pEstimateManager;
};

#endif /* CGAMMADIFFCALLBACK_H_ */
