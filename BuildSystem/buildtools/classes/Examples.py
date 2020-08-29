import os
import sys
import subprocess
import os.path
import fileinput
import re
from datetime import datetime, date
#from dateutil import tz

import Globals

EX_OK = getattr(os, "EX_OK", 0)

class Examples:
  def start(self):
    if Globals.operating_system_ == "windows":
      if os.path.exists(Globals.root_directory_ + '/examples'):
        os.chdir(Globals.root_directory_ + '/examples')
      print('--> Building SPM Examples')
      print('')
      os.system("run.bat")
      result = True
    else:
      return Globals.PrintError('Failed to run examples')
