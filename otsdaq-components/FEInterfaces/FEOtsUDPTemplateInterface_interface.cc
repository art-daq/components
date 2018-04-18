#include "otsdaq-components/FEInterfaces/FEOtsUDPTemplateInterface.h"
#include "otsdaq-core/MessageFacility/MessageFacility.h"
#include "otsdaq-core/Macros/CoutHeaderMacros.h"
#include "otsdaq-core/Macros/InterfacePluginMacros.h"
#include <iostream>
#include <set>

using namespace ots;

#undef 	__MF_SUBJECT__
#define __MF_SUBJECT__ "FE-FEOtsUDPTemplateInterface"

//========================================================================================================================
FEOtsUDPTemplateInterface::FEOtsUDPTemplateInterface(const std::string& interfaceUID, const ConfigurationTree& theXDAQContextConfigTree, const std::string& interfaceConfigurationPath)
: Socket               (
		theXDAQContextConfigTree.getNode(interfaceConfigurationPath).getNode("HostIPAddress").getValue<std::string>()
		, theXDAQContextConfigTree.getNode(interfaceConfigurationPath).getNode("HostPort").getValue<unsigned int>())
, FEVInterface         (interfaceUID, theXDAQContextConfigTree, interfaceConfigurationPath)
, OtsUDPHardware       (theXDAQContextConfigTree.getNode(interfaceConfigurationPath).getNode("InterfaceIPAddress").getValue<std::string>()
		, theXDAQContextConfigTree.getNode(interfaceConfigurationPath).getNode("InterfacePort").getValue<unsigned int>())
, OtsUDPFirmwareDataGen(theXDAQContextConfigTree.getNode(interfaceConfigurationPath).getNode("FirmwareVersion").getValue<unsigned int>())
{
	universalAddressSize_ = 8;
	universalDataSize_    = 8;
}

//========================================================================================================================
FEOtsUDPTemplateInterface::~FEOtsUDPTemplateInterface(void)
{}

//========================================================================================================================
void FEOtsUDPTemplateInterface::configure(void)
{
	__CFG_COUT__ << "configure" << std::endl;
	__CFG_COUT__ << "Clearing receive socket buffer: " << OtsUDPHardware::clearReadSocket() << " packets cleared." << std::endl;

	std::string sendBuffer;
	std::string recvBuffer;
	uint64_t 	readQuadWord;

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

	OtsUDPFirmwareCore::setDataDestination(sendBuffer,
			theXDAQContextConfigTree_.getNode(theConfigurationPath_).getNode("StreamToIPAddress").getValue<std::string>(),
			theXDAQContextConfigTree_.getNode(theConfigurationPath_).getNode("StreamToPort").getValue<uint64_t>()
	);
	OtsUDPHardware::write(sendBuffer);

	__CFG_COUT__ << "Reading back burst dest MAC/IP/Port: "  << std::endl;

	OtsUDPFirmwareCore::readDataDestinationMAC(sendBuffer);
	OtsUDPHardware::read(sendBuffer,readQuadWord);

	OtsUDPFirmwareCore::readDataDestinationIP(sendBuffer);
	OtsUDPHardware::read(sendBuffer,readQuadWord);

	OtsUDPFirmwareCore::readDataDestinationPort(sendBuffer);
	OtsUDPHardware::read(sendBuffer,readQuadWord);



	OtsUDPFirmwareCore::readControlDestinationPort(sendBuffer);
	OtsUDPHardware::read(sendBuffer,readQuadWord);

	//Run Configure Sequence Commands
	FEVInterface::runSequenceOfCommands("LinkToConfigureSequence");

	__CFG_COUT__ << "Done with ots Template configuring."  << std::endl;
}

//========================================================================================================================
//void FEOtsUDPTemplateInterface::configureDetector(const DACStream& theDACStream)
//{
//	__CFG_COUT__ << "\tconfigureDetector" << std::endl;
//}

//========================================================================================================================
void FEOtsUDPTemplateInterface::halt(void)
{
	__CFG_COUT__ << "\tHalt" << std::endl;
	stop();
}

//========================================================================================================================
void FEOtsUDPTemplateInterface::pause(void)
{
	__CFG_COUT__ << "\tPause" << std::endl;
	stop();
}

//========================================================================================================================
void FEOtsUDPTemplateInterface::resume(void)
{
	__CFG_COUT__ << "\tResume" << std::endl;
	start("");
}

