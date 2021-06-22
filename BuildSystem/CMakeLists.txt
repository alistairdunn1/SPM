cmake_minimum_required(VERSION 2.6)
project(SPM)

# Currently set up for GCC 10.3, using TDM-GCC x64

# to run (Windows, Mingw32-gcc)
#   cmake -G "MinGW Makefiles"
#   mingw32-make all
# or Linux
#   cmake -G "Unix Makefiles"
#   make all

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

SET(MAIN_NAME spm_unoptimised)
SET(TEST_NAME spm_unittests)
SET(OPTI_NAME spm)

IF (WIN32)
  INCLUDE_DIRECTORIES("${CMAKE_BINARY_DIR}/Boost/include/")
  LINK_DIRECTORIES("${CMAKE_BINARY_DIR}/Boost/lib")
  
  # Generic Build Settings
  SET(LINK_OPTIONS "-static icon.o")
  SET(COMPILE_OPTIONS_MAIN "-DBOOST_THREAD_USE_LIB=1 -DBOOST_THREAD_PROVIDES_GENERIC_SHARED_MUTEX_ON_WIN -O0 -g3 -Wno-deprecated-declarations -fmessage-length=0 -fopenmp -static -std=c++17")
  SET(COMPILE_OPTIONS_OPTI "-DBOOST_THREAD_USE_LIB=1 -DBOOST_THREAD_PROVIDES_GENERIC_SHARED_MUTEX_ON_WIN -DOPTIMIZE -O3 -g0 -Wall  -Wno-deprecated-declarations -fmessage-length=0 -fopenmp -static -std=c++17")
  SET(COMPILE_OPTIONS_TEST "-DBOOST_THREAD_USE_LIB=1 -DBOOST_THREAD_PROVIDES_GENERIC_SHARED_MUTEX_ON_WIN -DTEST -O0 -g3 -Wall -Wno-deprecated-declarations -fmessage-length=0 -fopenmp -static -std=c++17")
  ADD_CUSTOM_TARGET(icon ALL
    COMMAND windres --output icon.o --input "../../Source/spm.rc"
  )
  SET(MAIN_LIBRARIES    
    gomp
    pthread
    boost_system-mgw103-mt-s-x64-1_71
    boost_filesystem-mgw103-mt-s-x64-1_71
    boost_thread-mgw103-mt-s-x64-1_71
    boost_program_options-mgw103-mt-s-x64-1_71
    boost_chrono-mgw103-mt-s-x64-1_71
  )
  SET(TEST_LIBRARIES boost_unit_test_framework-mgw103-mt-s-x64-1_71)
  
ELSE (WIN32)
  SET(BOOST_LIBS "${CMAKE_BINARY_DIR}/Boost/lib")
  SET(BOOST_HEADERS "${CMAKE_BINARY_DIR}/Boost/include/")
  SET(LINK_OPTIONS "-L ${BOOST_LIBS} -lstdc++ -Wl,--no-as-needed -ldl")
  SET(COMPILE_OPTIONS_LIBR "-DBOOST_THREAD_USE_LIB=1 -O0 -g3 -ggdb -Wall -Werror -fmessage-length=0 -fopenmp -Wno-unused-local-typedefs -I ${BOOST_HEADERS} -std=c++17 ")
  SET(COMPILE_OPTIONS_MAIN "-DBOOST_THREAD_USE_LIB=1 -O0 -g3 -Wall -fmessage-length=0 -fopenmp -Wno-unused-local-typedefs -I ${BOOST_HEADERS} -std=c++17")
  SET(COMPILE_OPTIONS_OPTI "-DBOOST_THREAD_USE_LIB=1 -DOPTIMIZE -O3 -g0 -Wall -fmessage-length=0 -fopenmp -Wno-unused-local-typedefs -I ${BOOST_HEADERS} -std=c++17")
  SET(COMPILE_OPTIONS_TEST "-DBOOST_THREAD_USE_LIB=1 -DTEST -O0 -g3 -Wall -fmessage-length=0 -fopenmp -Wno-unused-local-typedefs -I ${BOOST_HEADERS} -std=c++17")
  SET(MAIN_LIBRARIES
    boost_system
    boost_filesystem
    boost_thread
    boost_program_options    
    gomp
    pthread
    )
  SET(TEST_LIBRARIES boost_unit_test_framework)
ENDIF (WIN32)

FILE(GLOB_RECURSE SOURCE_FILES "../Source/*.cpp")
FILE(GLOB_RECURSE TEST_FILES "../Source/*.Test.cpp")
list(REMOVE_ITEM SOURCE_FILES ${TEST_FILES})

# Build SPM unoptimised
ADD_EXECUTABLE(${MAIN_NAME} ${SOURCE_FILES})
SET_TARGET_PROPERTIES(${MAIN_NAME} PROPERTIES COMPILE_FLAGS ${COMPILE_OPTIONS_MAIN} LINK_FLAGS ${LINK_OPTIONS})
TARGET_LINK_LIBRARIES(${MAIN_NAME} ${MAIN_LIBRARIES})

# Build SPM unit tests
ADD_EXECUTABLE(${TEST_NAME} ${SOURCE_FILES} ${TEST_FILES})
SET_TARGET_PROPERTIES(${TEST_NAME} PROPERTIES COMPILE_FLAGS ${COMPILE_OPTIONS_TEST} LINK_FLAGS ${LINK_OPTIONS})
TARGET_LINK_LIBRARIES(${TEST_NAME} ${MAIN_LIBRARIES} ${TEST_LIBRARIES})

# Build SPM optimised
ADD_EXECUTABLE(${OPTI_NAME} ${SOURCE_FILES})
SET_TARGET_PROPERTIES(${OPTI_NAME} PROPERTIES COMPILE_FLAGS ${COMPILE_OPTIONS_OPTI} LINK_FLAGS ${LINK_OPTIONS})
TARGET_LINK_LIBRARIES(${OPTI_NAME} ${MAIN_LIBRARIES})

ADD_DEPENDENCIES(${MAIN_NAME} icon)
ADD_DEPENDENCIES(${TEST_NAME} icon)
ADD_DEPENDENCIES(${OPTI_NAME} icon)
