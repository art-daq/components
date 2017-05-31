#ifndef _ots_OtsUDPHardware_h_
#define _ots_OtsUDPHardware_h_

#include "otsdaq-components/DAQHardware/FrontEndHardwareBase.h"
#include "otsdaq-core/NetworkUtilities/TransceiverSocket.h"

namespace ots
{

class OtsUDPHardware : public FrontEndHardwareBase, public TransceiverSocket
{

public:
	OtsUDPHardware (std::string interfaceIPAddress, unsigned int interfacePort, std::string boardIPAddress, unsigned int boardPort);
	virtual ~OtsUDPHardware(void);

	int write              (const std::string&              writeBuffer);
	int write              (const std::vector<std::string>& writeBuffer);
	int writeAndAcknowledge(const std::string&              writeBuffer);
	int writeAndAcknowledge(const std::vector<std::string>& writeBuffer);
	int read               (const std::string&              writeBuffer, std::string&              readBuffer);
	int read               (const std::vector<std::string>& writeBuffer, std::vector<std::string>& readBuffer);

	int clearReadSocket	   ();
	//
//    virtual int write(uint64_t address, const std::string& value){return 0;}
//    virtual int read (uint64_t address, std::string& value){return 0;}

protected:
	OtsUDPHardware (std::string boardIPAddress, unsigned int boardPort);
	Socket      OtsUDPBoard_;
	std::string acknowledgment_;
};

}

#endif
