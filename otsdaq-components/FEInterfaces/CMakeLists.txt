#cet_make(LIBRARY_NAME OTSDAQComponentsFEInterfaces
#	EXCLUDE
#		FEOtsUDPTemplateInterface_interface.cc
#	LIBRARIES
#		DAQHardware
#		FECore
#		WorkLoopManager
#		Configurable
#)


basic_plugin(FEOtsUDPProducerTemplateInterface "interface"
  otsdaq_components::DAQHardware
  otsdaq::FECore
  otsdaq::WorkLoopManager
  otsdaq::Configurable
  otsdaq::DataManager
  otsdaq::ConfigurationInterface
  otsdaq::TableCore
  otsdaq::Macros
  MF_MessageLogger
  cetlib
  cetlib_except
  ${XDAQ_XERCES-C}
${Boost_SYSTEM_LIBRARY}
  pthread
  )
  
basic_plugin(FEOtsUDPTemplateInterface "interface"
  otsdaq_components::DAQHardware
  otsdaq::FECore
  otsdaq::WorkLoopManager
  otsdaq::Configurable
  otsdaq::ConfigurationInterface
  otsdaq::TableCore
  otsdaq::Macros
  cetlib
  cetlib_except
  ${XDAQ_XERCES-C}
  MF_MessageLogger
${Boost_SYSTEM_LIBRARY}
  pthread
  )

install_headers()
install_source()

