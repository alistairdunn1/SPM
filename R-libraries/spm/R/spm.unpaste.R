#' utility function
#'
#' @author Alistair Dunn
#'
"spm.unpaste" <- function(string, sep = " ") {
  return(unlist(strsplit(string, sep)))
}
