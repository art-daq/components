#ifndef _ots_FEPurdueNetworkMasterInterfaceConfiguration_h_
#define _ots_FEPurdueNetworkMasterInterfaceConfiguration_h_

#include <string>
#include "otsdaq-core/ConfigurationDataFormats/FEInterfaceTableBase.h"

namespace ots
{
class FEPurdueNetworkMasterInterfaceConfiguration : public FEInterfaceTableBase
{
  public:
	FEPurdueNetworkMasterInterfaceConfiguration(void);
	virtual ~FEPurdueNetworkMasterInterfaceConfiguration(void);

	// Methods
	void init(ConfigurationManager* configManager);

	// Getters
	bool         getStatus(std::string interfaceID) const;
	unsigned int getFirmwareVersion(std::string interfaceID) const;
	std::string  getIPAddress(std::string interfaceID) const;
	unsigned int getPort(std::string interfaceID) const;
	std::string  getInterfaceIPAddress(std::string interfaceID) const;
	unsigned int getInterfacePort(std::string interfaceID) const;

  private:
	enum
	{
		InterfaceID,
		Status,
		FirmwareVersion,
		IPAddress,
		Port,
		InterfaceIPAddress,
		InterfacePort
	};
};
}
#endif
