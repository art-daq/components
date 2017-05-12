#include "otsdaq-components/DAQHardware/OtsFirmwareCore.h"
#include "otsdaq-core/BitManipulator/BitManipulator.h"
#include "otsdaq-components/DAQHardware/FirmwareBaseDefinitions.h"
#include "otsdaq-core/MessageFacility/MessageFacility.h"
#include "otsdaq-core/Macros/CoutHeaderMacros.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <iomanip>
//#include "../UserConfigurationDataFormats/FEOtsUDPFSSRInterfaceConfiguration.h"

using namespace ots;


//========================================================================================================================
OtsFirmwareCore::OtsFirmwareCore(unsigned int version):
		FrontEndFirmwareBase(version)
{}

//========================================================================================================================
OtsFirmwareCore::~OtsFirmwareCore(void)
{}

//========================================================================================================================
int OtsFirmwareCore::init(void)
{
    return 0;
}

//========================================================================================================================
std::string OtsFirmwareCore::setDataDestination(std::string ip, uint32_t port)
{
    std::cout << __COUT_HDR_FL__ << "Set data destination!" << std::endl;
    std::string buffer;
    struct sockaddr_in socketAddress;
    inet_pton(AF_INET, ip.c_str(), &(socketAddress.sin_addr));
    //std::cout << __COUT_HDR_FL__ << __PRETTY_FUNCTION__ << "ADDRESS: " << hex << ntohl(socketAddress.sin_addr.s_addr) << dec << std::endl;
    write(buffer, DATA_DESTINATION_IP, ntohl(socketAddress.sin_addr.s_addr)); //  Set data destination IP 192.168.133.1
    //std::cout << __COUT_HDR_FL__ << __PRETTY_FUNCTION__ << "PORT: " << hex << 0xbeef0000+port << dec << std::endl;
    write(buffer, DATA_SOURCE_DESTINATION_PORT, 0xbeef0000 + port); //  Set data destination port
    return buffer;
}

//========================================================================================================================
std::string OtsFirmwareCore::read(char* address)
{
    std::string buffer;
    read(buffer, *(uint64_t*)address);
    return buffer;
}

//========================================================================================================================
std::string OtsFirmwareCore::write(char* address, char* data)
{
    std::string buffer;
    write(buffer, *(uint64_t*)address, *(uint64_t*)data);
    return buffer;
}

//========================================================================================================================
//unsigned int OtsFirmwareCore::write(std::string& buffer, uint64_t address, const std::string& value)
//{
//    std::cout << __COUT_HDR_FL__ << __COUT_HDR_PL__ <<"\tAddress:" << address << " Val: "<< value << "-" << std::endl;
//    buffer.resize(10);
//    buffer[0] = 1;
//    buffer[1] = value.size()/8;
//    std::copy_n((char *)&address,sizeof(uint64_t),&buffer[2]); //RIP the future
//    //memcpy(&buffer[2], &address,sizeof(uint64_t));
//    buffer += value;
//    std::cout << __COUT_HDR_FL__ << __COUT_HDR_PL__ <<"\tMessage:-" << std::endl;
//
//    for(uint32_t i=0; i<buffer.size(); i++)
//        std::cout << __COUT_HDR_FL__ << std::setfill('0') << std::setw(2) << std::hex << (int16_t) buffer[i] << "-" << std::endl;
//
//    std::cout << __COUT_HDR_FL__ << std::dec << std::endl;
//
//    return 1;
//}

//========================================================================================================================
unsigned int OtsFirmwareCore::write(std::string& buffer, uint64_t address, uint64_t value)
{
    //std::cout << __COUT_HDR_FL__ << "Address:" << std::hex << address << " Val: "<< value << std::dec << std::endl;
	unsigned int begin = buffer.length();
    buffer.resize(buffer.length() + 18, '\0');
    //buffer.resize(18);
    buffer[begin + 0] = 1;//WRITE
    buffer[begin + 1] = 1;//# of 64 bits words
    //memcpy(&buffer[2], &address,sizeof(uint64_t));
    std::copy_n((char *)&address,sizeof(uint64_t),&buffer[begin + 2]);
    //memcpy(&buffer[10], &value,  sizeof(uint64_t));
    std::copy_n((char *)&value,sizeof(uint64_t),&buffer[begin + 10]);

    std::cout << __COUT_HDR_FL__ <<"\tAdded to Buffer:-";
    for(uint32_t i=begin; i<buffer.size(); i++)
        std::cout << std::setfill('0') << std::setw(2) << std::hex << (int16_t) buffer[i] << "-" << std::dec;
    std::cout << std::endl;

    return 1;
}

