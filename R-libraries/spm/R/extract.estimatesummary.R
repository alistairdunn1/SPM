#' Helper function for 'extract'
#'
#' @author Alistair Dunn
#' @param lines list of lines to process
#'
"extract.estimatesummary" <- function(lines) {
  if (missing(lines))
    stop("ERROR: Missing argument lines")
  index.start <- (1:length(lines))[substring(lines, 1, 1) == "["][1]
  index.end <- (1:length(lines))[substring(lines, 1, 4) == "*end"][1]
  if (index.start >= index.end)
    stop("Error")
  res <- list()
  res$label <- substring(lines[index.start], 2, nchar(lines[index.start]) - 1)
  res$report.type <- substring(lines[index.start + 1], 14)
  data <- spm.string.to.vector.of.words(lines[(index.start + 2):(index.end - 1)], sep = " ")
  data <- matrix(data, ncol = 10, byrow = TRUE)
  data <- data.frame("parameter" = data[, 2], "lower_bound" = as.numeric(data[, 4]),
                     "upper_bound" = as.numeric(data[, 6]), "prior" = data[, 8],
                     "value" = as.numeric(data[, 10]))
  res$data <- data
  return(res)
}

