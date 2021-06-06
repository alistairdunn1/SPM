#' utility function
#'
#' @author Alistair Dunn
#'
"spm.convert.to.lines" <- function(filename) {
  # note blank lines are not included - I would rather they were but am not sure how
  scan(filename, what = "", sep = "\n")
}
