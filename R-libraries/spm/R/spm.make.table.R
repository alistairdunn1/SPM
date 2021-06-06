#' utility function
#'
#' @author Alistair Dunn
#'
"spm.make.table" <- function(lines) {
  columns <- spm.string.to.vector.of.words(lines[1])
  if (length(lines) < 2)
    return(NA)
  data <- matrix(0, length(lines) - 1, length(columns))
  for (i in 2:length(lines)) {
    data[i - 1,] <- spm.string.to.vector.of.numbers(lines[i])
  }
  data <- data.frame(data)
  names(data) <- columns
  data
}
