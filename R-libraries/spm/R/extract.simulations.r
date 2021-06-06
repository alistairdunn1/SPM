#' Helper function for 'extract'
#'
#' @author Alistair Dunn
#' @param lines list of lines to process
#'
"extract.simulations" <- function(file, path = "") {
  if (missing(path))
    path <- ""
  filename <- spm.make.filename(path = path, file = file)
  line <- scan(filename, what = "", sep = "\n")
  res <- list()
  index <- (1:length(line))[line == "#report.type: simulated_observation"]
  end.index <- (1:length(line))[line == "#end"]
  report.label <- substring(line[index - 1], 3, nchar(line[index - 1]) - 1)
  report.type <- substring(line[index], 15)
  if (length(report.label) != length(report.type))
    stop("Error")
  res <- vector("list", length = length(index))
  names(res) <- report.label
  N <- length(index)
  for (i in 1:N) {
    temp <- spm.extract.simulated.observation(lines = line[(index[i] - 1):(end.index[i])])
    res[[i]] <- temp
  }
  return(res)
}

