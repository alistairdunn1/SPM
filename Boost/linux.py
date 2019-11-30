import os
import os.path
import shutil
from distutils import dir_util

import Globals

class Builder():

  def start(self):    
    # Figure out GCC version
    pieces = Globals.compiler_version_.split('.')
    if len(pieces) != 3:
      return Globals.PrintError('Boost could not parse GCC Version properly: ' + Globals.compiler_version_)
    
    gcc_version = str(pieces[0]) + str(pieces[1])
    print('-- GCC Version for Boost: ' + gcc_version)
    
    boostFileName = Globals.boost_source_directory_ + '/' + Globals.boost_version

    if not os.path.exists(Globals.boost_directory_):
      os.mkdir(Globals.boost_directory_)
    os.chdir(Globals.boost_directory_)
  
    # Decompress our boost archive
    if not os.path.exists('temp.tar') and not os.path.exists('temp.tar.gz'):
      print('-- Copying Boost archive')
      os.system('cp ' + boostFileName + '.tar.gz temp.tar.gz')

    # Decompress our boost archive
    print('-- Decompressing Boost')
    if os.path.exists('temp.tar.gz'):
      os.system('gzip -f -d temp.tar.gz')
    
    if os.path.exists('temp.tar'):
      os.system('tar -xf temp.tar')
      os.system('rm -rf temp.tar')

    else:
        return Globals.PrintError('Unable to Decompress ' + boostFileName + 'tar.gz')
    
    # Build Boost
    print('-- Building Boost - check spm_build.log for progress')
    folder = Globals.boost_directory_ + '/' + Globals.boost_version + '/'
    print('-- Folder: ' + folder)
    if not os.path.exists(folder):
      os.mkdir(folder)
    os.chdir(folder)
    os.system('./bootstrap.sh gcc 1> spm_bootstrap.log 2>&1')
    #os.system("./b2 address-model=64 architecture=x86 --toolset=gcc link=static threading=multi -j " + Globals.threads_ + " cxxflags='-fPIC' 1> spm_build.log 2>&1")
    os.system('./b2 --toolset=gcc link=static threading=multi -j ' + Globals.threads_ + ' 1> spm_build.log 2>&1')
    print('-- Completed Boost')
    
    return True

