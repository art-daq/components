#include "otsdaq-components/UserConfigurationDataFormats/FENIMPlusInterfaceConfiguration.h"
#include "otsdaq-core/ConfigurationPluginDataFormats/DataManagerConfiguration.h"
#include "otsdaq-core/Macros/ConfigurationPluginMacros.h"

#include <iostream>

using namespace ots;

//==============================================================================
FENIMPlusInterfaceConfiguration::FENIMPlusInterfaceConfiguration(void)
    : FEInterfaceTableBase("FENIMPlusInterfaceConfiguration")
{
	//////////////////////////////////////////////////////////////////////
	// WARNING: the names and the order MUST match the ones in the enum  //
	//////////////////////////////////////////////////////////////////////
	// FENIMPlusInterfaceConfigurationInfo.xml
	//<?xml version="1.0" encoding="UTF-8" standalone="no" ?>
	//<ROOT xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
	// xsi:noNamespaceSchemaLocation="TableInfo.xsd">
	//  <CONFIGURATION InterfaceID="FEWRPurdueFSSRInterfaceConfiguration">
	//    <VIEW InterfaceID="FEWR_PURDUE_FSSR_INTERFACE_CONFIGURATION"
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
	//      InterfaceID="ClockSelect"        StorageName="CLOCK_SELECT"
	//      DataType="VARCHAR2"/> <COLUMN InterfaceID="ClockSpeedMHz"
	//      StorageName="CLOCK_SPEED_MHZ"      DataType="NUMBER"  /> <COLUMN
	//      InterfaceID="ChannelStatus0"     StorageName="CHANNEL0_STATUS"
	//      DataType="VARCHAR2"/> <COLUMN InterfaceID="ChannelStatus1"
	//      StorageName="CHANNEL1_STATUS"      DataType="VARCHAR2"/> <COLUMN
	//      InterfaceID="ChannelStatus2"     StorageName="CHANNEL2_STATUS"
	//      DataType="VARCHAR2"/> <COLUMN InterfaceID="ChannelStatus3"
	//      StorageName="CHANNEL3_STATUS"      DataType="VARCHAR2"/> <COLUMN
	//      InterfaceID="ChannelStatus4"     StorageName="CHANNEL4_STATUS"
	//      DataType="VARCHAR2"/> <COLUMN InterfaceID="ChannelStatus5"
	//      StorageName="CHANNEL5_STATUS"      DataType="VARCHAR2"/>
	//    </VIEW>
	//  </CONFIGURATION>
	//</ROOT>
}

//==============================================================================
FENIMPlusInterfaceConfiguration::~FENIMPlusInterfaceConfiguration(void) {}

//==============================================================================
void FENIMPlusInterfaceConfiguration::init(ConfigurationManager* configManager)
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
bool FENIMPlusInterfaceConfiguration::getStatus(std::string interfaceID) const
{
	bool tmpStatus;
	TableBase::activeTableView_->getValue(
	    tmpStatus,
	    TableBase::activeTableView_->findRow(InterfaceID, interfaceID),
	    Status);
	return tmpStatus;
}

//==============================================================================
unsigned int FENIMPlusInterfaceConfiguration::getFirmwareVersion(
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
std::string FENIMPlusInterfaceConfiguration::getIPAddress(std::string interfaceID) const
{
	std::string tmpIPAddress;
	TableBase::activeTableView_->getValue(
	    tmpIPAddress,
	    TableBase::activeTableView_->findRow(InterfaceID, interfaceID),
	    IPAddress);
	return tmpIPAddress;
}

//==============================================================================
unsigned int FENIMPlusInterfaceConfiguration::getPort(std::string interfaceID) const
{
	unsigned int tmpPort;
	TableBase::activeTableView_->getValue(
	    tmpPort, TableBase::activeTableView_->findRow(InterfaceID, interfaceID), Port);
	return tmpPort;
}

//==============================================================================
std::string FENIMPlusInterfaceConfiguration::getInterfaceIPAddress(
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
unsigned int FENIMPlusInterfaceConfiguration::getInterfacePort(
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
std::string FENIMPlusInterfaceConfiguration::getStreamingIPAddress(
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
unsigned int FENIMPlusInterfaceConfiguration::getStreamingPort(
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
std::string FENIMPlusInterfaceConfiguration::getClockSelect(std::string interfaceID) const
{
	std::string tmpClockSelect;
	TableBase::activeTableView_->getValue(
	    tmpClockSelect,
	    TableBase::activeTableView_->findRow(InterfaceID, interfaceID),
	    ClockSelect);
	return tmpClockSelect;
}

//==============================================================================
double FENIMPlusInterfaceConfiguration::getClockSpeedMHz(std::string interfaceID) const
{
	double tmpClockSpeedMHz;
	TableBase::activeTableView_->getValue(
	    tmpClockSpeedMHz,
	    TableBase::activeTableView_->findRow(InterfaceID, interfaceID),
	    ClockSpeedMHz);
	return tmpClockSpeedMHz;
}

//==============================================================================
bool FENIMPlusInterfaceConfiguration::getChannelStatus(std::string  interfaceID,
                                                       unsigned int channel) const
{
	bool tmpStatus;
	switch(channel)
	{
	case 0:
		TableBase::activeTableView_->getValue(
		    tmpStatus,
		    TableBase::activeTableView_->findRow(InterfaceID, interfaceID),
		    ChannelStatus0);
		break;
	case 1:
		TableBase::activeTableView_->getValue(
		    tmpStatus,
		    TableBase::activeTableView_->findRow(InterfaceID, interfaceID),
		    ChannelStatus1);
		break;
	case 2:
		TableBase::activeTableView_->getValue(
		    tmpStatus,
		    TableBase::activeTableView_->findRow(InterfaceID, interfaceID),
		    ChannelStatus2);
		break;
	case 3:
		TableBase::activeTableView_->getValue(
		    tmpStatus,
		    TableBase::activeTableView_->findRow(InterfaceID, interfaceID),
		    ChannelStatus3);
		break;
	case 4:
		TableBase::activeTableView_->getValue(
		    tmpStatus,
		    TableBase::activeTableView_->findRow(InterfaceID, interfaceID),
		    ChannelStatus4);
		break;
	case 5:
		TableBase::activeTableView_->getValue(
		    tmpStatus,
		    TableBase::activeTableView_->findRow(InterfaceID, interfaceID),
		    ChannelStatus5);
		break;
	default:  // There are only 6 channels on OtsUDPHardware board
		__SS____ << "Configuration Error:\t"
		         << "OtsUDPHardware FER Channel " << std::dec << channel
		         << " does not exist" << std::endl;
		__COUT_ERR__ << "\n" << ss.str();
		__SS_THROW__;
	}
	return tmpStatus;
}

DEFINE_OTS_CONFIGURATION(FENIMPlusInterfaceConfiguration)
