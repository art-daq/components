#ifndef _ots_OtsUDPFirmware_h_
#define _ots_OtsUDPFirmware_h_

#include <string>

#include "otsdaq-components/DAQHardware/FrontEndFirmwareBase.h"

namespace ots
{

class OtsUDPFirmware
{
public:
    OtsUDPFirmware (unsigned int version, std::string type);
    virtual ~OtsUDPFirmware(void);
    int  init(void);

    //FEW specific methods

protected:

    FrontEndFirmwareBase* protocolInstance_;

    void write(std::string& buffer, uint64_t address, uint64_t value);
    //void write(std::string& buffer, uint64_t address, const std::string& value);
    void read (std::string& buffer, uint64_t address);

    std::string universalRead	  (char* address);
    std::string universalWrite	  (char* address, char* data);

    void setNumberOfBurstWords    (std::string& buffer, uint64_t numberOfWords);
    void setBurstWordsRate        (std::string& buffer, uint64_t interval);
    std::string startBurst        (void);
    std::string stopBurst         (void);
    void readBurstDestinationIP   (std::string& buffer);
    void readBurstDestinationMAC  (std::string& buffer);
    void readBurstDestinationPort (std::string& buffer);


    void writeBurstDestinationIP  (std::string& buffer, const uint64_t value);
    void writeBurstDestinationMAC (std::string& buffer, const uint64_t value);
    void writeBurstDestinationPort(std::string& buffer, const uint64_t value);
    void setBurstDestinationAsSelf(std::string& buffer) { buffer.resize(0); buffer += (char)2; }

    void setupBurstDestination    (std::string& buffer, const std::string& ipAddress, const uint64_t& port);

//    uint32_t stripTriggerCSRRegisterValue_;
	//Registers setters
//	void BCOOffset(uint32_t offset);
//	void selectSpyFIFO(uint32_t input);
//	void halt(bool halt);


//	std::string  resetSlaveBCO(void);

};

}

#endif
