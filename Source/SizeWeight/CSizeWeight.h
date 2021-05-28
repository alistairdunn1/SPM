//============================================================================
// Name        : CSizeWeight.h
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CSIZEWEIGHT_H_
#define CSIZEWEIGHT_H_

// Local headers
#include "../BaseClasses/CBaseBuild.h"

//**********************************************************************
//
//
//**********************************************************************
class CSizeWeight : public CBaseBuild {
public:
  // Functions
  CSizeWeight();
  virtual ~CSizeWeight();
  virtual CSizeWeight* clone() = 0;
  void                 validate();
  void                 build();
  virtual void         rebuild();
  string               getType() { return sType; };
  virtual double       getMeanWeight(double& size, string& distribution, double& cv) = 0;
  int                  getMinAge() { return iMinAge; }
  int                  getMaxAge() { return iMaxAge; }
  bool                 getAgePlusGroup() { return bAgePlusGroup; }

protected:
  int    iMaxAge;
  int    iMinAge;
  bool   bAgePlusGroup;
  int    iNAges;
  string sType;
};

#endif /* CSIZEWEIGHT_H_ */
