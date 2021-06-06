#' Helper function for 'extract'
#'
#' @author Alistair Dunn
#' @param lines list of lines to process
#'
"extract.spatialmap" <- function(lines) {
  if (missing(lines))
    stop("ERROR: Missing argument lines")
  index.start <- (1:length(lines))[substring(lines, 1, 1) == "["][1]
  index.end <- (1:length(lines))[substring(lines, 1, 4) == "*end"][1]
  if (index.start >= index.end)
    stop("Error")
  values <- spm.string.to.vector.of.words(lines[(2 + index.start):(index.end - 1)], sep = " ")
  nrows <- length((2 + index.start):(index.end - 1))
  values <- matrix(values, nrow = nrows, byrow = TRUE)
  res <- list()
  res$label <- substring(lines[index.start], 2, nchar(lines[index.start]) - 1)
  res$report.type <- substring(lines[index.start + 1], 14)
  res$data <- values
  return(res)
}
