#' Helper function for 'extract'
#'
#' @author Alistair Dunn
#' @param lines list of lines to process
#'
"extract.preferencefunction" <- function(lines) {
  if (missing(lines))
    stop("ERROR: Missing argument lines")
  index.start <- (1:length(lines))[substring(lines, 1, 1) == "["][1]
  index.end <- (1:length(lines))[substring(lines, 1, 4) == "*end"][1]
  if (index.start >= index.end)
    stop("Error")
  res <- list()
  res$label <- substring(lines[index.start], 2, nchar(lines[index.start]) - 1)
  res$report.type <- substring(lines[index.start + 1], 14)
  res$data <- list()
  count <- 0
  label <- c()
  for (i in (index.start + 2):(index.end - 1)) {
    count <- count + 1
    label <- c(label, substring(lines[i], 1, regexpr(":", lines[i]) - 1))
    value <- spm.string.to.vector.of.words(substring(lines[i], regexpr(":", lines[i]) + 2))
    old.warn <- options()$warn
    options("warn" = -1)
    new.value <- try(as.numeric(value), silent = TRUE)
    options("warn" = old.warn)
    if (any(is.na(new.value)))
      new.value <- value
    res$data[[count]] <- new.value
  }
  names(res$data) <- label
  return(res)
}
