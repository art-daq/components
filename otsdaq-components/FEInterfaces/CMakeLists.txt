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
  ${CETLIB}
  ${CETLIB_EXCEPT}
  ${XDAQ_XERCES-C}
  pthread
  )
  
simple_plugin(FEOtsUDPTemplateInterface "interface"
  DAQHardware
  FECore
  WorkLoopManager
  Configurable
  ${CETLIB}
  ${CETLIB_EXCEPT}
  ${XDAQ_XERCES-C}
  pthread
  )

install_headers()
install_source()

