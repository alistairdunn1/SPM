//============================================================================
// Name        : CPDFManager.h
// Author      : A. Dunn
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
//============================================================================
#ifndef CPDFMANAGER_H_
#define CPDFMANAGER_H_

// Local Headers
#include "../BaseClasses/CBaseManager.h"

// Classes
class CPDF;

//**********************************************************************
//
//
//**********************************************************************
class CPDFManager : public CBaseManager
{
public:
  static CPDFManager *Instance();
  static void Destroy();

  // Functions
  void addPDF(CPDF *Function);
  int getPDFCount() { return (int)vPDFs.size(); }
  CPDF *getPDF(int index);
  CPDF *getPDF(string Label);
  void clone(CPDFManager *Manager);
  void validate();
  void build();
  virtual ~CPDFManager();

protected:
  // Functions
  CPDFManager();

  // Variables
  vector<CPDF *> vPDFs;

private:
  static boost::thread_specific_ptr<CPDFManager> clInstance;
};

#endif /*CPDFMANAGER_H_*/
