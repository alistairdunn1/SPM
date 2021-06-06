#' utility function
#'
#' @author Alistair Dunn
#'
"spm.string.to.vector.of.words" <- function(string, sep = " ") {
  temp <- spm.unpaste(unlist(string), sep = sep)
  return(temp[temp != ""])
}
