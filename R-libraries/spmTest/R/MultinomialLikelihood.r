#' Calculate the multinomial likelihood from a set of observed, expected, and error values
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
multinomialLikelihood <- function(observed, expected, errorValue, processError = 0, delta = 1e-11) {
  errorValue <- ifelse(processError > 0, (1.0 / (1.0 / errorValue + 1.0 / processError)), errorValue)
  lfact <- function(n) lgamma(n + 1)
  res <- lfact(errorValue * observed) - errorValue * observed * log(spm.zeroFun(expected, delta))
  return(res)
}
