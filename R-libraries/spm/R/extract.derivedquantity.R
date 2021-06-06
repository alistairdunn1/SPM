#' Helper function for 'extract'
#'
#' @author Alistair Dunn
#' @param lines list of lines to process
#'
"extract.derivedquantity" <- function(lines) {
  if (missing(lines))
    stop("ERROR: Missing argument lines")
  index.start <- (1:length(lines))[substring(lines, 1, 1) == "["][1]
  index.end <- (1:length(lines))[substring(lines, 1, 4) == "*end"][1]
  if (index.start >= index.end)
    stop("Error")
  res <- list()
  res$label <- substring(lines[index.start], 2, nchar(lines[index.start]) - 1)
  res$report.type <- substring(lines[index.start + 1], 14)
  res$derived_quantity.label <- substring(lines[index.start + 2], 25)
  res$data <- list()
  res$data$initialisation <- list()
  count <- 1
  for (i in index.start:index.end) {
    if (substring(lines[i], 1, 14) == "initialisation") {
      res$data$initialisation[[count]] <- spm.string.to.vector.of.numbers(substring(lines[i], regexpr(":", lines[i]) + 1))
      count <- count + 1
    }
    if (substring(lines[i], 1, 5) == "years")
      res$data$years <- spm.string.to.vector.of.numbers(substring(lines[i], 7))
    if (substring(lines[i], 1, 6) == "values")
      res$data$values <- spm.string.to.vector.of.numbers(substring(lines[i], 8))
  }
  return(res)
}
