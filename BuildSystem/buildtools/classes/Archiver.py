import os
import sys
import subprocess
import os.path
import shutil
import fileinput
import re
from datetime import datetime, date

import Globals
from Builder import *

EX_OK = getattr(os, "EX_OK", 0)

"""
This class is responsible for combining the project binaries into a simple archive
"""
class Archiver:
  cmake_compiler_ = ""
  output_directory_ = "";
  do_build_ = "doBuild"
  def start(self, skip_building = 'false'):
    if Globals.operating_system_ == "windows":
      self.do_build_ += '.bat'
    else:
      self.do_build_ = './' + self.do_build_ + '.sh'

    binary_name = 'spm'
    extension = ''
    if Globals.operating_system_ == "windows":
      binary_name += '.exe'

#    if skip_building != 'true':
#      print('--> Building boost')
#      print('-- Re-Entering build system to build boost')
#      print('-- All output is being diverted to boost.log')
#      print('-- Expected build time 10-60 minutes')
#      if os.system(self.do_build_ + '  boost > boost.log 2>&1') != EX_OK:
#        return Globals.PrintError('Failed to build boost. Please check boost.log for the error')

#      print('--> Building release version of SPM')
#      print('-- Re-Entering the build system to build SPM')
#      print('-- All output is being diverted to release_build.log')
#      if os.system(self.do_build_ + ' release > release_build.log 2>&1') != EX_OK:
#        return Globals.PrintError('Failed to build spm. Please check release_build.log for the error')

#      print('--> Building documentation')
#      print('-- Re-Entering the build system to build the documentation')
#      print('-- All output is being diverted to documentation_build.log')
#      if os.system(self.do_build_ + ' documentation > documentation_build.log 2>&1') != EX_OK:
#        return Globals.PrintError('Failed to build the documentation. Please check documenation_build.log for error')

#      print('--> Building R Library')
#      print('-- Re-Entering the build system to build the R Library')
#      print('-- All output is being diverted to RLibrary_build.log')
#      if os.system(self.do_build_ + ' rlibrary > RLibrary.log 2>&1') != EX_OK:
#        return Globals.PrintError('Failed to build the R Library. Please check RLibrary_build.log for error')

#      print('--> Running the unit tests of SPM')
#      print('-- Re-Entering the build system to run the unit test library')
#      print('-- All output is being diverted to spm_unittests.log')
#      if os.system(self.do_build_ + ' unittests > spm_unittests.log 2>&1') != EX_OK:
#        return Globals.PrintError('Failed to run unit tests successfuly. Please check spm_unittests.log for the error')

#      print('--> Building Windows installer for SPM')
#      print('-- Re-Entering the build system to build the installer')
#      print('-- All output is being diverted to installer_build.log')
#      if os.system(self.do_build_ + ' installer > installer_build.log 2>&1') != EX_OK:
#        return Globals.PrintError('Failed to build the installer. Please check installer_build.log for the error')

    ## Now we actually do the zipping of the binary
    output_directory = Globals.root_directory_ + '/Build/archive'
    binary_path = Globals.root_directory_ + '/Build'
    
    os.chdir(binary_path)
    
    if not os.path.exists(output_directory):
      os.makedirs(output_directory);
    else:
      os.system('rm -rf ' + output_directory + '/*')

    if not os.path.exists(output_directory + "/Linux"):
      os.makedirs(output_directory + "/Linux");

    print("-- Target output directory: " + output_directory)
    
    if os.path.exists(binary_path + "/spm_archive.zip"):
      print("-- Removing old Archive")
      os.system("rm -rf " + binary_path + "/spm_archive.zip")


    os.system('cp -r ../Examples/ ' + output_directory)
    print("-- Example code copied")
    os.system('cp -r ../Installer/README.txt ' + output_directory)
    os.system('cp -r ../Installer/README.make ' + output_directory)

    os.system('cp -r Setup_SPM.exe ' + output_directory)
    os.system('cp -r SPM*.* ' + output_directory)
    
    if Globals.operating_system_ == "windows":
      os.system('cp -r windows/spm*.* ' + output_directory)
      os.system('cp -r linux/spm* ' + output_directory + "/Linux")
      os.chdir(output_directory)
      os.system("zip -r ../spm_archive.zip *")
    else:
      os.system('cp -r linux/spm*.* ' + output_directory)
      os.system('tar cvf spm.tar spm/')
      os.system('gzip spm.tar')
      os.system('mv spm.tar.gz ' + output_directory + 'spm.tar.gz')

    return True #Success!
