//============================================================================
// Name        : CCategoricalMonotonicPreferenceFunction.cpp
// Author      : A.Dunn
// Date        : 20/04/2012
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local Headers
#include "CCategoricalMonotonicPreferenceFunction.h"

#include "../../Helpers/CComparer.h"
#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/String/Base/CCategoricalLayer.h"

//**********************************************************************
// CCategoricalMonotonicPreferenceFunction::CCategoricalMonotonicPreferenceFunction()
// Default Constructor
//**********************************************************************
CCategoricalMonotonicPreferenceFunction::CCategoricalMonotonicPreferenceFunction() {
  sType = PARAM_CATEGORICAL_MONOTONIC;

  // Register user allowed parameters
  pParameterList->registerAllowed(PARAM_CATEGORY_VALUES);
  pParameterList->registerAllowed(PARAM_CATEGORY_LABELS);
  pParameterList->registerAllowed(PARAM_LAYER);
}

//**********************************************************************
// void CCategoricalMonotonicPreferenceFunction::validate()
// Validate
//**********************************************************************
void CCategoricalMonotonicPreferenceFunction::validate() {
  try {
    // Assign local variables
    pParameterList->fillVector(vLabels, PARAM_CATEGORY_LABELS);
    pParameterList->fillVector(vValues, PARAM_CATEGORY_VALUES);
    sLayerName = pParameterList->getString(PARAM_LAYER);

    // Base Validation
    CPreferenceFunction::validate();

    for (int i = 1; i < (int)vValues.size(); i++) {
      if (vValues[i] < 0) {
        // TODO: Not a helpful error message: Should report that these values are not monotonically increasing.
        CError::errorLessThan(PARAM_CATEGORY_VALUES, PARAM_ZERO);
      }
    }
    if (vValues.size() != vLabels.size())
      CError::errorListSameSize(PARAM_CATEGORY_VALUES, PARAM_CATEGORY_LABELS);
    // Check For Duplicate Labels.
    if (CComparer::hasDuplicates(vLabels))
      CError::errorDuplicate(PARAM_CATEGORY_LABELS, getLabel());

    // Register estimables
    for (int i = 0; i < (int)vValues.size(); ++i) registerEstimable(PARAM_CATEGORY_VALUES, i, &vValues[i]);
  } catch (string& Ex) {
    Ex = "CCategoricalMonotonicPreferenceFunction.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CCategoricalMonotonicPreferenceFunction::build()
// Build our Object
//**********************************************************************
void CCategoricalMonotonicPreferenceFunction::build() {
  try {
    // Get our Layer Pointer
    CLayerManager* pLayerManager = CLayerManager::Instance();
    pLayer                       = pLayerManager->getCategoricalLayer(sLayerName);

    // Get list of layer values
    std::vector<std::string> vLayerLabels;
    for (int i = 0; i < pLayer->getHeight(); ++i) {
      for (int j = 0; j < pLayer->getWidth(); ++j) {
        vLayerLabels.push_back(pLayer->getValue(i, j));
      }
    }
    // Remove duplicates
    std::sort(vLayerLabels.begin(), vLayerLabels.end());
    vLayerLabels.erase(std::unique(vLayerLabels.begin(), vLayerLabels.end()), vLayerLabels.end());
    // Test to see if we have the correct number of labels defined
    if (vLayerLabels.size() > vLabels.size())
      CError::errorNotEnough(PARAM_CATEGORY_VALUES);
    if (vLayerLabels.size() < vLabels.size())
      CError::errorTooMuch(PARAM_CATEGORY_VALUES);

    for (int i = 0; i < (int)vLabels.size(); i++) {
      if (vLabels[i] == sLayerValue) {
        dRet = vValues[i];
        break;
      }
    }
  } catch (string& Ex) {
    Ex = "CCategoricalMonotonicPreferenceFunction.build(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// CCategoricalMonotonicPreferenceFunction::getIsStatic()
// getIsStatic
//**********************************************************************
bool CCategoricalMonotonicPreferenceFunction::getIsStatic() {
  return true;
}

//**********************************************************************
// double CCategoricalMonotonicPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
// Get Result
//**********************************************************************
double CCategoricalMonotonicPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex) {
  dRet = 0.0;

#ifndef OPTIMIZE
  try {
#endif
    // TODO: Scott to check code for efficiency
    // Function should identify the label, and then return the corresponding (cumulative) value
    sLayerValue = pLayer->getValue(TRIndex, TCIndex);

    for (int i = 0; i < (int)vLabels.size(); i++) {
      if (vLabels[i] == sLayerValue) {
        for (int j = 0; j < (i + 1); j++) {
          dRet += vValues[j];
        }
        break;
      }
    }

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CCategoricalMonotonicPreferenceFunction.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return CMath::zeroFun(pow(dRet, dAlpha), ZERO);
}
//**********************************************************************
// CCategoricalMonotonicPreferenceFunction::~CCategoricalMonotonicPreferenceFunction()
// Default De-Constructor
//**********************************************************************
CCategoricalMonotonicPreferenceFunction::~CCategoricalMonotonicPreferenceFunction() {}
