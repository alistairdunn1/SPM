#' Evaluate the double normal preference function
#'
#' @author Alistair Dunn
#' @param x x-values over which to evaluate. Default = 1
#' @param alpha The value of the alpha parameter. Default = 1
#' @param mu the mean of the double normal
#' @param sigmaL the standard deviation of the left-hand side of the double normal
#' @param sigmaR the standard deviation of the right-hand side of the double normal
#' @param rescale Rescale the function to have value 1?. Default = TRUE
#' 
#' @export
#'
"PFdouble_normal" <- function(x, alpha, mu, sigmaL, sigmaR, rescale = T) {
  pow <- function(x, y) {
    return(x ^ y)
  }
  res1 <- pow(2.0, - ((x - mu) / sigmaL * (x - mu) / sigmaL)) ^ alpha
  res2 <- pow(2.0, - ((x - mu) / sigmaR * (x - mu) / sigmaR)) ^ alpha
  res <- ifelse(x < mu, res1, res2)
  if (rescale)
    res <- res / max(res)
  return(res)
}
