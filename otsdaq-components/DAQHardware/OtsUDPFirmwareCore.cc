#include "OtsUDPFirmwareCore.h"

#include "otsdaq-core/MessageFacility/MessageFacility.h"
#include "otsdaq-core/Macros/CoutHeaderMacros.h"

//#include "otsdaq-core/BitManipulator/BitManipulator.h"
//#include "otsdaq-components/DAQHardware/FirmwareBaseDefinitions.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <iomanip>
//#include "../UserConfigurationDataFormats/FEOtsUDPFSSRInterfaceConfiguration.h"

using namespace ots;

/////////////////////////////////=======================================
//ADDRESS SPACE
//	http://otsdaq.fnal.gov/docs/oei_address_space.html
															//field size (bits)
#define UDP_CORE_BLOCK_ADDRESS 		((uint64_t)(0x1) << 32)
#define ADDR_SELF_UPPER_IP 			(uint64_t)(0x0)			//24
#define ADDR_SELF_LOWER_IP 			(uint64_t)(0x1)			//8
#define ADDR_SELF_MAC 				(uint64_t)(0x2)			//40

#define ADDR_CTRL_DEST_IP 			(uint64_t)(0x3)			//32
#define ADDR_CTRL_DEST_MAC 			(uint64_t)(0x4)			//48
#define ADDR_CTRL_DEST_PORT			(uint64_t)(0x5)			//16

#define ADDR_DATA_DEST_IP 			(uint64_t)(0x6)			//32
#define ADDR_DATA_DEST_MAC 			(uint64_t)(0x7)			//48
#define ADDR_DATA_DEST_PORT			(uint64_t)(0x8)			//16

#define ADDR_BURST_MODE 			(uint64_t)(0x9)			//1
#define ADDR_CTRL_RESOLVE_MAC		(uint64_t)(0xA)			//1
#define ADDR_DATA_RESOLVE_MAC		(uint64_t)(0xB)			//1
#define ADDR_SELF_VERSION			(uint64_t)(0x64)		//16 (read only)
#define ADDR_SELF_RESET				(uint64_t)(0x64)		//1  (write only)

//end ADDRESS SPACE
/////////////////////////////////=======================================


const uint8_t OtsUDPFirmwareCore::FIFO_ADDRESS_CMD_TYPE = (1 << 3);

//========================================================================================================================
OtsUDPFirmwareCore::OtsUDPFirmwareCore(unsigned int version)
:version_(version)
		//FrontEndFirmwareBase(version) //AUG-17-2017 RAR dissociated because function calls are entirely independent from PURDUE firmware calls //
{}

//========================================================================================================================
OtsUDPFirmwareCore::~OtsUDPFirmwareCore(void)
{}

//========================================================================================================================
void OtsUDPFirmwareCore::init(void)
{}

//========================================================================================================================
//write
//	size is in units of quad-words (8-Bytes)
void OtsUDPFirmwareCore::write(std::string& buffer,
		const char* address,
		const char* data,
		uint8_t size,
		uint8_t commandTypeOptions)
{
	if(size > 182)
	{
		__SS__ << "Invalid write size: " << size << std::endl;
		__COUT_ERR__ << "\n" << ss.str();
		throw std::runtime_error(ss.str());
	}

	if(buffer.size() + 2 + 8 + 8*size > 2 + 8 + 8*182)
	{
		__SS__ << "Aborting. Buffer overflow attempt: " << buffer.size() << " + " <<
				2 + 8 + 8*size << " > " << 2 + 8 + 8*182 << std::endl;
		__COUT_ERR__ << "\n" << ss.str();
		throw std::runtime_error(ss.str());
	}


	unsigned int begin = buffer.length();
	buffer.resize(buffer.length() + 2 + 8 + 8*size, '\0');

    buffer[begin + 0] = 1 | commandTypeOptions;//WRITE
    buffer[begin + 1] = size;//# of 64 bits words

	std::copy_n(address,sizeof(uint64_t),&buffer[begin + 2]);
    for(uint8_t i=0;i<size;++i)
    	std::copy_n((char *)&data[8*i],sizeof(uint64_t),&buffer[begin + 2 + 8 + 8*i]);

	///////
    __SS__ << "\tAdded WRITE to Buffer:-";
    for(uint32_t i=begin; i<buffer.size(); i++)
    {
    	if(i==begin+2) ss << ":::";
    	else if(i==begin+10) ss << ":::";
    	ss << std::setfill('0') << std::setw(2) << std::hex << (((int16_t) buffer[i]) &0xFF) << "-" << std::dec;
    }
    ss << std::endl;
    __COUT__ << "\n" << ss.str();
}

//========================================================================================================================
//write
// 	Note: size is required, to remove ambiguity when calling write with data=0
void OtsUDPFirmwareCore::write(std::string& buffer,
		const uint64_t& address,
		const char* data,
		uint8_t size,
		uint8_t commandTypeOptions)
{
	write(buffer,(char *)&address,data,size,commandTypeOptions);
}

