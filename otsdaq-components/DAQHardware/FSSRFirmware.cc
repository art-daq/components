#include "otsdaq-components/DAQHardware/FSSRFirmware.h"
#include "otsdaq-components/DAQHardware/FSSRFirmwareDefinitions.h"
#include "otsdaq-core/BitManipulator/BitManipulator.h"
#include "otsdaq-components/DetectorHardware/FSSRROCDefinitions.h"
#include "otsdaq-core/MessageFacility/MessageFacility.h"
#include "otsdaq-core/Macros/CoutHeaderMacros.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
#include <cstdlib>

using namespace ots;


//========================================================================================================================
FSSRFirmware::FSSRFirmware(unsigned int version, std::string type) :
		FrontEndFirmwareBase(version),
		stripCSRRegisterValue_(0)
{
	protocolInstance_ = FrontEndFirmwareBase::getInstance(type,version);
	assert(protocolInstance_ != NULL);
	//returns either new OtsUDPFirmware or new PurdueFirmwareCore,
	//now we can call write/read etc with protocol->write, protocol->read, etc

}

//========================================================================================================================
FSSRFirmware::~FSSRFirmware(void)
{
	delete protocolInstance_;
	protocolInstance_= NULL;
}

//========================================================================================================================
int FSSRFirmware::init(void)
{
	return 0;
}


//========================================================================================================================
std::string FSSRFirmware::universalRead(char* address)
{
	return protocolInstance_->read(address);
}

//========================================================================================================================
std::string FSSRFirmware::universalWrite(char* address, char* data)
{
	return protocolInstance_->write(address, data);
}

//========================================================================================================================
uint32_t FSSRFirmware::createRegisterFromValue (std::string& readBuffer, std::string& receivedValue)
{
	return protocolInstance_->createRegisterFromValue(readBuffer,receivedValue);
}

//========================================================================================================================
std::string FSSRFirmware::configureClocks(std::string source, double frequency)
{
	std::cout << __COUT_HDR_FL__ << "Writing Clock configuration!" << std::endl;

	std::string buffer;
	//NoNeedNowwrite(buffer, ETHIO_DESTINATION_PORT, 0x0000b798); //  Listen port for ethio stuff

	setPacketSizeStripCSR(6);
	setExternalBCOClockSourceStripCSR(source); //(source)
	protocolInstance_->write(buffer, STRIP_CSR, stripCSRRegisterValue_); //  Reset CSR - reset trigger counter, external 27 MHz clock

	resetDCM(buffer);
	alignReadOut(buffer,0x3000);//0x3000

	setFrequencyFromClockState(buffer, frequency);
	protocolInstance_->write(buffer, STRIP_CSR, stripCSRRegisterValue_);

	resetDCM(buffer);
	std::cout << __COUT_HDR_FL__ << "stripCSRRegisterValue :" << std::hex << stripCSRRegisterValue_ << std::dec << std::endl;

	return buffer;
}

//========================================================================================================================
void FSSRFirmware::resetDCM(std::string& buffer)
{
	resetDCMStripCSR(true);
	protocolInstance_->write(buffer, STRIP_CSR, stripCSRRegisterValue_); //  Set reset to DCM

	resetDCMStripCSR(false);
	protocolInstance_->write(buffer, STRIP_CSR, stripCSRRegisterValue_); //  Clear reset to DCM

	protocolInstance_->waitClear(buffer, STRIP_CSR, waitDCMResetStripCSR()); //  Wait for DCM to lock
}


//========================================================================================================================
void FSSRFirmware::alignReadOut(std::string& buffer, uint32_t value)
{
	protocolInstance_->write(buffer, STRIP_TRIM_CSR, value); //  MCLKB edge for channel 5 // was 0x00002000
}
//========================================================================================================================
std::string FSSRFirmware::resetDetector(int channel)
{
	std::cout << __COUT_HDR_FL__ << "Resetting detector!" << std::endl;
	std::string buffer;
	if (channel == -1)//reset all channels
	{
		//write(buffer,STRIP_RESET,0xd000003f);                  //  Issue reset
		protocolInstance_->write(buffer, STRIP_RESET, 0xf000003f); //  Issue reset // was 0xf000003f
		protocolInstance_->waitClear(buffer, STRIP_RESET, 0xf0000000); //  Wait for reset to complete // was 0xf0000000
	} else
	{
		protocolInstance_->write(buffer, STRIP_RESET, 0xf000003f); //  Issue reset
		protocolInstance_->waitClear(buffer, STRIP_RESET, 0xf0000000); //  Wait for reset to complete
	}

	return buffer;
}

//========================================================================================================================
std::string FSSRFirmware::enableTrigger(void)
{
	std::string buffer;
	std::cout << __COUT_HDR_FL__ << "Enabling Trigger!!!" << std::endl;
	std::cout << __COUT_HDR_FL__ << "stripCSRRegisterValue in :" << std::hex << stripCSRRegisterValue_ << std::dec << std::endl;

	//setHaltStripCSR(1);//WARNING THIS IS CLEARED BY THE MASTER BUT IF THERE IS NO MASTER NOTHING WORKS UNLESS THE BIT IS UNSET
	sendTriggerDataStripCSR(true);
	sendTriggerNumberStripCSR(true);
	sendBCOStripCSR(true);
	protocolInstance_->write(buffer, STRIP_CSR, stripCSRRegisterValue_);

	stripTriggerCSRRegisterValue_ = 0;
	BCOOffset(4);
	protocolInstance_->write(buffer, STRIP_TRIG_CSR, stripTriggerCSRRegisterValue_); //  BCO offset // was 0x00000004

	//  write(buffer,STRIP_TRIG_INPUT_0,0x1f060040);  //  FSSR GOTHIT trigger input - timed in for the 27 MHz external clock
	//  write(buffer,STRIP_TRIG_INPUT_3,0x3f874040);  //  Unbiased trigger input + external trigger

	configureStripTriggerUnbiased(buffer);

	configureTriggerInputs(buffer);

	//FIXME for IP .36 the number to set is 0x20401000

	if (ots::FrontEndFirmwareBase::version_ == 1)
		protocolInstance_->write(buffer, STRIP_TRIG_INPUT_3, 0x20401000); // Turn on streaming hits along with BCO data
	else if (ots::FrontEndFirmwareBase::version_ == 2)
		protocolInstance_->write(buffer, STRIP_TRIG_INPUT_3, 0x20301000); // Turn on streaming hits along with BCO data
	else
	{
		std::cout << __COUT_HDR_FL__ << "what version is this?" << ots::FrontEndFirmwareBase::version_ << std::endl;
		assert(0);
	}
	std::cout << __COUT_HDR_FL__ << "stripCSRRegisterValue out:" << std::hex << stripCSRRegisterValue_ << std::dec << std::endl;
	std::cout << __COUT_HDR_FL__ << "Done enabling Trigger!!!" << std::endl;

	return buffer;
}

