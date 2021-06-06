#' Helper function for 'extract'
#'
#' @author Alistair Dunn
#' @param lines list of lines to process
#'
"extract.objectivefunction" <- function(lines) {
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
  data <- matrix(data, ncol = 2, byrow = TRUE)
  data <- data.frame("type" = data[, 1], "parameter" = data[, 1], "value" = as.numeric(data[, 2]))
  data$parameter <- as.character(data$parameter)
  tmp <- regexpr("->", data$parameter)
  data$type <- substring(data$parameter, 1, tmp - 1)
  res$total <- data$value[nrow(data)]
  data$parameter <- substring(data$parameter, tmp + 2, nchar(data$parameter) - 1)
  res$data <- data[-nrow(data),]
  return(res)
}