//========================================================================================================================
unsigned int OtsFirmwareCore::read(std::string& buffer, uint64_t address)
{
	unsigned int begin = buffer.length();
    buffer.resize(buffer.length() + 10, '\0');
    //buffer.resize(10);
    buffer[begin + 0] = (char)0;//READ
    buffer[begin + 1] = 1;//# of 64 bits words
    //memcpy(&buffer[2], &address,sizeof(uint64_t));
    std::copy_n((char *)&address,sizeof(uint64_t),&buffer[begin + 2]);

    std::cout << __COUT_HDR_FL__ <<"\tAdded to Buffer:-";
    for(uint32_t i=begin; i<buffer.size(); i++)
        std::cout << std::setfill('0') << std::setw(2) << std::hex << (((int16_t) buffer[i]) &0xFF) << "-" << std::dec;
    std::cout << std::endl;
/*
    OtsUDPHardware::sendAndReceive(buffer,value);
    //OtsUDPHardware::receive(value);
    std::cout << __COUT_HDR_FL__ << __COUT_HDR_PL__ <<"\tMessage received:-" << std::endl;

    for(uint32_t i=0; i<value.size(); i++)
        std::cout << __COUT_HDR_FL__ << hex << (int16_t)value[i] << "-" << std::endl;

    std::cout << __COUT_HDR_FL__ << dec << std::endl;
*/
	return 0;
}

//========================================================================================================================
unsigned int OtsFirmwareCore::write(std::string& buffer, uint32_t address, uint32_t value)
{
	return OtsFirmwareCore::write(buffer,(uint64_t)address, (uint64_t)value);
/*
	unsigned int begin = buffer.length();
    unsigned int numberOfBufferedCommands = getNumberOfBufferedCommands(buffer);
    buffer.resize(buffer.length() + 12, '\0');
    if (begin != 0)
        begin -= 1;
    buffer[begin + 0] = numberOfBufferedCommands + 1;
    buffer[begin + 1] = WRITE;
    buffer[begin + 2] = 0;
    buffer[begin + 3] = 8;
    buffer[begin + 4] = (address >> 24) & 0xff;
    buffer[begin + 5] = (address >> 16) & 0xff;
    buffer[begin + 6] = (address >> 8) & 0xff;
    buffer[begin + 7] = address & 0xff;
    buffer[begin + 8] = (data >> 24) & 0xff;
    buffer[begin + 9] = (data >> 16) & 0xff;
    buffer[begin + 10] = (data >> 8) & 0xff;
    buffer[begin + 11] = data & 0xff;
    if (begin == 0)
        buffer += '\0';
    return (unsigned int) buffer[begin] + 1;
*/
}

//========================================================================================================================
//unsigned int OtsFirmwareCore::waitSet(std::string& buffer, uint32_t address, uint32_t data, uint32_t timeout)
//{
//    unsigned int begin = buffer.length();
//    unsigned int numberOfBufferedCommands = getNumberOfBufferedCommands(buffer);
//    buffer.resize(buffer.length() + 16, '\0');
//    if (begin != 0)
//        begin -= 1;
//    buffer[begin + 0] = numberOfBufferedCommands + 1;
//    buffer[begin + 1] = WAITSET;
//    buffer[begin + 2] = 0;
//    buffer[begin + 3] = 12;
//    buffer[begin + 4] = (address >> 24) & 0xff;
//    buffer[begin + 5] = (address >> 16) & 0xff;
//    buffer[begin + 6] = (address >> 8) & 0xff;
//    buffer[begin + 7] = address & 0xff;
//    buffer[begin + 8] = (data >> 24) & 0xff;
//    buffer[begin + 9] = (data >> 16) & 0xff;
//    buffer[begin + 10] = (data >> 8) & 0xff;
//    buffer[begin + 11] = data & 0xff;
//    buffer[begin + 12] = (timeout >> 24) & 0xff;
//    buffer[begin + 13] = (timeout >> 16) & 0xff;
//    buffer[begin + 14] = (timeout >> 8) & 0xff;
//    buffer[begin + 15] = timeout & 0xff;
//    if (begin == 0)
//        buffer += '\0';
//    return (unsigned int) buffer[begin] + 1;
//}

