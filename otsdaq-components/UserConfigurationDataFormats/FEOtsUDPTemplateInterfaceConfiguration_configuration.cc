#include "otsdaq-core/ConfigurationPluginDataFormats/DataManagerConfiguration.h"
#include "otsdaq-core/Macros/ConfigurationPluginMacros.h"

#include <iostream>
#include "otsdaq-components/UserConfigurationDataFormats/FEOtsUDPTemplateInterfaceConfiguration.h"

using namespace ots;

//==============================================================================
FEWROtsUDPTemplateInterfaceConfiguration::FEWROtsUDPTemplateInterfaceConfiguration(void)
    : FEInterfaceConfigurationBase("FEWROtsUDPTemplateInterfaceConfiguration") {
  //////////////////////////////////////////////////////////////////////
  // WARNING: the names and the order MUST match the ones in the enum  //
  //////////////////////////////////////////////////////////////////////
  // FEWROtsUDPTemplateInterfaceConfigurationInfo.xml
  //<?xml version="1.0" encoding="UTF-8" standalone="no" ?>
  //<ROOT xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="ConfigurationInfo.xsd">
  //  <CONFIGURATION InterfaceID="FEWRPurdueFSSRInterfaceConfiguration">
  //    <VIEW InterfaceID="FEWR_PURDUE_FSSR_INTERFACE_CONFIGURATION" Type="File,Database,DatabaseTest">
  //      <COLUMN NAME="InterfaceID"        StorageName="INTERFACE_ID"         DataType="VARCHAR2"  />
  //      <COLUMN InterfaceID="Status"             StorageName="STATUS"               DataType="VARCHAR2"/>
  //      <COLUMN InterfaceID="FirmwareVersion"    StorageName="FIRMWARE_VERSION"     DataType="NUMBER"  />
  //      <COLUMN InterfaceID="IPAddress"          StorageName="IP_ADDRESS"           DataType="VARCHAR2"/>
  //      <COLUMN InterfaceID="Port"               StorageName="PORT"                 DataType="NUMBER"  />
  //      <COLUMN InterfaceID="InterfaceIPAddress" StorageName="INTERFACE_IP_ADDRESS" DataType="VARCHAR2"/>
  //      <COLUMN InterfaceID="InterfacePort"      StorageName="INTERFACE_PORT"       DataType="NUMBER"  />
  //      <COLUMN InterfaceID="StreamingIPAddress" StorageName="STREAMING_IP_ADDRESS" DataType="VARCHAR2"/>
  //      <COLUMN InterfaceID="StreamingPort"      StorageName="STREAMING_PORT"       DataType="NUMBER"  />
  //      <COLUMN InterfaceID="NumberOfWords"      StorageName="NUMBER_OF_WORDS"      DataType="NUMBER"  />
  //      <COLUMN InterfaceID="DataRate"           StorageName="DATA_RATE"            DataType="NUMBER"  />
  //    </VIEW>
  //  </CONFIGURATION>
  //</ROOT>
}

//==============================================================================
FEWROtsUDPTemplateInterfaceConfiguration::~FEWROtsUDPTemplateInterfaceConfiguration(void) {}

//==============================================================================
void FEWROtsUDPTemplateInterfaceConfiguration::init(ConfigurationManager *configManager) {
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
bool FEWROtsUDPTemplateInterfaceConfiguration::getStatus(std::string interfaceID) const {
  bool tmpStatus;
  ConfigurationBase::activeConfigurationView_->getValue(
      tmpStatus, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID, interfaceID), Status);
  return tmpStatus;
}

//==============================================================================
unsigned int FEWROtsUDPTemplateInterfaceConfiguration::getFirmwareVersion(std::string interfaceID) const {
  unsigned int tmpFirmwareVersion;
  ConfigurationBase::activeConfigurationView_->getValue(
      tmpFirmwareVersion, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID, interfaceID),
      FirmwareVersion);
  return tmpFirmwareVersion;
}

//==============================================================================
std::string FEWROtsUDPTemplateInterfaceConfiguration::getIPAddress(std::string interfaceID) const {
  std::string tmpIPAddress;
  ConfigurationBase::activeConfigurationView_->getValue(
      tmpIPAddress, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID, interfaceID), IPAddress);
  return tmpIPAddress;
}

//==============================================================================
unsigned int FEWROtsUDPTemplateInterfaceConfiguration::getPort(std::string interfaceID) const {
  unsigned int tmpPort;
  ConfigurationBase::activeConfigurationView_->getValue(
      tmpPort, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID, interfaceID), Port);
  return tmpPort;
}

//==============================================================================
std::string FEWROtsUDPTemplateInterfaceConfiguration::getInterfaceIPAddress(std::string interfaceID) const {
  std::string tmpInterfaceIPAddress;
  ConfigurationBase::activeConfigurationView_->getValue(
      tmpInterfaceIPAddress, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID, interfaceID),
      InterfaceIPAddress);
  return tmpInterfaceIPAddress;
}

//==============================================================================
unsigned int FEWROtsUDPTemplateInterfaceConfiguration::getInterfacePort(std::string interfaceID) const {
  unsigned int tmpInterfacePort;
  ConfigurationBase::activeConfigurationView_->getValue(
      tmpInterfacePort, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID, interfaceID), InterfacePort);
  return tmpInterfacePort;
}

//==============================================================================
std::string FEWROtsUDPTemplateInterfaceConfiguration::getStreamingIPAddress(std::string interfaceID) const {
  std::string tmpStreamingIPAddress;
  ConfigurationBase::activeConfigurationView_->getValue(
      tmpStreamingIPAddress, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID, interfaceID),
      StreamingIPAddress);
  return tmpStreamingIPAddress;
}

//==============================================================================
unsigned int FEWROtsUDPTemplateInterfaceConfiguration::getStreamingPort(std::string interfaceID) const {
  unsigned int tmpStreamingPort;
  ConfigurationBase::activeConfigurationView_->getValue(
      tmpStreamingPort, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID, interfaceID), StreamingPort);
  return tmpStreamingPort;
}

//==============================================================================
int FEWROtsUDPTemplateInterfaceConfiguration::getNumberOfWords(std::string interfaceID) const {
  unsigned int tmpStreamingPort;
  ConfigurationBase::activeConfigurationView_->getValue(
      tmpStreamingPort, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID, interfaceID), NumberOfWords);
  return tmpStreamingPort;
}

//==============================================================================
unsigned int FEWROtsUDPTemplateInterfaceConfiguration::getDataRate(std::string interfaceID) const {
  unsigned int tmpStreamingPort;
  ConfigurationBase::activeConfigurationView_->getValue(
      tmpStreamingPort, ConfigurationBase::activeConfigurationView_->findRow(InterfaceID, interfaceID), DataRate);
  return tmpStreamingPort;
}

DEFINE_OTS_CONFIGURATION(FEWROtsUDPTemplateInterfaceConfiguration)
