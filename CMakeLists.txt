# ======================================================================
#  otsdaq-components main build file
#
#  cd .../path/to/build/directory
#  source .../path/to/otsdaq-components/ups/setup_for_development
#  buildtool
# ======================================================================


# use cmake 3.17 or later
cmake_minimum_required (VERSION 3.19 FATAL_ERROR)

find_package(cetmodules 3.16.00 REQUIRED)

project(otsdaq_components VERSION 2.06.08)

include(CetCMakeEnv)
cet_cmake_env()

cet_set_compiler_flags(
 DIAGS 
 VIGILANT
 WERROR
 NO_UNDEFINED
 EXTRA_FLAGS -pedantic -D_LIBCPP_ENABLE_CXX17_REMOVED_FEATURES=1
 )
 
cet_remove_compiler_flags(-std=c++98)

find_package(otsdaq 2.06.06 REQUIRED EXPORT)
 
 # XDAQ Extra setup
 include_directories($ENV{XDAQ_INC}/linux $ENV{XDAQ_INC})
link_directories($ENV{XDAQ_LIB})
link_directories($ENV{ARTDAQ_DATABASE_LIB})
 set(XDAQ_BASIC_LIB_LIST 
   xcept
   xoap
   xdaq
   toolbox
   xerces-c
   cgicc
 )
 set(XDAQ_XERCES-C xerces-c)

 include(BuildPlugins)

# Code
add_subdirectory(otsdaq-components)

# doxygen
if( $ENV{OTS_DOXY} MATCHES "DOIT" )
	add_subdirectory(doc)
endif()

cet_cmake_config()
