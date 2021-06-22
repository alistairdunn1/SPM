import os
import sys
import os.path
import subprocess
import fileinput
import distutils

sys.path.insert(0, "buildtools/classes")
EX_OK = getattr(os, "EX_OK", 0)

# These are SPM specific python objects
from System import *
from Globals import *
from Builder import *
from Documentation import *
from Examples import *
from Archiver import *
from UnitTests import *
from Installer import *
from DebBuilder import *
from CommandLineInterface import *
from Version import *
from RLibrary import *

"""
Get the build information from the user
"""
def start():
	cli = CommandLineInterface()
	if not cli.parse():
  		cli.print_usage()
  		return False;
      
	print( "*************************************************************************")
	print( "*************************************************************************")
	
	Globals.buildtools_directory_ = os.getcwd()
	Globals.root_directory_ = os.path.realpath(Globals.buildtools_directory_ + "/../")
	Globals.boost_source_directory_ = os.path.realpath(Globals.root_directory_ + "/Boost")
	Globals.build_directory_ = os.path.realpath(Globals.root_directory_ + "/Build/" + Globals.operating_system_ )
	Globals.boost_directory_ = os.path.realpath(Globals.build_directory_ + "/Boost")
	
	print('--> Directory: ' + Globals.root_directory_)

	if not os.path.exists(Globals.build_directory_):
		if not os.path.exists(Globals.root_directory_ + "/Build"):
			os.mkdir(Globals.root_directory_ + "/Build")
		os.mkdir(Globals.build_directory_)
	
	print( "--> Starting " + Globals.build_target_ + " Build")
	build_target = Globals.build_target_
	if build_target == "release":
		code_builder = Release()
		return code_builder.start()
	elif build_target == "archive":	
		archive_builder = Archiver()
		return archive_builder.start()
	elif build_target == "boost":
		code_builder = Boost()
		return code_builder.start()
	elif build_target == "documentation":
		documentation_builder = Documentation()
		return documentation_builder.start()
	elif build_target == "unittests":
		unit_tests = UnitTests()
		return unit_tests.start()
	elif build_target == "examples":
		examples = Examples()
		return examples.start()
	elif build_target == "clean":
		cleaner = Cleaner()
		return cleaner.clean()
	elif build_target == "rlibrary":
		rlibrary = RLibrary()
		return rlibrary.start()
	elif build_target == "rinstall":
		Globals.install_r_library = "true"
		rlibrary = RLibrary()
		return rlibrary.start()
	elif build_target == "installer":
		installer = Installer()
		return installer.start()
#	elif build_target == "deb":
#		deb_builder = DebBuilder()
#		return deb_builder.start(build_parameters)
	elif build_target == "version":
		version = Version()
		return version.create_version_header()
	return False # Default return from this, we didn't find a run mode
  
"""
This is the entry point in to our build system
"""
system_info = SystemInfo()
if not system_info.set_required_tools_paths():
  system_info.reset_original_path()
  exit(1)

exit_code = 0
if not start():
  exit_code = 1
  
system_info.reset_original_path()
print("--> Finished ")
exit(exit_code)  
