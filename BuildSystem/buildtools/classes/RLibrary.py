import os
import sys
import subprocess
import os.path
import fileinput
import re
import time

import Globals

EX_OK = getattr(os, "EX_OK", 0)

class RLibrary:
  """
  Build the R library
  """
  def start(self):
    library_name = 'spm'
    binary_name = 'spm'
    if Globals.operating_system_ == 'windows':
      binary_name += '.exe'
   
    ## Check SPM is in your path. The R script needs it to get versions and that sort of information. 
    if not os.path.exists(Globals.build_directory_ ):
      print('Looking for spm binary in ' + Globals.build_directory_ )
      print('\n\n*****************\nERROR\n*****************\nSPM binary was not found. Cannot continue\n\n')
      return False
    ## CHG Dir to R library
    os.chdir(Globals.root_directory_ + "/R-libraries/")
    ## Build Namespace
    os.system("R --vanilla < SPM_make_version.R")
    ## Run the oxygen
    os.system("R --vanilla < run-roxygen.R")   
    ## build package
    os.system("R CMD build --force spm")
    os.system("R CMD INSTALL --build spm")
    os.system("R CMD check spm")
    os.system("del spm.html")
    #os.system("mv -f spm_" + Globals.SPM_version_number + "* " + Globals.root_directory_ + "/Build")

    #os.system("R CMD build --force spmTest")
    #os.system("R CMD INSTALL --build spmTest")
    #os.system("R CMD check spmTest")
    #os.system("mv -f spmTest_" + Globals.SPM_version_number + "* " + Globals.root_directory_ + "/Build")
    return True
