#' Helper function for 'extract'
#'
#' @author Alistair Dunn
#' @param lines list of lines to process
#'
"extract.observation" <- function(lines) {
  if (missing(lines))
    stop("ERROR: Missing argument lines")
  index.start <- (1:length(lines))[substring(lines, 1, 1) == "["][1]
  index.end <- (1:length(lines))[substring(lines, 1, 4) == "*end"][1]
  if (index.start >= index.end)
    stop("Error")
  res <- list()
  res$report.type <- substring(lines[index.start + 1], 14)
  res$label <- substring(lines[index.start + 2], 8)
  res$type <- substring(lines[index.start + 3], 7)
  if (res$type == "abundance") {
    res$year <- as.numeric(substring(lines[index.start + 4], 7))
    res$time_step <- substring(lines[index.start + 5], 12)
    res$catchability <- substring(lines[index.start + 6], 15)
    this.line <- index.start + 6
  } else if (res$type == "biomass") {
    res$year <- as.numeric(substring(lines[index.start + 4], 7))
    res$time_step <- substring(lines[index.start + 5], 12)
    res$catchability <- substring(lines[index.start + 6], 15)
    this.line <- index.start + 6
  } else if (res$type == "presence") {
    res$year <- as.numeric(substring(lines[index.start + 4], 7))
    res$time_step <- substring(lines[index.start + 5], 12)
    res$catchability <- substring(lines[index.start + 6], 15)
    this.line <- index.start + 6
  } else if (res$type == "proportions_at_age") {
    res$year <- as.numeric(substring(lines[index.start + 4], 7))
    res$time_step <- substring(lines[index.start + 5], 12)
    res$min_age <- as.numeric(substring(lines[index.start + 6], 10))
    res$max_age <- substring(lines[index.start + 7], 10)
    res$age_plus_group <- substring(lines[index.start + 8], 17)
    this.line <- index.start + 8
  } else if (res$type == "proportions_by_category") {
    res$year <- as.numeric(substring(lines[index.start + 4], 7))
    res$time_step <- substring(lines[index.start + 5], 12)
    res$min_age <- as.numeric(substring(lines[index.start + 6], 10))
    res$max_age <- substring(lines[index.start + 7], 10)
    res$age_plus_group <- substring(lines[index.start + 8], 17)
    this.line <- index.start + 8
  } else if (res$type == "proportions_at_length") {
    res$year <- as.numeric(substring(lines[index.start + 4], 7))
    res$time_step <- substring(lines[index.start + 5], 12)
    res$number_of_bins <- as.numeric(substring(lines[index.start + 6], 17))
    res$length_bins <- substring(lines[index.start + 7], 14)
    this.line <- index.start + 7
  } else {
    stop(paste("Error: Observation type '", res$type, "' not known", sep = ""))
  }
  variables <- spm.string.to.vector.of.words(lines[this.line + 1])
  data <- spm.string.to.vector.of.words(lines[(this.line + 2):(index.end - 1)])
  data <- matrix(data, ncol = length(variables), byrow = TRUE)
  data <- as.data.frame(data, stringsAsFactors = FALSE)
  names(data) <- variables
  data <- data.frame(data[-1,])
  names(data) <- variables
  data$area <- as.character(data$area)
  data$observed <- as.numeric(as.character(data$observed))
  data$expected <- as.numeric(as.character(data$expected))
  data$residual <- as.numeric(as.character(data$residual))
  data$errorvalue <- as.numeric(as.character(data$errorvalue))
  data$processerror <- as.numeric(as.character(data$processerror))
  data$totalerror <- as.numeric(as.character(data$totalerror))
  data$score <- as.numeric(as.character(data$score))
  res$data <- data
  return(res)
}
