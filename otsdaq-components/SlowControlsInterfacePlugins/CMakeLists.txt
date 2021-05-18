
simple_plugin(OtsSlowControlsInterface "slowcontrols"	
    otsdaq::SlowControlsCore   
	otsdaq::Configurable
	otsdaq::TableCore
	otsdaq::ConfigurationInterface
	MF_MessageLogger
  )

install_headers()
install_source()
