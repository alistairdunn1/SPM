#' Helper function for 'extract'
#'
#' @author Alistair Dunn
#' @param lines list of lines to process
#'
"extract.initialisationphase" <- function(lines) {
  if (missing(lines))
    stop("ERROR: Missing argument lines")
  index.start <- (1:length(lines))[substring(lines, 1, 1) == "["][1]
  index.end <- (1:length(lines))[substring(lines, 1, 4) == "*end"][1]
  if (index.start >= index.end)
    stop("Error")
  if (substring(lines[index.start + 4], 1, 6) == "lambda") {
    has.lambda <- TRUE
    has.year <- TRUE
    lambda <- spm.string.to.vector.of.numbers(substring(lines[index.start + 4], regexpr(":", lines[index.start + 4]) + 1))
    lambdahat <- spm.string.to.vector.of.numbers(substring(lines[index.start + 5], regexpr(":", lines[index.start + 5]) + 1))
    lambdayears <- spm.string.to.vector.of.numbers(substring(lines[index.start + 6], regexpr(":", lines[index.start + 6]) + 1))
    start.line <- 7
  } else if (substring(lines[index.start + 3], 1, 5) == "years") {
    # For backwards compatibility ... we can delete has.year at some stage in the future
    start.line <- 4
    has.lambda <- FALSE
    has.year <- TRUE
  } else {
    start.line <- 3
    has.lambda <- FALSE
    has.year <- FALSE
  }
  col.labs <- spm.string.to.vector.of.words(lines[start.line + index.start])
  values <- spm.string.to.vector.of.words(lines[(start.line + index.start + 1):(index.end - 1)])
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
  res <- list()
  res$label <- substring(lines[index.start], 2, nchar(lines[index.start]) - 1)
  res$report.type <- substring(lines[index.start + 1], 14)
  res$phase <- substring(lines[index.start + 2], 38)
  res$years <- substring(lines[index.start + 3], 8)
  if (has.lambda) {
    res$lambda <- lambda
    res$lambda.hat <- lambdahat
    res$lambda.years <- lambdayears
  } else {
    res$lambda <- NA
    res$lambda.hat <- NA
    if (has.year) res$lambda.years <- substring(lines[index.start + 3], 8)
    else res$lambda.years <- NA
  }
  res$data <- values
  return(res)
}
