//============================================================================
// Name        : CBaseValidate.h
// Author      : S.Rasmussen
// Date        : 28/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description : This is a base class for any class that requires a
//       validate function.
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CBASEVALIDATE_H_
#define CBASEVALIDATE_H_

// Local Headers
#include "CBaseObject.h"

//**********************************************************************
//
//
//**********************************************************************
class CBaseValidate : public CBaseObject {
public:
  CBaseValidate();
  virtual ~CBaseValidate();
  virtual void validate() = 0;
  string       getLabel() { return sLabel; }

protected:
  string sLabel;
};

#endif /* CBASEVALIDATE_H_ */
