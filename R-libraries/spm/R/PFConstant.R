#' Evaluate the constant preference function
#'
#' @author Alistair Dunn
#' @param x x-values over which to evaluate. Default = 1
#' @param alpha The value of the alpha parameter. Default = 1
#' @param rescale Rescale the function to have value 1?. Default = TRUE
#' 
#' @export
#'
"PFconstant" <- function(x, alpha, rescale = T) {
  res <- x ^ alpha
  if (rescale)
    res <- res / max(res)
  return(res)
}
