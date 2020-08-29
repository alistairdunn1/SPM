"""
This module contains the list of global variables we're going to be
using throughout the build system
"""
import os

SPM_version_number= "2.0.3"
operating_system_ = ""
path_             = ""
compiler_path_    = ""
gfortran_path_    = ""
python_cmd_       = ""
compiler_ 		  = ""
compiler_version_ = ""
make_command_     = ""
cmake_compiler_	  = "unknown"
latex_path_       = ""
git_path_         = ""
cmd_path_         = ""
build_target_     = ""

root_directory_          = ""
buildtools_directory_    = ""
build_directory_         = ""
boost_directory_         = ""
boost_source_directory_  = ""

target_success_path_     = ""
target_include_path_     = ""
target_debug_lib_path_   = ""
target_release_lib_path_ = ""

threads_          = "8"
boost_version     = 'boost_1_71_0'

allowed_build_targets_ = [ "release", "examples", "documentation", "boost", "archive", "clean", 
                           "check", "unittests", "installer", "deb", "rlibrary", "version"]

EX_OK = getattr(os, "EX_OK", 0)

def PrintError(error_message):
  print("\n\n\n")
  print("###### ERROR ######")
  print( "Error Description:")
  print(error_message)
  print("###### ERROR ######")
  print("\n\n\n")
  return False
