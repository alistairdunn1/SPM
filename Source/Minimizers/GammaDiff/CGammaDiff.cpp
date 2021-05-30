//============================================================================
// Name        : CGammaDiff.cpp
// Author      : S.Rasmussen
// Date        : 8/09/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CGammaDiff.h"

#include "../../Estimates/CEstimate.h"
#include "../../Estimates/CEstimateManager.h"
#include "CGammaDiffCallback.h"
#include "Engine/GammaDiffEngine.h"

//**********************************************************************
// CGammaDiff::CGammaDiff()
// Default Constructor
//**********************************************************************
CGammaDiff::CGammaDiff() {
  // Register Allowed Parameters
  pParameterList->registerAllowed(PARAM_MAX_ITERATIONS);
  pParameterList->registerAllowed(PARAM_MAX_EVALUATIONS);
  pParameterList->registerAllowed(PARAM_TOLERANCE);
  pParameterList->registerAllowed(PARAM_STEPSIZE);
  pParameterList->registerAllowed(PARAM_TRANSFORM_METHOD);
}

//**********************************************************************
// void CGammaDiff::validate()
// Validate our Minimizer
//**********************************************************************
void CGammaDiff::validate() {
  try {
    CMinimizer::validate();

    // Get Variables
    iMaxIterations     = pParameterList->getInt(PARAM_MAX_ITERATIONS, true, 1000);
    iMaxEvaluations    = pParameterList->getInt(PARAM_MAX_EVALUATIONS, true, 4000);
    dGradientTolerance = pParameterList->getDouble(PARAM_TOLERANCE, true, 0.002);
    dStepSize          = pParameterList->getDouble(PARAM_STEPSIZE, true, 1e-6);
    sTransformMethod   = pParameterList->getString(PARAM_TRANSFORM_METHOD, true, PARAM_TRANSFORM_ASIN);
    // dStepSize default is 1e-7 = pow(10.0,-14/2.0)
    // using modified version of Dennis & Schnabel's FDGRAD here with digits=14

  } catch (string& Ex) {
    Ex = "CGammaDiff.validate()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CGammaDiff::runEstimation()void CGammaDiff::runEstimation()
// Run the Estimation through our Minimizer
//**********************************************************************
void CGammaDiff::runEstimation() {
  try {
    // Variables
    CGammaDiffCallback clGammaDiffCallback;
    CEstimateManager*  pEstimateManager = CEstimateManager::Instance();
    vector<double>     vStartValues;
    vector<double>     vLowerBounds;
    vector<double>     vUpperBounds;

    // Get our Variables, Upper and Lower Bounds From
    // The EstimateManager
    int iCount = pEstimateManager->getEnabledEstimateCount();

    for (int i = 0; i < iCount; ++i) {
      CEstimate* pEstimate = pEstimateManager->getEnabledEstimate(i);

      vStartValues.push_back(pEstimate->getValue());
      vLowerBounds.push_back(pEstimate->getLowerBound());
      vUpperBounds.push_back(pEstimate->getUpperBound());
    }

    int status = 0;

    // Setup copies of our variables for return information
    int iMaxIters = iMaxIterations;
    int iMaxEvals = iMaxEvaluations;

    GammaDiffEngine clGammaDiff;
    clGammaDiff.optimise_finite_differences(clGammaDiffCallback, vStartValues, vLowerBounds, vUpperBounds, status, iMaxIters, iMaxEvals, dGradientTolerance, pHessian, 1, dStepSize,
                                            sTransformMethod);
  } catch (string& Ex) {
    Ex = "CGammaDiff.runEstimation()->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CGammaDiff::~CGammaDiff()
// Default Destructor
//**********************************************************************
CGammaDiff::~CGammaDiff() {}
