//============================================================================
// Name        : CConstantMortalityRateProcess.h
// Author      : S.Rasmussen
// Date        : 15/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CAGEMORTALITYRATEPROCESS_H_
#define CAGEMORTALITYRATEPROCESS_H_

// Local headers
#include "../CProcess.h"

// Forward-Dec
class CNumericLayer;
class CLayerManager;

//**********************************************************************
//
//
//**********************************************************************
class CAgeMortalityRateProcess : public CProcess
{
public:
  // Functions
  CAgeMortalityRateProcess();
  virtual ~CAgeMortalityRateProcess();
  CProcess *clone() { return new CAgeMortalityRateProcess(*this); }
  void validate();
  void build();
  void rebuild();
  void execute();

protected:
  // Variables
  vector<double> vMortalityRates;
  CWorldSquare **pGrid;
  CNumericLayer *pLayer;
  string sLayer;
};

#endif /* CAGEMORTALITYRATEPROCESS_H_ */
