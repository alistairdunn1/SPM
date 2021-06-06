#' utility function
#'
#' @author Alistair Dunn
#'
"spm.string.to.vector.of.numbers" <- function(string, sep = " ") {
  as.numeric(spm.string.to.vector.of.words(string, sep))
}
