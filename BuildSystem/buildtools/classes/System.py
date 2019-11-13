import os
import sys
import os.path
import subprocess
import fileinput
import re
import Globals # Global Variables for build system

EX_OK = getattr(os, "EX_OK", 0)

class SystemInfo:
  # Variables
  original_path_ = "" 
    
  # Constructor
  def __init__(self):
    print('--> Starting SystemInfo object')
    Globals.operating_system_ = sys.platform
    self.original_path_    = os.getenv('PATH')
    
    if (Globals.operating_system_.startswith("linux")):
      Globals.operating_system_ = "linux"
    elif (Globals.operating_system_.startswith("darwin")):
      Globals.operating_system_ = "darwin"
    elif (Globals.operating_system_.startswith("win")):
      Globals.operating_system_ = "windows"
      
    print( "-- Configuring for Operating System: " + Globals.operating_system_)
    cwd = os.path.normpath(os.getcwd())
    if (Globals.operating_system_ == "windows"):
      Globals.path_ += cwd + '\\buildtools\\windows\\unixutils;'
      Globals.path_ += cwd + '\\buildtools\\windows\\cmake\\bin;'   
    
  def set_new_path(self):
    print("-- Overriding the system path with new values")
    if Globals.operating_system_ == "windows":
      os.environ['PATH'] = Globals.path_ + ":" + self.original_path_
    else:
      os.environ['PATH'] = Globals.path_ + ":" + self.original_path_
    print('-- New Path: ' + os.environ['PATH'])
    
  def reset_original_path(self):
    os.environ['PATH'] = self.original_path_
    
  """
  This method will search the path for a specific EXE and then ensure we put it in to our
  path
  """
  def find_exe_path(self, exe):
    print('-- Searching path for ' + exe)
    if os.system('which ' + exe + ' > which.tmp 2> err.tmp') != EX_OK:
      os.system('rm -rf err.tmp')
      print('## ' + exe + ' not found in the current path')
      return ''
      
    # Read path back from file
    fi = fileinput.FileInput('which.tmp')    
    path = ''
    for line in fi:
        path = line
    path = path.replace(exe + '\n', '').rstrip()
    print('-- ' + exe + ' found @ ' + path)

    if path != "" and Globals.operating_system_ == "windows":
      Globals.path_ = path + ";" + Globals.path_
    elif path != "":
      Globals.path_ = path + ":" + Globals.path_

    os.system('rm -rf err.tmp')      
    if os.system('rm -rf which.tmp') != EX_OK:
      Globals.PrintError('Could not delete the temporary file "which.tmp". Do you have correct file system access?')
      return
    
    return path
	
  """
  This method will determine the compiler to use
  """
  def determine_compiler(self):
    ext = ""
    if Globals.operating_system_ == "windows":
      ext = ".exe"
    # Check for GCC
    target = "g++" + ext
    p = subprocess.Popen(["which", target], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    out, err = p.communicate()
    if p.wait() == 0:
      Globals.compiler_ = "gcc"
      Globals.compiler_path_ = out.decode("utf-8").rstrip() 
      print("-- G++ Path: " + out.decode("utf-8").rstrip())
      return

    Globals.PrintError("Could not find g++")   
    exit(-1)

  """
  Find out Compiler version
  """
  def find_compiler_version(self):
    if Globals.operating_system_ == "windows":
      Globals.compiler_path_ = Globals.compiler_path_.replace("/", "\\")

    if Globals.compiler_ == "gcc":
      return self.find_gcc_version()

    return False

  """
  This method will find the GCC Version
  """
  def find_gcc_version(self):
    print("--> Searching for g++ compiler verstion in '" + Globals.compiler_path_ + "'")
    p = subprocess.Popen([Globals.compiler_path_, "-v"], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    out, err = p.communicate()
    err_lines = re.split('version', str(err))
    target_line = err_lines[len(err_lines) - 1].lstrip().rstrip()
    print('--> Full Version: ' + target_line)
    pieces = target_line.split(' ')
    if len(pieces) < 2:
      return Globals.PrintError('STD out did not return correct GCC Version format ' + str(len(pieces)) + ': ' + target_line)

    Globals.compiler_version_ = pieces[0].lstrip().rstrip()
    print('--> gcc version: ' + Globals.compiler_version_)

    pieces = Globals.compiler_version_.split('.')
    if int(pieces[0]) < 7:
      return Globals.PrintError("g++ version " + Globals.compiler_version_ + " is not supported due to it's age")

    return True
