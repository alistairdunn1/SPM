//============================================================================
// Name        : GammaDiffEngine.h
// Author      : S.Rasmussen
// Date        : 21/08/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

#ifndef GAMMADIFFENGINE_H_
#define GAMMADIFFENGINE_H_

// Global Headers
#include "../../../BaseClasses/CBaseObject.h"
#include "../CGammaDiffCallback.h"

//**********************************************************************
//
//
//**********************************************************************
class GammaDiffEngine : public CBaseObject {
public:
  GammaDiffEngine();
  virtual ~GammaDiffEngine();
  double optimise_finite_differences(CGammaDiffCallback& objective, vector<double>& StartValues, vector<double>& LowerBounds, vector<double>& UpperBounds, int& convergence,
                                     int& iMaxIter, int& iMaxFunc, double dGradTol, double** pOptimiseHessian, int untransformedHessians, double dStepSize, string transformMethod);

private:
  // Variables
  vector<double> vStartValues;
  vector<double> vLowerBounds;
  vector<double> vUpperBounds;
  vector<double> vScaledValues;
  vector<double> vCurrentValues;
  vector<double> vGradientValues;
  double         dPenalty;
  string         sTransformMethod;

  // Functions
  void   buildScaledValues();
  void   buildCurrentValues();
  double scaleValue(double value, double min, double max);
  double unScaleValue(const double& value, double min, double max);
  void   condAssign(double& res, const double& cond, const double& arg1, const double& arg2);
  void   condAssign(double& res, const double& cond, const double& arg);
};

#endif /* GAMMADIFFENGINE_H_ */
