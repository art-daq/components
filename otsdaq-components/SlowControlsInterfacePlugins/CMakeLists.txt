
include(otsdaq::slowControls)
cet_build_plugin(OtsSlowControlsInterface otsdaq::slowControls	LIBRARIES REG
  )
install_headers()
install_source()
