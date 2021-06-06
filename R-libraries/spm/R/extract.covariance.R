#' Helper function for 'extract'
#'
#' @author Alistair Dunn
#' @param lines list of lines to process
#'
"extract.covariance" <- function(lines) {
  make.matrix <- function(lines, columns) {
    data <- matrix(0, length(lines), length(lines))
    for (i in 1:length(lines)) {
      data[i,] <- spm.string.to.vector.of.numbers(lines[i])
    }
    return(data)
  }
  if (missing(lines))
    stop("ERROR: Missing argument lines")
  index.start <- (1:length(lines))[substring(lines, 1, 1) == "["][1]
  index.end <- (1:length(lines))[substring(lines, 1, 4) == "*end"][1]
  index.hessian <- (1:length(lines))[substring(lines, 1, 7) == "Hessian"][1]
  index.cov <- (1:length(lines))[substring(lines, 1, 10) == "Covariance"][1]
  index.cor <- (1:length(lines))[substring(lines, 1, 11) == "Correlation"][1]
  if (index.start >= index.end)
    stop("Error")
  res <- list()
  res$label <- substring(lines[index.start], 2, nchar(lines[index.start]) - 1)
  res$report.type <- substring(lines[index.start + 1], 14)
  res$variables <- spm.string.to.vector.of.words(lines[index.start + 2], sep = " ")
  res$variables[1] <- substring(res$variables[1], 12)
  res$hessian <- make.matrix(lines[(index.hessian + 1):(index.cov - 1)])
  res$covariance <- make.matrix(lines[(index.cov + 1):(index.cor - 1)])
  res$correlation <- make.matrix(lines[(index.cor + 1):(index.end - 1)])
  return(res)
}
