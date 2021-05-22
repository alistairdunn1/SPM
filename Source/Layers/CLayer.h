//============================================================================
// Name        : CLayer.h
// Author      : S.Rasmussen
// Date        : 11/02/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date$
//============================================================================
#ifndef CLAYER_H_
#define CLAYER_H_

// Local Includes
#include "../BaseClasses/CBaseBuild.h"

//**********************************************************************
//
//
//**********************************************************************
class CLayer : public CBaseBuild
{
public:
  CLayer();
  virtual ~CLayer();
  virtual CLayer *clone() = 0;
  int getWidth() { return iWidth; }
  int getHeight() { return iHeight; }
  virtual void validate();
  string getLayerType() { return sType; };
  bool getIsStatic() { return bIsStatic; }
  bool getIsZero() { return bIsZero; }

protected:
  int iWidth;
  int iHeight;
  string sType;
  bool bIsStatic;
  bool bIsZero;
};

#endif /*CLAYER_H_*/