//========================================================================================================================
std::string FSSRFirmware::setDataDestination(std::string ip, uint32_t port)
{
    std::cout << __COUT_HDR_FL__ << "Set data destination!" << std::endl;
    std::string buffer;
    struct sockaddr_in socketAddress;
    inet_pton(AF_INET, ip.c_str(), &(socketAddress.sin_addr));
    std::cout << __COUT_HDR_FL__ << "ADDRESS: " << std::hex << ntohl(socketAddress.sin_addr.s_addr) << std::dec << std::endl;
    protocolInstance_->write(buffer, DATA_DESTINATION_IP, ntohl(socketAddress.sin_addr.s_addr)); //  Set data destination IP 192.168.133.1
    std::cout << __COUT_HDR_FL__ << "PORT: " << std::hex << port << std::dec << std::endl;
    protocolInstance_->write(buffer, DATA_SOURCE_DESTINATION_PORT, port); //  Set data destination port
    std::cout << __COUT_HDR_FL__ << "THIS IS THE BUFFER: " << buffer << std::endl;

    for(uint32_t i=0; i<buffer.size(); i++)
        printf("%2.2X-",(uint8_t)buffer[i]);
    std::cout << std::dec << std::endl;

    return buffer;
}




//========================================================================================================================
std::string FSSRFirmware::resetBCO(void)
{
	std::cout << __COUT_HDR_PL__ << "Reset BCO!!!" << std::endl;
	std::cout << __COUT_HDR_FL__ << "stripCSRRegisterValue in :" << std::hex << stripCSRRegisterValue_ << std::dec << std::endl;
	std::string buffer;

	resetTriggerCounterStripCSR(buffer);
	//write(buffer, STRIP_CSR, stripCSRRegisterValue_);//the write is done in the reset
	std::cout << __COUT_HDR_PL__ << "stripCSRRegisterValue :" << std::hex << stripCSRRegisterValue_ << std::dec << std::endl;

	//msg->Write(STRIP_SC_CSR,0x90000b95|(chmask<<16));
	protocolInstance_->write(buffer,STRIP_SC_CSR,0x903f0b95);//  This is the <SCR,set> command with the bit set to sync SHIFT with BCO=0.

	//enableBCOStripCSR(true);
	//protocolInstance_->write(buffer, STRIP_CSR, stripCSRRegisterValue_);

	std::cout << __COUT_HDR_PL__ << "stripCSRRegisterValue out:" << std::hex << stripCSRRegisterValue_ << std::dec << std::endl;
	std::cout << __COUT_HDR_FL__ << "Done reset BCO!!!" << std::endl;

	return buffer;
}

//========================================================================================================================
std::string FSSRFirmware::armBCOReset(void)
{
	std::cout << __COUT_HDR_FL__ << std::endl;
	std::cout << __COUT_HDR_PL__ << "stripCSRRegisterValue in :" << std::hex << stripCSRRegisterValue_ << std::dec << std::endl;
	std::string buffer;

	enableBCOStripCSR(true);
	protocolInstance_->write(buffer, STRIP_CSR, stripCSRRegisterValue_);
	std::cout << __COUT_HDR_PL__ << "stripCSRRegisterValue out:" << std::hex << stripCSRRegisterValue_ << std::dec << std::endl;
	std::cout << __COUT_HDR_FL__ << "Done!" << std::endl;

	return buffer;
}

//========================================================================================================================
std::string FSSRFirmware::startStream(bool channel0, bool channel1, bool channel2, bool channel3, bool channel4, bool channel5)
{
	std::cout << __COUT_HDR_FL__ << "Start Stream!" << std::endl;
	std::cout << __COUT_HDR_PL__ << "stripCSRRegisterValue in:" << std::hex << stripCSRRegisterValue_ << std::dec << std::endl;
	std::string buffer;

	std::cout << __COUT_HDR_PL__ << " channel0 " << channel0 << " channel1 " << channel1 << " channel2 " << channel2 << " channel3 " << channel3 << " channel4 " << channel4 << " channel5 " << channel5 << std::endl;

	enableChannelsStripCSR(channel0, channel1, channel2, channel3, channel4, channel5);
	//    if (version_ == 1)
	//        enableChannelsStripCSR(true, true, true, true, false, false);
	//    else if (version_ == 2)
	//        enableChannelsStripCSR(true, true, true, true, true, true);

	enableStreamStripCSR(true); //  Turn on streaming hits along with BCO data // was 0x0f000f30
	protocolInstance_->write(buffer, STRIP_CSR, stripCSRRegisterValue_);

	std::cout << __COUT_HDR_PL__ << "stripCSRRegisterValue out:" << std::hex << stripCSRRegisterValue_ << std::dec << std::endl;
	std::cout << __COUT_HDR_PL__ << "Done start Stream!" << std::endl;

	return buffer;
}

//========================================================================================================================
std::string FSSRFirmware::stopStream(void)
{
	std::string buffer;
	enableChannelsStripCSR(false, false, false, false, false, false);
	enableStreamStripCSR(false);
	protocolInstance_->write(buffer, STRIP_CSR, stripCSRRegisterValue_);
	return buffer;
}

