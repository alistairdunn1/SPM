#' utility function
#'
#' @author Alistair Dunn
#'
"spm.isin" <- function(x, y) {
  !is.na(match(x, y))
}
