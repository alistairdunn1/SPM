#' utility function
#'
#' @author Alistair Dunn
#'
"spm.recodevector" <- function(in.data, from.vals, to.vals) {
  data <- in.data
  for (count in 1:length(from.vals)) {
    data[in.data == from.vals[count]] <- to.vals[count]
  }
  return(data)
}
