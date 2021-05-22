//============================================================================
// Name        : CMinimizer.cpp
// Author      : S.Rasmussen
// Date        : 2/05/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Global Headers
#define NDEBUG 1
#define BOOST_UBLAS_TYPE_CHECK 0
#define BOOST_UBLAS_SINGULAR_CHECK 1

#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <iostream>

// Local Headers
#include "CMinimizer.h"
#include "../Estimates/CEstimateManager.h"
#include "../Helpers/CError.h"
#include "../Helpers/CComparer.h"

// Using
using std::cout;
using std::endl;

//**********************************************************************
// CMinimizer::CMinimizer()
// Default Constructor
//**********************************************************************
CMinimizer::CMinimizer()
{
  // Default Variables
  pHessian = 0;
  bCovarianceError = false;

  // Register user allowed Parameters
  pParameterList->registerAllowed(PARAM_COVARIANCE);
}

//**********************************************************************
// void CMinimizer::buildCovarianceMatrix()
// Build our Covariance matrix from the Hessian
//**********************************************************************
void CMinimizer::buildCovarianceMatrix()
{

  if (pHessian == 0)
  {
    cout << "WARNING: No Hessian" << endl;
    return;
  }

  try
  {

    // Get handle to our Minimizer and Hessian
    // Locate zero rows, and set the corresponding diagonal element of the Hessian = 1
    ublas::matrix<double> mxHessian(iEstimateCount, iEstimateCount);
    vector<bool> bZeroRow;
    for (int i = 0; i < iEstimateCount; ++i)
    {
      bZeroRow.push_back(1);
      for (int j = 0; j < iEstimateCount; ++j)
      {
        mxHessian(i, j) = pHessian[i][j];
        if (!CComparer::isZero(mxHessian(i, j)))
          bZeroRow[i] = 0;
      }
      if (bZeroRow[i])
        mxHessian(i, i) = 1.0;
    }

    //TODO: Replace the following code with a better inversion algorithm

    // Convert Hessian to Covariance
    ublas::permutation_matrix<> pm(mxHessian.size1());
    ublas::matrix<double> copiedMatrix = ublas::matrix<double>(mxHessian);
    ublas::lu_factorize(copiedMatrix, pm);

    ublas::matrix<double> identityMatrix(ublas::identity_matrix<double>(copiedMatrix.size1()));
    ublas::lu_substitute(copiedMatrix, pm, identityMatrix);

    mxCovariance.swap(identityMatrix);

    mxCorrelation = mxCovariance;
    double dDiag;
    for (int i = 0; i < iEstimateCount; ++i)
    {
      dDiag = mxCorrelation(i, i);
      for (int j = 0; j < iEstimateCount; ++j)
      {
        mxCorrelation(i, j) = mxCorrelation(i, j) / sqrt(dDiag);
        mxCorrelation(j, i) = mxCorrelation(j, i) / sqrt(dDiag);
      }
    }
  }
  catch (...)
  {
    // Something went wrong.
    bCovarianceError = true;
  }
}

//**********************************************************************
// double CMinimizer::getCovarianceValue(int row, int col)
// Return our Covariance Matrix Value
//**********************************************************************
double CMinimizer::getCovarianceValue(int row, int col)
{
  if ((mxCovariance.size1() == 0) || (mxCovariance.size2() == 0))
    CError::errorMissing(PARAM_COVARIANCE);

  return mxCovariance(row, col);
}

//**********************************************************************
// double CMinimizer::getCorrelationValue(int row, int col)
// Return our Correlation Matrix Value
//**********************************************************************
double CMinimizer::getCorrelationValue(int row, int col)
{
  if ((mxCorrelation.size1() == 0) || (mxCorrelation.size2() == 0))
    CError::errorMissing(PARAM_COVARIANCE);
  return mxCorrelation(row, col);
}

//**********************************************************************
// void CMinimizer::validate()
//
//**********************************************************************
void CMinimizer::validate()
{
  try
  {
    // Base
    CBaseBuild::validate();

    // Assign our param
    bCovariance = pParameterList->getBool(PARAM_COVARIANCE, true, true);
  }
  catch (string &Ex)
  {
    Ex = "CMinimizer.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CMinimizer::build()
//
//**********************************************************************
void CMinimizer::build()
{

  CEstimateManager *pManager = CEstimateManager::Instance();
  iEstimateCount = pManager->getEnabledEstimateCount();

  pHessian = new double *[iEstimateCount];
  for (int i = 0; i < iEstimateCount; ++i)
    pHessian[i] = new double[iEstimateCount];

  for (int i = 0; i < iEstimateCount; ++i)
    for (int j = 0; j < iEstimateCount; ++j)
      pHessian[i][j] = 0.0;
}

//**********************************************************************
// CMinimizer::~CMinimizer()
// Default De-Constructor
//**********************************************************************
CMinimizer::~CMinimizer()
{
  if (pHessian != 0)
  {
    for (int i = 0; i < iEstimateCount; ++i)
      delete[] pHessian[i];
    delete[] pHessian;
  }
}
