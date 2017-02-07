#cet_make(LIBRARY_NAME UserConfigurationDataFormats
#		 LIBRARIES
#         FECore
#         ${CETLIB}
#)

#install_headers()
#install_source()


simple_plugin(FEWROtsUDPFSSRInterfaceConfiguration "configuration"
  ConfigurationDataFormats  
  ${CETLIB}
  )
    
simple_plugin(FEWROtsUDPTemplateInterfaceConfiguration "configuration"
  ConfigurationDataFormats  
  ${CETLIB}
  )
  
simple_plugin(FEWRNIMPlusInterfaceConfiguration "configuration"
  ConfigurationDataFormats  
  ${CETLIB}
  )
    
simple_plugin(FEWRPurdueFSSRInterfaceConfiguration "configuration"
  ConfigurationDataFormats  
  ${CETLIB}
  )
    
simple_plugin(FEPurdueNetworkMasterInterfaceConfiguration "configuration"
  ConfigurationDataFormats  
  ${CETLIB}
  )

simple_plugin(FSSRDACsConfiguration "configuration"
  ConfigurationDataFormats  
  ${CETLIB}
  )
   