//========================================================================================================================
void FEOtsUDPTemplateInterface::start(std::string )//runNumber)
{
	__CFG_COUT__ << "\tStart" << std::endl;


	//Run Start Sequence Commands
	FEVInterface::runSequenceOfCommands("LinkToStartSequence");

	std::string sendBuffer;
	OtsUDPFirmwareCore::startBurst(sendBuffer);
	OtsUDPHardware::write(sendBuffer);
}

//========================================================================================================================
void FEOtsUDPTemplateInterface::stop(void)
{
	__CFG_COUT__ << "\tStop" << std::endl;

	//Run Stop Sequence Commands

	FEVInterface::runSequenceOfCommands("LinkToStopSequence");

	std::string sendBuffer;
	OtsUDPFirmwareCore::stopBurst(sendBuffer);
	OtsUDPHardware::write(sendBuffer);
}

//========================================================================================================================
bool FEOtsUDPTemplateInterface::running(void)
{
	__CFG_COUT__ << "\tRunning" << std::endl;

	int state = -1;
	while(WorkLoop::continueWorkLoop_)
	{
		//while running
		//play with the LEDs at address 0x1003

		++state;
		if(state < 8)
			sleep(1);
		else
			break;
	}

	//		//example!
	//		//play with array of 8 LEDs at address 0x1003

	//
	//	bool flashLEDsWhileRunning = false;
	//	if(flashLEDsWhileRunning)
	//	{
	//		std::string writeBuffer;
	//		int state = -1;
	//		while(WorkLoop::continueWorkLoop_)
	//		{
	//			//while running
	//			//play with the LEDs at address 0x1003
	//
	//			++state;
	//			if(state < 8)
	//			{
	//				writeBuffer.resize(0);
	//				OtsUDPFirmwareCore::write(writeBuffer, 0x1003,1<<state);
	//				OtsUDPHardware::write(writeBuffer);
	//			}
	//			else if(state%2 == 1 && state < 11)
	//			{
	//				writeBuffer.resize(0);
	//				OtsUDPFirmwareCore::write(writeBuffer, 0x1003, 0xFF);
	//				OtsUDPHardware::write(writeBuffer);
	//			}
	//			else if(state%2 == 0 && state < 11)
	//			{
	//				writeBuffer.resize(0);
	//				OtsUDPFirmwareCore::write(writeBuffer, 0x1003,0);
	//				OtsUDPHardware::write(writeBuffer);
	//			}
	//			else
	//				state = -1;
	//
	//			sleep(1);
	//		}
	//	}

	return false;
}

//========================================================================================================================
//NOTE: buffer for address must be at least size universalAddressSize_
//NOTE: buffer for returnValue must be max UDP size to handle return possibility
int ots::FEOtsUDPTemplateInterface::universalRead(char *address, char *returnValue)
{
	__CFG_COUT__ << "address size " << universalAddressSize_ << std::endl;

	__CFG_COUT__ << "Request: ";
	for(unsigned int i=0;i<universalAddressSize_;++i)
		printf("%2.2X",(unsigned char)address[i]);
	std::cout << std::endl;

	std::string readBuffer, sendBuffer;
	OtsUDPFirmwareCore::readAdvanced(sendBuffer,address,1 /*size*/);

	//OtsUDPHardware::read(FSSRFirmware::universalRead(address), readBuffer) < 0;
	try
	{
		OtsUDPHardware::read(sendBuffer, readBuffer); // data reply
	}
	catch(std::runtime_error &e)
	{
		__CFG_COUT__ << "Caught it! This is when it's getting time out error" << std::endl;
		__CFG_COUT_ERR__ << e.what() << std::endl;
		return -1;
	}

	__CFG_COUT__ << "Result SIZE: " << readBuffer.size() << std::endl;
	std::memcpy(returnValue,readBuffer.substr(2).c_str(),universalDataSize_);
	return 0;
}

//========================================================================================================================
//NOTE: buffer for address must be at least size universalAddressSize_
//NOTE: buffer for writeValue must be at least size universalDataSize_
void ots::FEOtsUDPTemplateInterface::universalWrite(char* address, char* writeValue)
{
	__CFG_COUT__ << "address size " << universalAddressSize_ << std::endl;
	__CFG_COUT__ << "data size " << universalDataSize_ << std::endl;
	__CFG_COUT__ << "Sending: ";
	for(unsigned int i=0;i<universalAddressSize_;++i)
		printf("%2.2X",(unsigned char)address[i]);
	std::cout << std::endl;

	std::string sendBuffer;
	OtsUDPFirmwareCore::writeAdvanced(sendBuffer,address,writeValue,1 /*size*/);
	OtsUDPHardware::write(sendBuffer); // data request
}

DEFINE_OTS_INTERFACE(FEOtsUDPTemplateInterface)
