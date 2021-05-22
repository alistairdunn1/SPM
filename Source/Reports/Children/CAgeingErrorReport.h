//============================================================================
// Name        : CAgeingErrorReport.h
// Author      : S.Rasmussen
// Date        : 26/03/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CAGEINGERRORREPORT_H_
#define CAGEINGERRORREPORT_H_

// Local headers
#include "Base/CFileReport.h"

// Forward-Declaration
class CAgeingError;

//**********************************************************************
//
//
//**********************************************************************
class CAgeingErrorReport : public CFileReport
{
public:
  CAgeingErrorReport();
  virtual ~CAgeingErrorReport();
  CReport *clone() { return new CAgeingErrorReport(*this); }
  void validate();
  void build();
  void execute();

protected:
  string sAgeingError;
  CAgeingError *pAgeingError;
};

#endif /* CAGEINGERRORREPORT_H_ */
