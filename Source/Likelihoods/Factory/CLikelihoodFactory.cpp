//============================================================================
// Name        : CLikelihoodFactory.cpp
// Author      : S.Rasmussen
// Date        : 14/04/2009
// Copyright   : Copyright NIWA Science �2009 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CLikelihoodFactory.h"

#include "../../Helpers/CError.h"
#include "../../Translations/Translations.h"
#include "../Children/CBinomialApproxLikelihood.h"
#include "../Children/CBinomialLikelihood.h"
#include "../Children/CBinomialwithQLikelihood.h"
#include "../Children/CDirichletLikelihood.h"
#include "../Children/CLogNormalLikelihood.h"
#include "../Children/CLogNormalWithQLikelihood.h"
#include "../Children/CMultinomialLikelihood.h"
#include "../Children/CNormalLikelihood.h"
#include "../Children/CPseudoLikelihood.h"

//**********************************************************************
// CLikelihood* CLikelihoodFactory::buildLikelihood(string observationType, string type)
// Build likelihood based on type
//**********************************************************************
CLikelihood* CLikelihoodFactory::buildLikelihood(string observationType, string type) {
  CLikelihood* pLikelihood = 0;

  if (observationType == PARAM_ABUNDANCE) {
    if (type == PARAM_NORMAL)
      pLikelihood = new CNormalLikelihood();
    else if (type == PARAM_LOGNORMAL)
      pLikelihood = new CLogNormalWithQLikelihood();
    else if (type == PARAM_PSEUDO)
      pLikelihood = new CPseudoLikelihood();
    else
      CError::errorUnknown(PARAM_LIKELIHOOD, type);
  } else if (observationType == PARAM_BIOMASS) {
    if (type == PARAM_NORMAL)
      pLikelihood = new CNormalLikelihood();
    else if (type == PARAM_LOGNORMAL)
      pLikelihood = new CLogNormalWithQLikelihood();
    else if (type == PARAM_PSEUDO)
      pLikelihood = new CPseudoLikelihood();
    else
      CError::errorUnknown(PARAM_LIKELIHOOD, type);
  } else if (observationType == PARAM_PRESENCE) {
    if (type == PARAM_BINOMIAL)
      pLikelihood = new CBinomialwithQLikelihood();
    else if (type == PARAM_PSEUDO)
      pLikelihood = new CPseudoLikelihood();
    else
      CError::errorUnknown(PARAM_LIKELIHOOD, type);
  } else if (observationType == PARAM_PROPORTIONS_AT_AGE) {
    if (type == PARAM_LOGNORMAL)
      pLikelihood = new CLogNormalLikelihood();
    else if (type == PARAM_MULTINOMIAL)
      pLikelihood = new CMultinomialLikelihood();
    else if (type == PARAM_DIRICHLET)
      pLikelihood = new CDirichletLikelihood();
    else if (type == PARAM_PSEUDO)
      pLikelihood = new CPseudoLikelihood();
    else
      CError::errorUnknown(PARAM_LIKELIHOOD, type);
  } else if (observationType == PARAM_PROPORTIONS_BY_CATEGORY) {
    if (type == PARAM_BINOMIAL_APPROX)
      pLikelihood = new CBinomialApproxLikelihood();
    else if (type == PARAM_BINOMIAL)
      pLikelihood = new CBinomialLikelihood();
    else if (type == PARAM_PSEUDO)
      pLikelihood = new CPseudoLikelihood();
    else
      CError::errorUnknown(PARAM_LIKELIHOOD, type);
  } else if (observationType == PARAM_PROPORTIONS_AT_LENGTH) {
    if (type == PARAM_LOGNORMAL)
      pLikelihood = new CLogNormalLikelihood();
    else if (type == PARAM_MULTINOMIAL)
      pLikelihood = new CMultinomialLikelihood();
    else if (type == PARAM_DIRICHLET)
      pLikelihood = new CDirichletLikelihood();
    else if (type == PARAM_PSEUDO)
      pLikelihood = new CPseudoLikelihood();
    else
      CError::errorUnknown(PARAM_LIKELIHOOD, type);
  } else if (observationType == PARAM_PROPORTIONS_AT_LENGTH_BY_CATEGORY) {
    if (type == PARAM_BINOMIAL_APPROX)
      pLikelihood = new CBinomialApproxLikelihood();
    else if (type == PARAM_BINOMIAL)
      pLikelihood = new CBinomialLikelihood();
    else if (type == PARAM_PSEUDO)
      pLikelihood = new CPseudoLikelihood();
    else
      CError::errorUnknown(PARAM_LIKELIHOOD, type);
  } else
    CError::errorUnknown(PARAM_OBSERVATION, observationType);

  return pLikelihood;
}
