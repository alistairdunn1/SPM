#' Evaluate the exponential preference function
#'
#' @author Alistair Dunn
#' @param x x-values over which to evaluate. Default = 1
#' @param alpha The value of the alpha parameter. Default = 1
#' @param lambda the rate of the exponential
#' @param rescale Rescale the function to have value 1?. Default = TRUE
#' 
#' @export
#'
"PFexponential" <- function(x, alpha, lambda, rescale = T) {
  res <- exp(-lambda * x) ^ alpha
  if (rescale)
    res <- res / max(res)
  return(res)
}
