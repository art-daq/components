#include "otsdaq-components/DAQHardware/OtsUDPFirmware.h"
#include "otsdaq-components/DAQHardware/FSSRFirmwareDefinitions.h"
#include "otsdaq-core/BitManipulator/BitManipulator.h"
#include "otsdaq-components/DetectorHardware/FSSRROCDefinitions.h"
#include "otsdaq-core/MessageFacility/MessageFacility.h"
#include "otsdaq-core/Macros/CoutHeaderMacros.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <algorithm>
#include <string.h>
#include "../UserConfigurationDataFormats/FEOtsUDPFSSRInterfaceConfiguration.h"


using namespace ots;


//========================================================================================================================
OtsUDPFirmware::OtsUDPFirmware (unsigned int version, std::string type)
{
	protocolInstance_ = FrontEndFirmwareBase::getInstance(type,version);
	assert(protocolInstance_ != NULL);
}

//========================================================================================================================
OtsUDPFirmware::~OtsUDPFirmware(void)
{}

//========================================================================================================================
int OtsUDPFirmware::init(void)
{
	return 0;
}

//========================================================================================================================
std::string OtsUDPFirmware::universalRead(char* address)
{
	return protocolInstance_->read(address);
}

//========================================================================================================================
std::string OtsUDPFirmware::universalWrite(char* address, char* data)
{
	return protocolInstance_->write(address, data);
}


////========================================================================================================================
//int OtsUDPFirmware::write(std::string& buffer, uint64_t address, const std::string& value)
//{
//    std::cout << __COUT_HDR_PL__ <<"\tAddress:" << address << " Val: "<< value << "-" << std::endl;
//    buffer.resize(10);
//    buffer[0] = 1;
//    buffer[1] = value.size()/8;
//    std::copy_n((char *)&address,sizeof(uint64_t),&buffer[2]); //RIP the future
//    //memcpy(&buffer[2], &address,sizeof(uint64_t));
//    buffer += value;
//    std::cout << __COUT_HDR_PL__ <<"\tMessage:-";
//
//    for(uint32_t i=0; i<buffer.size(); i++)
//    	printf("%2.2X-",(uint8_t)buffer[i]);
//
//    std::cout << std::dec << std::endl;
//
//    return 1;
////}

//========================================================================================================================
void OtsUDPFirmware::write(std::string& buffer, uint64_t address, uint64_t value)
{
	protocolInstance_->write(buffer,address, value);
}

//========================================================================================================================
void OtsUDPFirmware::read(std::string& buffer, uint64_t address)
{
	protocolInstance_->read(buffer,address);
}

//========================================================================================================================
void OtsUDPFirmware::setNumberOfBurstWords(std::string& buffer, uint64_t numberOfWords)
{
	std::cout << __COUT_HDR_FL__ << __COUT_HDR_PL__ << std::endl;
	protocolInstance_->write(buffer, 0x1001,numberOfWords);
}

//========================================================================================================================
void OtsUDPFirmware::setBurstWordsRate(std::string& buffer, uint64_t interval)
{
	std::cout << __COUT_HDR_FL__ << std::endl;
	protocolInstance_->write(buffer, 0x1002,interval);
}


//========================================================================================================================
std::string OtsUDPFirmware::startBurst(void)
{
	std::cout << __COUT_HDR_FL__ << std::endl;
	std::string buffer;
	protocolInstance_->write(buffer, (uint64_t)0x0000000100000009,0x1);
	return buffer;
}

//========================================================================================================================
std::string OtsUDPFirmware::stopBurst(void)
{
	//	uint64_t address = 0x0000000100000009;
	//    string value2(8,'\0');
	//    value2[0] = (unsigned char)1;
	std::cout << __COUT_HDR_FL__ << std::endl;
	std::string buffer;
	protocolInstance_->write(buffer, (uint64_t)0x0000000100000009,0x0);
	return buffer;
}

//========================================================================================================================
void OtsUDPFirmware::readBurstDestinationIP(std::string& buffer)
{
	protocolInstance_->read(buffer, (uint64_t)0x0000000100000006);
}

//========================================================================================================================
void OtsUDPFirmware::readBurstDestinationMAC(std::string& buffer)
{
	protocolInstance_->read(buffer, (uint64_t)0x0000000100000007);
}

//========================================================================================================================
void OtsUDPFirmware::readBurstDestinationPort(std::string& buffer)
{
	protocolInstance_->read(buffer, (uint64_t)0x0000000100000008);
}

//========================================================================================================================
void OtsUDPFirmware::writeBurstDestinationIP(std::string& buffer, const uint64_t value)
{
	protocolInstance_->write(buffer, (uint64_t)0x0000000100000006, value);
}

//========================================================================================================================
void OtsUDPFirmware::writeBurstDestinationMAC(std::string& buffer, const uint64_t value)
{
	protocolInstance_->write(buffer, (uint64_t)0x0000000100000007, value);
}

//========================================================================================================================
void OtsUDPFirmware::writeBurstDestinationPort(std::string& buffer, const uint64_t value)
{
	protocolInstance_->write(buffer, (uint64_t)0x0000000100000008, value);
}

//========================================================================================================================
void OtsUDPFirmware::setupBurstDestination(std::string& buffer,
		const std::string& ipAddress, const uint64_t& port)
{
	//put firmware in dynamic mac resolution mode for burst mode
	protocolInstance_->write(buffer, (uint64_t)0x000000010000000B, 1);

	//extract ip address from string
	__MOUT__ << "ipAddress = " << ipAddress << std::endl;
	uint64_t ip = 0;
	int ipArr[4];
	sscanf(ipAddress.c_str(),"%d.%d.%d.%d",
			&ipArr[3],
			&ipArr[2],
			&ipArr[1],
			&ipArr[0]
	);
	for(int i=0;i<4;++i)
		(((char *)&ip)[i]) += ipArr[i]&0xFF;


	writeBurstDestinationIP(buffer,ip);
	writeBurstDestinationPort(buffer,port);
}


















