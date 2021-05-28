//============================================================================
// Name        : CAgeSizeManager.h
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CAGESIZEMANAGER_H_
#define CAGESIZEMANAGER_H_

// Local header
#include "../BaseClasses/CBaseManager.h"

// Forward-Dec
class CAgeSize;

//**********************************************************************
//
//
//**********************************************************************
class CAgeSizeManager : public CBaseManager {
public:
  static CAgeSizeManager* Instance();
  static void             Destroy();

  // Functions
  void      clone(CAgeSizeManager* Manager);
  void      addAgeSize(CAgeSize* AgeSize);
  CAgeSize* getAgeSize(string label);
  void      validate();
  void      build();
  void      rebuild();
  virtual ~CAgeSizeManager();

protected:
  // Function
  CAgeSizeManager();

  // Variables
  vector<CAgeSize*> vAgeSizes;

private:
  // Variables
  static boost::thread_specific_ptr<CAgeSizeManager> clInstance;
};

#endif /* CAGESIZEMANAGER_H_ */