//========================================================================================================================
unsigned int OtsFirmwareCore::waitClear(std::string& buffer, uint32_t address, uint32_t value, uint32_t timeout)
{
	return 1;
	//return write(buffer,(uint64_t)address, (uint64_t)value);
/*
	unsigned int begin = buffer.length();
    unsigned int numberOfBufferedCommands = getNumberOfBufferedCommands(buffer);
    buffer.resize(buffer.length() + 16, '\0');
    if (begin != 0)
        begin -= 1;
    buffer[begin + 0] = numberOfBufferedCommands + 1;
    buffer[begin + 1] = WAITCLR;
    buffer[begin + 2] = 0;
    buffer[begin + 3] = 12;
    buffer[begin + 4] = (address >> 24) & 0xff;
    buffer[begin + 5] = (address >> 16) & 0xff;
    buffer[begin + 6] = (address >> 8) & 0xff;
    buffer[begin + 7] = address & 0xff;
    buffer[begin + 8] = (data >> 24) & 0xff;
    buffer[begin + 9] = (data >> 16) & 0xff;
    buffer[begin + 10] = (data >> 8) & 0xff;
    buffer[begin + 11] = data & 0xff;
    buffer[begin + 12] = (timeout >> 24) & 0xff;
    buffer[begin + 13] = (timeout >> 16) & 0xff;
    buffer[begin + 14] = (timeout >> 8) & 0xff;
    buffer[begin + 15] = timeout & 0xff;
    if (begin == 0)
        buffer += '\0';
    return (unsigned int) buffer[begin] + 1;
*/
}

//========================================================================================================================
unsigned int OtsFirmwareCore::read(std::string& buffer, uint32_t address)
{
	return read(buffer, (uint64_t)address);
/*
	unsigned int begin = buffer.length();
    unsigned int numberOfBufferedCommands = getNumberOfBufferedCommands(buffer);
    buffer.resize(buffer.length() + 8, '\0');
    if (begin != 0)
        begin -= 1;
    buffer[begin + 0] = numberOfBufferedCommands + 1;
    buffer[begin + 1] = READ;
    buffer[begin + 2] = 0;
    buffer[begin + 3] = 4;
    buffer[begin + 4] = (address >> 24) & 0xff;
    buffer[begin + 5] = (address >> 16) & 0xff;
    buffer[begin + 6] = (address >> 8) & 0xff;
    buffer[begin + 7] = address & 0xff;
    if (begin == 0)
        buffer += '\0';
    return (unsigned int) buffer[begin] + 1;
*/
}

//========================================================================================================================
unsigned int OtsFirmwareCore::getNumberOfBufferedCommands(std::string& buffer)
{
    if (buffer.length() == 0)
        return 0;
    unsigned int bufferPosition = 0;
    unsigned int commandNumber = 0;
    while (bufferPosition < buffer.length() - 1)
    {
        bufferPosition += (unsigned int) buffer[bufferPosition + 3] + 4;
        ++commandNumber;
    }
    return commandNumber;
}

