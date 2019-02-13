#include "otsdaq-core/ConfigurationPluginDataFormats/DataManagerConfiguration.h"
#include "otsdaq-core/Macros/ConfigurationPluginMacros.h"

#include <iostream>
#include "otsdaq-components/UserConfigurationDataFormats/FEPurdueFSSRInterfaceConfiguration.h"

using namespace ots;

//==============================================================================
FEPurdueFSSRInterfaceConfiguration::FEPurdueFSSRInterfaceConfiguration(void)
    : FEInterfaceConfigurationBase("FEPurdueFSSRInterfaceConfiguration") {
  //////////////////////////////////////////////////////////////////////
  // WARNING: the names and the order MUST match the ones in the enum  //
  //////////////////////////////////////////////////////////////////////
  // FEPurdueFSSRInterfaceConfigurationInfo.xml
  //<?xml version="1.0" encoding="UTF-8" standalone="no" ?>
  //<ROOT xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="ConfigurationInfo.xsd">
  //  <CONFIGURATION Name="FEPurdueFSSRInterfaceConfiguration">
  //    <VIEW Name="FEWR_OTS_UDP_FSSR_INTERFACE_CONFIGURATION" Type="File,Database,DatabaseTest">
  //      <COLUMN NAME="InterfaceID"        StorageName="INTERFACE_ID"         DataType="VARCHAR2"  />
  //      <COLUMN Name="Status"             StorageName="STATUS"               DataType="VARCHAR2"/>
  //      <COLUMN Name="FirmwareVersion"    StorageName="FIRMWARE_VERSION"     DataType="NUMBER"  />
  //      <COLUMN Name="IPAddress"          StorageName="IP_ADDRESS"           DataType="VARCHAR2"/>
  //      <COLUMN Name="Port"               StorageName="PORT"                 DataType="NUMBER"  />
  //      <COLUMN Name="InterfaceIPAddress" StorageName="INTERFACE_IP_ADDRESS" DataType="VARCHAR2"/>
  //      <COLUMN Name="InterfacePort"      StorageName="INTERFACE_PORT"       DataType="NUMBER"  />
  //      <COLUMN Name="StreamingIPAddress" StorageName="STREAMING_IP_ADDRESS" DataType="VARCHAR2"/>
  //      <COLUMN Name="StreamingPort"      StorageName="STREAMING_PORT"       DataType="NUMBER"  />
  //      <COLUMN Name="ClockSelect"        StorageName="CLOCK_SELECT"         DataType="VARCHAR2"/>
  //      <COLUMN Name="ClockSpeedMHz"      StorageName="CLOCK_SPEED_MHZ"      DataType="NUMBER"  />
  //    </VIEW>
  //  </CONFIGURATION>
  //</ROOT>
}

//==============================================================================
FEPurdueFSSRInterfaceConfiguration::~FEPurdueFSSRInterfaceConfiguration(void) {}

//==============================================================================
void FEPurdueFSSRInterfaceConfiguration::init(ConfigurationManager *configManager) {
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
bool FEPurdueFSSRInterfaceConfiguration::getStatus(std::string interfaceID) const {
  bool tmpStatus;
  ConfigurationBase::activeConfigurationView_->getValue(
      tmpStatus, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID, interfaceID), Status);
  return tmpStatus;
}

//==============================================================================
unsigned int FEPurdueFSSRInterfaceConfiguration::getFirmwareVersion(std::string interfaceID) const {
  unsigned int tmpFirmwareVersion;
  ConfigurationBase::activeConfigurationView_->getValue(
      tmpFirmwareVersion, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID, interfaceID),
      FirmwareVersion);
  return tmpFirmwareVersion;
}

//==============================================================================
std::string FEPurdueFSSRInterfaceConfiguration::getIPAddress(std::string interfaceID) const {
  std::string tmpIPAddress;
  ConfigurationBase::activeConfigurationView_->getValue(
      tmpIPAddress, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID, interfaceID), IPAddress);
  return tmpIPAddress;
}

