//============================================================================
// Name        : CProcess.h
// Author      : S.Rasmussen
// Date        : 13/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CPROCESS_H_
#define CPROCESS_H_

// Local Headers
#include "../BaseClasses/CBaseExecute.h"

// Classes
class CSelectivity;

//**********************************************************************
//
//
//**********************************************************************
class CProcess : public CBaseExecute
{
public:
  // Functions
  CProcess();
  virtual ~CProcess();
  virtual CProcess *clone() = 0;
  int getCategoryCount() { return vCategoryList.size(); }
  string getCategory(int index);
  int getSelectivityCount() { return vSelectivityList.size(); }
  string getSelectivity(int index);
  virtual void validate();
  virtual void build();
  virtual void execute();
  string getProcessType() { return sType; };
  bool getRequiresMerge() { return bRequiresMerge; }

protected:
  // Variables
  vector<string> vCategoryList;
  vector<int> vCategoryIndex;
  vector<string> vSelectivityList;
  vector<CSelectivity *> vSelectivityIndex;
  vector<string> vLayerCategoryList;
  CWorldSquare *pDiff;
  int iBaseColCount;
  double dCurrent;
  double dSelectivityResult;
  string sType;
  bool bRequiresMerge;
  int iNumberOfProcesses;
};

#endif /*CPROCESS_H_*/
