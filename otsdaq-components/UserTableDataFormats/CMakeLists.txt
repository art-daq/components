#cet_make(LIBRARY_NAME UserTableCore
#		 LIBRARIES
#         FECore
#         ${CETLIB}
#)

#install_headers()
#install_source()


simple_plugin(FEWROtsUDPFSSRInterfaceTable "table"
  TableCore  
  ConfigurationInterface
  ${CETLIB}
  )
    
simple_plugin(FEWROtsUDPTemplateInterfaceTable "table"
  TableCore  
  ConfigurationInterface
  ${CETLIB}
  )
  
simple_plugin(FEWRNIMPlusInterfaceTable "table"
  TableCore 
  ConfigurationInterface 
  ${CETLIB}
  )
    
simple_plugin(FEWRPurdueFSSRInterfaceTable "table"
  TableCore 
  ConfigurationInterface 
  ${CETLIB}
  )
    
simple_plugin(FEPurdueNetworkMasterInterfaceTable "table"
  TableCore  
  ConfigurationInterface
  ${CETLIB}
  )

simple_plugin(FSSRDACsConfiguration "table"
  TableCore  
  ConfigurationInterface
  ${CETLIB}
  )
   
