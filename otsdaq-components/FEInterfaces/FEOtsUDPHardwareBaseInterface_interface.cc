#include "otsdaq-components/FEInterfaces/FEOtsUDPHardwareBaseInterface.h"
#include "otsdaq-core/MessageFacility/MessageFacility.h"
#include "otsdaq-core/Macros/CoutMacros.h"
#include "otsdaq-core/Macros/InterfacePluginMacros.h"
#include <iostream>
#include <set>

using namespace ots;

#undef 	__MF_SUBJECT__
#define __MF_SUBJECT__ "FE-FEOtsUDPHardwareBaseInterface"

//========================================================================================================================
FEOtsUDPHardwareBaseInterface::FEOtsUDPHardwareBaseInterface(const std::string& interfaceUID, const ConfigurationTree& theXDAQContextConfigTree, const std::string& interfaceConfigurationPath)
: Socket(
		theXDAQContextConfigTree.getNode(interfaceConfigurationPath).getNode("HostIPAddress").getValue<std::string>()
		, theXDAQContextConfigTree.getNode(interfaceConfigurationPath).getNode("HostPort").getValue<unsigned int>()
)
, FEVInterface(
		interfaceUID
		, theXDAQContextConfigTree
		, interfaceConfigurationPath
)
, OtsUDPHardware(
		theXDAQContextConfigTree.getNode(interfaceConfigurationPath).getNode("InterfaceIPAddress").getValue<std::string>()
		, theXDAQContextConfigTree.getNode(interfaceConfigurationPath).getNode("InterfacePort").getValue<unsigned int>())
, OtsUDPFirmwareDataGen(
		theXDAQContextConfigTree.getNode(interfaceConfigurationPath).getNode("FirmwareVersion").getValue<unsigned int>()
)
{
	universalAddressSize_ = 8;
	universalDataSize_    = 8;
}

//========================================================================================================================
FEOtsUDPHardwareBaseInterface::~FEOtsUDPHardwareBaseInterface(void)
{}

//========================================================================================================================
void FEOtsUDPHardwareBaseInterface::configure(void)
{
	//__CFG_COUT__ << "Configure" << std::endl;

	unsigned int numberOfClearedPackets = OtsUDPHardware::clearReadSocket();
	//__CFG_COUT__ << "Clearing receive socket buffer: " << numberOfClearedPackets << " packets cleared." << std::endl;

	std::string sendBuffer;

	/*
	__CFG_COUT__ << "Configuration Path Table: " <<
			theXDAQContextConfigTree_.getNode(theConfigurationPath_).getConfigurationName() <<
			"-v" <<
			theXDAQContextConfigTree_.getNode(theConfigurationPath_).getConfigurationVersion() <<
			std::endl;

	__CFG_COUT__ << "Interface name: " <<
			theXDAQContextConfigTree_.getNode(theConfigurationPath_) << __E__;

	__CFG_COUT__ << "Configured Firmware Version: " <<
			theXDAQContextConfigTree_.getNode(theConfigurationPath_).getNode("FirmwareVersion").getValue<unsigned int>()
			<< std::endl;

	__CFG_COUT__ << "Setting Destination IP: " <<
			theXDAQContextConfigTree_.getNode(theConfigurationPath_).getNode("StreamToIPAddress").getValue<std::string>()
			<< std::endl;
	__CFG_COUT__ << "And Destination Port: " <<
			theXDAQContextConfigTree_.getNode(theConfigurationPath_).getNode("StreamToPort").getValue<unsigned int>()
			<< std::endl;
	 */

	OtsUDPFirmwareCore::setDataDestination(sendBuffer,
			theXDAQContextConfigTree_.getNode(theConfigurationPath_).getNode("StreamToIPAddress").getValue<std::string>(),
			theXDAQContextConfigTree_.getNode(theConfigurationPath_).getNode("StreamToPort").getValue<uint64_t>()
	);
	OtsUDPHardware::write(sendBuffer);

	/*
	__CFG_COUT__ << "Reading back burst destination MAC/IP/Port: " << std::endl;

	uint64_t 	readQuadWord;

	OtsUDPFirmwareCore::readDataDestinationMAC(sendBuffer);
	OtsUDPHardware::read(sendBuffer,readQuadWord);

	OtsUDPFirmwareCore::readDataDestinationIP(sendBuffer);
	OtsUDPHardware::read(sendBuffer,readQuadWord);

	OtsUDPFirmwareCore::readDataDestinationPort(sendBuffer);
	OtsUDPHardware::read(sendBuffer,readQuadWord);

	OtsUDPFirmwareCore::readControlDestinationPort(sendBuffer);
	OtsUDPHardware::read(sendBuffer,readQuadWord);
	 */

	//__CFG_COUT__ << "Done configuring." << std::endl;
}

