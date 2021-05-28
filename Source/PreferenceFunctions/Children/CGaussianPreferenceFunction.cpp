//============================================================================
// Name        : CGaussianPreferenceFunction.cpp
// Author      : C. Marsh
// Copyright   : Copyright NIWA Science �2014 - www.niwa.co.nz
//============================================================================

// Local Headers
#include "CGaussianPreferenceFunction.h"

#include "../../Helpers/CError.h"
#include "../../Helpers/CMath.h"
#include "../../Helpers/DefinedValues.h"
#include "../../Layers/CLayerManager.h"
#include "../../Layers/Numeric/Base/CNumericLayer.h"
#include "../../PDFs/CPDF.h"
#include "../../PDFs/CPDFManager.h"

//**********************************************************************
// CGaussianPreferenceFunction::CGaussianPreferenceFunction()
// Default Constructor
//**********************************************************************
CGaussianPreferenceFunction::CGaussianPreferenceFunction() {
  sType = PARAM_GAUSSIAN_COPULA;

  // Register Estimables
  registerEstimable(PARAM_RHO, &dRho);

  // Register user allowed variables
  pParameterList->registerAllowed(PARAM_RHO);
  pParameterList->registerAllowed(PARAM_PDFS);
  pParameterList->registerAllowed(PARAM_LAYERS);
}