//========================================================================================================================
void FSSRFirmware::makeDACSequence(FirmwareSequence<uint64_t>& sequence, unsigned int channel, const ROCStream& rocStream)
{
	const ROCDACs& rocDACs = rocStream.getROCDACs();
	for (DACList::const_iterator it = rocDACs.getDACList().begin(); it	!= rocDACs.getDACList().end(); it++)
	{
		//if(it->first != "SendData" && it->first != "RejectHits") continue;
		uint64_t data = FSSRROCDefinitions::makeDACWriteCommand(
				rocStream.getFEWROCAddress(), it->first, it->second.second);
		sequence.pushBack(ChannelFIFOAddress[channel], data);
		sequence.pushBack(ChannelFIFOAddress[channel],
				BitManipulator::insertBits(data, (uint64_t) 0x48, 56, 8));
		//set WRITE
		sequence.pushBack(ChannelFIFOAddress[channel],
				BitManipulator::insertBits(data, (uint64_t) 1, 60, 1));
		//clr WRITE
		sequence.pushBack(ChannelFIFOAddress[channel],
				BitManipulator::insertBits(data, (uint64_t) 0, 60, 1));
		//clr TALK
		sequence.pushBack(ChannelFIFOAddress[channel],
				BitManipulator::insertBits(data, (uint64_t) 0, 62, 1));
		sequence.pushBack(ChannelFIFOAddress[channel],
				BitManipulator::insertBits(data, (uint64_t) 0x40, 56, 8));
		//break;
	}
}

//========================================================================================================================
void FSSRFirmware::makeDACSequence(FirmwareSequence<uint32_t>& sequence,
		unsigned int channel, const ROCStream& rocStream)
{
	const ROCDACs& rocDACs = rocStream.getROCDACs();
	for (DACList::const_iterator it = rocDACs.getDACList().begin(); it
	!= rocDACs.getDACList().end(); it++)
	{
		/*RYAN
         //if(it->first != "SendData" && it->first != "RejectHits") continue;
         uint64_t data = FSSRROCDefinitions::makeDACWriteCommand(rocStream.getFEWROCAddress(), it->first, it->second.second);
         sequence.pushBack(ChannelFIFOAddress[channel], data);
         sequence.pushBack(ChannelFIFOAddress[channel], BitManipulator::insertBits(data,(uint32_t)0x48,56,8));
         //set WRITE
         sequence.pushBack(ChannelFIFOAddress[channel], BitManipulator::insertBits(data,(uint32_t)1,60,1));
         //clr WRITE
         sequence.pushBack(ChannelFIFOAddress[channel], BitManipulator::insertBits(data,(uint32_t)0,60,1));
         //clr TALK
         sequence.pushBack(ChannelFIFOAddress[channel], BitManipulator::insertBits(data,(uint32_t)0,62,1));
         sequence.pushBack(ChannelFIFOAddress[channel], BitManipulator::insertBits(data,(uint32_t)0x40,56,8));
		 */

		//if(it->first != "SendData" && it->first != "RejectHits") continue;
		uint32_t data = FSSRROCDefinitions::makeDACWriteHeader(
				rocStream.getFEWROCAddress(), it->first);
		//Insert channel
		BitManipulator::insertBits(data, 1, 16 + channel, 1);
		sequence.pushBack(ChannelFIFOAddress[channel], it->second.second);
		std::cout << __COUT_HDR_FL__ << "Register: " << it->first << " value: "
				<< it->second.second << std::hex << " -> Data: " << data << std::dec
				<< std::endl;
		sequence.pushBack(STRIP_SC_CSR, data);
	}
}

//========================================================================================================================
void FSSRFirmware::makeDACBuffer(std::string& buffer, unsigned int channel, const ROCStream& rocStream)
{
	std::cout << __COUT_HDR_FL__ << "Channel: " << channel << std::endl;
	std::cout << __COUT_HDR_FL__ << "BufferINsize: " << buffer.size() << std::endl;
	const ROCDACs& rocDACs = rocStream.getROCDACs();
//	for (DACList::const_iterator it = rocDACs.getDACList().begin(); it != rocDACs.getDACList().end(); it++)
//	{
//		std::string bufferElement;
//		protocolInstance_->waitClear(bufferElement, STRIP_SC_CSR, 0x80000000);
//		uint32_t registerHeader = 0;
//		//FIXME This must go in the FSSRROCDefinitions stuff
//		//if (it->first != "RejectHits" && it->first != "SendData")
//		if (it->first == "VTp0")
//		{
//			//protocolInstance_->write(bufferElement, ChannelFIFOAddress[channel], it->second.second);
//			registerHeader = FSSRROCDefinitions::makeDACReadHeader(rocStream.getFEWROCAddress(), it->first);
//			//Insert channel
//			BitManipulator::insertBits(registerHeader, 1, 16 + channel, 1);
////		}
////		else
////		if (it->first == "SendData")
////		{
////			if (it->second.second == 1 || it->second.second == 2)
////			{
////				registerHeader = FSSRROCDefinitions::makeDACSetHeader(rocStream.getFEWROCAddress(), it->first);
////				//Insert channel
////				BitManipulator::insertBits(registerHeader, 1, 16 + channel, 1);
////			}
////			else if (it->second.second == 0 || it->second.second == 5)
////			{
////				registerHeader = FSSRROCDefinitions::makeDACResetHeader(rocStream.getFEWROCAddress(), it->first);
////				//Insert channel
////				BitManipulator::insertBits(registerHeader, 1, 16 + channel, 1);
////			}
////			else
////				std::cout << __COUT_HDR_FL__ << "Register value for : " << it->first
////				<< " doesn't have a value I expect -> value = "
////				<< it->second.second << std::endl;
////
////		}
//
//	    std::cout << __COUT_HDR_FL__ << "Register: " << it->first << " value: " << it->second.second << std::hex << " -> Data: " << registerHeader << std::dec << std::endl;
//		protocolInstance_->write(bufferElement, STRIP_SC_CSR, registerHeader);
//		protocolInstance_->waitClear(bufferElement, STRIP_SC_CSR, 0x80000000);
//
//		//buffer.push_back(bufferElement);
//		buffer += bufferElement;
//		}
//		//break;
//	}
	for (DACList::const_iterator it = rocDACs.getDACList().begin(); it != rocDACs.getDACList().end(); it++)
	{
		std::string bufferElement;
		protocolInstance_->waitClear(bufferElement, STRIP_SC_CSR, 0x80000000);
		uint32_t registerHeader = 0;
		//FIXME This must go in the FSSRROCDefinitions stuff
		if (it->first != "RejectHits" && it->first != "SendData")
		{
			protocolInstance_->write(bufferElement, ChannelFIFOAddress[channel], it->second.second);
			registerHeader = FSSRROCDefinitions::makeDACWriteHeader(rocStream.getFEWROCAddress(), it->first);
			//Insert channel
			BitManipulator::insertBits(registerHeader, 1, 16 + channel, 1);
		}
		else
		{
			if (it->second.second == 1 || it->second.second == 2)
			{
				registerHeader = FSSRROCDefinitions::makeDACSetHeader(rocStream.getFEWROCAddress(), it->first);
				//Insert channel
				BitManipulator::insertBits(registerHeader, 1, 16 + channel, 1);
			}
			else if (it->second.second == 0 || it->second.second == 5)
			{
				registerHeader = FSSRROCDefinitions::makeDACResetHeader(rocStream.getFEWROCAddress(), it->first);
				//Insert channel
				BitManipulator::insertBits(registerHeader, 1, 16 + channel, 1);
			}
			else
				std::cout << __COUT_HDR_FL__ << "Register value for : " << it->first
				<< " doesn't have a value I expect -> value = "
				<< it->second.second << std::endl;

		}

	    //std::cout << __COUT_HDR_FL__ << "Register: " << it->first << " value: " << it->second.second << std::hex << " -> Data: " << registerHeader << std::dec << std::endl;
		protocolInstance_->write(bufferElement, STRIP_SC_CSR, registerHeader);
		protocolInstance_->waitClear(bufferElement, STRIP_SC_CSR, 0x80000000);

		//buffer.push_back(bufferElement);
		buffer += bufferElement;
		//break;
	}
	std::cout << __COUT_HDR_FL__ << "BufferOUTsize: " << buffer.size() << std::endl;
}

