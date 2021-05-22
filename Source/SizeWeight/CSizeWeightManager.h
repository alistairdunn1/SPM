//============================================================================
// Name        : CSizeWeightManager.h
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CSIZEWEIGHTMANAGER_H_
#define CSIZEWEIGHTMANAGER_H_

// Local header
#include "../BaseClasses/CBaseManager.h"

// Forward-Dec
class CSizeWeight;

//**********************************************************************
//
//
//**********************************************************************
class CSizeWeightManager : public CBaseManager
{
public:
  static CSizeWeightManager *Instance();
  static void Destroy();

  // Functions
  void clone(CSizeWeightManager *Manager);
  void addSizeWeight(CSizeWeight *SizeWeight);
  CSizeWeight *getSizeWeight(string label);
  void validate();
  void build();
  void rebuild();
  virtual ~CSizeWeightManager();

protected:
  // Function
  CSizeWeightManager();

  // Variables
  vector<CSizeWeight *> vSizeWeights;

private:
  // Variables
  static boost::thread_specific_ptr<CSizeWeightManager> clInstance;
};

#endif /* CSIZEWEIGHTMANAGER_H_ */
