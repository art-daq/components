#ifndef _ots_OtsFirmwareCore_h_
#define _ots_OtsFirmwareCore_h_

#include "otsdaq-components/DAQHardware/FirmwareSequence.h"
#include "otsdaq-components/DAQHardware/FrontEndFirmwareBase.h"


#include <string>
//#include <cstdint>

namespace ots
{
class FrontEndFirmwareBase;
class OtsFirmwareCore : public FrontEndFirmwareBase
{

public:

    OtsFirmwareCore                               (unsigned int version);
    virtual ~OtsFirmwareCore                      (void);
    virtual int init                  			  (void);

    std::string read	  (char* address);
    std::string write	  (char* address, char* data);

    virtual std::string  setDataDestination          (std::string ip, uint32_t port);
    virtual unsigned int write                       (std::string& buffer, uint64_t address, uint64_t data);
    virtual unsigned int write                       (std::string& buffer, uint32_t address, uint32_t data);
//    virtual unsigned int waitSet                     (std::string& buffer, unsigned int address, unsigned int data, unsigned int timeout = 255);
    virtual unsigned int waitClear                   (std::string& buffer, uint32_t address, uint32_t data, uint32_t timeout = 255);
    virtual unsigned int read                        (std::string& buffer, uint64_t address);
    virtual unsigned int read                        (std::string& buffer, uint32_t address);
    virtual unsigned int getNumberOfBufferedCommands (std::string& buffer);
    virtual std::string  compareSendAndReceive       (const std::string& sentBuffer, std::string& acknowledgment);
    virtual uint32_t     createRegisterFromValue     (std::string& readBuffer, std::string& receivedValue);

};

}

#endif
