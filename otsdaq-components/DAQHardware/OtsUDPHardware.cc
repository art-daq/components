#include "otsdaq-components/DAQHardware/OtsUDPHardware.h"
#include "otsdaq-core/MessageFacility/MessageFacility.h"
#include "otsdaq-core/Macros/CoutHeaderMacros.h"
#include <iostream>
#include <iomanip>

using namespace ots;


//========================================================================================================================
OtsUDPHardware::OtsUDPHardware (std::string boardIPAddress, unsigned int boardPort)
:	//Socket() default constructor
	OtsUDPBoard_	(boardIPAddress, 		boardPort)
//	FrontEndHardwareBase ()
{
	Socket::initialize();


//	char msg[100];
//	sprintf(msg,"_%d",getPort());
//	std::string fn = "/tmp/new_udp_chk" + std::string(msg) + ".dat";
//	FILE *fp = fopen(fn.c_str(),"w");
//	if(fp) fclose(fp);
//	std::cout << __COUT_HDR_FL__ << fn << std::endl;
}

//========================================================================================================================
OtsUDPHardware::OtsUDPHardware (std::string hostIPAddress, unsigned int hostPort,
		std::string OtsUDPHardwareIPAddress, unsigned int OtsUDPHardwarePort,
		unsigned int version)
:	Socket        (hostIPAddress,      hostPort)
, 	FrontEndHardwareBase (version)
,	OtsUDPBoard_  (OtsUDPHardwareIPAddress, OtsUDPHardwarePort)
{
	Socket::initialize();


//	char msg[100];
//	sprintf(msg,"_%d",getPort());
//	std::string fn = "/tmp/new_udp_chk" + std::string(msg) + ".dat";
//	FILE *fp = fopen(fn.c_str(),"w");
//	if(fp) fclose(fp);
//	std::cout << __COUT_HDR_FL__ << fn << std::endl;
}

//========================================================================================================================
OtsUDPHardware::~OtsUDPHardware(void)
{}

//========================================================================================================================
void OtsUDPHardware::write(const std::string& sendBuffer)
throw(std::runtime_error)
try
{
//	char msg[100];
//	sprintf(msg,"_%d",getPort());
//	std::string fn = "/tmp/new_udp_chk" + std::string(msg) + ".dat";
//	FILE *fp = fopen(fn.c_str(),"a");
//	std::cout << __COUT_HDR_FL__ << fn << std::endl;

//
//	if(fp) //debug
//	{
//		std::stringstream ss;
//		ss << "\t";
//		uint32_t begin = 0;
//		for(uint32_t i=begin; i<sendBuffer.size(); i++)
//		{
//			if(i==begin+2) ss << ":::";
//			else if(i==begin+10) ss << ":::";
//			ss << std::setfill('0') << std::setw(2) << std::hex << (((int16_t) sendBuffer[i]) &0xFF) << "-" << std::dec;
//		}
//		ss << std::endl;
//		fprintf(fp,"%s",ss.str().c_str());
//	}
//	if(fp) fclose(fp);


	if(TransceiverSocket::send(OtsUDPBoard_, sendBuffer) < 0)
	{
		__SS__ << "Write failed." << std::endl;
		__COUT_ERR__ << "\n" << ss.str() << std::endl;
		throw std::runtime_error(ss.str());
	}
}
catch(std::runtime_error &e)
{
	throw;
}
catch(...)
{
	__SS__ << "Unrecognized exception caught!" << std::endl;
	__COUT_ERR__ << "\n" << ss.str() << std::endl;
	throw std::runtime_error(ss.str());
}

//========================================================================================================================
void OtsUDPHardware::write(const std::vector<std::string>& sendBuffer)
throw(std::runtime_error)
{
	for(const auto& it : sendBuffer)
	{

//		char msg[100];
//		sprintf(msg,"_%d",getPort());
//		std::string fn = "/tmp/new_udp_chk" + std::string(msg) + ".dat";
//		FILE *fp = fopen(fn.c_str(),"a");
//		std::cout << __COUT_HDR_FL__ << fn << std::endl;


//		if(fp) //debug
//		{
//			std::stringstream ss;
//			ss << "\t";
//			uint32_t begin = 0;
//			for(uint32_t i=begin; i<it.size(); i++)
//			{
//				if(i==begin+2) ss << ":::";
//				else if(i==begin+10) ss << ":::";
//				ss << std::setfill('0') << std::setw(2) << std::hex << (((const int16_t) it[i]) &0xFF) << "-" << std::dec;
//			}
//			ss << std::endl;
//			fprintf(fp,"%s",ss.str().c_str());
//		}
//		if(fp) fclose(fp);

		write(it);
	}
}

//========================================================================================================================
void OtsUDPHardware::writeAndAcknowledge(const std::string& buffer,
		int timeoutSeconds)
