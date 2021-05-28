//============================================================================
// Name        : CReportFactory.cpp
// Author      : S.Rasmussen
// Date        : 9/01/2009
// Copyright   : Copyright NIWA Science �2008 - www.niwa.co.nz
// Description :
// $Date: 2008-03-04 16:33:32 +1300 (Tue, 04 Mar 2008) $
//============================================================================

// Local headers
#include "CReportFactory.h"

#include "../CReportManager.h"
#include "../Children/CAgeSizeReport.h"
#include "../Children/CAgeWeightReport.h"
#include "../Children/CAgeingErrorReport.h"
#include "../Children/CBiomassPartitionReport.h"
#include "../Children/CCovarianceReport.h"
#include "../Children/CDerivedQuantityByCellReport.h"
#include "../Children/CDerivedQuantityReport.h"
#include "../Children/CEstimateSummaryReport.h"
#include "../Children/CEstimateValueReport.h"
#include "../Children/CInitializationReport.h"
#include "../Children/CLayerDerivedWorldViewReport.h"
#include "../Children/CLayerReport.h"
#include "../Children/CMCMCObjectivesReport.h"
#include "../Children/CMCMCReport.h"
#include "../Children/CMCMCSamplesReport.h"
#include "../Children/CObjectiveFunctionReport.h"
#include "../Children/CObservationReport.h"
#include "../Children/CPartitionReport.h"
#include "../Children/CPreferenceFunctionReport.h"
#include "../Children/CProcessReport.h"
#include "../Children/CRandomNumberSeedReport.h"
#include "../Children/CSelectivityReport.h"
#include "../Children/CSimulatedObservationReport.h"
#include "../Children/CSizeWeightReport.h"
#include "../Children/CSpatialMapReport.h"

//**********************************************************************
//
//
//**********************************************************************
CReport* CReportFactory::buildReport(string type, bool registerWithManager) {
  CReport* pReporter = 0;

  if (type == PARAM_PARTITION)
    pReporter = new CPartitionReport();
  else if (type == PARAM_PARTITION_BIOMASS)
    pReporter = new CBiomassPartitionReport();
  else if (type == PARAM_OBJECTIVE_FUNCTION)
    pReporter = new CObjectiveFunctionReport();
  else if (type == PARAM_ESTIMATE_SUMMARY)
    pReporter = new CEstimateSummaryReport();
  else if (type == PARAM_ESTIMATE_VALUE)
    pReporter = new CEstimateValueReport();
  else if (type == PARAM_OBSERVATION)
    pReporter = new CObservationReport();
  else if (type == PARAM_INITIALIZATION)
    pReporter = new CInitializationReport();
  else if (type == PARAM_DERIVED_QUANTITY_BY_CELL)
    pReporter = new CDerivedQuantityByCellReport();
  else if (type == PARAM_DERIVED_QUANTITY)
    pReporter = new CDerivedQuantityReport();
  else if (type == PARAM_RANDOM_NUMBER_SEED)
    pReporter = new CRandomNumberSeedReport();
  else if (type == PARAM_SELECTIVITY)
    pReporter = new CSelectivityReport();
  else if (type == PARAM_LAYER_DERIVED_WORLD_VIEW)
    pReporter = new CLayerDerivedWorldViewReport();
  else if (type == PARAM_PROCESS)
    pReporter = new CProcessReport();
  else if (type == PARAM_COVARIANCE)
    pReporter = new CCovarianceReport();
  else if (type == PARAM_SIMULATED_OBSERVATION)
    pReporter = new CSimulatedObservationReport();
  else if (type == PARAM_SPATIAL_MAP)
    pReporter = new CSpatialMapReport();
  else if (type == PARAM_AGEING_ERROR)
    pReporter = new CAgeingErrorReport();
  else if (type == PARAM_SIZE_WEIGHT)
    pReporter = new CSizeWeightReport();
  else if (type == PARAM_AGE_SIZE)
    pReporter = new CAgeSizeReport();
  else if (type == PARAM_AGE_WEIGHT)
    pReporter = new CAgeWeightReport();
  else if (type == PARAM_LAYER)
    pReporter = new CLayerReport();
  else if (type == PARAM_MCMC)
    pReporter = new CMCMCReport();
  else if (type == PARAM_MCMC_OBJECTIVES)
    pReporter = new CMCMCObjectivesReport();
  else if (type == PARAM_MCMC_SAMPLES)
    pReporter = new CMCMCSamplesReport();
  else if (type == PARAM_PREFERENCE_FUNCTION)
    pReporter = new CPreferenceFunctionReport();
  else
    throw string("Unknown type: " + type);

  // Add to manager if needed
  if (registerWithManager)
    CReportManager::Instance()->addReporter(pReporter);

  return pReporter;
}
