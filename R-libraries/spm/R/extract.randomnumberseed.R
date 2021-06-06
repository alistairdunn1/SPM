#' Helper function for 'extract'
#'
#' @author Alistair Dunn
#' @param lines list of lines to process
#'
"extract.randomnumberseed" <- function(lines) {
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
  res$data <- data[2]
  return(res)
}

