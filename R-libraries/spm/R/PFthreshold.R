#' Evaluate the threshold preference function
#'
#' @author Alistair Dunn
#' @param x x-values over which to evaluate. Default = 1
#' @param alpha The value of the alpha parameter. Default = 1
#' @param N the threshhold value
#' @param lambda the lambda value
#' @param rescale Rescale the function to have value 1?. Default = TRUE
#' 
#' @export
#'
"PFthreshold" <- function(x, alpha, N, lambda, rescale = T) {
  pow <- function(x, y) {
    return(x ^ y)
  }
  res <- 1.0 / (pow(x / N, lambda))
  res <- ifelse(x > N, res, 1) ^ alpha
  if (rescale)
    res <- res / max(res)
  return(res)
}
