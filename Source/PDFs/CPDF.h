//============================================================================
// Name        : CPDF.h
// Author      : A.Dunn
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
//============================================================================
#ifndef CPDF_H_
#define CPDF_H_

// Local Includes
#include "../BaseClasses/CBaseBuild.h"

// Forward Decs
class CNumericLayer;

//**********************************************************************
//
//
//**********************************************************************
class CPDF : public CBaseBuild
{
public:
  CPDF();
  virtual ~CPDF();
  virtual CPDF *clone() = 0;
  virtual double getPDFResult(double Value) = 0;
  virtual double getCDFResult(double Value) = 0;
  string getPDFType() { return sType; };
  virtual void validate();
  void build();

protected:
  // Variables
  double dRet;
  string sType;
};

#endif /* CPDF_H_ */
