import os
import sys
import subprocess
import os.path
import shutil
import fileinput
import re
import time
import pytz
from datetime import datetime, date
import importlib.util

import Globals
from Version import *

EX_OK = getattr(os, "EX_OK", 0)
"""
This class is responsible for building the main code base of the project
"""
class Release:
  cmake_compiler_ = ""
  output_directory_ = "";
  
  def start(self):
    start = time.time()
    print( "--> Starting build of the main code base")
    print( "--> Build configuration " + Globals.build_target_ )
    print( "--> Operating System: " + Globals.operating_system_)
    
    self.cmake_compiler_ = Globals.cmake_compiler_ #[ 'Unix', 'MinGW' ][ Globals.operating_system_ == "windows" ]
    print( "--> CMake Compiler: " + Globals.cmake_compiler_)
    
    # Check to see if boost has been built
    folder = Globals.boost_directory_ + '/' + Globals.boost_version + '/bin.v2'
    if not os.path.exists(Globals.boost_directory_ + '/' + Globals.boost_version + '/bin.v2'):
      return Globals.PrintError("Boost has not been built. Please build these first with boost argument")

    ## Build Version.h
    version = Version()
    version.create_version_header()
    
    print( "--> Target output directory: " + Globals.build_directory_)
    
    os.chdir(Globals.build_directory_);
    
    print( '--> Preparing CMake command')
    if Globals.operating_system_ == "windows":
      build_string = Globals.buildtools_directory_ + '/buildtools/windows/cmake/bin/cmake ' + self.cmake_compiler_ + ' -S ' + Globals.root_directory_ + '/BuildSystem/' + ' -B ' + Globals.build_directory_
    else:
      build_string = 'cmake ' + self.cmake_compiler_ + ' ' + Globals.root_directory_ + '/BuildSystem'
    print( "--> CMake command: " + build_string)
    if os.system(build_string) != EX_OK:
      return Globals.PrintError("Failed to execute cmake successfully to rebuild the make files")
    
    print( "--> Build main code base")
    if Globals.operating_system_ == "windows":
      if os.system("mingw32-make -j " + Globals.threads_) != EX_OK:
        return Globals.PrintError("Failed to build code base. Please see above for build error")
      else:
        print('-->strip ' + Globals.build_directory_ + '/spm.exe')
        os.system('strip ' + Globals.build_directory_ + '/spm.exe')
        print('-->strip ' + Globals.build_directory_ + '/spm_unittests.exe')
        os.system('strip ' + Globals.build_directory_ + '/spm_unittests.exe')
        print('-->strip ' + Globals.build_directory_ + '/spm_unoptimised.exe')
        os.system('strip ' + Globals.build_directory_ + '/spm_unoptimised.exe')
    else:
      os.chdir(Globals.build_directory_)
      if os.system("make -j " + Globals.threads_) != EX_OK:
        return Globals.PrintError("Failed to build code base. Please see above for build error")

    elapsed = time.time() - start
    print( 'Compile finished in ' + str(round(elapsed, 2)) + ' seconds')
    
    return True 

