#' utility function
#'
#' @author Alistair Dunn
#'
"spm.remove.last.words" <- function(string, words = 1) {
  temp <- spm.unpaste(string, sep = " ")
  to.drop <- length(temp) - (0:(words - 1))
  paste(unlist(temp[-to.drop]), collapse = " ")
}
