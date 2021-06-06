#' Helper function for 'extract'
#'
#' @author Alistair Dunn
#' @param lines list of lines to process
#'
"extract.layer" <- function(lines) {
  if (missing(lines))
    stop("ERROR: Missing argument lines")
  index.start <- (1:length(lines))[substring(lines, 1, 1) == "["][1]
  index.end <- (1:length(lines))[substring(lines, 1, 4) == "*end"][1]
  if (index.start >= index.end)
    stop("Error")
  if (substring(lines[3 + index.start], 1, 10) == "layer.type") {
    layer.type <- substring(lines[3 + index.start], 13)
    has.layer.type <- 1
  } else {
    layer.type <- ""
    has.layer.type <- 0
  }
  if (substring(lines[5 + index.start + has.layer.type], 1, 8) == "from_row") {
    variables <- spm.string.to.vector.of.words(lines[5 + index.start + has.layer.type])
    values <- spm.string.to.vector.of.words(lines[(6 + index.start + has.layer.type):(index.end - 1)])
    nrows <- length((6 + index.start + has.layer.type):(index.end - 1))
    values <- as.data.frame(matrix(values, nrow = nrows, byrow = TRUE), stringsAsFactors = FALSE)
    names(values) <- variables
  } else {
    values <- spm.string.to.vector.of.words(lines[(5 + index.start + has.layer.type):(index.end - 1)])
    nrows <- length((5 + index.start + has.layer.type):(index.end - 1))
    values <- matrix(values, nrow = nrows, byrow = TRUE)
  }
  if (layer.type %in% c("numeric", "distance", "dijkstra", "haversine", "haversine_dijkstra")) {
    values <- t(apply(values, 1, as.numeric))
  }
  res <- list()
  res$layer <- substring(lines[index.start + 2], 8)
  res$layer.type <- layer.type
  res$year <- substring(lines[index.start + 3 + has.layer.type], 7)
  res$"time_step" <- substring(lines[index.start + 4 + has.layer.type], 12)
  res$label <- substring(lines[index.start], 2, nchar(lines[index.start]) - 1)
  res$report.type <- substring(lines[index.start + 1], 14)
  res$data <- values
  return(res)
}
