include_directories(${MPI_INCLUDE_PATH})


simple_plugin(FEOtsUDPTemplateInterface "interface"
  DAQHardware
  FECore
  WorkLoopManager
  #MessageFacility
  Configurable
  NetworkUtilities
  ConfigurationInterface
  ConfigurationDataFormats
  $ENV{XERCES_C_LIB}/libxerces-c.so
  ${CETLIB}
  ${CETLIB_EXCEPT}
  )

#simple_plugin(FEOuterTrackerInterface "interface"
#  NetworkUtilities
#  FECore
#  ${CETLIB}
#  cactus_uhal_uhal
#  cactus_uhal_log
#  cactus_uhal_grammars 
#  $ENV{MRB_SOURCE}/otsdaq_cmsoutertracker/uhal/uhal_2_4_2/cactuscore/extern/pugixml/pugixml-1.2/libcactus_extern_pugixml.so
#  )

install_headers()
install_source()

