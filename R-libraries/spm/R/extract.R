#' Extract SPM output into R
#'
#' @author Alistair Dunn
#' @param file the name of the input file containing model output to extract
#' @param path Optionally, the path to the file
#' @param ignore.unknown Ignore unknown objects in the output file
#' 
#' @export
#'
"extract" <- function(file, path = "", ignore.unknown = FALSE) {
  if (missing(path)) path <- ""
  filename <- spm.make.filename(path = path, file = file)
  line <- scan(filename, what = "", sep = "\n")
  line <- c(line, " ")
  res <- list()
  if (substring(line[1], 1, 3) == "SPM") {
    header <- list()
    header$call <- line[2]
    header$date <- line[3]
    header$version <- line[4]
    header$user.name <- line[5]
    header$machine.name <- line[6]
    res$header <- header
    temp <- substr(res$header$version[1], 2, 17)
    if (temp != spm.binary.version()) {
      cat("Warning: spm and the spm R library versions are different\n")
      cat("SPM v", temp, "\n", sep = "")
      cat("R   v", spm.binary.version(), "\n", sep = "")
    }
  }
  index <- (1:length(line))[substring(line, 1, 1) == "["]
  report.label <- substring(line[index], 2, nchar(line[index]) - 1)
  report.type <- substring(line[index + 1], 14)
  if (length(report.label) != length(report.type))
    stop("Error")
  index <- c(index, length(line))
  report.types <- spm.report.types()
  counter <- as.list(rep(0, length(report.types)))
  names(counter) <- report.types
  for (i in 1:length(report.type)) {
    if (report.type[i] == "ageing_error") {
      if (!("ageing_error" %in% names(res)))
        res$"ageing_error" <- list()
      counter$"ageing_error" <- counter$"ageing_error" + 1
      temp <- extract.ageingerror(lines = line[index[i]:(index[i + 1] - 1)])
      res$"ageing_error"[[counter$"ageing_error"]] <- temp
      names(res$"ageing_error")[counter$"ageing_error"] <- report.label[i]
    } else if (report.type[i] == "age_size") {
      if (!("age_size" %in% names(res)))
        res$age_size <- list()
      counter$age_size <- counter$age_size + 1
      temp <- extract.agesize(lines = line[index[i]:(index[i + 1] - 1)])
      res$age_size[[counter$age_size]] <- temp
      names(res$age_size)[counter$age_size] <- report.label[i]
    } else if (report.type[i] == "age_weight") {
      if (!("age_weight" %in% names(res)))
        res$age_weight <- list()
      counter$age_weight <- counter$age_weight + 1
      temp <- extract.ageweight(lines = line[index[i]:(index[i + 1] - 1)])
      res$age_weight[[counter$age_weight]] <- temp
      names(res$age_weight)[counter$age_weight] <- report.label[i]
    } else if (report.type[i] == "covariance") {
      if (!("covariance" %in% names(res)))
        res$covariance <- list()
      counter$covariance <- counter$covariance + 1
      temp <- extract.covariance(lines = line[index[i]:(index[i + 1] - 1)])
      res$covariance[[counter$covariance]] <- temp
      names(res$covariance)[counter$covariance] <- report.label[i]
    } else if (report.type[i] == "derived_quantity") {
      if (!("derived_quantity" %in% names(res)))
        res$derived_quantity <- list()
      counter$derived_quantity <- counter$derived_quantity + 1
      temp <- extract.derivedquantity(lines = line[index[i]:(index[i + 1] - 1)])
      res$derived_quantity[[counter$derived_quantity]] <- temp
      names(res$derived_quantity)[counter$derived_quantity] <- report.label[i]
    } else if (report.type[i] == "derived_quantity_by_cell") {
      if (!("derived_quantity_by_cell" %in% names(res)))
        res$derived_quantity_by_cell <- list()
      counter$derived_quantity_by_cell <- counter$derived_quantity_by_cell + 1
      temp <- extract.derivedquantitybycell(lines = line[index[i]:(index[i + 1] - 1)])
      res$derived_quantity_by_cell[[counter$derived_quantity_by_cell]] <- temp
      names(res$derived_quantity_by_cell)[counter$derived_quantity_by_cell] <- report.label[i]
    } else if (report.type[i] == "estimate_summary") {
      if (!("estimate_summary" %in% names(res)))
        res$estimate_summary <- list()
      counter$estimate_summary <- counter$estimate_summary + 1
      temp <- extract.estimatesummary(lines = line[index[i]:(index[i + 1] - 1)])
      res$estimate_summary[[counter$estimate_summary]] <- temp
      names(res$estimate_summary)[counter$estimate_summary] <- report.label[i]
    } else if (report.type[i] == "estimate_value") {
      if (!("estimate_value" %in% names(res)))
        res$estimate_value <- list()
      counter$estimate_value <- counter$estimate_value + 1
      temp <- extract.estimatevalue(lines = line[index[i]:(index[i + 1] - 1)])
      res$estimate_value[[counter$estimate_value]] <- temp
      names(res$estimate_value)[counter$estimate_value] <- report.label[i]
    } else if (report.type[i] == "initialisation") {
      if (!("initialisation" %in% names(res)))
        res$initialisation <- list()
      counter$initialisation <- counter$initialisation + 1
      temp <- extract.initialisationphase(lines = line[index[i]:(index[i + 1] - 1)])
      res$initialisation[[counter$initialisation]] <- temp
      names(res$initialisation)[counter$initialisation] <- report.label[i]
    } else if (report.type[i] == "layer") {
      if (!("layer" %in% names(res)))
        res$layer <- list()
      counter$layer <- counter$layer + 1
      temp <- extract.layer(lines = line[index[i]:(index[i + 1] - 1)])
      res$layer[[counter$layer]] <- temp
      names(res$layer)[counter$layer] <- report.label[i]
    } else if (report.type[i] == "layer_derived_view") {
      if (!("layer_derived_view" %in% names(res)))
        res$layer_derived_view <- list()
      counter$layer_derived_view <- counter$layer_derived_view + 1
      temp <- extract.layerderivedview(lines = line[index[i]:(index[i + 1] - 1)])
      res$layer_derived_view[[counter$layer_derived_view]] <- temp
      names(res$layer_derived_view)[counter$layer_derived_view] <- report.label[i]
    } else if (report.type[i] == "MCMC") {
      if (!("MCMC" %in% names(res)))
        res$MCMC <- list()
      counter$MCMC <- counter$MCMC + 1
      temp <- extract.MCMC(lines = line[index[i]:(index[i + 1])]) #don't remove the *end
      res$MCMC[[counter$MCMC]] <- temp
      names(res$MCMC)[counter$MCMC] <- report.label[i]
    } else if (report.type[i] == "objective_function") {
      if (!("objective_function" %in% names(res)))
        res$objective_function <- list()
      counter$objective_function <- counter$objective_function + 1
      temp <- extract.objectivefunction(lines = line[index[i]:(index[i + 1] - 1)])
      res$objective_function[[counter$objective_function]] <- temp
      names(res$objective_function)[counter$objective_function] <- report.label[i]
    } else if (report.type[i] == "observation") {
      if (!("observation" %in% names(res)))
        res$observation <- list()
      counter$observation <- counter$observation + 1
      temp <- extract.observation(lines = line[index[i]:(index[i + 1] - 1)])
      res$observation[[counter$observation]] <- temp
      names(res$observation)[counter$observation] <- report.label[i]
    } else if (report.type[i] == "partition") {
      if (!("partition" %in% names(res)))
        res$partition <- list()
      counter$partition <- counter$partition + 1
      temp <- extract.partition(lines = line[index[i]:(index[i + 1] - 1)])
      res$partition[[counter$partition]] <- temp
      names(res$partition)[counter$partition] <- report.label[i]
    } else if (report.type[i] == "partition_biomass") {
      if (!("partition_biomass" %in% names(res)))
        res$partition_biomass <- list()
      counter$partition_biomass <- counter$partition_biomass + 1
      temp <- extract.partitionbiomass(lines = line[index[i]:(index[i + 1] - 1)])
      res$partition_biomass[[counter$partition_biomass]] <- temp
      names(res$partition_biomass)[counter$partition_biomass] <- report.label[i]
    } else if (report.type[i] == "process") {
      if (!("process" %in% names(res)))
        res$process <- list()
      counter$process <- counter$process + 1
      temp <- extract.process(lines = line[index[i]:(index[i + 1] - 1)])
      res$process[[counter$process]] <- temp
      names(res$process)[counter$process] <- report.label[i]
    } else if (report.type[i] == "preference_function") {
      if (!("preference_function" %in% names(res)))
        res$"preference_function" <- list()
      counter$preference_function <- counter$preference_function + 1
      temp <- extract.preferencefunction(lines = line[index[i]:(index[i + 1] - 1)])
      res$preference_function[[counter$preference_function]] <- temp
      names(res$preference_function)[counter$preference_function] <- report.label[i]
    } else if (report.type[i] == "random_number_seed") {
      if (!("random_number_seed" %in% names(res)))
        res$random_number_seed <- list()
      counter$random_number_seed <- counter$random_number_seed + 1
      temp <- extract.randomnumberseed(lines = line[index[i]:(index[i + 1] - 1)])
      res$random_number_seed[[counter$random_number_seed]] <- temp
      names(res$random_number_seed)[counter$random_number_seed] <- report.label[i]
    } else if (report.type[i] == "selectivity") {
      if (!("selectivity" %in% names(res)))
        res$selectivity <- list()
      counter$selectivity <- counter$selectivity + 1
      temp <- extract.selectivity(lines = line[index[i]:(index[i + 1] - 1)])
      res$selectivity[[counter$selectivity]] <- temp
      names(res$selectivity)[counter$selectivity] <- report.label[i]
    } else if (report.type[i] == "size_weight") {
      if (!("size_weight" %in% names(res)))
        res$size_weight <- list()
      counter$size_weight <- counter$size_weight + 1
      temp <- extract.sizeweight(lines = line[index[i]:(index[i + 1] - 1)])
      res$size_weight[[counter$size_weight]] <- temp
      names(res$size_weight)[counter$size_weight] <- report.label[i]
    } else if (report.type[i] == "spatial_map") {
      if (!("spatial_map" %in% names(res)))
        res$spatial_map <- list()
      counter$spatial_map <- counter$spatial_map + 1
      temp <- extract.spatialmap(lines = line[index[i]:(index[i + 1] - 1)])
      res$spatial_map[[counter$spatial_map]] <- temp
      names(res$spatial_map)[counter$spatial_map] <- report.label[i]
    } else if (ignore.unknown == FALSE) {
      stop(paste("ERROR: Unknown report type (report.type=", report.type[i], ")"))
    }
  }
  return(res)
}