"""
This class is responsible for build the third party libraries part of the code base
"""
class Boost:
  include_directory = ""
  lib_directory     = ""
  lib_debug_directory = ""
  lib_release_directory = ""
  
  def start(self):
    print("--> Starting build of boost")
    print("-- Operating System: " + Globals.operating_system_)
    print("-- Compiler: " + Globals.compiler_)
  
    # Clean out any existing files if they already exist
    print('-- Cleaning Boost files in: ' + Globals.boost_directory_)
    if os.path.exists(Globals.boost_directory_):
      shutil.rmtree(Globals.boost_directory_)
      os.mkdir(Globals.boost_directory_)
   
    print( "-- Checking if Boost folder exists: " + Globals.boost_source_directory_)
    if not os.path.exists(Globals.boost_source_directory_):
      return Globals.PrintError('Boost folder does not exist')

    print( "-- Checking if Boost build folder exists: " + Globals.boost_directory_)
    if not os.path.exists(Globals.boost_directory_):
      print( "-- Creating output directory: " + Globals.boost_directory_)
      os.makedirs(Globals.boost_directory_)

    self.include_directory = Globals.boost_directory_ + "/include"
    if not os.path.exists(self.include_directory):
      print( "-- Creating include directory: " + self.include_directory)
      os.makedirs(self.include_directory)
      
    self.lib_directory = Globals.boost_directory_ + "/lib"
    if not os.path.exists(self.lib_directory):
      print("-- Creating lib directory: " + self.lib_directory)
      os.makedirs(self.lib_directory)
      
    self.lib_debug_directory = self.lib_directory + "/debug"
    if not os.path.exists(self.lib_debug_directory):
      print( "-- Creating lib debug directory: " + self.lib_debug_directory)
      os.makedirs(self.lib_debug_directory)
      
    self.lib_release_directory = self.lib_directory + "/release"
    if not os.path.exists(self.lib_release_directory):
      print( "-- Creating lib release directory: " + self.lib_release_directory)
      os.makedirs(self.lib_release_directory)
      
    Globals.target_success_path_      = Globals.boost_directory_ + '/'
    Globals.target_include_path_      = Globals.boost_directory_ + '/include/'
    Globals.target_debug_lib_path_    = Globals.boost_directory_ + '/lib/'
    Globals.target_release_lib_path_  = Globals.boost_directory_ + '/lib/'
   
    os.chdir(Globals.boost_source_directory_)
    sys.path.append(os.path.normpath(os.getcwd()))

    if Globals.operating_system_ == "windows":
      if not os.path.exists(Globals.boost_source_directory_ + '/windows.py'):
        return Globals.PrintError('Boost library ' + Globals.boost_source_directory_ + ' does not have a windows.py file.\nThis file is required to build this library on Windows')
      import windows as boost_builder
      builder = boost_builder.Builder()        
      print("")
      print( "--> Building Boost: " + Globals.boost_directory_)

      success = builder.start()
      if success:
        os.system('echo ' + 'boost' + Globals.boost_version + ' > ' + Globals.boost_directory_ + '.success')
        print( "")
        print('-- Moving headers and libraries')
        if os.path.exists(Globals.target_include_path_ + 'boost/'):
          print('--Cleaning old directory')
          shutil.rmtree(Globals.target_include_path_ + 'boost/')
        print('copy ' + 'boost' + ' to ' + Globals.target_include_path_ + 'boost/')
        shutil.copytree('boost', Globals.target_include_path_ + 'boost/')
        print(Globals.boost_directory_ + '/' + Globals.boost_version + '/stage/lib/')
        os.system("cp -f " + Globals.boost_directory_ + '/' + Globals.boost_version + '/stage/lib/*-mt-s-* ' + Globals.boost_directory_ + '\lib')
        os.system("cp -f " + Globals.boost_directory_ + '/' + Globals.boost_version + '/stage/lib/*-mt-sd-* ' + Globals.boost_directory_ + '\lib')
      else:
        return Globals.PrintError('Boost library ' + Globals.boost_directory_ + ' had an error during the build. Check log files for more information')
      del sys.modules["windows"]
    else:
      if not os.path.exists(Globals.boost_source_directory_ + '/linux.py'):
        return Globals.PrintError('Boost library ' + Globals.boost_source_directory_ + ' does not have a linux.py file.\nThis file is required to build this library on Linux')
      import linux as boost_builder
      builder = boost_builder.Builder()        
      print( "")
      print( "--> Building Boost: " + Globals.boost_directory_)
      success = builder.start()
      if success:
        os.system('echo ' + 'boost' + Globals.boost_version + ' > ' + Globals.boost_directory_ + '.success')
        print("")
        print('-- Moving headers and libraries')
        if os.path.exists(Globals.target_include_path_ + 'boost/'):
          print('--Cleaning old directory')
          shutil.rmtree(Globals.target_include_path_ + 'boost/')
        print('copy ' + 'boost' + ' to ' + Globals.target_include_path_ + 'boost/')
        shutil.copytree('boost', Globals.target_include_path_ + 'boost/')
        print(Globals.boost_directory_ + '/' + Globals.boost_version + '/stage/lib/')
        os.system("cp -f " + Globals.boost_directory_ + '/' + Globals.boost_version + '/stage/lib/* ' + Globals.boost_directory_ + '/lib')
      else:
        return Globals.PrintError('Boost library ' + Globals.boost_directory_ + ' had an error during the build. Check log files for more information')
      del sys.modules["linux"]
          
    if not success:
      print( "--> Boost libraries failed")
      return False
  
    print( "")
    print( "--> Boost libraries have been built successfully")
    return True


"""
This class is responsible for cleaning the build folders
"""   
class Cleaner:    
  def clean(self):
    print( '--> Starting clean of SPM build files')
    if (os.path.exists(Globals.build_directory_)):
      print( '--> Deleting folder: ' + Globals.build_directory_)
      shutil.rmtree(Globals.build_directory_)
    else:
      print( '--> Folder not found: ' + Globals.build_directory_)
    return True
        