//**********************************************************************
// void CGaussianPreferenceFunction::validate()
// Validate
//**********************************************************************
void CGaussianPreferenceFunction::validate() {
  try {
    // Assign our variables
    dRho = pParameterList->getDouble(PARAM_RHO);
    pParameterList->fillVector(vPDFNames, PARAM_PDFS);
    pParameterList->fillVector(vLayerNames, PARAM_LAYERS);

    // Validate parent
    CPreferenceFunction::validate();

    //********************************************
    //  dRho must be in [-1,1]
    //*********************************************
    if (dRho <= -1.0)
      CError::errorLessThanEqualTo(PARAM_RHO, "-1.0");
    else if (dRho >= 1.0)
      CError::errorGreaterThanEqualTo(PARAM_RHO, "1.0");

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
    Ex = "CGaussianPreferenceFunction.validate(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
}

//**********************************************************************
// void CGaussianPreferenceFunction::build()
// Build
//**********************************************************************
void CGaussianPreferenceFunction::build() {
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
// CGaussianPreferenceFunction::getIsStatic()
// getIsStatic
//**********************************************************************
bool CGaussianPreferenceFunction::getIsStatic() {
  for (int i = 0; i < (int)vLayers.size(); ++i) {
    if (!(vLayers[i]->getIsStatic()))
      return false;
  }

  return true;
}

//************************************************************************************************
//  double CGaussianPreferenceFunction::NormalInverse
//        a function that takes three parameters double quantile
//        It calculates the the inverse CDF which of the standard Normal Distribution
//        Needed to convert U1 and U2 for the Gaussian copula
//************************************************************************************************
double CGaussianPreferenceFunction::NormalInverse(double p) {
  double q, r, val;
  q = p - 0.5;
  /*-- use AS 241 --- */
  /* double ppnd16_(double *p, long *ifault)*/
  /*      ALGORITHM AS241  APPL. STATIST. (1988) VOL. 37, NO. 3
            Produces the normal deviate Z corresponding to a given lower
            tail area of P; Z is accurate to about 1 part in 10**16.
    */
  if (p <= 0.00001) {
    val = -5;  // return a large negative number (in std normal space)
  } else if (p >= 0.99999) {
    // return a large number (in std normal space)
    val = 5;
  } else if (fabs(q) <= 0.425) { /* 0.075 <= p <= 0.925 */
    r   = 0.180625 - q * q;
    val = q
          * (((((((r * 2509.0809287301226727 + 33430.575583588128105) * r + 67265.770927008700853) * r + 45921.953931549871457) * r + 13731.693765509461125) * r
               + 1971.5909503065514427)
                  * r
              + 133.14166789178437745)
                 * r
             + 3.387132872796366608)
          / (((((((r * 5226.495278852854561 + 28729.085735721942674) * r + 39307.89580009271061) * r + 21213.794301586595867) * r + 5394.1960214247511077) * r
               + 687.1870074920579083)
                  * r
              + 42.313330701600911252)
                 * r
             + 1.0);
  } else { /* closer than 0.075 from {0,1} boundary */
    /* r = min(p, 1-p) < 0.075 */
    if (q > 0.0)
      r = 1.0 - p;
    else
      r = p;
    r = sqrt(-log(r));
    /* r = sqrt(-log(r))  <==>  min(p, 1-p) = exp( - r^2 ) */
    if (r <= 5.0) { /* <==> min(p,1-p) >= exp(-25) ~= 1.3888e-11 */
      r += -1.6;
      val = (((((((r * 7.7454501427834140764e-4 + 0.0227238449892691845833) * r + 0.24178072517745061177) * r + 1.27045825245236838258) * r + 3.64784832476320460504) * r
               + 5.7694972214606914055)
                  * r
              + 4.6303378461565452959)
                 * r
             + 1.42343711074968357734)
            / (((((((r * 1.05075007164441684324e-9 + 5.475938084995344946e-4) * r + 0.0151986665636164571966) * r + 0.14810397642748007459) * r + 0.68976733498510000455) * r
                 + 1.6763848301838038494)
                    * r
                + 2.05319162663775882187)
                   * r
               + 1.0);
    } else { /* very close to  0 or 1 */
      r += -5.0;
      val = (((((((r * 2.01033439929228813265e-7 + 2.71155556874348757815e-5) * r + 0.0012426609473880784386) * r + 0.026532189526576123093) * r + 0.29656057182850489123) * r
               + 1.7848265399172913358)
                  * r
              + 5.4637849111641143699)
                 * r
             + 6.6579046435011037772)
            / (((((((r * 2.04426310338993978564e-15 + 1.4215117583164458887e-7) * r + 1.8463183175100546818e-5) * r + 7.868691311456132591e-4) * r + 0.0148753612908506148525) * r
                 + 0.13692988092273580531)
                    * r
                + 0.59983220655588793769)
                   * r
               + 1);
    }
    if (q < 0.0) {
      val = -val;
    }
  }
  return val;
}

//**********************************************************************
// double CGaussianPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex)
// getResult
//**********************************************************************
double CGaussianPreferenceFunction::getResult(int RIndex, int CIndex, int TRIndex, int TCIndex) {
  dRet = 0.0;

#ifndef OPTIMIZE
  try {
#endif

    vector<double> dValue;

    // Evaluate using copula
    double x1 = vLayers[0]->getValue(TRIndex, TCIndex, RIndex, CIndex);
    double x2 = vLayers[1]->getValue(TRIndex, TCIndex, RIndex, CIndex);

    double dPDF1 = vPDFs[0]->getPDFResult(x1);
    double dPDF2 = vPDFs[1]->getPDFResult(x2);

    double dCDF1 = vPDFs[0]->getCDFResult(x1);
    double dCDF2 = vPDFs[1]->getCDFResult(x2);

    double dI1 = NormalInverse(dCDF1);
    double dI2 = NormalInverse(dCDF2);

    dRet = 1.0 / (1.0 - dRho * dRho) * exp(-(dI1 * dI1 - 2.0 * dRho * dI1 * dI2 + dI2 * dI2) / (2.0 - 2.0 * dRho * dRho)) * exp((dI1 * dI1 + dI2 * dI2) / 2.0) * dPDF1 * dPDF2;

    // std::cerr << "x1 = " << x1 << "; x2 = " << x2 << "; PDF1 = " << dPDF1 << "; PDF2 = " << dPDF2 << "; CDF1 = " << dCDF1 << "; CDF2 = " << dCDF2 << "; I1 = " << dI1 << "; I2 =
    // " << dI2 << "; dret = " << dRet << "\n";

#ifndef OPTIMIZE
  } catch (string& Ex) {
    Ex = "CGaussianPreferenceFunction.getResult(" + getLabel() + ")->" + Ex;
    throw Ex;
  }
#endif

  return CMath::zeroFun(pow(dRet, dAlpha), ZERO);
}
//**********************************************************************
// CGaussianPreferenceFunction::~CGaussianPreferenceFunction()
// Default De-Constructor
//**********************************************************************
CGaussianPreferenceFunction::~CGaussianPreferenceFunction() {}
