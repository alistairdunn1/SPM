//============================================================================
// Name        : CKnifeEdgeSelectivity.h
// Author      : A. Dunn
// Date        : 12/03/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CKNIFEEDGESELECTIVITY_H_
#define KNIFEEDGESELECTIVITY_H_

// Local Headers
#include "../CSelectivity.h"

//**********************************************************************
//
//
//**********************************************************************
class CKnifeEdgeSelectivity : public CSelectivity {
public:
  // Functions
  CKnifeEdgeSelectivity();
  virtual ~CKnifeEdgeSelectivity();
  CSelectivity* clone() { return new CKnifeEdgeSelectivity(*this); }
  void          validate();
  double        getResult(int Param);

protected:
  // Variables
  double dE;
  double dAlpha;
};

#endif /*KNIFEEDGESELECTIVITY_H_*/
