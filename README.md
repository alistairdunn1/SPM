SPM v2.0.3-2020-06-03
=====================

Spatial Population Model (SPM)

SPM is an advanced population modelling programme, originally developed by NIWA and since updated, to undertake spatially explicit stock assessment scientific research. The software is written in C++ and is available under an open source licence. SPM was designed to allow populations with a high-resolution and complex spatial structure to be easily modelled, in particular using environmental covariates to inform spatial distribution and movement. It implements an age-structured population model with unlimited user-defined categories (for example, sex, maturity, and species). It can be used for a single stock for a single fishery, or for multiple stocks (independent as well as dynamic predator-prey relationships), at a high-resolution spatial structure, with multiple fisheries. The user can choose the sequence of events in a model year. The observational data that can be used include catch-at-age or catch-at-length data from commercial fishing, survey and other biomass indices, survey catch-at-age or catch-at-length data, and tag-release and tag-recapture data.

SPM can be used to generate point estimates of the parameters of interest, calculate profiles, and generate Bayesian posterior distributions using Monte Carlo Markov Chain methods. SPM can also be used to simulate observations from a given model for use in management procedure evaluations or other simulation experiments.

This repository is a fork of the NIWA SPM code base from 2018 and is actively under development. Information on SPM can be obtained from the authors (Alistair.Dunn@OceanEnvironmental.co.nz) or from NIWA (casal@NIWA.co.nz).

The suitable reference for citing the original version of SPM is: Dunn, A.; Rasmussen, S.; Mormede, S. (2018). Spatial Population Model User Manual, SPM v1.1-2018-05-31 (rev. 1291) NIWA Technical Report 138. NIWA, Wellington, New Zealand, 210 p.

The current release version is 2.0.3. See the user manual for the more information, the most recent build, and a suitable reference for SPM.

[![CodeFactor](https://www.codefactor.io/repository/github/alistairdunn1/spm/badge)](https://www.codefactor.io/repository/github/alistairdunn1/spm)
[![Build Status](https://dev.azure.com/OceanEnvironmental/SPM/_apis/build/status/alistairdunn1.SPM?branchName=master)](https://dev.azure.com/OceanEnvironmental/SPM/_build/latest?definitionId=1&branchName=master)