//========================================================================================================================
void OtsUDPFirmwareCore::write(std::string& buffer,
		const uint64_t& address,
		const uint64_t& data,
		uint8_t commandTypeOptions)
{
	write(buffer,(char *)&address,(char *)&data,1 /*size*/,commandTypeOptions);
}

//========================================================================================================================
void OtsUDPFirmwareCore::write(std::string& buffer,
		const uint64_t& address,
		const std::vector<uint64_t>& data,
		uint8_t commandTypeOptions)
{
	write(buffer,(char *)&address,(char *)&data[0],data.size() /*size*/,commandTypeOptions);
}

//========================================================================================================================
void OtsUDPFirmwareCore::read(std::string& buffer,
		char* address,
		uint8_t size,
		uint8_t commandTypeOptions)
{
	if(size > 182)
	{
		__SS__ << "Invalid read size: " << size << std::endl;
		__COUT_ERR__ << "\n" << ss.str();
		throw std::runtime_error(ss.str());
	}

	if(buffer.size() + 2 + 8 > 2 + 8 + 8*182)
	{
		__SS__ << "Aborting. Buffer overflow attempt: " << buffer.size() << " + " <<
				2 + 8 << " > " << 2 + 8 + 8*182 << std::endl;
		__COUT_ERR__ << "\n" << ss.str();
		throw std::runtime_error(ss.str());
	}

	unsigned int begin = buffer.length();
	buffer.resize(buffer.length() + 2 + 8, '\0');

    buffer[begin + 0] = (uint8_t)0 | commandTypeOptions;//READ
    buffer[begin + 1] = size;//# of 64 bits words

	std::copy_n(address,sizeof(uint64_t),&buffer[begin + 2]);

	///////
    __SS__ << "\tAdded READ to Buffer:-";
    for(uint32_t i=begin; i<buffer.size(); i++)
    {
    	if(i==begin+2) ss << ":::";
    	else if(i==begin+10) ss << ":::";
    	ss << std::setfill('0') << std::setw(2) << std::hex << (((int16_t) buffer[i]) &0xFF) << "-" << std::dec;
    }
    ss << std::endl;
    __COUT__ << "\n" << ss.str();
}


//========================================================================================================================
void OtsUDPFirmwareCore::read(std::string& buffer,
		const uint64_t& address,
		uint8_t size,
		uint8_t commandTypeOptions)
{
	read(buffer,(char *)&address,size,commandTypeOptions);
//	unsigned int begin = buffer.length();
//    buffer.resize(buffer.length() + 10, '\0');
//    //buffer.resize(10);
//    buffer[begin + 0] = (uint8_t)0 | commandTypeOptions;//READ
//    buffer[begin + 1] = size;//# of 64 bits words
//    std::copy_n((char *)&address,sizeof(uint64_t),&buffer[begin + 2]);
//
//	///////
//    std::cout << __COUT_HDR_FL__ <<"\tAdded to Buffer:-";
//    for(uint32_t i=begin; i<buffer.size(); i++)
//    {
//    	if(i==begin+2) std::cout << ":::";
//    	else if(i==begin+10) std::cout << ":::";
//    	std::cout << std::setfill('0') << std::setw(2) << std::hex << (((int16_t) buffer[i]) &0xFF) << "-" << std::dec;
//    }
//    std::cout << std::endl;
/*
    OtsUDPHardware::sendAndReceive(buffer,value);
    //OtsUDPHardware::receive(value);
    std::cout << __COUT_HDR_FL__ << __COUT_HDR_PL__ <<"\tMessage received:-" << std::endl;

    for(uint32_t i=0; i<value.size(); i++)
        std::cout << __COUT_HDR_FL__ << hex << (int16_t)value[i] << "-" << std::endl;

    std::cout << __COUT_HDR_FL__ << dec << std::endl;
*/
}


//========================================================================================================================
void OtsUDPFirmwareCore::setDataDestination(std::string& buffer,
		const std::string& ipAddress, const uint16_t port)
{
	//put firmware in dynamic mac resolution mode for burst mode
	__COUT__ << "dynamic mac address: " << std::hex <<
			uint64_t(UDP_CORE_BLOCK_ADDRESS | ADDR_DATA_RESOLVE_MAC) << std::endl;
	write(buffer,
			UDP_CORE_BLOCK_ADDRESS | ADDR_DATA_RESOLVE_MAC /* addr */,
			1 /* data */);

	//extract ip address from string
	__COUT__ << "ipAddress = " << ipAddress << std::endl;
	uint64_t ip = 0;
	int ipArr[4];
	sscanf(ipAddress.c_str(),"%d.%d.%d.%d",
			&ipArr[3],
			&ipArr[2],
			&ipArr[1],
			&ipArr[0]
	);
	for(int i=0;i<4;++i)
		(((char *)&ip)[i]) += ipArr[i]&0x0FF;

	writeDataDestinationIP(buffer,ip);
	writeDataDestinationPort(buffer,port);
}