//========================================================================================================================
std::string OtsFirmwareCore::compareSendAndReceive(const std::string& sentBuffer, std::string& acknowledgment)
{
    std::string reSendBuffer;
    unsigned int skipBuffer = 0;
    unsigned int skipAcknow = 0;
    unsigned int remainBufferCommands;
    unsigned int remainAcknowCommands;

    std::cout << __COUT_HDR_FL__ << "Comparing sent buffer and received acknowledgment!!!" << std::endl;

    std::cout << __COUT_HDR_FL__ << "Buffer size (send): " << sentBuffer.size() << std::endl;
    std::cout << __COUT_HDR_FL__ << "Acknowledgment size (receive): " << acknowledgment.size() << std::endl;

    while(skipBuffer < sentBuffer.size())
    {

        for (int position = 0; position < 4; position++)
        {
            if (position + skipBuffer >= sentBuffer.size()) //make sure the number NEVER goes above the limit
            {
                reSendBuffer.clear();
                std::cout << __COUT_HDR_FL__ << "Done... Works!!!" << std::endl;
                return reSendBuffer;
            }

            if (position == 0)
            {
                if (sentBuffer[position + skipBuffer] != acknowledgment[position + skipAcknow])
                {
                    std::cout << __COUT_HDR_FL__ << "ERROR - Sent " << position + skipBuffer << "th: " << std::hex << (unsigned int)sentBuffer[position + skipBuffer] << std::dec
                    << " different from Received " << position + skipAcknow << "th:"
			      << std::hex << (unsigned int)acknowledgment[position + skipAcknow] << std::dec << std::endl;
                    std::cout << __COUT_HDR_FL__ << "Position: " << position << std::endl;
                    reSendBuffer.clear();
                    for (unsigned int i = skipBuffer; i < (skipBuffer + 4 + sentBuffer[skipBuffer + 3]); i++)
                    {
                        reSendBuffer+= sentBuffer[i];
                    }
                    return reSendBuffer;
                }
            }

            if (position == 1)
            {
                if ( (sentBuffer[position + skipBuffer]) != (acknowledgment[position + skipAcknow] & 0xf) )
                {
                    std::cout << __COUT_HDR_FL__ << "ERROR - Sent " << position + skipBuffer << "th: " << std::hex << (unsigned int)sentBuffer[position + skipBuffer] << std::dec
                    << " different from Received " << position + skipAcknow << "th:"
			      << std::hex << (unsigned int)acknowledgment[position + skipAcknow] << std::dec << std::endl;
                    std::cout << __COUT_HDR_FL__ << "Position: " << position << std::endl;
                    reSendBuffer.clear();
                    for (unsigned int i = skipBuffer; i < (skipBuffer + 4 + sentBuffer[skipBuffer + 3]); i++)
                    {
                        reSendBuffer+= sentBuffer[i];
                    }
                    return reSendBuffer;
                }
            }

            if (position == 2)
            {
                if ( (sentBuffer[position + skipBuffer] != 0) || (acknowledgment[position + skipAcknow] != 0) )
                {
                    std::cout << __COUT_HDR_FL__ << "ERROR - Sent " << position + skipBuffer << "th: " << std::hex << (unsigned int)sentBuffer[position + skipBuffer] << std::dec
                    << " different from Received " << position + skipAcknow << "th:"
                    << std::hex << (unsigned int)acknowledgment[position + skipAcknow] << std::dec << std::endl;
                    std::cout << __COUT_HDR_FL__ << "Position: " << position << std::endl;
                    reSendBuffer.clear();
                    for (unsigned int i = skipBuffer; i < (skipBuffer + 4 + sentBuffer[skipBuffer + 3]); i++)
                    {
                        reSendBuffer+= sentBuffer[i];
                    }
                    return reSendBuffer;
                }
            }

            if ( position == 3)
            {
                remainBufferCommands = sentBuffer[position + skipBuffer]; //4th bit tells us how many bits are left
                remainAcknowCommands = acknowledgment[position + skipAcknow];

                if ( ((remainBufferCommands == 12) && (remainAcknowCommands == 4)) || ((remainBufferCommands == 8) && (remainAcknowCommands == 0)) )
                {
                    skipBuffer += (4 + remainBufferCommands); //go to the beginning of next buffer
                    skipAcknow += (4 + remainAcknowCommands);
                }
                else
                {
                    std::cout << __COUT_HDR_FL__ << "ERROR - Sent " << position + skipBuffer << "th: " << std::hex << (unsigned int)sentBuffer[position + skipBuffer] << std::dec
                    << " not compatible with Received " << position + skipAcknow << "th:"
                    << std::hex << (unsigned int)acknowledgment[position + skipAcknow] << std::dec << std::endl;
                    std::cout << __COUT_HDR_FL__ << "Position: " << position << std::endl;
                    reSendBuffer.clear();
                    for (unsigned int i = skipBuffer; i < (skipBuffer + 4 + sentBuffer[skipBuffer + 3]); i++)
                    {
                        reSendBuffer+= sentBuffer[i];
                    }
                    return reSendBuffer;
                }
            }
        }
    }

    reSendBuffer.clear();
    std::cout << __COUT_HDR_FL__ << "Done... Works!!!" << std::endl;
    return reSendBuffer;
}

//========================================================================================================================
uint32_t OtsFirmwareCore::createRegisterFromValue(std::string& readBuffer, std::string& receivedValue)
{
	uint32_t registerValue;

	memcpy(&registerValue,&receivedValue[2],4);
	//    registerValue = ((unsigned int)receivedValue[2])
	//                    + ((unsigned int)receivedValue[3] << 8)
	//                    + ((unsigned int)receivedValue[4] << 16
	//                    + (unsigned int)receivedValue[5] << 24);

	std::cout << __COUT_HDR_FL__ << "Didn't check for any problem! Register value created!!!" << std::endl;
	return registerValue;
}
