//============================================================================
// Name        : CAgeSizeFactory.h
// Author      : A.Dunn
// Date        : 24/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CAGESIZEFACTORY_H_
#define CAGESIZEFACTORY_H_

// Global headers
#include <string>

// Local headers
#include "../CAgeSize.h"

// Using
using std::string;

//**********************************************************************
//
//
//**********************************************************************
class CAgeSizeFactory {
public:
  // Functions
  static CAgeSize* buildAgeSize(string type, bool registerWithManager = true);

private:
  // Functions
  CAgeSizeFactory() {}
  virtual ~CAgeSizeFactory() {}
};

#endif /* CAGESIZEFACTORY_H_ */
