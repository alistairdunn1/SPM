#' Generate a multivariate uniform distribution based on the bounds for the estimated parameters
#'
#' @author Alistair Dunn
#' @param data data representing a partition
#' @param categories Optional subset of categories
#' @param ages Optional subset of ages
#' @param total If true, then sum over selected categories and ages. Default = TRUE
#' 
#' @export
#'
"calc.abundance" <- function(data, categories = NULL, ages = NULL, total = T) {
  if (!is.null(categories))
    data <- data[data$category %in% categories,]
  index <- paste(data$col, data$row, sep = "-")
  data <- data[, regexpr("age", names(data)) > 0]
  Ages <- substring(names(data), 5)
  Ages <- as.numeric(substring(Ages, 1, nchar(Ages) - 1))
  if (!is.null(ages)) {
    data <- data[, Ages %in% ages]
    Ages <- Ages[Ages %in% ages]
  }
  data <- aggregate(data, by = list(index = index), sum)
  Col <- rep(NA, nrow(data))
  Row <- rep(NA, nrow(data))
  index <- strsplit(data$index, split = "-")
  for (i in 1:length(index)) {
    Col[i] <- index[[i]][1]
    Row[i] <- index[[i]][2]
  }
  if (length(Ages) == 1) {
    data$Total <- data[, -1]
  }
  data$total <- apply(data[, -1], 1, sum)
  data$row <- Row
  data$column <- Col
  row.names(data) <- 1:nrow(data)
  if (total)
    return(data[, names(data) %in% c("row", "column", "total")])
  else return(data)
}
