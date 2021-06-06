#' utility function
#'
#' @author Alistair Dunn
#'
"spm.pos" <- function(vector, x) {
  min((1:length(vector))[vector == x])
}
