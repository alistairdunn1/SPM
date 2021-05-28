//============================================================================
// Name        : CMCMCReport.h
// Author      : S.Rasmussen
// Date        : 26/03/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CMCMCREPORT_H_
#define CMCMCREPORT_H_

// Local headers
#include "../../MCMC/CMCMC.h"
#include "Base/CFileReport.h"

// Forward-Declaration
class CMCMC;

//**********************************************************************
//
//
//**********************************************************************
class CMCMCReport : public CFileReport {
public:
  CMCMCReport();
  virtual ~CMCMCReport();
  CReport* clone() { return new CMCMCReport(*this); }
  void     validate();
  void     build();
  void     execute();

protected:
  string             sMCMC;
  CMCMC*             pMCMC;
  vector<SChainItem> vChain;
};

#endif /* CMCMCREPORT_H_ */
