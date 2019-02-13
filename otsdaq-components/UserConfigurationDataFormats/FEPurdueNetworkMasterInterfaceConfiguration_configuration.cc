#include "otsdaq-components/UserConfigurationDataFormats/FEPurdueNetworkMasterInterfaceConfiguration.h"
#include "otsdaq-core/ConfigurationPluginDataFormats/DataManagerConfiguration.h"
#include "otsdaq-core/Macros/ConfigurationPluginMacros.h"

#include <iostream>

using namespace ots;

//==============================================================================
FEPurdueNetworkMasterInterfaceConfiguration::FEPurdueNetworkMasterInterfaceConfiguration(void)
: FEInterfaceConfigurationBase("FEPurdueNetworkMasterInterfaceConfiguration")
{
	//////////////////////////////////////////////////////////////////////
	//WARNING: the names and the order MUST match the ones in the enum  //
	//////////////////////////////////////////////////////////////////////
	//FEPurdueNetworkMasterInterfaceConfigurationInfo.xml
	//<?xml version="1.0" encoding="UTF-8" standalone="no" ?>
	//<ROOT xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="ConfigurationInfo.xsd">
	//  <CONFIGURATION Name="FEPurdueNetworkMasterInterfaceConfiguration">
	//    <VIEW Name="FE_PURDUE_NETWORK_MASTER_INTERFACE_CONFIGURATION" Type="File,Database,DatabaseTest">
	//      <COLUMN NAME="InterfaceID"        StorageName="INTERFACE_ID"         DataType="VARCHAR2"  />
	//      <COLUMN Name="Status"             StorageName="STATUS"               DataType="VARCHAR2"/>
	//      <COLUMN Name="FirmwareVersion"    StorageName="FIRMWARE_VERSION"     DataType="NUMBER"  />
	//      <COLUMN Name="IPAddress"          StorageName="IP_ADDRESS"           DataType="VARCHAR2"/>
	//      <COLUMN Name="Port"               StorageName="PORT"                 DataType="NUMBER"  />
	//      <COLUMN Name="InterfaceIPAddress" StorageName="INTERFACE_IP_ADDRESS" DataType="VARCHAR2"/>
	//      <COLUMN Name="InterfacePort"      StorageName="INTERFACE_PORT"       DataType="NUMBER"  />
	//    </VIEW>
	//  </CONFIGURATION>
	//</ROOT>

}

//==============================================================================
FEPurdueNetworkMasterInterfaceConfiguration::~FEPurdueNetworkMasterInterfaceConfiguration(void)
{}

//==============================================================================
void FEPurdueNetworkMasterInterfaceConfiguration::init(ConfigurationManager *configManager)
{
	/*
    std::string       enumValue1;
        unsigned int enumValue2;
        for(unsigned int row=0; row<ConfigurationBase::configurationData_.getNumberOfRows(); row++)
        {
            ConfigurationBase::configurationData_.getValue(enumValue1,row,Enum1);
            ConfigurationBase::configurationData_.getValue(enumValue2,row,Enum2);
        }
	 */
}

//==============================================================================
bool  FEPurdueNetworkMasterInterfaceConfiguration::getStatus(std::string interfaceID) const
{
	bool tmpStatus;
	ConfigurationBase::activeConfigurationView_->getValue(tmpStatus, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID,interfaceID), Status);
	return tmpStatus;
}

//==============================================================================
unsigned int FEPurdueNetworkMasterInterfaceConfiguration::getFirmwareVersion(std::string interfaceID) const
{
	unsigned int tmpFirmwareVersion;
	ConfigurationBase::activeConfigurationView_->getValue(tmpFirmwareVersion, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID,interfaceID), FirmwareVersion);
	return tmpFirmwareVersion;
}

//==============================================================================
std::string FEPurdueNetworkMasterInterfaceConfiguration::getIPAddress(std::string interfaceID) const
{
	std::string tmpIPAddress;
	ConfigurationBase::activeConfigurationView_->getValue(tmpIPAddress, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID,interfaceID), IPAddress);
	return tmpIPAddress;
}

//==============================================================================
unsigned int FEPurdueNetworkMasterInterfaceConfiguration::getPort(std::string interfaceID) const
{
	unsigned int tmpPort;
	ConfigurationBase::activeConfigurationView_->getValue(tmpPort, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID,interfaceID), Port);
	return tmpPort;
}

//==============================================================================
std::string FEPurdueNetworkMasterInterfaceConfiguration::getInterfaceIPAddress(std::string interfaceID) const
{
	std::string tmpInterfaceIPAddress;
	ConfigurationBase::activeConfigurationView_->getValue(tmpInterfaceIPAddress, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID,interfaceID), InterfaceIPAddress);
	return tmpInterfaceIPAddress;
}

//==============================================================================
unsigned int FEPurdueNetworkMasterInterfaceConfiguration::getInterfacePort(std::string interfaceID) const
{
	unsigned int tmpInterfacePort;
	ConfigurationBase::activeConfigurationView_->getValue(tmpInterfacePort, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID,interfaceID), InterfacePort);
	return tmpInterfacePort;
}

DEFINE_OTS_CONFIGURATION(FEPurdueNetworkMasterInterfaceConfiguration)
