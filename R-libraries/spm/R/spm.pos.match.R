#' utility function
#'
#' @author Alistair Dunn
#'
"spm.pos.match" <- function(vector, regexp) {
  min((1:length(vector))[regexpr(regexp, vector) > 0])
}
