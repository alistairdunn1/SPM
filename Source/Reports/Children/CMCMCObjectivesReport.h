//============================================================================
// Name        : CMCMCReport.h
// Author      : S.Rasmussen
// Date        : 26/03/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CMCMCOBJECTIVESREPORT_H_
#define CMCMCOBJECTIVESREPORT_H_

// Local headers
#include "../../MCMC/CMCMC.h"
#include "Base/CFileReport.h"

// Forward-Declaration
class CMCMC;

//**********************************************************************
//
//
//**********************************************************************
class CMCMCObjectivesReport : public CFileReport {
public:
  CMCMCObjectivesReport();
  virtual ~CMCMCObjectivesReport();
  CReport* clone() { return new CMCMCObjectivesReport(*this); }
  void     validate();
  void     build();
  void     execute();

protected:
  string     sMCMC;
  CMCMC*     pMCMC;
  SChainItem vChain;
  bool       bWrittenHeader;
};

#endif /* CMCMCOBJECTIVESREPORT_H_ */
