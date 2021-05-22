//============================================================================
// Name        : CSelectivity.h
// Author      : S.Rasmussen
// Date        : 14/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CSELECTIVITY_H_
#define CSELECTIVITY_H_

// Local Headers
#include "../BaseClasses/CBaseBuild.h"

//**********************************************************************
//
//
//**********************************************************************
class CSelectivity : public CBaseBuild
{
public:
  // Functions
  CSelectivity();
  virtual ~CSelectivity();
  virtual CSelectivity *clone() = 0;
  virtual double getResult(int Index) = 0;
  virtual void validate() = 0;
  virtual void build() {}
};

#endif /*CSELECTIVITY_H_*/
