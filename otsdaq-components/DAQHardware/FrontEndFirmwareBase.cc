#include "otsdaq-components/DAQHardware/FrontEndFirmwareBase.h"
#include "otsdaq-components/DAQHardware/PurdueFirmwareCore.h"
#include "otsdaq-core/MessageFacility/MessageFacility.h"
#include "otsdaq-core/Macros/CoutHeaderMacros.h"
#include "otsdaq-components/DAQHardware/OtsUDPFirmwareCore.h"

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
	if(choice == "OtsUDPFirmwareCore") //AUG-17-2017 RAR dissociated because function calls are entirely independent from PURDUE firmware calls //
		return new OtsUDPFirmwareCore(version);
	else
	{
		__SS__ << "Unknown firmware type choice: " << choice << std::endl;
		__COUT_ERR__ << ss.str();
		throw std::runtime_error(ss.str());
		return NULL;
	}
}
