#' Generate a multivariate uniform distribution based on the bounds for the extimated parameters
#'
#' @author Sophie Mormede
#' @param file the name of the input file containing the estimated fits
#' @param path Optionally, the path to the file
#' @param output.file The name of the output file to write randomly generated values
#' @param sample.size The number f samples to generate
#' 
#' @export
#'
"generate.MVU" <- function(file, path = "", output.file, sample.size = 1) {
  run <- extract(file, path)
  parbnds <- run$"estimate_summary"[[1]]$data
  rand <- runif(n = sample.size * nrow(parbnds), min = parbnds$lower_bound, max = parbnds$upper_bound * 1.0000000000001)
  rand <- matrix(rand, nrow = sample.size, byrow = T)
  colnames(rand) <- parbnds$parameter
  if (!missing(output.file)) {
    outfile <- spm.make.filename(file = output.file, path = path)
    write.table(x = signif(rand, 6), file = outfile, append = FALSE, quote = FALSE, sep = " ", row.names = FALSE, col.names = TRUE)
  }
  invisible(list("header" = names(rand), "parameters" = parbnds$value, "bounds" = parbnds[, c("lower_bound", "upper_bound")], "MVU" = rand))
}


