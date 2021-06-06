#' Helper function for 'extract'
#'
#' @author Alistair Dunn
#' @param lines list of lines to process
#'
"extract.layerderivedview" <- function(lines) {
  if (missing(lines))
    stop("ERROR: Missing argument lines")
  index.start <- (1:length(lines))[substring(lines, 1, 1) == "["][1]
  index.end <- (1:length(lines))[substring(lines, 1, 4) == "*end"][1]
  if (index.start >= index.end)
    stop("Error")
  col.labs <- spm.string.to.vector.of.words(lines[4 + index.start])
  values <- spm.string.to.vector.of.words(lines[(5 + index.start):(index.end - 1)])
  values <- as.data.frame(matrix(values, ncol = length(col.labs), byrow = TRUE), stringsAsFactors = FALSE)
  names(values) <- col.labs
  values$category <- as.character(values$category)
  values$area <- as.character(values$area)
  values[, 3:ncol(values)] <- apply(values[, 3:ncol(values)], 2, as.numeric)
  res <- list()
  res$label <- substring(lines[index.start], 2, nchar(lines[index.start]) - 1)
  res$report.type <- substring(lines[index.start + 1], 14)
  res$data <- values
  res$year <- substring(lines[index.start + 2], 7)
  res$"time_step" <- substring(lines[index.start + 3], 12)
  return(res)
}