throw(std::runtime_error)
try
{

//	char msg[100];
//	sprintf(msg,"_%d",getPort());
//	std::string fn = "/tmp/new_udp_chk" + std::string(msg) + ".dat";
//	FILE *fp = fopen(fn.c_str(),"a");
//	std::cout << __COUT_HDR_FL__ << fn << std::endl;


//	if(fp) //debug
//	{
//		std::stringstream ss;
//		ss << "\tack ";
//		uint32_t begin = 0;
//		for(uint32_t i=begin; i<buffer.size(); i++)
//		{
//			if(i==begin+2) ss << ":::";
//			else if(i==begin+10) ss << ":::";
//			ss << std::setfill('0') << std::setw(2) << std::hex << (((int16_t) buffer[i]) &0xFF) << "-" << std::dec;
//		}
//		ss << std::endl;
//		fprintf(fp,"%s",ss.str().c_str());
//	}
//	if(fp) fclose(fp);

	//	std::cout << __COUT_HDR_FL__ << std::endl;
	//	for(auto& b: buffer)
	//	{
	//		std::cout << __COUT_HDR_FL__ << std::hex << (uint16_t)b << std::dec << std::endl;
	//	}
	TransceiverSocket::send(OtsUDPBoard_, buffer);
	//acknowledgment_.clear();

	if(timeoutSeconds < 0) //use default timeout
	{
		if(TransceiverSocket::receive(acknowledgment_) < 0)
		{
			__SS__ << "writeAndAcknowledge failed. Default timeout period reached without response." << std::endl;
			__COUT_ERR__ << "\n" << ss.str() << std::endl;
			throw std::runtime_error(ss.str());
		}
	}
	else
	{
		if(TransceiverSocket::receive(acknowledgment_,timeoutSeconds) < 0)
		{
			__SS__ << "writeAndAcknowledge failed. " << timeoutSeconds <<
					" second timeout period reached without response." << std::endl;
			__COUT_ERR__ << "\n" << ss.str() << std::endl;
			throw std::runtime_error(ss.str());
		}
	}


	//	std::cout << __COUT_HDR_FL__ << "Acknowledgment size: " << acknowledgment_.size() << std::endl;
	//	for(unsigned int i=0; i< acknowledgment_.size(); i++)
	//	{
	//		if(i%24 == 0)
	//		std::cout << __COUT_HDR_FL__ << i << "("<< (unsigned int)acknowledgment_[i] << ")-" << std::endl;
	//	}
	//

}
catch(std::runtime_error &e)
{
	throw;
}
catch(...)
{
	__SS__ << "Unrecognized exception caught!" << std::endl;
	__COUT_ERR__ << "\n" << ss.str() << std::endl;
	throw std::runtime_error(ss.str());
}

//========================================================================================================================
void OtsUDPHardware::writeAndAcknowledge(const std::vector<std::string>& buffer,
		int timeoutSeconds)
throw(std::runtime_error)
{
	for(const auto& it : buffer)
	{
//		char msg[100];
//		sprintf(msg,"_%d",getPort());
//		std::string fn = "/tmp/new_udp_chk" + std::string(msg) + ".dat";
//		FILE *fp = fopen(fn.c_str(),"a");
//		std::cout << __COUT_HDR_FL__ << fn << std::endl;


//		if(fp) //debug
//		{
//			std::stringstream ss;
//			ss << "\tack ";
//			uint32_t begin = 0;
//			for(uint32_t i=begin; i<it.size(); i++)
//			{
//				if(i==begin+2) ss << ":::";
//				else if(i==begin+10) ss << ":::";
//				ss << std::setfill('0') << std::setw(2) << std::hex << (((const int16_t) it[i]) &0xFF) << "-" << std::dec;
//			}
//			ss << std::endl;
//			fprintf(fp,"%s",ss.str().c_str());
//		}
//		if(fp) fclose(fp);

		writeAndAcknowledge(it);
	}
}

//========================================================================================================================
//return -1 on failure
void OtsUDPHardware::read(const std::string& sendBuffer, std::string& receiveBuffer,
		int timeoutSeconds)
throw(std::runtime_error)
try
{
	{ //clear packets so that read matches!
		int clearedPackets = OtsUDPHardware::clearReadSocket();
		if(clearedPackets)
			std::cout << __COUT_HDR_FL__ << "Cleared receive socket buffer: " << clearedPackets << " packets cleared." << std::endl;
	}

	__COUT__ << "sending" << std::endl;
	TransceiverSocket::send(OtsUDPBoard_, sendBuffer);
	__COUT__ << "receiving" << std::endl;

	if(timeoutSeconds < 0) //use default timeout
	{
		if(TransceiverSocket::receive(receiveBuffer) < 0)
		{
			__SS__ << "Read failed. Default timeout period reached without response." << std::endl;
			__COUT_ERR__ << "\n" << ss.str() << std::endl;
			throw std::runtime_error(ss.str());
		}
	}
	else
	{
		if(TransceiverSocket::receive(receiveBuffer,timeoutSeconds) < 0)
		{
			__SS__ << "Read failed. " << timeoutSeconds <<
					" second timeout period reached without response." << std::endl;
			__COUT_ERR__ << "\n" << ss.str() << std::endl;
			throw std::runtime_error(ss.str());
		}
	}
	__COUT__ << "done" << std::endl;

	std::cout << __COUT_HDR_FL__ << "RECEIVED MESSAGE: ";
	for(uint32_t i=0; i<receiveBuffer.size(); i++)
		std::cout << std::setfill('0') << std::setw(2) << std::hex << (((int16_t) receiveBuffer[i]) &0xff) << "-" << std::dec;
	std::cout << std::endl;

}
catch(std::runtime_error &e)
{
	throw;
}
catch(...)
{
	__SS__ << "Unrecognized exception caught!" << std::endl;
	__COUT_ERR__ << "\n" << ss.str() << std::endl;
	throw std::runtime_error(ss.str());
}

