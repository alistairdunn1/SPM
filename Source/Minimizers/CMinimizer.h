//============================================================================
// Name        : CMinimizer.h
// Author      : S.Rasmussen
// Date        : 2/05/2008
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================
#ifndef CMINIMIZER_H_
#define CMINIMIZER_H_

// Global headers
#include <boost/numeric/ublas/matrix.hpp>

// Local headers
#include "../BaseClasses/CBaseBuild.h"

// Usings
using namespace boost::numeric;

//**********************************************************************
// class CMinimzer
//
//**********************************************************************
class CMinimizer : public CBaseBuild {
public:
  // Functions
  CMinimizer();
  virtual ~CMinimizer();
  bool                   getBuildCovariance() { return bCovariance; }
  double                 getHessianValue(int row, int col) { return pHessian[row][col]; }
  double                 getCovarianceValue(int row, int col);
  double                 getCorrelationValue(int row, int col);
  ublas::matrix<double>& getCovarianceMatrix() { return mxCovariance; }
  int                    getEstimateCount() { return iEstimateCount; }
  bool                   getCovarianceError() { return bCovarianceError; }
  void                   buildCovarianceMatrix();
  virtual void           runEstimation() = 0;
  virtual void           validate();
  virtual void           build();

protected:
  // Variables
  double**              pHessian;
  ublas::matrix<double> mxCovariance;
  ublas::matrix<double> mxCorrelation;
  int                   iEstimateCount;
  bool                  bCovariance;
  bool                  bCovarianceError;
};

#endif /*CMINIMIZER_H_*/
