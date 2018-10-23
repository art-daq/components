cet_make(LIBRARY_NAME OTSDAQComponentsFEInterfaces
	EXCLUDE FEOtsUDPTemplateInterface_interface.cc
	LIBRARIES
	DAQHardware
	FECore
	WorkLoopManager
	Configurable
)


simple_plugin(FEOtsUDPTemplateInterface "interface"
  DAQHardware
  FECore
  WorkLoopManager
  Configurable
  ${CETLIB}
  ${CETLIB_EXCEPT}
  )

install_headers()
install_source()

