#' Calculate the binomial likelihood from a set of observed, expected, and error values
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
binomialLikelihood <- function(observed, expected, errorValue, processError = 0, delta = 1e-11) {
  errorValue <- ifelse(processError > 0, (1.0 / (1.0 / errorValue + 1.0 / processError)), errorValue)
  lfact <- function(n) lgamma(n + 1)
  res <- lfact(errorValue) - lfact(errorValue * (1 - observed)) - lfact(errorValue * observed) + errorValue * observed * log(spm.zeroFun(expected, delta)) + errorValue * (1 - observed) * log(spm.zeroFun(1 - expected, delta))
  return(-res)
}