//========================================================================================================================
void FSSRFirmware::makeDACBuffer(std::vector<std::string>& buffer, unsigned int channel, const ROCStream& rocStream)
{

	std::cout << __COUT_HDR_FL__ << "\tMaking DAC Buffer" << std::endl;

	int limitCount = 0;
	unsigned int singleVectorCount = 0;

	std::string alternateBuffer;

	std::cout << __COUT_HDR_FL__ << "Channel: " << channel << std::endl;
	const ROCDACs& rocDACs = rocStream.getROCDACs();
	//std::cout << __COUT_HDR_FL__ << "Number of DACs: " << rocDACs.getDACList().size() << std::endl;
	std::string bufferElement;
	//FIXME My
	//	for (const auto it: rocDACs.getDACList())
    for (const std::pair<std::string, std::pair<unsigned int, unsigned int> >& it: rocDACs.getDACList())
//	for (std::map<std::string, std::pair<unsigned int, unsigned int> >::const_iterator it = rocDACs.getDACList().begin(); it != rocDACs.getDACList().end(); it++)
	{
		//std::cout << __COUT_HDR_FL__ << "Register?" << std::endl;
//		if (it.first != "ActiveLines") continue;
//		std::cout << __COUT_HDR_FL__ << "Register-1: " << it->first << " val: " << it->second.first  << " = " << it->second.second << std::endl;
		protocolInstance_->waitClear(bufferElement, STRIP_SC_CSR, 0x80000000);
		uint32_t registerHeader = 0;
		//FIXME This must go in the FSSRROCDefinitions stuff
		//std::cout << __COUT_HDR_FL__ << "Register0: " << it.first << std::endl;
		if (it.first != "RejectHits" && it.first != "SendData")
		{
			//std::cout << __COUT_HDR_FL__ << "Register1: " << it.first << "Channel: " << channel << " fifo address: " << ChannelFIFOAddress[channel] << std::endl;
			protocolInstance_->write(bufferElement, ChannelFIFOAddress[channel], it.second.second);
			registerHeader = FSSRROCDefinitions::makeDACWriteHeader(rocStream.getFEWROCAddress(), it.first);
			//Insert channel
			BitManipulator::insertBits(registerHeader, 1, 16 + channel, 1);
		}
		else
		{
			//std::cout << __COUT_HDR_FL__ << "Register2: " << it.first << std::endl;
			if (it.second.second == 1 || it.second.second == 2)
			{
				registerHeader = FSSRROCDefinitions::makeDACSetHeader(rocStream.getFEWROCAddress(), it.first);
				//Insert channel
				BitManipulator::insertBits(registerHeader, 1, 16 + channel, 1);
			}
			else if (it.second.second == 0 || it.second.second == 5)
			{
				registerHeader = FSSRROCDefinitions::makeDACResetHeader(rocStream.getFEWROCAddress(), it.first);
				//Insert channel
				BitManipulator::insertBits(registerHeader, 1, 16 + channel, 1);
			}
			else
				std::cout << __COUT_HDR_FL__ << "Register value for : " << it.first
				<< " doesn't have a value I expect -> value = "
				<< it.second.second << std::endl;

		}
		//std::cout << __COUT_HDR_FL__ << "Register: " << it.first << " value: " << it.second.second << std::hex << " -> Data: " << registerHeader << std::dec << std::endl;
		protocolInstance_->write(bufferElement, STRIP_SC_CSR, registerHeader);
		protocolInstance_->waitClear(bufferElement, STRIP_SC_CSR, 0x80000000);

		//std::cout << __COUT_HDR_FL__ << "Register3: " << it.first << std::endl;
		//alternateBuffer += bufferElement;
		limitCount++;
		singleVectorCount++;

		if (limitCount == STIB_DAC_WRITE_MAX)
		{
			std::cout << __COUT_HDR_FL__ << "\tBuffer length:" << bufferElement.size() << std::endl;
			buffer.push_back(bufferElement);
			limitCount = 0;
			bufferElement.clear();
		}
		else if (singleVectorCount == rocDACs.getDACList().size()) //case for incomplete packet
		{
			buffer.push_back(bufferElement);
		}

		//buffer.push_back(bufferElement);
		//break;
	}
	std::cout << __COUT_HDR_FL__ << "\tDone making DAC Buffer" << std::endl;

}

//========================================================================================================================
void FSSRFirmware::makeMaskBuffer(std::string& buffer, unsigned int channel,
		const ROCStream& rocStream)
{
	std::cout << __COUT_HDR_FL__ << "Making mask! " << std::endl;
	makeMaskBuffer(buffer, channel, rocStream, "Kill");
	//    makeMaskSequence(buffer, channel, rocStream, "Inject");
}

