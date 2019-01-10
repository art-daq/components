#ifndef _ots_FEOtsUDPHardwareBaseInterface_h_
#define _ots_FEOtsUDPHardwareBaseInterface_h_

#include "otsdaq-core/FECore/FEVInterface.h"
#include "otsdaq-components/DAQHardware/OtsUDPHardware.h"
#include "otsdaq-components/DAQHardware/OtsUDPFirmwareDataGen.h"

#include <string>

namespace ots
{

class FEOtsUDPHardwareBaseInterface : public FEVInterface, public OtsUDPHardware, public OtsUDPFirmwareDataGen
{

public:
	FEOtsUDPHardwareBaseInterface (const std::string& interfaceUID, const ConfigurationTree& theXDAQContextConfigTree, const std::string& interfaceConfigurationPath);
	virtual ~FEOtsUDPHardwareBaseInterface(void);

	void configure (void) override;
	void halt 	   (void) override;
	void pause 	   (void) override;
	void resume    (void) override;
	void start 	   (std::string runNumber) override;
	void stop 	   (void) override;
	//bool running   (void) override;

	virtual void universalRead		(char* address, char* readValue) override;
	virtual void universalWrite		(char* address, char* writeValue) override;

private:
};

}

#endif
