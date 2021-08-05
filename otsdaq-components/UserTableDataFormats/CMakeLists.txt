#cet_make(LIBRARY_NAME UserTableCore
#		 LIBRARIES
#         FECore
#         cetlib
#)

#install_headers()
#install_source()


simple_plugin(FEWROtsUDPFSSRInterfaceTable "table"
  TableCore  
  ConfigurationInterface
  cetlib
  )
    
simple_plugin(FEWROtsUDPTemplateInterfaceTable "table"
  TableCore  
  ConfigurationInterface
  cetlib
  )
  
simple_plugin(FEWRNIMPlusInterfaceTable "table"
  TableCore 
  ConfigurationInterface 
  cetlib
  )
    
simple_plugin(FEWRPurdueFSSRInterfaceTable "table"
  TableCore 
  ConfigurationInterface 
  cetlib
  )
    
simple_plugin(FEPurdueNetworkMasterInterfaceTable "table"
  TableCore  
  ConfigurationInterface
  cetlib
  )

simple_plugin(FSSRDACsConfiguration "table"
  TableCore  
  ConfigurationInterface
  cetlib
  )
   
