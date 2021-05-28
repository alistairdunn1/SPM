//============================================================================
// Name        : CIndependencePreferenceFunction.cpp
// Author      : C. Marsh
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
//============================================================================

// Local Headers
#include "CIndependencePreferenceFunction.h"

#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/DefinedValues.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../PDFs/CPDF.h"
#include "../../PDFs/CPDFManager.h"

//**********************************************************************
// CIndependencePreferenceFunction::CIndependencePreferenceFunction()
// Default Constructor
//**********************************************************************
CIndependencePreferenceFunction::CIndependencePreferenceFunction() {
  sType = PARAM_INDEPENDENCE_COPULA;

  // Register user allowed variables
  pParameterList->registerAllowed(PARAM_PDFS);
  pParameterList->registerAllowed(PARAM_LAYERS);
}

//**********************************************************************
// void CIndependencePreferenceFunction::validate()
// Validate
//**********************************************************************
void CIndependencePreferenceFunction::validate() {
  try {
    // Assign our variables
    pParameterList->fillVector(vPDFNames, PARAM_PDFS);
    pParameterList->fillVector(vLayerNames, PARAM_LAYERS);

    // Validate parent
    CPreferenceFunction::validate();

    //********************************************
    //  We can allow either one or two PDF's
    //*********************************************
    // Ensure either 1 or 2 PDFs
    if (!(vPDFNames.size() == 1 || vPDFNames.size() == 2))
      CError::errorNotEqual(PARAM_PDFS, "either 1 or 2");

    // Ensure exactly 2 layers
    if (vLayerNames.size() != vPDFNames.size())
      CError::errorListSameSize(PARAM_LAYERS, PARAM_PDFS);
  } catch (string& Ex) {
    Ex = "CIndependencePreferenceFunction.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CIndependencePreferenceFunction::build()
// Validate
//**********************************************************************
void CIndependencePreferenceFunction::build() {
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
// CIndependencePreferenceFunction::getIsStatic()
// getIsStatic
//**********************************************************************
bool CIndependencePreferenceFunction::getIsStatic() {
  for (int i = 0; i < (int)vLayers.size(); ++i) {
    if (!(vLayers[i]->getIsStatic()))
      return false;
  }
  return true;
}

//**********************************************************************
// double CIndependencePreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
// get Result
//**********************************************************************
double CIndependencePreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex) {
  dRet = 0.0;

#ifndef OPTIMIZE
  try {
#endif

    if (vPDFs.size() == 1) {
      double x1 = vLayers[0]->getValue(TRIndex, TCIndex, RIndex, CIndex);
      dRet      = vPDFs[0]->getPDFResult(x1);
    } else {
      double x1 = vLayers[0]->getValue(TRIndex, TCIndex, RIndex, CIndex);
      double x2 = vLayers[1]->getValue(TRIndex, TCIndex, RIndex, CIndex);

      double dPDF1 = vPDFs[0]->getPDFResult(x1);
      double dPDF2 = vPDFs[1]->getPDFResult(x2);

      dRet = dPDF1 * dPDF2;
    }

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CIndependencePreferenceFunction.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return CMath::zeroFun(pow(dRet, dAlpha), ZERO);
}
//**********************************************************************
// CCIndependencePreferenceFunction::~CIndependencePreferenceFunction()
// Default De-Constructor
//**********************************************************************
CIndependencePreferenceFunction::~CIndependencePreferenceFunction() {}
