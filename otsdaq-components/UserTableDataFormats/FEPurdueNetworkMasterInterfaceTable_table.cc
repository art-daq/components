#include <iostream>
#include "otsdaq-components/UserTableDataFormats/FEPurdueNetworkMasterInterfaceTable.h"
#include "otsdaq-core/Macros/TablePluginMacros.h"
#include "otsdaq-core/TablePluginDataFormats/DataManagerTable.h"

using namespace ots;

//==============================================================================
FEPurdueNetworkMasterInterfaceTable::FEPurdueNetworkMasterInterfaceTable(void)
    : FEInterfaceTableBase("FEPurdueNetworkMasterInterfaceTable")
{
	//////////////////////////////////////////////////////////////////////
	// WARNING: the names and the order MUST match the ones in the enum  //
	//////////////////////////////////////////////////////////////////////
	// FEPurdueNetworkMasterInterfaceTableInfo.xml
	//<?xml version="1.0" encoding="UTF-8" standalone="no" ?>
	//<ROOT xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
	// xsi:noNamespaceSchemaLocation="TableInfo.xsd">
	//  <TABLE Name="FEPurdueNetworkMasterInterfaceTable">
	//    <VIEW Name="FE_PURDUE_NETWORK_MASTER_INTERFACE_TABLE"
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
	//  </TABLE>
	//</ROOT>
}

//==============================================================================
FEPurdueNetworkMasterInterfaceTable::~FEPurdueNetworkMasterInterfaceTable(void) {}

//==============================================================================
void FEPurdueNetworkMasterInterfaceTable::init(ConfigurationManager* configManager)
{
	/*
	std::string       enumValue1;
	    unsigned int enumValue2;
	    for(unsigned int row=0; row<TableBase::tableData_.getNumberOfRows();
	row++)
	    {
	        TableBase::tableData_.getValue(enumValue1,row,Enum1);
	        TableBase::tableData_.getValue(enumValue2,row,Enum2);
	    }
	 */
}

//==============================================================================
bool FEPurdueNetworkMasterInterfaceTable::getStatus(std::string interfaceID) const
{
	bool tmpStatus;
	TableBase::activeTableView_->getValue(
	    tmpStatus,
	    TableBase::activeTableView_->findRow(InterfaceID, interfaceID),
	    Status);
	return tmpStatus;
}

//==============================================================================
unsigned int FEPurdueNetworkMasterInterfaceTable::getFirmwareVersion(
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
std::string FEPurdueNetworkMasterInterfaceTable::getIPAddress(
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
unsigned int FEPurdueNetworkMasterInterfaceTable::getPort(std::string interfaceID) const
{
	unsigned int tmpPort;
	TableBase::activeTableView_->getValue(
	    tmpPort, TableBase::activeTableView_->findRow(InterfaceID, interfaceID), Port);
	return tmpPort;
}

//==============================================================================
std::string FEPurdueNetworkMasterInterfaceTable::getInterfaceIPAddress(
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
unsigned int FEPurdueNetworkMasterInterfaceTable::getInterfacePort(
    std::string interfaceID) const
{
	unsigned int tmpInterfacePort;
	TableBase::activeTableView_->getValue(
	    tmpInterfacePort,
	    TableBase::activeTableView_->findRow(InterfaceID, interfaceID),
	    InterfacePort);
	return tmpInterfacePort;
}

DEFINE_OTS_TABLE(FEPurdueNetworkMasterInterfaceTable)
