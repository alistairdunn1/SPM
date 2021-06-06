#' Calculate the normal likelihood from a set of observed, expected, and error values
#'
#' @author Alistair Dunn
#' @param observed The observed values for the likelihood
#' @param expected The expected values for the likelihood
#' @param errorValue The errorValues (variance estimates) for the likelihood
#' @param processError The additional process error for the likelihood
#' @param delta The robustifying constant to prevent divide by zero errors
#'
#' @export
#'
normalLikelihood <- function(observed, expected, errorValue, processError = 0, delta = 1e-11) {
  errorValue <- sqrt(processError ^ 2 + errorValue ^ 2)
  dSigma <- errorValue * expected
  dScore <- (observed - expected) / spm.zeroFun(errorValue * expected, delta)
  res <- log(dSigma) + 0.5 * (dScore ^ 2)
  return(res)
}
