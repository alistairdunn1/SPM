#' Model configuration write function
#'
#' This function writes an SPM configuration file. Where each element is a command and subcommand from the configuration file
#'
#' @author Alistair Dunn
#' @param object the name of the object containing model configuration
#' @param file The file to write to
#' @param path Optionally, the path to the file
#' @param header Optionally, a text header to append as a comment at the top of the file
#' @param date Optionally, a comment giving the current date
#' 
#' @export
#'
"write.spm.config" <- function(object, file, path = "", header = "SPM config file", date = FALSE) {
  # create filename and write file
  if (missing(path))
    path <- ""
  filename <- spm.make.filename(path = path, file = file)
  cat(paste("#", header, "\n"), file = filename, sep = "", fill = F, labels = NULL, append = F)
  if (date)
    cat(paste("#", date(), "\n\n"), file = filename, sep = "", fill = F, labels = NULL, append = T)
  for (i in 1:length(object)) {
    index <- regexpr("\\[", names(object)[i])
    if (index > 0) {
      command <- paste("@", substring(names(object)[i], 1, index - 1), sep = "")
      label <- substring(names(object)[i], index + 1, nchar(names(object)[i]) - 1)
    } else {
      command <- paste("@", names(object)[i], sep = "")
      label <- ""
    }
    cat(paste(command, label, sep = " "), file = filename, sep = "", fill = F, labels = NULL, append = T)
    cat("\n", file = filename, sep = "", fill = F, labels = NULL, append = T)
    subcommands <- object[[i]]
    if (length(subcommands) > 0) {
      for (j in 1:length(subcommands)) {
        if (names(subcommands)[j] %in% c("data", "obs", "error_value")) {
          for (k in 1:nrow(subcommands[[j]])) {
            line <- paste(subcommands[[j]][k,], sep = "", collapse = " ")
            line <- paste(names(subcommands)[j], " ", line, "\n", sep = "")
            cat(line, file = filename, sep = "", fill = F, labels = NULL, append = T)
          }
        } else {
          line <- paste(subcommands[[j]], sep = "", collapse = " ")
          line <- paste(names(subcommands)[j], " ", line, "\n", sep = "")
          cat(line, file = filename, sep = "", fill = F, labels = NULL, append = T)
        }
      }
    }
    cat("\n", file = filename, sep = "", fill = F, labels = NULL, append = T)
  }
  invisible()
}
