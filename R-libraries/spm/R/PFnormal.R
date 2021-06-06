#' Evaluate the normal preference function
#'
#' @author Alistair Dunn
#' @param x x-values over which to evaluate. Default = 1
#' @param alpha The value of the alpha parameter. Default = 1
#' @param mu the mean of the normal
#' @param sigma the standard deviation of the normal
#' @param rescale Rescale the function to have value 1?. Default = TRUE
#' 
#' @export
#'
"PFnormal" <- function(x, alpha, mu, sigma, rescale = T) {
  pow <- function(x, y) {
    return(x ^ y)
  }
  res <- pow(2.0, - ((x - mu) / sigma * (x - mu) / sigma)) ^ alpha
  if (rescale)
    res <- res / max(res)
  return(res)
}
