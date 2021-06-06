#' Helper function for 'extract'
#'
#' @author Alistair Dunn
#' @param lines list of lines to process
#'
"extract.partition" <- function(lines) {
  if (missing(lines))
    stop("ERROR: Missing argument lines")
  index.start <- (1:length(lines))[substring(lines, 1, 1) == "["][1]
  index.end <- (1:length(lines))[substring(lines, 1, 4) == "*end"][1]
  if (index.start >= index.end)
    stop("Error")
  res <- list()
  res$label <- substring(lines[index.start], 2, nchar(lines[index.start]) - 1)
  res$report.type <- substring(lines[index.start + 1], 14)
  res$year <- substring(lines[index.start + 2], 7)
  res$"time_step" <- substring(lines[index.start + 3], 12)
  col.labs <- spm.string.to.vector.of.words(lines[4 + index.start])
  values <- spm.string.to.vector.of.words(lines[(5 + index.start):(index.end - 1)])
  values <- as.data.frame(matrix(values, ncol = length(col.labs), byrow = TRUE), stringsAsFactors = FALSE)
  names(values) <- col.labs
  values$category <- as.character(values$category)
  values$row <- as.numeric(as.character(values$row))
  values$column <- as.numeric(as.character(values$column))
  # To solve errors when age classes are of length 1
  if (length(col.labs) > 4)
    values[, 4:ncol(values)] <- apply(values[, 4:ncol(values)], 2, as.numeric)
  else
    values[, 4] <- as.numeric(values[, 4:ncol(values)])
  res$data <- values
  return(res)
}
