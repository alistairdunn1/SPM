//============================================================================
// Name        : CEstimate.h
// Author      : S.Rasmussen
// Date        : 27/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description : The estimate info class is built from the configuration
//                file parameters. It's then processed to build the
//                actual estimate objects.
// $Date: 2012-06-08 17:29:15 +1200 (Fri, 08 Jun 2012) $
//============================================================================
#ifndef CESTIMATEINFO_H_
#define CESTIMATEINFO_H_

// Headers
#include "../BaseClasses/CBaseBuild.h"

//**********************************************************************
//
//
//**********************************************************************
class CEstimateInfo : public CBaseObject {
public:
  // Methods
  CEstimateInfo();
  virtual ~CEstimateInfo();
  string getTargetParameter() { return ""; }
  void   fillSameVector(vector<string>& sames);
  void   generateEstimates();

private:
  // Members
  vector<string> vSameList;
  string         sObjectType;
  string         sObjectLabel;
  string         sObjectParameter;
  int            iObjectIndex;
};

#endif /* CESTIMATEINFO_H_ */
