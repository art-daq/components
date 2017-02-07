#include "otsdaq-components/DAQHardware/FrontEndFirmwareBase.h"
#include "otsdaq-components/DAQHardware/OtsFirmwareCore.h"
#include "otsdaq-components/DAQHardware/PurdueFirmwareCore.h"
#include "otsdaq-core/MessageFacility/MessageFacility.h"
#include "otsdaq-core/Macros/CoutHeaderMacros.h"

using namespace ots;
//class PurdueFirmwareCore;
//class OtsFirmwareCore;
//========================================================================================================================
FrontEndFirmwareBase::FrontEndFirmwareBase(unsigned int version)
: version_(version)
{}

//========================================================================================================================
FrontEndFirmwareBase::~FrontEndFirmwareBase(void)
{}

//========================================================================================================================
int FrontEndFirmwareBase::init(void)
{
	return 0;
}

//========================================================================================================================
FrontEndFirmwareBase* FrontEndFirmwareBase::getInstance(std::string choice, unsigned int version)
{
	if(choice == "PurdueFirmwareCore") //could also use string and: if(choice == "purdue") etc.
		return new PurdueFirmwareCore(version);
	if(choice == "OtsFirmwareCore")
		return new OtsFirmwareCore(version);
	else
		return NULL;
}