//========================================================================================================================
void FSSRFirmware::makeMaskBuffer(std::string& buffer, unsigned int channel, const ROCStream& rocStream, const std::string& registerName)
{
	int chipId = rocStream.getFEWROCAddress();
	const std::string& mask = rocStream.getROCMask();
	std::cout << __COUT_HDR_FL__ << "\tMaking mask! Length = " << mask.length() << std::endl;
//	std::cout << __COUT_HDR_FL__ << "\tMask length: " << mask.length() << std::endl;
//	std::cout << __COUT_HDR_FL__ << "\tMask: " << mask << std::endl;

	unsigned int data[4] = { 0, 0, 0, 0 };

	char val;
	//int j = 0;
	for (unsigned int d = 0; d < 4; d++)
	{ //d goes from 0 to 4. 4 bytes
		//std::cout << __COUT_HDR_FL__ << "---------------------" << d << "-------------------" << std::endl;
		for (unsigned int m = 0; m < 8 * 4; m++)
		{ //m goes from 0 to 31, since each byte has 8 bits, there are 32 bits
			val = mask[(8 * 4 * d) + m]; //assigns to val the value of the corresponding bit. 0-31, 32-63, 64-95, 96-127. it goes through each of the 128 bits
			//std::cout << __COUT_HDR_FL__ << "---------------------" << j++ << std::endl;
			//std::cout << __COUT_HDR_FL__ << "data[" << d << "] before: " << std::hex << data[d] << std::dec << std::endl;
			data[d] |= (unsigned int) atoi(&val) << (8 * 4 - 1 - m);
			//std::cout << __COUT_HDR_FL__ << "(unsigned int) atoi(&val): " << (unsigned int) atoi(&val) << std::endl;
			//std::cout << __COUT_HDR_FL__ << "data[" << d << "] after: " << std::hex << data[d] << std::dec << std::endl;
			//std::cout << __COUT_HDR_FL__ << std::hex << "D: " << data[d] << " Val: " << (unsigned int)atoi(&val) << " index: " << std::dec << (8*4-1-m) << " bit: " << mask[(8*4*d)+m] << std::dec << std::endl;
		}
		//
	}

	int i, ierr;
	unsigned int w;
	unsigned char len = 4;
	unsigned char addr = 17;//Kill
	unsigned char bitMask = 1 << channel;
	unsigned char inst = WRITE;

	protocolInstance_->waitClear(buffer, STRIP_SC_CSR, 0x80000000);

	for (i = 0; i < 4; i++)
		//write(buffer, STRIP_SCI + 4 * i, data[i]);
		protocolInstance_->write(buffer, STRIP_SCI + 4 * (4 - i - 1), data[i]);

	w = 0x80000000 | (len << 24) | (bitMask << 16) | (inst << 10) | (addr << 5) | chipId;

	ierr = protocolInstance_->write(buffer, STRIP_SC_CSR, w);

	protocolInstance_->waitClear(buffer, STRIP_SC_CSR, 0x80000000);
}

//========================================================================================================================
void FSSRFirmware::makeMaskSequence(FirmwareSequence<uint64_t>& sequence,
		unsigned int channel, const ROCStream& rocStream)
{
	std::cout << __COUT_HDR_FL__ << "Making mask! " << std::endl;
	makeMaskSequence(sequence, channel, rocStream, "Kill");
	//    makeMaskSequence(sequence, channel, rocStream, "Inject");
}

//========================================================================================================================
void FSSRFirmware::makeMaskSequence(FirmwareSequence<uint32_t>& sequence,
		unsigned int channel, const ROCStream& rocStream)
{
	std::cout << __COUT_HDR_FL__ << "Making mask! " << std::endl;
	makeMaskSequence(sequence, channel, rocStream, "Kill");
	//    makeMaskSequence(channel,rocStream,sequence,"Inject");
}

//========================================================================================================================
void FSSRFirmware::makeMaskSequence(FirmwareSequence<uint64_t>& sequence,
		unsigned int channel, const ROCStream& rocStream,
		const std::string& registerName)
{
	int chipId = rocStream.getFEWROCAddress();//9, 14 or 21 bcast
	std::string mask = rocStream.getROCMask();
	std::cout << __COUT_HDR_FL__ << "Mask length: " << mask.length() << std::endl;

	uint64_t uInt64Data = 0;
	std::string stringData = "";

	//have to manually set every bit for mask writes.
	//reset fifo
	//download every bit (shift_in and shift_ctrl) to fifo (setup muxes and control lines)
	//configure muxes for readout
	//commence readout

	//FIFO Controls - byte 5 (7:0)
	//7 - FIFO Clock
	//6 - Shift Ctrl bit
	//MASK_CELL_H - Shift In bit
	//MUX Controls - byte 0 (7:0)
	//7 - Read En/Output MUX sel (1 for masks)
	//1 - Write En for mux
	//0 - Reset Fifo

	//reset fifo
	BitManipulator::insertBits(uInt64Data, 0x1, 56, 8);
	sequence.pushBack(ChannelFIFOAddress[channel], uInt64Data);

	//configure fifo for write
	BitManipulator::insertBits(uInt64Data, 0x2, 56, 8);
	sequence.pushBack(ChannelFIFOAddress[channel], uInt64Data);

	//Download every bit (shift_in and shift_control) to fifo (setup muxes and control lines)
	//Bit 7 of data is FIFO clock, bit 6 is shift_control, bit 5 is shift_in
	//start bits (ctrl 0, data 0 => ctrl 1, data 0)

	BitManipulator::insertBits(uInt64Data, 0x40, 16, 8);//(0<<7) | (1<<6) | (0<<5)
	sequence.pushBack(ChannelFIFOAddress[channel], uInt64Data);
	BitManipulator::insertBits(uInt64Data, 0xc0, 16, 8);//(1<<7) | (1<<6) | (0<<5) -> clock the data in the fifo
	sequence.pushBack(ChannelFIFOAddress[channel], uInt64Data);

	stringData = FSSRROCDefinitions::makeMaskWriteCommand(chipId,
			registerName, mask);

	uint8_t data;
	for (unsigned int s = 0; s < stringData.length(); s++)
		for (int b = 8 - 1; b >= 0 && (s * 8 + 8 - b < 13 + 128); b--)
		{
			//std::cout << __COUT_HDR_FL__ << "S: " << s << " val: " << stringData.data()[s] << " b: " << b << " bit: " << ((stringData.data()[s]>>b)&1) << std::endl;
			data = 0x40 | (((stringData.data()[s] >> b) & 1) << 5);
			BitManipulator::insertBits(uInt64Data, (uint64_t) data, 16, 8);
			sequence.pushBack(ChannelFIFOAddress[channel], uInt64Data);
			data |= 0x80;
			BitManipulator::insertBits(uInt64Data, (uint64_t) data, 16, 8);
			sequence.pushBack(ChannelFIFOAddress[channel], uInt64Data);
		}

	//reset Shift Control
	BitManipulator::insertBits(uInt64Data, 0x0, 16, 8);
	sequence.pushBack(ChannelFIFOAddress[channel], uInt64Data);
	BitManipulator::insertBits(uInt64Data, 0x80, 16, 8);
	sequence.pushBack(ChannelFIFOAddress[channel], uInt64Data);

	//configure muxes for readout
	BitManipulator::insertBits(uInt64Data, 0x0, 56, 8);
	sequence.pushBack(ChannelFIFOAddress[channel], uInt64Data);

	//commence readout
	BitManipulator::insertBits(uInt64Data, 0x80, 56, 8);
	sequence.pushBack(ChannelFIFOAddress[channel], uInt64Data);

}

