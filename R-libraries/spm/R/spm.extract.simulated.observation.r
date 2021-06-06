#' utility function
#'
#' @author Alistair Dunn
#'
"spm.extract.simulated.observation" <- function(lines) {
  if (missing(lines))
    stop("ERROR: Missing argument lines")
  res <- list()
  res$label <- substring(lines[1], 3, nchar(lines[1]) - 1)
  res$report.type <- "simulated_observation"
  res$observation.label <- substring(lines[4], 14)
  data <- list()
  for (i in 1:length(lines)) {
    temp <- lines[i]
    if (substring(temp, 1, 1) == "#") {
      if ("comments" %in% names(data))
        data[["comments"]] <- c(data[["comments"]], temp)
      else
        data[["comments"]] <- temp
    } else {
      temp <- spm.string.to.vector.of.words(lines[i], sep = " ")
      if (temp[1] %in% names(data)) {
        data[[temp[1]]] <- rbind(data[[temp[1]]], temp[-1])
      } else {
        data[[temp[1]]] <- temp[-1]
      }
    }
  }
  res$data <- data
  return(res)
}
