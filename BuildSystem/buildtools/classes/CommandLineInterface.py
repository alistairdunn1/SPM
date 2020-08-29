import sys
import os

import Globals

class CommandLineInterface:
	def __init__(self):
		print('--> Spawning Command Line Interface Parser')

	def print_usage(self):
		#os.system( [ 'clear', 'cls' ][ os.name == 'nt' ] )
		print('###########################################################')
		print( '# SPM Build System Usage                                  #')
		print( '###########################################################')
		print( 'Usage:')
		print( 'doBuild <build_target>')
		print( '')
		print( 'Valid Build Types:')
		print( '  help          - Print this help page')
		print( '  check         - Do a check of the build system')
		print( '  boost         - Build boost libraries (build this before building the release)')
		print( '  release       - Build standalone release executable')
		print( '  examples      - Build the SPM examples')
		print( '  documentation - Build the user manual')
		print( '  rlibrary      - Build the R library')
		print( '  unittests     - Run the unit tests')
		print( '  installer     - Build a MS-Windows installer package')
		print( '  deb           - Build the Linux .deb installer')
		print( '  archive       - Build a zipped archive of the application.')
		print( '  clean         - Remove any previous debug/release build information')
		print( '')
		return True

	def parse(self):
		print('--> Parsing Command Line Parameters')
		build_target = ""

		"""
		Handle build information already passed in
		"""
		if len(sys.argv) != 2:
			return Globals.PrintError('Please provide a single valid build target. Use doBuild help to see options');

		build_target = str(sys.argv[1])
		build_target = build_target.lower()    

		if build_target == "help":
			return False

		if build_target == "check":
			print("--> All checks completed successfully")
			return True

		if build_target == "":
			return Globals.PrintError('Please provide a valid build target. Use doBuild help to see options');
		if not build_target in Globals.allowed_build_targets_:
			return Globals.PrintError(build_target + " is not a valid build target")


		if build_target == "check":
			print("--> All checks completed successfully")
			return True

		Globals.build_target_ = build_target

		print("-- Build target: " + Globals.build_target_)

		return True
