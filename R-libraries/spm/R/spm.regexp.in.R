#' utility function
#'
#' @author Alistair Dunn
#'
"spm.regexp.in" <- function(vector, regexp) {
  if (length(vector) == 0)
    return(F)
  any(regexpr(regexp, vector) > 0)
}
