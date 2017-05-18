#include "otsdaq-components/DAQHardware/OtsUDPHardware.h"
#include "otsdaq-core/MessageFacility/MessageFacility.h"
#include "otsdaq-core/Macros/CoutHeaderMacros.h"
#include <iostream>
#include <iomanip>

using namespace ots;


//========================================================================================================================
OtsUDPHardware::OtsUDPHardware (std::string boardIPAddress, unsigned int boardPort) :
        		OtsUDPBoard_(boardIPAddress, boardPort)
{
	Socket::initialize();
}

//========================================================================================================================
OtsUDPHardware::OtsUDPHardware (std::string interfaceIPAddress, unsigned int interfacePort, std::string OtsUDPHardwareIPAddress, unsigned int OtsUDPHardwarePort) :
        		Socket        (interfaceIPAddress,      interfacePort),
				OtsUDPBoard_  (OtsUDPHardwareIPAddress, OtsUDPHardwarePort)
{
	Socket::initialize();
}

//========================================================================================================================
OtsUDPHardware::~OtsUDPHardware(void)
{}

//========================================================================================================================
int OtsUDPHardware::write(const std::string& sendBuffer)
{

	TransceiverSocket::send(OtsUDPBoard_, sendBuffer);
	return 1;
}

//========================================================================================================================
int OtsUDPHardware::write(const std::vector<std::string>& sendBuffer)
{
	for(const auto& it : sendBuffer)
		write(it);
	return 1;
}

//========================================================================================================================
int OtsUDPHardware::writeAndAcknowledge(const std::string& buffer)
{

//	std::cout << __COUT_HDR_FL__ << std::endl;
//	for(auto& b: buffer)
//	{
//		std::cout << __COUT_HDR_FL__ << std::hex << (uint16_t)b << std::dec << std::endl;
//	}
	TransceiverSocket::send(OtsUDPBoard_, buffer);
	//acknowledgment_.clear();
	TransceiverSocket::receive(acknowledgment_);

//	std::cout << __COUT_HDR_FL__ << "Acknowledgment size: " << acknowledgment_.size() << std::endl;
//	for(unsigned int i=0; i< acknowledgment_.size(); i++)
//	{
//		if(i%24 == 0) 
//		std::cout << __COUT_HDR_FL__ << i << "("<< (unsigned int)acknowledgment_[i] << ")-" << std::endl;
//	}
//	

	return 1;
}

//========================================================================================================================
int OtsUDPHardware::writeAndAcknowledge(const std::vector<std::string>& buffer)
{
	for(const auto& it : buffer)
		writeAndAcknowledge(it);

	return 1;
}

//========================================================================================================================
//return -1 on failure
int OtsUDPHardware::read(const std::string& sendBuffer, std::string& receiveBuffer)
{
  { //clear packets so that read matches!
    int clearedPackets = OtsUDPHardware::clearReadSocket();
    if(clearedPackets)
      std::cout << __COUT_HDR_FL__ << "Cleared receive socket buffer: " << clearedPackets << " packets cleared." << std::endl;
  }

    std::cout << __COUT_HDR_FL__ << __PRETTY_FUNCTION__ << "sending" << std::endl;
	TransceiverSocket::send(OtsUDPBoard_, sendBuffer);
	std::cout << __COUT_HDR_FL__ << __PRETTY_FUNCTION__ << "receiving" << std::endl;
	if(TransceiverSocket::receive(receiveBuffer) < 0) return -1;
	std::cout << __COUT_HDR_FL__ << __PRETTY_FUNCTION__ << "done" << std::endl;

	std::cout << __COUT_HDR_FL__ << "RECEIVED MESSAGE: ";
	for(uint32_t i=0; i<receiveBuffer.size(); i++)
		std::cout << std::setfill('0') << std::setw(2) << std::hex << (((int16_t) receiveBuffer[i]) &0xff) << "-" << std::dec;
	std::cout << std::endl;


	return 1;
}

//========================================================================================================================
int OtsUDPHardware::read(const std::vector<std::string>& sendBuffer, std::vector<std::string>& receiveBuffer)
{
	receiveBuffer.resize(sendBuffer.size());
	auto receiveIt = receiveBuffer.begin();
	//    for(std::vector<std::string>::const_iterator it=sendBuffer.begin(); it!=sendBuffer.end(); it++, receiveIt++)
	for(const auto& it : sendBuffer)
		read(it,*(receiveIt++));

	return 1;
}

//========================================================================================================================
//reads from read socket until timeout is reached (remove stale packets)
// returns count of packets that were cleared
int OtsUDPHardware::clearReadSocket()
{
	std::string dummerReceiveBuffer;
	int cnt = 0;
	while(TransceiverSocket::receive(dummerReceiveBuffer) >= 0) ++cnt;
	return cnt;
}