//========================================================================================================================
void FSSRFirmware::makeMaskSequence(FirmwareSequence<uint32_t>& sequence,
		unsigned int channel, const ROCStream& rocStream,
		const std::string& registerName)
{}

//========================================================================================================================
std::string FSSRFirmware::readCSRRegister()
{
	std::string buffer;
	std::cout << __COUT_HDR_FL__ << "FSSR readCSRRegister" << std::endl;
	protocolInstance_->read(buffer,STRIP_CSR);
	return buffer;
}

//========================================================================================================================
std::string FSSRFirmware::readSCCSRRegister()
{
	std::string buffer;
	std::cout << __COUT_HDR_FL__ << "FSSR readCSRRegister" << std::endl;
	protocolInstance_->read(buffer,STRIP_SC_CSR);
	return buffer;
}

//========================================================================================================================
void FSSRFirmware::setFrequencyFromClockState(std::string& buffer, double frequency)
{
	std::cout << __COUT_HDR_FL__ << "Setting up clock frequency!!!" << std::endl;

	int quotient;
	int numerator;
	int denominator;
	double realClockFrequency;

	if (BitManipulator::readBits(stripCSRRegisterValue_, 17, 1) == 1) //if fastBCO is enabled
		quotient = 4;
	else //normal cases
		quotient = 8;

	if (isClockStateExternal()) //base freq: 54MHz
	{
		realClockFrequency = EXTERNAL_CLOCK_FREQUENCY / quotient; //this is the REAL frequency being used
	}
	else //base freq: 66.667MHz
	{
		realClockFrequency = INTERNAL_CLOCK_FREQUENCY / quotient; //this is the REAL frequency being used
	}

	double factor = frequency / realClockFrequency;

	//The device needs the denominator and the denominator to be load into a 5 bit register
	//It will take two initial numerator and denominator bigger than necessary (to do not loose precision)
	//and divide them for their gcd. If they still do not fit in 5 bit, they are trunked (divided by 2)
	//untill they are less than 32
	numerator = factor * 100; //we will work with 2 digits precision after the decimal point
	denominator = 100;

	do
	{
		//We will need the GCD at some point in order to simplify fractions //taken from other sources
		int gcd = numerator;
		int rest = denominator;
		int tmp;

		while (rest != 0)
		{
			tmp = rest;
			rest = gcd % tmp;
			gcd = tmp;
		}
		//Done finding the GCD

		if (gcd == 1) //if there's no GCD, just divide by 2 to find the nearest approssimation with less bits
		{
			numerator /= 2;
			denominator /= 2;
		}
		else
		{
			numerator /= gcd;
			denominator /= gcd;
		}

	}
	while (denominator >= 32 || numerator >= 32);
	std::cout << __COUT_HDR_FL__ << "Numerator: " << numerator << std::endl;
	std::cout << __COUT_HDR_FL__ << "Denominator: " << denominator << std::endl;
	setFrequencyRatio(buffer, numerator, denominator);
	std::cout << __COUT_HDR_FL__ << "Done with clock frequency setup!!!" << std::endl;
}
//========================================================================================================================
bool FSSRFirmware::isClockStateExternal() //returns true if the clock state is External
{
	if (BitManipulator::readBits(stripCSRRegisterValue_, 16, 1) == 1)
		return true;
	else
		return false;
}

//========================================================================================================================
void FSSRFirmware::setCSRRegister(uint32_t total)
{
	stripCSRRegisterValue_ = total;
}

//========================================================================================================================
void FSSRFirmware::setPacketSizeStripCSR(uint32_t size)
{
	if (size > 31)
		std::cout << __COUT_HDR_FL__
		<< "ERROR: Maximum packet size is 31 while here you are trying to set "
		<< size << " packets!" << std::endl;
	BitManipulator::insertBits(stripCSRRegisterValue_, size, 3, 5);
	//write(buffer,STRIP_CSR, stripSCRRegisterValue_);
}

//========================================================================================================================
void FSSRFirmware::enableChannelsStripCSR(bool channel0, bool channel1,
		bool channel2, bool channel3, bool channel4, bool channel5)
{
	BitManipulator::insertBits(stripCSRRegisterValue_, ((uint32_t) channel0)
			+ ((uint32_t) channel1 << 1) + ((uint32_t) channel2 << 2)
			+ ((uint32_t) channel3 << 3) + ((uint32_t) channel4 << 4)
			+ ((uint32_t) channel5 << 5), 8, 6);
}

//========================================================================================================================
void FSSRFirmware::setExternalBCOClockSourceStripCSR(std::string clockSource)
{
	if (clockSource == "External")
		BitManipulator::insertBits(stripCSRRegisterValue_, 1, 16, 1);
	else if (clockSource == "Internal")
		BitManipulator::insertBits(stripCSRRegisterValue_, 0, 16, 1);
}