//========================================================================================================================
void OtsUDPFirmwareCore::setControlDestination(std::string& buffer,
		const std::string& ipAddress, const uint16_t port)
{
	//put firmware in dynamic mac resolution mode for burst mode
	write(buffer,
			UDP_CORE_BLOCK_ADDRESS | ADDR_CTRL_RESOLVE_MAC /* addr */,
			1 /* data */);

	//extract ip address from string
	__COUT__ << "ipAddress = " << ipAddress << std::endl;
	uint64_t ip = 0;
	int ipArr[4];
	sscanf(ipAddress.c_str(),"%d.%d.%d.%d",
			&ipArr[3],
			&ipArr[2],
			&ipArr[1],
			&ipArr[0]
	);
	for(int i=0;i<4;++i)
		(((char *)&ip)[i]) += ipArr[i]&0x0FF;

	writeControlDestinationIP(buffer,ip);
	writeControlDestinationPort(buffer,port);
}

//========================================================================================================================
void OtsUDPFirmwareCore::writeDataDestinationIP(std::string& buffer, const uint64_t value)
{
	write(buffer,
			UDP_CORE_BLOCK_ADDRESS | ADDR_DATA_DEST_IP /* addr */,
			value /* data */);
}

//========================================================================================================================
void OtsUDPFirmwareCore::writeDataDestinationMAC(std::string& buffer, const uint64_t value)
{
	write(buffer,
			UDP_CORE_BLOCK_ADDRESS | ADDR_DATA_DEST_MAC /* addr */,
			value /* data */);
}

//========================================================================================================================
void OtsUDPFirmwareCore::writeDataDestinationPort(std::string& buffer, const uint64_t value)
{
	write(buffer,
			UDP_CORE_BLOCK_ADDRESS | ADDR_DATA_DEST_PORT /* addr */,
			value /* data */);
}

//========================================================================================================================
void OtsUDPFirmwareCore::readDataDestinationIP(std::string& buffer)
{
	read(buffer,
			UDP_CORE_BLOCK_ADDRESS | ADDR_DATA_DEST_IP /* addr */);
}

//========================================================================================================================
void OtsUDPFirmwareCore::readDataDestinationMAC(std::string& buffer)
{
	read(buffer,
			UDP_CORE_BLOCK_ADDRESS | ADDR_DATA_DEST_MAC /* addr */);
}

//========================================================================================================================
void OtsUDPFirmwareCore::readDataDestinationPort(std::string& buffer)
{
	read(buffer,
			UDP_CORE_BLOCK_ADDRESS | ADDR_DATA_DEST_PORT /* addr */);
}

//========================================================================================================================
void OtsUDPFirmwareCore::writeControlDestinationIP(std::string& buffer, const uint64_t value)
{
	write(buffer,
			UDP_CORE_BLOCK_ADDRESS | ADDR_CTRL_DEST_IP /* addr */,
			value /* data */);
}

//========================================================================================================================
void OtsUDPFirmwareCore::writeControlDestinationMAC(std::string& buffer, const uint64_t value)
{
	write(buffer,
			UDP_CORE_BLOCK_ADDRESS | ADDR_CTRL_DEST_MAC /* addr */,
			value /* data */);
}

//========================================================================================================================
void OtsUDPFirmwareCore::writeControlDestinationPort(std::string& buffer, const uint64_t value)
{
	write(buffer,
			UDP_CORE_BLOCK_ADDRESS | ADDR_CTRL_DEST_PORT /* addr */,
			value /* data */);
}

//========================================================================================================================
void OtsUDPFirmwareCore::readControlDestinationIP(std::string& buffer)
{
	read(buffer,
			UDP_CORE_BLOCK_ADDRESS | ADDR_CTRL_DEST_IP /* addr */);
}

//========================================================================================================================
void OtsUDPFirmwareCore::readControlDestinationMAC(std::string& buffer)
{
	read(buffer,
			UDP_CORE_BLOCK_ADDRESS | ADDR_CTRL_DEST_MAC /* addr */);
}

//========================================================================================================================
void OtsUDPFirmwareCore::readControlDestinationPort(std::string& buffer)
{
	read(buffer,
			UDP_CORE_BLOCK_ADDRESS | ADDR_CTRL_DEST_PORT /* addr */);
}

//========================================================================================================================
void OtsUDPFirmwareCore::readUDPFirmwareVersion(std::string& buffer)
{
	read(buffer,
			UDP_CORE_BLOCK_ADDRESS | ADDR_SELF_VERSION /* addr */);
}

//========================================================================================================================
void OtsUDPFirmwareCore::forceReset(std::string& buffer)
{
	write(buffer,
			UDP_CORE_BLOCK_ADDRESS | ADDR_SELF_RESET /* addr */,
			1 /* data */);
}

//========================================================================================================================
void OtsUDPFirmwareCore::startBurst(std::string& buffer)
{
	__COUT__ << std::endl;
	write(buffer,
			UDP_CORE_BLOCK_ADDRESS | ADDR_BURST_MODE /* addr */,
			1 /* data */);
}

//========================================================================================================================
void OtsUDPFirmwareCore::stopBurst(std::string& buffer)
{
	__COUT__ << std::endl;
	write(buffer,
			UDP_CORE_BLOCK_ADDRESS | ADDR_BURST_MODE /* addr */,
			0 /* data */);
}

