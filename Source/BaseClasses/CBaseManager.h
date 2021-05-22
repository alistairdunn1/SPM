//============================================================================
// Name        : CBaseManager.h
// Author      : S.Rasmussen
// Date        : 27/01/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description : This is a base class for all the managers.
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CBASEMANAGER_H_
#define CBASEMANAGER_H_

// Global Headers
#include <vector>
#include <string>
#include <boost/thread/tss.hpp>
#include <boost/thread/mutex.hpp>

// Local Headers
#include "CBaseObject.h"

// Namespaces
using std::string;
using std::vector;

//**********************************************************************
//
//
//**********************************************************************
class CBaseManager : public CBaseObject
{
public:
  CBaseManager();
  virtual ~CBaseManager();
  virtual void validate() = 0;
  virtual void build() = 0;
  virtual void rebuild() {}
};

#endif /* CBASEMANAGER_H_ */
