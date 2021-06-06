#' utility function
#'
#' @author Alistair Dunn
#'
spm.zeroFun <- function(x, delta = 1e-11) {
  res <- ifelse(x >= delta, x, delta / (2 - (x / delta)))
  return(res)
}