//========================================================================================================================
void FEOtsUDPHardwareBaseInterface::halt(void)
{
	//	__CFG_COUT__ << "\tHalt" << std::endl;
	stop();
}

//========================================================================================================================
void FEOtsUDPHardwareBaseInterface::pause(void)
{
	//	__CFG_COUT__ << "\tPause" << std::endl;
	stop();
}

//========================================================================================================================
void FEOtsUDPHardwareBaseInterface::resume(void)
{
	//	__CFG_COUT__ << "\tResume" << std::endl;
	start("");
}

//========================================================================================================================
void FEOtsUDPHardwareBaseInterface::start(std::string )//runNumber)
{
	//	__CFG_COUT__ << "\tStart" << std::endl;

	std::string sendBuffer;
	OtsUDPFirmwareCore::startBurst(sendBuffer);
	OtsUDPHardware::write(sendBuffer);
}

//========================================================================================================================
void FEOtsUDPHardwareBaseInterface::stop(void)
{
	//	__CFG_COUT__ << "\tStop" << std::endl;

	std::string sendBuffer;
	OtsUDPFirmwareCore::stopBurst(sendBuffer);
	OtsUDPHardware::write(sendBuffer);
}

//========================================================================================================================
//NOTE: buffer for address must be at least size universalAddressSize_
//NOTE: buffer for returnValue must be max UDP size to handle return possibility
int ots::FEOtsUDPHardwareBaseInterface::universalRead(char *address, char *returnValue)
{
	//	__CFG_COUT__ << "Address size " << universalAddressSize_ << std::endl;

	/*
	__CFG_COUT__ << "Request: ";
	for(unsigned int i=0;i<universalAddressSize_;++i)
		printf("%2.2X",(unsigned char)address[i]);
	__CFG_COUT__ << std::endl;
	 */

	std::string readBuffer, sendBuffer;
	OtsUDPFirmwareCore::readAdvanced(sendBuffer,address,1 /*size*/);

	//OtsUDPHardware::read(FSSRFirmware::universalRead(address), readBuffer) < 0;
	try
	{
		OtsUDPHardware::read(sendBuffer, readBuffer); // data reply
	}
	catch(std::runtime_error &e)
	{
		__CFG_COUT__ << "Caught read error. Typically time out error!" << std::endl;
		__CFG_COUT_ERR__ << e.what() << std::endl;
		return -1;
	}

	//__CFG_COUT__ << "Result SIZE: " << readBuffer.size() << std::endl;
	std::memcpy(returnValue,readBuffer.substr(2).c_str(),universalDataSize_);
	return 0;
}

//========================================================================================================================
//NOTE: buffer for address must be at least size universalAddressSize_
//NOTE: buffer for writeValue must be at least size universalDataSize_
void ots::FEOtsUDPHardwareBaseInterface::universalWrite(char* address, char* writeValue)
{
	std::string sendBuffer;
	OtsUDPFirmwareCore::writeAdvanced(sendBuffer,address,writeValue,1 /*size*/);
	OtsUDPHardware::write(sendBuffer); // data request
}
