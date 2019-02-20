#include "otsdaq-core/TablePluginDataFormats/DataManagerTable.h"
#include <iostream>

#include "../../../otsdaq/otsdaq-core/Macros/TablePluginMacros.h"
#include "otsdaq-components/UserTableDataFormats/FEOtsUDPTemplateInterfaceTable.h"

using namespace ots;

//==============================================================================
FEWROtsUDPTemplateInterfaceTable::FEWROtsUDPTemplateInterfaceTable(void)
    : FEInterfaceTableBase("FEWROtsUDPTemplateInterfaceTable")
{
	//////////////////////////////////////////////////////////////////////
	// WARNING: the names and the order MUST match the ones in the enum  //
	//////////////////////////////////////////////////////////////////////
	// FEWROtsUDPTemplateInterfaceTableInfo.xml
	//<?xml version="1.0" encoding="UTF-8" standalone="no" ?>
	//<ROOT xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
	// xsi:noNamespaceSchemaLocation="TableInfo.xsd">
	//  <TABLE InterfaceID="FEWRPurdueFSSRInterfaceTable">
	//    <VIEW InterfaceID="FEWR_PURDUE_FSSR_INTERFACE_TABLE"
	//    Type="File,Database,DatabaseTest">
	//      <COLUMN NAME="InterfaceID"        StorageName="INTERFACE_ID"
	//      DataType="VARCHAR2"  /> <COLUMN InterfaceID="Status"
	//      StorageName="STATUS"               DataType="VARCHAR2"/> <COLUMN
	//      InterfaceID="FirmwareVersion"    StorageName="FIRMWARE_VERSION"
	//      DataType="NUMBER"  /> <COLUMN InterfaceID="IPAddress"
	//      StorageName="IP_ADDRESS"           DataType="VARCHAR2"/> <COLUMN
	//      InterfaceID="Port"               StorageName="PORT" DataType="NUMBER"  />
	//      <COLUMN InterfaceID="InterfaceIPAddress" StorageName="INTERFACE_IP_ADDRESS"
	//      DataType="VARCHAR2"/> <COLUMN InterfaceID="InterfacePort"
	//      StorageName="INTERFACE_PORT"       DataType="NUMBER"  /> <COLUMN
	//      InterfaceID="StreamingIPAddress" StorageName="STREAMING_IP_ADDRESS"
	//      DataType="VARCHAR2"/> <COLUMN InterfaceID="StreamingPort"
	//      StorageName="STREAMING_PORT"       DataType="NUMBER"  /> <COLUMN
	//      InterfaceID="NumberOfWords"      StorageName="NUMBER_OF_WORDS"
	//      DataType="NUMBER"  /> <COLUMN InterfaceID="DataRate"
	//      StorageName="DATA_RATE"            DataType="NUMBER"  />
	//    </VIEW>
	//  </TABLE>
	//</ROOT>
}

//==============================================================================
FEWROtsUDPTemplateInterfaceTable::~FEWROtsUDPTemplateInterfaceTable(void)
{
}

//==============================================================================
void FEWROtsUDPTemplateInterfaceTable::init(ConfigurationManager* configManager)
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
bool FEWROtsUDPTemplateInterfaceTable::getStatus(std::string interfaceID) const
{
	bool tmpStatus;
	TableBase::activeTableView_->getValue(
	    tmpStatus,
	    TableBase::activeTableView_->findRow(InterfaceID, interfaceID),
	    Status);
	return tmpStatus;
}

//==============================================================================
unsigned int FEWROtsUDPTemplateInterfaceTable::getFirmwareVersion(
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
std::string FEWROtsUDPTemplateInterfaceTable::getIPAddress(
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
unsigned int FEWROtsUDPTemplateInterfaceTable::getPort(
    std::string interfaceID) const
{
	unsigned int tmpPort;
	TableBase::activeTableView_->getValue(
	    tmpPort, TableBase::activeTableView_->findRow(InterfaceID, interfaceID), Port);
	return tmpPort;
}

//==============================================================================
std::string FEWROtsUDPTemplateInterfaceTable::getInterfaceIPAddress(
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
unsigned int FEWROtsUDPTemplateInterfaceTable::getInterfacePort(
    std::string interfaceID) const
{
	unsigned int tmpInterfacePort;
	TableBase::activeTableView_->getValue(
	    tmpInterfacePort,
	    TableBase::activeTableView_->findRow(InterfaceID, interfaceID),
	    InterfacePort);
	return tmpInterfacePort;
}

//==============================================================================
std::string FEWROtsUDPTemplateInterfaceTable::getStreamingIPAddress(
    std::string interfaceID) const
{
	std::string tmpStreamingIPAddress;
	TableBase::activeTableView_->getValue(
	    tmpStreamingIPAddress,
	    TableBase::activeTableView_->findRow(InterfaceID, interfaceID),
	    StreamingIPAddress);
	return tmpStreamingIPAddress;
}

//==============================================================================
unsigned int FEWROtsUDPTemplateInterfaceTable::getStreamingPort(
    std::string interfaceID) const
{
	unsigned int tmpStreamingPort;
	TableBase::activeTableView_->getValue(
	    tmpStreamingPort,
	    TableBase::activeTableView_->findRow(InterfaceID, interfaceID),
	    StreamingPort);
	return tmpStreamingPort;
}

//==============================================================================
int FEWROtsUDPTemplateInterfaceTable::getNumberOfWords(
    std::string interfaceID) const
{
	unsigned int tmpStreamingPort;
	TableBase::activeTableView_->getValue(
	    tmpStreamingPort,
	    TableBase::activeTableView_->findRow(InterfaceID, interfaceID),
	    NumberOfWords);
	return tmpStreamingPort;
}

//==============================================================================
unsigned int FEWROtsUDPTemplateInterfaceTable::getDataRate(
    std::string interfaceID) const
{
	unsigned int tmpStreamingPort;
	TableBase::activeTableView_->getValue(
	    tmpStreamingPort,
	    TableBase::activeTableView_->findRow(InterfaceID, interfaceID),
	    DataRate);
	return tmpStreamingPort;
}

DEFINE_OTS_TABLE(FEWROtsUDPTemplateInterfaceTable)
