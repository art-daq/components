#ifndef _ots_FrontEndFirmwareBase_h_
#define _ots_FrontEndFirmwareBase_h_

#include <string>
#include <iostream>
#include <vector>
#include <assert.h>
//#include "otsdaq-core/ConfigurationInterface/DACStream.h"
#include "otsdaq-core/MessageFacility/MessageFacility.h"
#include "otsdaq-core/Macros/CoutHeaderMacros.h"
#include "otsdaq-components/DetectorConfiguration/ROCStream.h"

namespace ots
{


class FrontEndFirmwareBase
{

public:
	//factory method for choosing network protocol
	FrontEndFirmwareBase          (void);
    FrontEndFirmwareBase          (unsigned int version);
    virtual ~FrontEndFirmwareBase (void);
    virtual int init              (void);

    //ryan's firmware
    //TODO: these should never be called directly if the factory is used correctly, but
    //not all classes will implement every function (so no pure virtuals). should be obvious
    //that the wrong thing is happening if these are called
    virtual std::string read	  (char* address){assert(0);return 0;};
    virtual std::string write	  (char* address, char* data){assert(0);return 0;};

    virtual std::string  setDataDestination          (std::string ip, uint32_t port){assert(0);return "";};
    //virtual unsigned int write                       (std::string& buffer, uint64_t address, const std::string& value);
    virtual unsigned int write                       (std::string& buffer, uint64_t address, uint64_t data){assert(0);return 0;};
    virtual unsigned int write                       (std::string& buffer, uint32_t address, uint32_t data){assert(0);return 0;};
    virtual unsigned int waitSet                     (std::string& buffer, uint32_t address, uint32_t data, uint32_t timeout = 255){assert(0);return 0;};
    virtual unsigned int waitClear                   (std::string& buffer, uint32_t address, uint32_t data, uint32_t timeout = 255){assert(0);return 0;};
    virtual unsigned int read                        (std::string& buffer, uint64_t address){assert(0);return 0;};
    virtual unsigned int read                        (std::string& buffer, uint32_t address){assert(0);return 0;};
    virtual unsigned int getNumberOfBufferedCommands (std::string& buffer){assert(0);return 0;};
    virtual std::string  compareSendAndReceive       (const std::string& sentBuffer, std::string& acknowledgment){assert(0);return "";};
    virtual uint32_t     createRegisterFromValue     (std::string& readBuffer, std::string& receivedValue){assert(0);return 0;};

    //purdue firmware
//    virtual std::string  setDataDestination          (std::string ip, unsigned int port);
//    virtual unsigned int waitSet                     (std::string& buffer, unsigned int address, unsigned int data, unsigned int timeout = 255);
//    virtual unsigned int waitClear                   (std::string& buffer, unsigned int address, unsigned int data, unsigned int timeout = 255);
//    virtual unsigned int getNumberOfBufferedCommands (std::string& buffer);
//    virtual std::string  compareSendAndReceive       (const std::string& sentBuffer, std::string& acknowledgment);
//    virtual uint32_t     createRegisterFromValue     (std::string& readBuffer, std::string& receivedValue);

    //FSSROtsFirmware
//    virtual void makeDACSequence 				(FirmwareSequence<uint64_t>& sequence, unsigned int channel, const ROCStream& rocStream);
//    virtual void makeMaskSequence				(FirmwareSequence<uint64_t>& sequence, unsigned int channel, const ROCStream& rocStream);
//    virtual void makeDACSequence 				(FirmwareSequence<uint32_t>& sequence, unsigned int channel, const ROCStream& rocStream);
//    virtual void makeDACBuffer   				(std::string& buffer, unsigned int channel, const ROCStream& rocStream);
//    virtual void makeDACBuffer   				(std::vector<std::string>& buffer, unsigned int channel, const ROCStream& rocStream);
//    virtual void makeMaskSequence				(FirmwareSequence<uint32_t>& sequence, unsigned int channel, const ROCStream& rocStream);
//    virtual void makeMaskBuffer  				(std::string& buffer, unsigned int channel, const ROCStream& rocStream);

    //for generic interface
    /*these functions have to be in FirmwareBase because the FEWOtsGenericInterface wants to access them
     *through a pointer to FirmwareBase. Might want to change how that works.
     */
    virtual std::string readCSRRegister(void)
    {
    	assert(0);
    	std::cout << __COUT_HDR_FL__ << "Something bad happened!" << std::endl;
    	return "";
    };
//    virtual void makeDACBuffer(std::vector<std::string>& buffer, unsigned int channel, const ROCStream& rocStream){assert(0); return;};
//    virtual void makeMaskBuffer(std::string& buffer, unsigned int channel, const ROCStream& rocStream){assert(0); return;};

	static FrontEndFirmwareBase* getInstance(std::string choice, unsigned int version);
protected:
    unsigned int version_;
};

}

#endif
