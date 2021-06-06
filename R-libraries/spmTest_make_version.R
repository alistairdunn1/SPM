# Get SPM Version
source("version.R")
VERSION <- paste(version.number, " (", version.date, ")", sep = "")

# Build DESCRIPTION file
filename <- "spmTest/DESCRIPTION"
cat("Package: spmTest\nTitle: SPM functions for testing SPM program equations and functions\nVersion: ", file = filename)
cat(version.number, file = filename, append = TRUE)
cat("\nDate: ", file = filename, append = TRUE)
cat(version.date, file = filename, append = TRUE)
cat("\n", file = filename, append = TRUE)
cat("Author: A. Dunn\n", file = filename, append = TRUE)
cat("Description: A set of R functions for assisting with the testing of SPM.\n", file = filename, append = TRUE)
cat("Depends: spm\n", file = filename, append = TRUE)
cat("Maintainer: A Dunn <Alistair.Dunn@OceanEnvironmental.co.nz>\n", file = filename, append = TRUE)
cat("License: CPL v1.0. See the SPM User Manual for license details.\n", file = filename, append = TRUE)
cat("URL: https://github.com/alistairdunn1/SPM\n", file = filename, append = TRUE)
cat("Copyright: National Institute of Water & Atmospheric Research (NIWA), New Zealand Ministry for Primary Industries.\n", file = filename, append = TRUE)

# Make a man page for the library
#filename<-"spmTest/man/spmTest-package.Rd"
#promptPackage("spmTest",filename=filename,final=T)

# Create R function to return version number
filename <- "spmTest/R/spmTest.binary.version.R"
cat("\"spmTest.binary.version\"<-\n", file = filename)
cat("function() {\n", file = filename, append = T)
cat(paste("return(\"", VERSION, "\")\n", sep = ""), file = filename, append = T)
cat("}\n", file = filename, append = T)

# Write a .html file to report version number for the Wiki
cat(paste("Version", VERSION), file = "spmTest.html")

# Exit
q()

