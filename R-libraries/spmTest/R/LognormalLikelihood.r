#' Calculate the lognormal likelihood from a set of observed, expected, and error values
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
lognormalLikelihood <- function(observed, expected, errorValue, processError = 0, delta = 1e-11) {
  errorValue <- sqrt(processError ^ 2 + errorValue ^ 2)
  sigma <- sqrt(log(1 + errorValue ^ 2))
  res <- log(sigma) + 0.5 * (((log(observed / spm.zeroFun(expected, delta))) / sigma + 0.5 * sigma) ^ 2)
  return(res)
}
