#ifndef _ots_FEOtsUDPTemplateInterface_h_
#define _ots_FEOtsUDPTemplateInterface_h_

#include "otsdaq-core/FECore/FEVInterface.h"
#include "otsdaq-components/DAQHardware/OtsUDPHardware.h"
#include "otsdaq-components/DAQHardware/OtsUDPFirmwareDataGen.h"

#include <string>

namespace ots
{

class FEOtsUDPTemplateInterface	: public FEVInterface, public OtsUDPHardware, public OtsUDPFirmwareDataGen
{

public:
	FEOtsUDPTemplateInterface (const std::string& interfaceUID, const ConfigurationTree& theXDAQContextConfigTree, const std::string& interfaceConfigurationPath);
	virtual ~FEOtsUDPTemplateInterface(void);

	void configure (void) override;
	void halt 	   (void) override;
	void pause 	   (void) override;
	void resume    (void) override;
	void start 	   (std::string runNumber) override;
	void stop 	   (void) override;
	bool running   (void) override;

	virtual int universalRead		(char* address, char* readValue) override;
	virtual void universalWrite		(char* address, char* writeValue) override;

private:


public: // FEMacro 'TestMyMacro' generated, Oct-03-2018 04:54:57, by 'admin' using MacroMaker.
	void TestMyMacro	(frontEndMacroInArgs_t argsIn, frontEndMacroOutArgs_t argsOut);
};

}

#endif
