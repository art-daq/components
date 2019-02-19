#include "otsdaq-components/UserConfigurationDataFormats/FEPurdueNetworkMasterInterfaceConfiguration.h"
#include "otsdaq-core/ConfigurationPluginDataFormats/DataManagerConfiguration.h"
#include "otsdaq-core/Macros/ConfigurationPluginMacros.h"

#include <iostream>

using namespace ots;

//==============================================================================
FEPurdueNetworkMasterInterfaceConfiguration::FEPurdueNetworkMasterInterfaceConfiguration(
    void)
    : FEInterfaceTableBase("FEPurdueNetworkMasterInterfaceConfiguration")
{
	//////////////////////////////////////////////////////////////////////
	// WARNING: the names and the order MUST match the ones in the enum  //
	//////////////////////////////////////////////////////////////////////
	// FEPurdueNetworkMasterInterfaceConfigurationInfo.xml
	//<?xml version="1.0" encoding="UTF-8" standalone="no" ?>
	//<ROOT xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
	// xsi:noNamespaceSchemaLocation="TableInfo.xsd">
	//  <CONFIGURATION Name="FEPurdueNetworkMasterInterfaceConfiguration">
	//    <VIEW Name="FE_PURDUE_NETWORK_MASTER_INTERFACE_CONFIGURATION"
	//    Type="File,Database,DatabaseTest">
	//      <COLUMN NAME="InterfaceID"        StorageName="INTERFACE_ID"
	//      DataType="VARCHAR2"  /> <COLUMN Name="Status"             StorageName="STATUS"
	//      DataType="VARCHAR2"/> <COLUMN Name="FirmwareVersion"
	//      StorageName="FIRMWARE_VERSION"     DataType="NUMBER"  /> <COLUMN
	//      Name="IPAddress"          StorageName="IP_ADDRESS" DataType="VARCHAR2"/>
	//      <COLUMN Name="Port"               StorageName="PORT" DataType="NUMBER"  />
	//      <COLUMN Name="InterfaceIPAddress" StorageName="INTERFACE_IP_ADDRESS"
	//      DataType="VARCHAR2"/> <COLUMN Name="InterfacePort"
	//      StorageName="INTERFACE_PORT"       DataType="NUMBER"  />
	//    </VIEW>
	//  </CONFIGURATION>
	//</ROOT>
}

//==============================================================================
FEPurdueNetworkMasterInterfaceConfiguration::~FEPurdueNetworkMasterInterfaceConfiguration(
    void)
{
}

//==============================================================================
void FEPurdueNetworkMasterInterfaceConfiguration::init(
    ConfigurationManager* configManager)
{
	/*
	std::string       enumValue1;
	    unsigned int enumValue2;
	    for(unsigned int row=0; row<TableBase::configurationData_.getNumberOfRows();
	row++)
	    {
	        TableBase::configurationData_.getValue(enumValue1,row,Enum1);
	        TableBase::configurationData_.getValue(enumValue2,row,Enum2);
	    }
	 */
}

//==============================================================================
bool FEPurdueNetworkMasterInterfaceConfiguration::getStatus(std::string interfaceID) const
{
	bool tmpStatus;
	TableBase::activeTableView_->getValue(
	    tmpStatus,
	    TableBase::activeTableView_->findRow(InterfaceID, interfaceID),
	    Status);
	return tmpStatus;
}

//==============================================================================
unsigned int FEPurdueNetworkMasterInterfaceConfiguration::getFirmwareVersion(
    std::string interfaceID) const
{
	unsigned int tmpFirmwareVersion;
	TableBase::activeTableView_->getValue(
	    tmpFirmwareVersion,
	    TableBase::activeTableView_->findRow(InterfaceID, interfaceID),
	    FirmwareVersion);
	return tmpFirmwareVersion;
}

//==============================================================================
std::string FEPurdueNetworkMasterInterfaceConfiguration::getIPAddress(
    std::string interfaceID) const
{
	std::string tmpIPAddress;
	TableBase::activeTableView_->getValue(
	    tmpIPAddress,
	    TableBase::activeTableView_->findRow(InterfaceID, interfaceID),
	    IPAddress);
	return tmpIPAddress;
}

//==============================================================================
unsigned int FEPurdueNetworkMasterInterfaceConfiguration::getPort(
    std::string interfaceID) const
{
	unsigned int tmpPort;
	TableBase::activeTableView_->getValue(
	    tmpPort, TableBase::activeTableView_->findRow(InterfaceID, interfaceID), Port);
	return tmpPort;
}

//==============================================================================
std::string FEPurdueNetworkMasterInterfaceConfiguration::getInterfaceIPAddress(
    std::string interfaceID) const
{
	std::string tmpInterfaceIPAddress;
	TableBase::activeTableView_->getValue(
	    tmpInterfaceIPAddress,
	    TableBase::activeTableView_->findRow(InterfaceID, interfaceID),
	    InterfaceIPAddress);
	return tmpInterfaceIPAddress;
}

//==============================================================================
unsigned int FEPurdueNetworkMasterInterfaceConfiguration::getInterfacePort(
    std::string interfaceID) const
{
	unsigned int tmpInterfacePort;
	TableBase::activeTableView_->getValue(
	    tmpInterfacePort,
	    TableBase::activeTableView_->findRow(InterfaceID, interfaceID),
	    InterfacePort);
	return tmpInterfacePort;
}

DEFINE_OTS_CONFIGURATION(FEPurdueNetworkMasterInterfaceConfiguration)
