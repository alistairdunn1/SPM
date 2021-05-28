//============================================================================
// Name        : CConstantMortalityRateProcess.h
// Author      : S.Rasmussen
// Date        : 15/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CCONSTANTMORTALITYRATEPROCESS_H_
#define CCONSTANTMORTALITYRATEPROCESS_H_

// Local headers
#include "../CProcess.h"

// Forward-Dec
class CNumericLayer;
class CLayerManager;

//**********************************************************************
//
//
//**********************************************************************
class CConstantMortalityRateProcess : public CProcess {
public:
  // Functions
  CConstantMortalityRateProcess();
  virtual ~CConstantMortalityRateProcess();
  CProcess* clone() { return new CConstantMortalityRateProcess(*this); }
  void      validate();
  void      build();
  void      rebuild();
  void      execute();

protected:
  // Variables
  vector<double> vMortalityRates;
  CWorldSquare** pGrid;
  CNumericLayer* pLayer;
  string         sLayer;
};

#endif /* CCONSTANTMORTALITYRATEPROCESS_H_ */
