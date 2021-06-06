#' Helper function for 'extract'
#'
#' @author Alistair Dunn
#' @param lines list of lines to process
#'
"extract.MCMC" <- function(lines) {
  if (missing(lines))
    stop("ERROR: Missing argument lines")
  index.start <- (1:length(lines))[substring(lines, 1, 1) == "["][1]
  index.end <- (1:length(lines))[substring(lines, 1, 4) == "*end"][1]
  if (index.start >= index.end)
    stop("Error")
  res <- list()
  res$label <- substring(lines[index.start], 2, nchar(lines[index.start]) - 1)
  res$report.type <- substring(lines[index.start + 1], 14)
  res$covariance <- spm.string.to.vector.of.numbers(spm.get.lines(lines, clip.to = "Original covariance matrix:", clip.from = "Proposal distribution covariance matrix:"))
  res$covariance <- matrix(res$covariance, nrow = sqrt(length(res$covariance)), byrow = T)
  res$proposal <- spm.string.to.vector.of.numbers(spm.get.lines(lines, clip.to = "Proposal distribution covariance matrix:", clip.from = "Cholesky decomposition matrix:"))
  res$proposal <- matrix(res$proposal, nrow = sqrt(length(res$proposal)), byrow = T)
  res$choelsky <- spm.string.to.vector.of.numbers(spm.get.lines(lines, clip.to = "Cholesky decomposition matrix:", clip.from = "MCMC objective function values:"))
  res$choelsky <- matrix(res$choelsky, nrow = sqrt(length(res$choelsky)), byrow = T)
  objectives.start <- (1:length(lines))[lines == "MCMC objective function values:"]
  objectives.end <- (1:length(lines))[lines == "MCMC samples:"]
  res$objective <- spm.make.table(lines[(objectives.start + 1):(objectives.end - 1)])
  res$samples <- spm.make.table(lines[(objectives.end + 1):(index.end - 1)])
  return(res)
}