//========================================================================================================================
void FSSRFirmware::setHaltStripCSR(bool set)
{
	BitManipulator::insertBits(stripCSRRegisterValue_, (uint32_t) set, 17, 1);
}

//========================================================================================================================
void FSSRFirmware::enableBCOStripCSR(bool enable)
{
	BitManipulator::insertBits(stripCSRRegisterValue_, (uint32_t) enable, 19, 1);
}

//========================================================================================================================
void FSSRFirmware::flushBuffersStripCSR(void)
{
	BitManipulator::insertBits(stripCSRRegisterValue_, 1, 20, 1);
}

//========================================================================================================================
void FSSRFirmware::resetTriggerCounterStripCSR(std::string& buffer)
{
	//Ryan's firmware is too fast so I need to make sure he understand the 1!!!!
	BitManipulator::insertBits(stripCSRRegisterValue_, 1, 21, 1);
	protocolInstance_->write(buffer, STRIP_CSR, stripCSRRegisterValue_);

	BitManipulator::insertBits(stripCSRRegisterValue_, 0, 21, 1);
	protocolInstance_->write(buffer, STRIP_CSR, stripCSRRegisterValue_);
}

//========================================================================================================================
void FSSRFirmware::resetBCOCounterStripCSR(void)
{
	BitManipulator::insertBits(stripCSRRegisterValue_, 1, 22, 1);
}

//========================================================================================================================
void FSSRFirmware::enableTriggerStripCSR(bool enable)
{
	BitManipulator::insertBits(stripCSRRegisterValue_, (uint32_t) enable, 23, 1);
}

//========================================================================================================================
void FSSRFirmware::sendTriggerDataStripCSR(bool send)
{
	BitManipulator::insertBits(stripCSRRegisterValue_, (uint32_t) send, 24, 1);
}

//========================================================================================================================
void FSSRFirmware::sendTriggerNumberStripCSR(bool send)
{
	BitManipulator::insertBits(stripCSRRegisterValue_, (uint32_t) send, 25, 1);
}

//========================================================================================================================
void FSSRFirmware::sendBCOStripCSR(bool send)
{
	BitManipulator::insertBits(stripCSRRegisterValue_, (uint32_t) send, 26, 1);
}

//========================================================================================================================
void FSSRFirmware::enableStreamStripCSR(bool enable)
{
	BitManipulator::insertBits(stripCSRRegisterValue_, (uint32_t) enable, 27, 1);
}

//========================================================================================================================
void FSSRFirmware::resetDCMStripCSR(bool clear)
{
	BitManipulator::insertBits(stripCSRRegisterValue_, (uint32_t) clear, 31, 1);
}

//========================================================================================================================
uint32_t FSSRFirmware::waitDCMResetStripCSR(void)
{
	uint32_t bitToCheck = 0;
	BitManipulator::insertBits(bitToCheck, 1, 31, 2);
	return bitToCheck;
}

//========================================================================================================================
void FSSRFirmware::resetDAC(void)
{
	BitManipulator::insertBits(stripResetRegisterValue_, 1, 27, 1);
}

//========================================================================================================================
void FSSRFirmware::resetLink(bool channel0, bool channel1, bool channel2,
		bool channel3, bool channel4, bool channel5)
{
	stripResetRegisterValue_ = 0;
	BitManipulator::insertBits(stripResetRegisterValue_,
			((uint32_t) channel0) + ((uint32_t) channel1 << 1)
			+ ((uint32_t) channel2 << 2) + ((uint32_t) channel3 << 3)
			+ ((uint32_t) channel4 << 4) + ((uint32_t) channel5 << 5),
			0, 6);
	BitManipulator::insertBits(stripResetRegisterValue_, 1, 29, 1);
	/*
     write(buffer, STRIP_RESET, (1<<28) +
     ((uint32_t)channel0) +
     ((uint32_t)channel1<<1) +
     ((uint32_t)channel2<<2) +
     ((uint32_t)channel3<<3) +
     ((uint32_t)channel4<<4) +
     ((uint32_t)channel5<<5)
     );
	 */
}

//========================================================================================================================
void FSSRFirmware::clearErrors(bool channel0, bool channel1, bool channel2,
		bool channel3, bool channel4, bool channel5)
{
	stripResetRegisterValue_ = 0;
	BitManipulator::insertBits(stripResetRegisterValue_,
			((uint32_t) channel0) + ((uint32_t) channel1 << 1)
			+ ((uint32_t) channel2 << 2) + ((uint32_t) channel3 << 3)
			+ ((uint32_t) channel4 << 4) + ((uint32_t) channel5 << 5),
			0, 6);
	BitManipulator::insertBits(stripResetRegisterValue_, 1, 29, 1);
}

//========================================================================================================================
void FSSRFirmware::clearFIFO(bool channel0, bool channel1, bool channel2,
		bool channel3, bool channel4, bool channel5)
{
	stripResetRegisterValue_ = 0;
	BitManipulator::insertBits(stripResetRegisterValue_,
			((uint32_t) channel0) + ((uint32_t) channel1 << 1)
			+ ((uint32_t) channel2 << 2) + ((uint32_t) channel3 << 3)
			+ ((uint32_t) channel4 << 4) + ((uint32_t) channel5 << 5),
			0, 6);
	BitManipulator::insertBits(stripResetRegisterValue_, 1, 30, 1);
}

//========================================================================================================================
void FSSRFirmware::resetChip(bool channel0, bool channel1, bool channel2,
		bool channel3, bool channel4, bool channel5)
{
	stripResetRegisterValue_ = 0;
	BitManipulator::insertBits(stripResetRegisterValue_,
			((uint32_t) channel0) + ((uint32_t) channel1 << 1)
			+ ((uint32_t) channel2 << 2) + ((uint32_t) channel3 << 3)
			+ ((uint32_t) channel4 << 4) + ((uint32_t) channel5 << 5),
			0, 6);
	BitManipulator::insertBits(stripResetRegisterValue_, 1, 31, 1);
}