//========================================================================================================================
void OtsUDPHardware::read(const std::vector<std::string>& sendBuffers,
		std::vector<std::string>& receiveBuffers,
		int timeoutSeconds)
throw(std::runtime_error)
{
	receiveBuffers.resize(sendBuffers.size());
	auto receiveBufferIterator = receiveBuffers.begin();
	for(const auto& sendBuffer : sendBuffers)
		read(sendBuffer, *(receiveBufferIterator++));
}

//========================================================================================================================
void OtsUDPHardware::read(const std::string& sendBuffer,
		uint64_t& receiveQuadWord,
		int timeoutSeconds)
throw(std::runtime_error)
{
	std::string receiveBuffer;
	read(sendBuffer,receiveBuffer);

	//force response to be only one quad word
	if(receiveBuffer.length() != 10)
	{
		__SS__ << "Read uint64_t quad-word failed. Invalid size of received buffer: " <<
				receiveBuffer.length() << " != " << 10 << std::endl;
		__COUT_ERR__ << "\n" << ss.str() << std::endl;
		throw std::runtime_error(ss.str());
	}
	std::copy_n((char *)&receiveBuffer[2],sizeof(uint64_t),&receiveQuadWord);
}

//========================================================================================================================
void OtsUDPHardware::read(const std::string& sendBuffer,
		std::vector<uint64_t>& receiveQuadWords,
		int timeoutSeconds)
throw(std::runtime_error)
{
	receiveQuadWords.resize(0); //clear

	std::string receiveBuffer;
	read(sendBuffer,receiveBuffer);

	//force response to be only integer quad words
	if((receiveBuffer.length()-2) % 8 != 0)
	{
		__SS__ << "Read vector of uint64_t quad-word failed. Invalid size of received buffer: (" <<
				receiveBuffer.length() << " - 2) % 8 != 0" << std::endl;
		__COUT_ERR__ << "\n" << ss.str() << std::endl;
		throw std::runtime_error(ss.str());
	}

	for(unsigned int i = 2; i < receiveBuffer.length(); i += 8)
	{
		receiveQuadWords.push_back(uint64_t());
		std::copy_n((char *)&receiveBuffer[i],sizeof(uint64_t),&receiveQuadWords[receiveQuadWords.size()-1]);
	}
}

//========================================================================================================================
void OtsUDPHardware::read(const std::vector<std::string>& sendBuffers,
		std::vector<std::vector<uint64_t> >& receiveQuadWordsVector,
		int timeoutSeconds)
throw(std::runtime_error)
{
	receiveQuadWordsVector.resize(sendBuffers.size()); //create a return vector for each send buffer

	std::string receiveBuffer;

	//for each send buffere
	for(unsigned int b = 0; b < sendBuffers.size(); ++b)
	{
		receiveQuadWordsVector[b].resize(0); //clear

		read(sendBuffers[b], receiveBuffer);

		//force response to be only integer quad words
		if((receiveBuffer.length()-2) % 8 != 0)
		{
			__SS__ << "Read vector of uint64_t quad-word failed. Invalid size of received buffer: (" <<
					receiveBuffer.length() << " - 2) % 8 != 0" << std::endl;
			__COUT_ERR__ << "\n" << ss.str() << std::endl;
			throw std::runtime_error(ss.str());
		}

		//copy to uint64_t's
		for(unsigned int i = 2; i < receiveBuffer.length(); i += 8)
		{
			receiveQuadWordsVector[b].push_back(uint64_t());
			std::copy_n((char *)&receiveBuffer[i],sizeof(uint64_t),
					&receiveQuadWordsVector[b][receiveQuadWordsVector[b].size()-1]);
		}
	}
}

//========================================================================================================================
//clearReadSocket
//
//	flushes read socket.
//
//	reads from read socket until timeout is reached (remove stale packets)
// returns count of packets that were cleared
int OtsUDPHardware::clearReadSocket()
{
	std::string dummerReceiveBuffer;
	int cnt = 0;

	//receive with no timeout
	try
	{
		while(TransceiverSocket::receive(dummerReceiveBuffer,
				0/*timeoutSeconds*/,
				0/*timeoutUSeconds*/,
				false /*verbose*/)>= 0)
			++cnt;
	}
	catch(...)
	{
		//ignore exceptions... assume due to there be nothing to read
	}
	return cnt;
}









