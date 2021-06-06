#' Evaluate a preference function
#'
#' @author Alistair Dunn
#' @param type A type of preference function. Valid values include constant", "doublenormal", "exponential", "inverselogistic", "logistic", "normal", and "threshold"
#' @param x x-values over which to evaluate. Default = 1
#' @param alpha The value of the alpha parameter. Default = 1
#' @param ... the parameters of the preference functions
#' @param rescale Rescale the function to have value 1. Default = TRUE
#' 
#' @export
#'
"PF" <- function(type = "none", x, alpha, ..., rescale = T) {
  valid <- c("constant", "normal", "double_normal", "logistic", "inverse_logistic", "exponential", "threshold")
  if (length(type) != 1)
    stop("Only 1 preference function can be specified")
  type <- valid[pmatch(type, valid)]
  if (type == "")
    stop(paste("type must be one of", paste(valid, collapse = ", "), sep = " "))
  type <- type
  fun <- get(paste("PF", type, sep = ""))
  res <- fun(x = x, alpha = alpha, rescale = rescale, ...)
  return(res)
}
