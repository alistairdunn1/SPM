//============================================================================
// Name        : CAgeingError.h
// Author      : S.Rasmussen
// Date        : 18/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CAGEINGERROR_H_
#define CAGEINGERROR_H_

// Local headers
#include "../BaseClasses/CBaseBuild.h"

//**********************************************************************
//
//
//**********************************************************************
class CAgeingError : public CBaseBuild
{
public:
  // Functions
  CAgeingError();
  virtual ~CAgeingError();
  virtual CAgeingError *clone() { return new CAgeingError(*this); }
  void validate();
  void build();
  virtual void rebuild();
  virtual void getExpected(vector<double> &expected) {}
  int getMinAge() { return iMinAge; }
  int getMaxAge() { return iMaxAge; }
  bool getAgePlusGroup() { return bAgePlusGroup; }
  vector<vector<double>> getMisMatrix() { return mMisMatrix; }

protected:
  int iMaxAge;
  int iMinAge;
  bool bAgePlusGroup;
  int iNAges;
  vector<vector<double>> mMisMatrix;
};

#endif /* CAGEINGERROR_H_ */
