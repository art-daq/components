#cet_make(LIBRARY_NAME UserConfigurationDataFormats
#		 LIBRARIES
#         FECore
#         ${CETLIB}
#)

#install_headers()
#install_source()


simple_plugin(FEWROtsUDPFSSRInterfaceConfiguration "configuration"
  ConfigurationDataFormats  
  ConfigurationInterface
  ${CETLIB}
  )
    
simple_plugin(FEWROtsUDPTemplateInterfaceConfiguration "configuration"
  ConfigurationDataFormats  
  ConfigurationInterface
  ${CETLIB}
  )
  
simple_plugin(FEWRNIMPlusInterfaceConfiguration "configuration"
  ConfigurationDataFormats 
  ConfigurationInterface 
  ${CETLIB}
  )
    
simple_plugin(FEWRPurdueFSSRInterfaceConfiguration "configuration"
  ConfigurationDataFormats 
  ConfigurationInterface 
  ${CETLIB}
  )
    
simple_plugin(FEPurdueNetworkMasterInterfaceConfiguration "configuration"
  ConfigurationDataFormats  
  ConfigurationInterface
  ${CETLIB}
  )

simple_plugin(FSSRDACsConfiguration "configuration"
  ConfigurationDataFormats  
  ConfigurationInterface
  ${CETLIB}
  )
   
