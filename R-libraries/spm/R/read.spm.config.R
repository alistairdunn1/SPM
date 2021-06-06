#' Model configuration read function
#'
#' This function reads an SPM configuration file and returns a list object in R. Where each element is a command and subcommand from the configuration file
#'
#' @author Alistair Dunn
#' @param file the name of the input file containing model configuration
#' @param path Optionally, the path to the file
#' 
#' @export
#'
"read.spm.config" <- function(file, path = "") {
  if (missing(path))
    path <- ""
  filename <- spm.make.filename(path = path, file = file)
  file = spm.convert.to.lines(filename)

  ## remove white space at the beginning of a subcommand or command e.g
  while (any(regexpr(" ", file) == 1)) {
    index <- regexpr(" ", file) == 1
    file <- ifelse(index, substring(file, 2), file)
  }

  ## Remove any lines that begin with a #
  file <- file[substring(file, 1, 1) != "#"]

  ## Find and remove any lines that begin or end with { or } which is also a comment
  index1 <- ifelse(substring(file, 1, 1) == "{", 1:length(file), 0)
  index2 <- ifelse(substring(file, 1, 1) == "}", 1:length(file), 0)
  index1 <- index1[index1 != 0]
  index2 <- index2[index2 != 0]
  if (length(index1) != length(index2))
    stop(paste("Error in the file ", filename, ". Cannot find a matching '/*' or '*/'", sep = ""))
  if (length(index1) > 0 || length(index2) > 0) {
    index <- unlist(apply(cbind(index1, index2), 1, function(x) seq(x[1], x[2])))
    file <- file[!is.in(1:length(file), index)]
  }

  ## strip any remaining comments
  file <- ifelse(regexpr("#", file) > 0, substring(file, 1, regexpr("#", file) - 1), file)
  file <- file[file != ""]
  if (substring(file[1], 1, 1) != "@")
    stop(paste("Error in the file ", filename, ". Cannot find a '@' at the beginning of the file", sep = ""))

  ## create a labels for blocks that do not take a label following the @block statement
  blocks = spm.get.lines(file, starts.with = "\\@", fixed = F)
  exception_blocks = c("model", "estimation")
  ans <- list()

  print(paste("The SPM configuration input parameter file has", length(file[substring(file, 1, 1) == "@"]), "commands, and", length(file), "lines"))

  CommandCount <- 0

  for (i in 1:length(file)) {
    temp <- spm.string.to.vector.of.words(file[i])
    # If an '@', then this is a command
    if (substring(temp[1], 1, 1) == "@") {
      CommandCount <- CommandCount + 1
      Command <- substring(temp[1], 2)
      if (length(temp) > 1) {
        label <- temp[2]
        ans[[paste(Command, "[", label, "]", sep = "")]] <- list() #"command"=Command,"label"=label
      } else {
        ans[[Command]] <- list() #"command"=Command
      }
    } else {
      # must be a subcommand
      if (temp[1] %in% c("data", "obs", "error_value")) {
        if (temp[1] %in% names(ans[[CommandCount]])) {
          ans[[CommandCount]][[temp[1]]] <- rbind(ans[[CommandCount]][[temp[1]]], temp[-1])
        } else {
          ans[[CommandCount]][[temp[1]]] <- matrix(temp[-1], ncol = length(temp[-1]))
        }
      } else {
        ans[[CommandCount]][[temp[1]]] <- temp[-1]
      }
    }
  }
  return(ans)
}
