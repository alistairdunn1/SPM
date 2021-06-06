#' Evaluate the inverse-logistic preference function
#'
#' @author Alistair Dunn
#' @param x x-values over which to evaluate. Default = 1
#' @param alpha The value of the alpha parameter. Default = 1
#' @param a50 the a50 value of the inverse logisitic
#' @param ato95 the ato95 value of the inverse logisitic
#' @param rescale Rescale the function to have value 1?. Default = TRUE
#' 
#' @export
#'
"PFinverse_logistic" <- function(x, alpha, a50, ato95, rescale = T) {
  pow <- function(x, y) {
    return(x ^ y)
  }
  temp <- (a50 - x) / ato95
  result <- ifelse(temp > 5.0, 0, -1)
  result <- ifelse(temp < -5.0, 1, result)
  result[result < 0] <- 1.0 / (1.0 + pow(19.0, temp[result < 0]))
  result <- (1 - result) ^ alpha
  if (rescale)
    result <- result / max(result)
  return(result)
}
