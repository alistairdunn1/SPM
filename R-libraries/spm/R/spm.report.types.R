#' utility function
#'
#' @author Alistair Dunn
#'
spm.report.types <- function() {
  return(c("ageing_error",
           "age_size",
           "age_weight",
           "covariance",
           "derived_quantity",
           "derived_quantity_by_cell",
           "estimate_summary",
           "estimate_value",
           "initialisation",
           "layer",
           "layer_derived_view",
           "MCMC",
           "objective_function",
           "observation",
           "partition",
           "partition_biomass",
           "process",
           "random_number_seed",
           "selectivity",
           "simulated_observation",
           "size_weight",
           "spatial_map",
           "preference_function"))
}
