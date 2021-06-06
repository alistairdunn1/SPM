#' utility function
#'
#' @author Alistair Dunn
#'
"spm.is.whole.number" <- function(string) {
  # this function is very dicey - works in its intended context but ...
  for (i in 1:nchar(string)) {
    digit <- substring(string, i, i)
    if (!spm.isin(digit, as.character(0:9))) {
      return(F)
    }
  }
  return(T)
}
