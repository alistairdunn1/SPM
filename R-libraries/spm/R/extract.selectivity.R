#' Helper function for 'extract'
#'
#' @author Alistair Dunn
#' @param lines list of lines to process
#'
"extract.selectivity" <- function(lines) {
  if (missing(lines))
    stop("ERROR: Missing argument lines")
  index.start <- (1:length(lines))[substring(lines, 1, 1) == "["][1]
  index.end <- (1:length(lines))[substring(lines, 1, 4) == "*end"][1]
  if (index.start >= index.end)
    stop("Error")
  res <- list()
  res$label <- substring(lines[index.start], 2, nchar(lines[index.start]) - 1)
  res$report.type <- substring(lines[index.start + 1], 14)
  res$label <- substring(lines[index.start + 2], 8)
  data <- spm.string.to.vector.of.words(lines[(index.start + 3):(index.end - 1)])
  data <- matrix(data, ncol = 2, byrow = FALSE)
  data <- data.frame("ages" = as.numeric(data[-1, 1]), "values" = as.numeric(data[-1, 2]))
  res$data <- data
  return(res)
}

