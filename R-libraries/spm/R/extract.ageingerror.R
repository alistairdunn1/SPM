#' Helper function for 'extract'
#'
#' @author Alistair Dunn
#' @param lines list of lines to process
#'
"extract.ageingerror" <- function(lines) {
  if (missing(lines))
    stop("ERROR: Missing argument lines")
  index.start <- (1:length(lines))[substring(lines, 1, 1) == "["][1]
  index.end <- (1:length(lines))[substring(lines, 1, 4) == "*end"][1]
  if (index.start >= index.end)
    stop("Error")
  res <- list()
  res$label <- substring(lines[index.start], 2, nchar(lines[index.start]) - 1)
  res$report.type <- substring(lines[index.start + 1], 14)
  res$type <- substring(lines[index.start + 2], 7)
  col.labs <- spm.string.to.vector.of.words(lines[3 + index.start])[-1]
  col.labs[1] <- substring(col.labs[1], regexpr(":", col.labs[1]) + 2)
  values <- spm.string.to.vector.of.words(lines[(4 + index.start):(index.end - 1)])
  values <- as.data.frame(matrix(values, ncol = length(col.labs) + 1, byrow = TRUE), stringsAsFactors = FALSE)[, -1]
  names(values) <- col.labs
  values <- apply(values, 2, as.numeric)
  res$data <- values
  return(res)
}