//==============================================================================
unsigned int FEPurdueFSSRInterfaceConfiguration::getPort(std::string interfaceID) const {
  unsigned int tmpPort;
  ConfigurationBase::activeConfigurationView_->getValue(
      tmpPort, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID, interfaceID), Port);
  return tmpPort;
}

//==============================================================================
std::string FEPurdueFSSRInterfaceConfiguration::getInterfaceIPAddress(std::string interfaceID) const {
  std::string tmpInterfaceIPAddress;
  ConfigurationBase::activeConfigurationView_->getValue(
      tmpInterfaceIPAddress, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID, interfaceID),
      InterfaceIPAddress);
  return tmpInterfaceIPAddress;
}

//==============================================================================
unsigned int FEPurdueFSSRInterfaceConfiguration::getInterfacePort(std::string interfaceID) const {
  unsigned int tmpInterfacePort;
  ConfigurationBase::activeConfigurationView_->getValue(
      tmpInterfacePort, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID, interfaceID), InterfacePort);
  return tmpInterfacePort;
}

//==============================================================================
std::string FEPurdueFSSRInterfaceConfiguration::getStreamingIPAddress(std::string interfaceID) const {
  std::string tmpStreamingIPAddress;
  ConfigurationBase::activeConfigurationView_->getValue(
      tmpStreamingIPAddress, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID, interfaceID),
      StreamingIPAddress);
  return tmpStreamingIPAddress;
}

//==============================================================================
unsigned int FEPurdueFSSRInterfaceConfiguration::getStreamingPort(std::string interfaceID) const {
  unsigned int tmpStreamingPort;
  ConfigurationBase::activeConfigurationView_->getValue(
      tmpStreamingPort, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID, interfaceID), StreamingPort);
  return tmpStreamingPort;
}

//==============================================================================
std::string FEPurdueFSSRInterfaceConfiguration::getClockSelect(std::string interfaceID) const {
  std::string tmpClockSelect;
  ConfigurationBase::activeConfigurationView_->getValue(
      tmpClockSelect, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID, interfaceID), ClockSelect);
  return tmpClockSelect;
}

//==============================================================================
double FEPurdueFSSRInterfaceConfiguration::getClockSpeedMHz(std::string interfaceID) const {
  double tmpClockSpeedMHz;
  ConfigurationBase::activeConfigurationView_->getValue(
      tmpClockSpeedMHz, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID, interfaceID), ClockSpeedMHz);
  return tmpClockSpeedMHz;
}

//==============================================================================
bool FEPurdueFSSRInterfaceConfiguration::getChannelStatus(std::string interfaceID, unsigned int channel) const {
  bool tmpStatus;
  switch (channel) {
    case 0:
      ConfigurationBase::activeConfigurationView_->getValue(
          tmpStatus, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID, interfaceID), ChannelStatus0);
      break;
    case 1:
      ConfigurationBase::activeConfigurationView_->getValue(
          tmpStatus, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID, interfaceID), ChannelStatus1);
      break;
    case 2:
      ConfigurationBase::activeConfigurationView_->getValue(
          tmpStatus, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID, interfaceID), ChannelStatus2);
      break;
    case 3:
      ConfigurationBase::activeConfigurationView_->getValue(
          tmpStatus, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID, interfaceID), ChannelStatus3);
      break;
    case 4:
      ConfigurationBase::activeConfigurationView_->getValue(
          tmpStatus, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID, interfaceID), ChannelStatus4);
      break;
    case 5:
      ConfigurationBase::activeConfigurationView_->getValue(
          tmpStatus, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID, interfaceID), ChannelStatus5);
      break;
    default:  // There are only 6 channels on OtsUDPHardware board
      __SS__ << "Configuration Error:\t"
             << "OtsUDPHardware FER Channel " << std::dec << channel << " does not exist" << std::endl;
      __COUT_ERR__ << "\n" << ss.str();
      __SS_THROW__;
  }
  return tmpStatus;
}

DEFINE_OTS_CONFIGURATION(FEPurdueFSSRInterfaceConfiguration)
