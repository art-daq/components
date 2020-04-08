#cet_make(LIBRARY_NAME OTSDAQComponentsFEInterfaces
#	EXCLUDE
#		FEOtsUDPTemplateInterface_interface.cc
#	LIBRARIES
#		DAQHardware
#		FECore
#		WorkLoopManager
#		Configurable
#)


simple_plugin(FEOtsUDPProducerTemplateInterface "interface"
  DAQHardware
  FECore
  WorkLoopManager
  Configurable
  DataManager
  ConfigurationInterface
  TableCore
  Macros
  ${MF_MESSAGELOGGER}
  ${CETLIB}
  ${CETLIB_EXCEPT}
  ${XDAQ_XERCES-C}
${Boost_SYSTEM_LIBRARY}
  pthread
  )
  
simple_plugin(FEOtsUDPTemplateInterface "interface"
  DAQHardware
  FECore
  WorkLoopManager
  Configurable
  ConfigurationInterface
  TableCore
  Macros
  ${CETLIB}
  ${CETLIB_EXCEPT}
  ${XDAQ_XERCES-C}
  ${MF_MESSAGELOGGER}
${Boost_SYSTEM_LIBRARY}
  pthread
  )

install_headers()
install_source()

