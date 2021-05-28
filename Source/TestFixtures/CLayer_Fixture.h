//============================================================================
// Name        : CLayer_Fixture.h
// Author      : S.Rasmussen
// Date        : 18/02/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifdef TEST
#ifndef CLAYER_FIXTURE_H_
#define CLAYER_FIXTURE_H_

// Local headers
#include "CWorld_Fixture.h"

//**********************************************************************
//
//
//**********************************************************************
class CLayer_Fixture : public CWorld_Fixture {
public:
  CLayer_Fixture();
  virtual ~CLayer_Fixture();
};

#endif /* CLAYER_FIXTURE_H_ */
#endif /* TEST */
