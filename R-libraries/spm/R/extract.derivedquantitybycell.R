#' Helper function for 'extract'
#'
#' @author Alistair Dunn
#' @param lines list of lines to process
#'
"extract.derivedquantitybycell" <- function(lines) {
  if (missing(lines))
    stop("ERROR: Missing argument lines")
  index.start <- (1:length(lines))[substring(lines, 1, 1) == "["][1]
  index.end <- (1:length(lines))[substring(lines, 1, 4) == "*end"][1]
  if (index.start >= index.end)
    stop("Error")
  res <- list()
  res$label <- substring(lines[index.start], 2, nchar(lines[index.start]) - 1)
  res$report.type <- substring(lines[index.start + 1], 14)
  res$derived_quantity_by_cell.label <- substring(lines[index.start + 2], 8)
  row.column <- as.vector(unlist(spm.string.to.vector.of.numbers(substring(lines[index.start + 3], 12))))
  res$data <- list()
  res$initialisation <- list()
  init.count <- 1
  count <- 1
  for (i in index.start:index.end) {
    if (substring(lines[i], 1, 14) == "initialisation") {
      res$initialisation[[init.count]] <- list()
      res$initialisation[[init.count]]$year <- substring(lines[i], regexpr(":", lines[i]) + 2)
      res$initialisation[[init.count]]$values <- matrix(NA, nrow = row.column[1], ncol = row.column[2])
      for (j in 1:row.column[1])
        res$initialisation[[init.count]]$values[j,] <- spm.string.to.vector.of.numbers(lines[i + j])
      init.count <- init.count + 1
    }
    if (substring(lines[i], 1, 4) == "year") {
      res$data[[count]] <- list()
      res$data[[count]]$year <- substring(lines[i], regexpr(":", lines[i]) + 2)
      res$data[[count]]$values <- matrix(NA, nrow = row.column[1], ncol = row.column[2])
      for (j in 1:row.column[1])
        res$data[[count]]$values[j,] <- spm.string.to.vector.of.numbers(lines[i + j])
      count <- count + 1
    }
  }
  return(res)
}
