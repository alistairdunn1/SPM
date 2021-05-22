//============================================================================
// Name        : CNormalAgeingError.cpp
// Author      : S.Rasmussen
// Date        : 18/05/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CNormalAgeingError.h"
#include "../../Distributions/CNormalDistribution.h"
#include "../../Helpers/CError.h"

//**********************************************************************
// CNormalAgeingError::CNormalAgeingError()
// Default Constructor
//**********************************************************************
CNormalAgeingError::CNormalAgeingError()
{

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_CV);
  pParameterList->registerAllowed(PARAM_K);

  // Register our variables as estimable
  registerEstimable(PARAM_CV, &dCV);
}

//**********************************************************************
// voidCNormalError::validate()
// Validate the ageing error
//**********************************************************************
void CNormalAgeingError::validate()
{
  try
  {

    // Get our variables
    dCV = pParameterList->getDouble(PARAM_CV);
    iK = pParameterList->getInt(PARAM_K, true, 0);

    // Parent validation
    CAgeingError::validate();

    // Local validations
    if (dCV <= 0)
      CError::errorLessThanEqualTo(PARAM_CV, PARAM_ZERO);
    if (iK > iMaxAge)
      CError::errorGreaterThan(PARAM_K, PARAM_MAX_AGE);
  }
  catch (string &Ex)
  {
    Ex = "CNormalError.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// voidCNormalAgeingError::build()
// Validate the ageing error
//**********************************************************************
void CNormalAgeingError::build()
{
  try
  {
    // Base
    CAgeingError::build();

    // Rebuild
    rebuild();
  }
  catch (string &Ex)
  {
    Ex = "CNormalAgeingError.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CNormalAgeingError::rebuild()
// Rebuild Normal Ageing Error
//**********************************************************************
void CNormalAgeingError::rebuild()
{
  try
  {
    // Base
    CAgeingError::rebuild();

    for (int i = 0; i < iNAges; i++)
    {
      double dAge = iMinAge + i;
      for (int j = 0; j < iNAges; ++j)
      {
        double dMinAgeClass = (iMinAge + j) - 0.5;
        if (j == 0)
          mMisMatrix[i][j] = CNormalDistribution::getCDF(dMinAgeClass + 1, dAge, dAge * dCV);
        else if ((j == (iNAges - 1)) && bAgePlusGroup)
          mMisMatrix[i][j] = 1 - CNormalDistribution::getCDF(dMinAgeClass, dAge, dAge * dCV);
        else
          mMisMatrix[i][j] = CNormalDistribution::getCDF(dMinAgeClass + 1, dAge, dAge * dCV) - CNormalDistribution::getCDF(dMinAgeClass, dAge, dAge * dCV);
      }
    }
    if (iK > iMinAge)
    {
      for (int i = 0; i < (iK - iMinAge); ++i)
      {
        for (int j = 0; j < (iK - iMinAge); ++j)
        {
          mMisMatrix[i][j] = 0;
        }
        mMisMatrix[i][i] = 1;
      }
    }
  }
  catch (string &Ex)
  {
    Ex = "CNormalAgeingError.rebuild(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CNormalAgeingError::getExpected(vector<double> &expected)
// Apply ageing error
//**********************************************************************
void CNormalAgeingError::getExpected(vector<double> &expected)
{
  try
  {
    vector<double> vResult(expected.size(), 0);

    for (int i = 0; i < (int)mMisMatrix.size(); ++i)
    {
      for (int j = 0; j < (int)mMisMatrix[i].size(); ++j)
      {
        vResult[j] += expected[i] * mMisMatrix[i][j];
      }
    }

    for (int i = 0; i < (int)expected.size(); ++i)
      expected[i] = vResult[i];
  }
  catch (string &Ex)
  {
    Ex = "CNormalAgeingError.getExpected(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CNormalAgeingError::~CNormalAgeingError()
// Destructor
//**********************************************************************
CNormalAgeingError::~CNormalAgeingError()
{
}

/*
 # Normal ageing error

Expected<-c(10,20,30,20,15,5)

mMisMatrix<-Normal(min.age=3,max.age=8,dCV=0.1,iK=0,bAgePlusGroup=T)
round(mMisMatrix,5)
#        [,1]    [,2]    [,3]    [,4]    [,5]    [,6]
#[1,] 0.95221 0.04779 0.00000 0.00000 0.00000 0.00000
#[2,] 0.10565 0.78870 0.10556 0.00009 0.00000 0.00000
#[3,] 0.00135 0.15731 0.68269 0.15731 0.00135 0.00000
#[4,] 0.00002 0.00619 0.19612 0.59534 0.19612 0.00621
#[5,] 0.00000 0.00018 0.01588 0.22146 0.52495 0.23753
#[6,] 0.00000 0.00001 0.00088 0.02951 0.23559 0.73401

execute(Expected,mMisMatrix)
#11.675902 21.097643 26.756975 20.097275 13.015051  7.357153


mMisMatrix<-Normal(min.age=3,max.age=8,dCV=0.1,iK=4,bAgePlusGroup=T)
round(mMisMatrix,5)
#        [,1]    [,2]    [,3]    [,4]    [,5]    [,6]
#[1,] 1.00000 0.00000 0.00000 0.00000 0.00000 0.00000
#[2,] 0.10565 0.78870 0.10556 0.00009 0.00000 0.00000
#[3,] 0.00135 0.15731 0.68269 0.15731 0.00135 0.00000
#[4,] 0.00002 0.00619 0.19612 0.59534 0.19612 0.00621
#[5,] 0.00000 0.00018 0.01588 0.22146 0.52495 0.23753
#[6,] 0.00000 0.00001 0.00088 0.02951 0.23559 0.73401

execute(Expected,mMisMatrix)
#[1] 12.153806 20.619743 26.756972 20.097275 13.015051  7.357153


mMisMatrix<-Normal(min.age=3,max.age=8,dCV=0.1,iK=0,bAgePlusGroup=F)
round(mMisMatrix,5)
#        [,1]    [,2]    [,3]    [,4]    [,5]    [,6]
#[1,] 0.95221 0.04779 0.00000 0.00000 0.00000 0.00000
#[2,] 0.10565 0.78870 0.10556 0.00009 0.00000 0.00000
#[3,] 0.00135 0.15731 0.68269 0.15731 0.00135 0.00000
#[4,] 0.00002 0.00619 0.19612 0.59534 0.19612 0.00619
#[5,] 0.00000 0.00018 0.01588 0.22146 0.52495 0.22146
#[6,] 0.00000 0.00001 0.00088 0.02951 0.23559 0.46803

execute(Expected,mMisMatrix)
#[1] 11.675902 21.097643 26.756975 20.097275 13.015051  5.785982


mMisMatrix<-Normal(min.age=3,max.age=8,dCV=0.1,iK=4,bAgePlusGroup=F)
round(mMisMatrix,5)
#        [,1]    [,2]    [,3]    [,4]    [,5]    [,6]
#[1,] 1.00000 0.00000 0.00000 0.00000 0.00000 0.00000
#[2,] 0.10565 0.78870 0.10556 0.00009 0.00000 0.00000
#[3,] 0.00135 0.15731 0.68269 0.15731 0.00135 0.00000
#[4,] 0.00002 0.00619 0.19612 0.59534 0.19612 0.00619
#[5,] 0.00000 0.00018 0.01588 0.22146 0.52495 0.22146
#[6,] 0.00000 0.00001 0.00088 0.02951 0.23559 0.46803

execute(Expected,mMisMatrix)
#[1] 12.153806 20.619743 26.756972 20.097275 13.015051  5.785982

*/
