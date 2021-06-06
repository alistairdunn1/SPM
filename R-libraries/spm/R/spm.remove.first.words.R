#' utility function
#'
#' @author Alistair Dunn
#'
"spm.remove.first.words" <- function(string, words = 1) {
  paste(spm.unpaste(string, sep = " ")[-(1:words)], collapse = " ")
}
