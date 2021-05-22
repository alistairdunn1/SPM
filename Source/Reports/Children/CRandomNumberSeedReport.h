//============================================================================
// Name        : CRandomNumberSeedReport.h
// Author      : S.Rasmussen
// Date        : 26/03/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CRANDOMNUMBERSEEDREPORT_H_
#define CRANDOMNUMBERSEEDREPORT_H_

// Local headers
#include "Base/CFileReport.h"

//**********************************************************************
//
//
//**********************************************************************
class CRandomNumberSeedReport : public CFileReport
{
public:
  CRandomNumberSeedReport();
  virtual ~CRandomNumberSeedReport();
  CReport *clone() { return new CRandomNumberSeedReport(*this); }
  void execute();
};

#endif /* CRANDOMNUMBERSEEDREPORT_H_ */