//========================================================================================================================
void FSSRFirmware::setFrequencyRatio(std::string& buffer, int numerator, int denominator)
{
	//The device need to load numerator minus one and denominator minus one, with an internal address of 0x50 and 052 respectively
	protocolInstance_->write(buffer, STRIP_BCO_DCM, 0x80500000 + (numerator - 1)); //  Set BCOCLK numerator // was 0x80500003
	protocolInstance_->waitClear(buffer, STRIP_BCO_DCM, 0xf0000000); //  Wait DCM write to finish // was 0x80000000

	protocolInstance_->write(buffer, STRIP_BCO_DCM, 0x80520000 + (denominator - 1)); //  Set BCOCLK denominator // was 0x80520001
	protocolInstance_->waitClear(buffer, STRIP_BCO_DCM, 0xf0000000); //  Wait DCM write to finish - BCO frequency should be 13.513 MHz // was 0x80000000
}

//========================================================================================================================
void FSSRFirmware::BCOOffset(uint32_t offset)
{
	BitManipulator::insertBits(stripTriggerCSRRegisterValue_, offset, 0, 4);
}

//========================================================================================================================
void FSSRFirmware::selectSpyFIFO(uint32_t input)
{
	BitManipulator::insertBits(stripTriggerCSRRegisterValue_, input, 4, 3);
}

//========================================================================================================================
void FSSRFirmware::halt(bool halt)
{
	BitManipulator::insertBits(stripTriggerCSRRegisterValue_, (uint32_t) halt, 7, 1);
}

//========================================================================================================================
void FSSRFirmware::configureStripTriggerUnbiased(std::string& buffer)
{
	protocolInstance_->write(buffer, STRIP_TRIG_UNBIASED, 0x002805c); //  Configure unbiased trigger
}

//========================================================================================================================
void FSSRFirmware::configureTriggerInputs(std::string& buffer)
{
//	protocolInstance_->write(buffer, STRIP_TRIG_INPUT_0, 0x3f440000); //  FSSR GOTHIT trigger input channel 0,1
//	protocolInstance_->write(buffer, STRIP_TRIG_INPUT_1, 0x3f440000); //  FSSR GOTHIT trigger input channel 2,3
	protocolInstance_->write(buffer, STRIP_TRIG_INPUT_0, 0x0); //  FSSR GOTHIT trigger input channel 0,1
	protocolInstance_->write(buffer, STRIP_TRIG_INPUT_1, 0x0); //  FSSR GOTHIT trigger input channel 2,3
	protocolInstance_->write(buffer, STRIP_TRIG_INPUT_2, 0x0); //  FSSR GOTHIT trigger input channel 4,5
}

//========================================================================================================================
std::string FSSRFirmware::resetSlaveBCO(void)
{
	std::string buffer;
	/*TODO:make unambiguous by casting to uint32_t*/
	protocolInstance_->write(buffer, (uint32_t)0xc5000000, (uint32_t)0x00000008);
	return buffer;
}

/*
 //========================================================================================================================
 void FSSRFirmware::chipID(uint32_t size)
 {
 BitManipulator::insertBits(stripSCRegisterValue_, size, 0, 5);
 }

 //========================================================================================================================
 void FSSRFirmware::addressSlowControls(uint32_t size)
 {
 BitManipulator::insertBits(stripSCRegisterValue_, size, 5, 5);
 }

 //========================================================================================================================
 void FSSRFirmware::instructionSlowControls(uint32_t size)
 {
 BitManipulator::insertBits(stripSCRegisterValue_, size, 10, 3);
 }

 //========================================================================================================================
 void FSSRFirmware::channelreadSelect(uint32_t size)
 {
 BitManipulator::insertBits(stripSCRegisterValue_, size, 13, 3);
 }

 //========================================================================================================================
 void FSSRFirmware::channelMask(uint32_t size)
 {
 BitManipulator::insertBits(stripSCRegisterValue_, size, 16, 8);
 }

 //========================================================================================================================
 void FSSRFirmware::bitsLength(uint32_t length)
 {
 BitManipulator::insertBits(stripSCRegisterValue_, length, 26, 3);
 }


 //========================================================================================================================
 void FSSRFirmware::syncFallingBCO(bool sync)
 {
 BitManipulator::insertBits(stripSCRegisterValue_, (uint32_t)sync, 28, 1);
 }

 //========================================================================================================================
 void FSSRFirmware::syncRisingBCO(bool sync)
 {
 BitManipulator::insertBits(stripSCRegisterValue_, (uint32_t)sync, 29, 1);
 }

 //========================================================================================================================
 void FSSRFirmware::setRaw(bool set)
 {
 BitManipulator::insertBits(stripSCRegisterValue_, (uint32_t)set, 30, 1);
 }

 //========================================================================================================================
 void FSSRFirmware::initSlowControls(bool init)
 {
 BitManipulator::insertBits(stripSCRegisterValue_, (uint32_t)init, 31, 1);
 }

 //========================================================================================================================
 void FSSRFirmware::resetCount(bool reset)
 {
 BitManipulator::insertBits(stripAnalysisCSRRegisterValue_, (uint32_t)reset, 30, 1);
 }

 //========================================================================================================================
 void FSSRFirmware::setBCO_0(uint32_t void FSSRFirmware::BCOOffset(uint32_t offset)
 {
 BitManipulator::insertBits(stripTrigCSRRegisterValue_, offset, 0, 4);
 }input)
 {
 BitManipulator::insertBits(trigInputRegisterValue_, input, 0, 8);
 }

 //========================================================================================================================
 void FSSRFirmware::setBCO_1(uint32_t input)
 {
 BitManipulator::insertBits(trigInputRegisterValue_, input, 8, 8);
 }

 //========================================================================================================================
 void FSSRFirmware::trimFracBCO_0(uint32_t input)
 {
 BitManipulator::insertBits(trigInputRegisterValue_, input, 16, 4);
 }

 //========================================================================================================================
 void FSSRFirmware::trimFracBCO_1(uint32_t input)
 {
 BitManipulator::insertBits(trigInputRegisterValue_, input, 20, 4);
 }

 //========================================================================================================================
 void FSSRFirmware::enable_0(bool enable)
 {
 BitManipulator::insertBits(trigInputRegisterValue_, (uint32_t)enable, 28, 1);
 }

 //========================================================================================================================
 void FSSRFirmware::enable_1(bool enable)
 {
 BitManipulator::insertBits(trigInputRegisterValue_, (uint32_t)enable, 29, 1);
 }

 */
