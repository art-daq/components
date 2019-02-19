#cet_make(LIBRARY_NAME UserTableCore
#		 LIBRARIES
#         FECore
#         ${CETLIB}
#)

#install_headers()
#install_source()


simple_plugin(FEWROtsUDPFSSRInterfaceConfiguration "configuration"
  TableCore  
  ConfigurationInterface
  ${CETLIB}
  )
    
simple_plugin(FEWROtsUDPTemplateInterfaceConfiguration "configuration"
  TableCore  
  ConfigurationInterface
  ${CETLIB}
  )
  
simple_plugin(FEWRNIMPlusInterfaceConfiguration "configuration"
  TableCore 
  ConfigurationInterface 
  ${CETLIB}
  )
    
simple_plugin(FEWRPurdueFSSRInterfaceConfiguration "configuration"
  TableCore 
  ConfigurationInterface 
  ${CETLIB}
  )
    
simple_plugin(FEPurdueNetworkMasterInterfaceConfiguration "configuration"
  TableCore  
  ConfigurationInterface
  ${CETLIB}
  )

simple_plugin(FSSRDACsConfiguration "configuration"
  TableCore  
  ConfigurationInterface
  ${CETLIB}
  )
   
