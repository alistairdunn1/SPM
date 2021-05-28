//============================================================================
// Name        : CConstantSelectivity.h
// Author      : S.Rasmussen
// Date        : 6/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CCONSTANTSELECTIVITY_H_
#define CCONSTANTSELECTIVITY_H_

// Local Headers
#include "../CSelectivity.h"

//**********************************************************************
//
//
//**********************************************************************
class CConstantSelectivity : public CSelectivity {
public:
  // Functions
  CConstantSelectivity();
  virtual ~CConstantSelectivity();
  CSelectivity* clone() { return new CConstantSelectivity(*this); }
  void          validate();
  double        getResult(int Index);

protected:
  // Variables
  double dC;
  double dAlpha;
};

#endif /*CCONSTANTSELECTIVITY_H_*/
