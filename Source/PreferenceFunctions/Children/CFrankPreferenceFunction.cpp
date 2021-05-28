//============================================================================
// Name        : CFrankPreferenceFunction.cpp
// Author      : C. Marsh
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
//============================================================================

// Local Headers
#include "CFrankPreferenceFunction.h"

#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/DefinedValues.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../PDFs/CPDF.h"
#include "../../PDFs/CPDFManager.h"

//**********************************************************************
// CFrankPreferenceFunction::CFrankPreferenceFunction()
// Default Constructor
//**********************************************************************
CFrankPreferenceFunction::CFrankPreferenceFunction() {
  sType = PARAM_FRANK_COPULA;

  // Register Estimables
  registerEstimable(PARAM_RHO, &dRho);

  // Register user allowed variables
  pParameterList->registerAllowed(PARAM_RHO);
  pParameterList->registerAllowed(PARAM_PDFS);
  pParameterList->registerAllowed(PARAM_LAYERS);
}

//**********************************************************************
// void CFrankPreferenceFunction::validate()
// Validate
//**********************************************************************
void CFrankPreferenceFunction::validate() {
  try {
    // Assign our variables
    dRho = pParameterList->getDouble(PARAM_RHO);
    pParameterList->fillVector(vPDFNames, PARAM_PDFS);
    pParameterList->fillVector(vLayerNames, PARAM_LAYERS);

    // Validate parent
    CPreferenceFunction::validate();

    //********************************************
    //  dRho must be in !0
    //*********************************************
    if (dRho == 0.0)
      CError::errorNotEqual(PARAM_RHO, "0.0");

    //********************************************
    //  We allow only two PDF's
    //*********************************************
    // Ensure exactly 2 PDFs
    if (vPDFNames.size() != 2)
      CError::errorNotEqual(PARAM_PDFS, "two");

    // Ensure exactly 2 layers
    if (vLayerNames.size() != 2)
      CError::errorNotEqual(PARAM_LAYERS, "two");
  } catch (string& Ex) {
    Ex = "CFrankPreferenceFunction.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CFrankPreferenceFunction::build()
// Build
//**********************************************************************
void CFrankPreferenceFunction::build() {
  // Build parent
  CPreferenceFunction::build();

  // Get PDFs
  CPDFManager* pPDFManager = CPDFManager::Instance();

  for (int i = 0; i < (int)vPDFNames.size(); ++i) {
    vPDFs.push_back(pPDFManager->getPDF(vPDFNames[i]));
    vPDFTypes.push_back(vPDFs[i]->getPDFType());
  }

  // Get Layers
  CLayerManager* pLayerManager = CLayerManager::Instance();

  for (int i = 0; i < (int)vLayerNames.size(); ++i) {
    vLayers.push_back(pLayerManager->getNumericLayer(vLayerNames[i]));
  }
}

//**********************************************************************
// CFrankPreferenceFunction::getIsStatic()
// getIsStatic
//**********************************************************************
bool CFrankPreferenceFunction::getIsStatic() {
  for (int i = 0; i < (int)vLayers.size(); ++i) {
    if (!(vLayers[i]->getIsStatic()))
      return false;
  }
  return true;
}

//**********************************************************************
// double CFrankPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
// get Result
//**********************************************************************
double CFrankPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex) {
  dRet = 0.0;

#ifndef OPTIMIZE
  try {
#endif

    vector<double> dValue;

    double x1 = vLayers[0]->getValue(TRIndex, TCIndex, RIndex, CIndex);
    double x2 = vLayers[1]->getValue(TRIndex, TCIndex, RIndex, CIndex);

    // Evaluate using Frank copula

    double dPDF1 = vPDFs[0]->getPDFResult(x1);
    double dPDF2 = vPDFs[1]->getPDFResult(x2);

    double dCDF1 = vPDFs[0]->getCDFResult(x1);
    double dCDF2 = vPDFs[1]->getCDFResult(x2);

    dRet = (dRho * exp(-dRho * dCDF1) * exp(-dRho * dCDF2)) / (exp(-dRho) - 1) * (1 / (1 + ((exp(-dRho * dCDF1) - 1) * (exp(-dRho * dCDF2) - 1) / (exp(-dRho) - 1))))
           * (((exp(-dRho * dCDF1) - 1) * (exp(-dRho * dCDF2) - 1)) / (exp(-dRho) - 1) * (1 / (1 + ((exp(-dRho * dCDF1) - 1) * (exp(-dRho * dCDF2) - 1) / (exp(-dRho) - 1)))) - 1)
           * dPDF1 * dPDF2;

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CFrankPreferenceFunction.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return CMath::zeroFun(pow(dRet, dAlpha), ZERO);
}
//**********************************************************************
// CFrankPreferenceFunction::~CFrankPreferenceFunction()
// Default De-Constructor
//**********************************************************************
CFrankPreferenceFunction::~CFrankPreferenceFunction() {}
