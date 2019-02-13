#ifndef _ots_FEOtsUDPLCLS2InterfaceConfiguration_h_
#define _ots_FEOtsUDPLCLS2InterfaceConfiguration_h_

#include <string>
#include "otsdaq-core/ConfigurationDataFormats/FEInterfaceConfigurationBase.h"

namespace ots {

class FEOtsUDPLCLS2InterfaceConfiguration : public FEInterfaceConfigurationBase {
 public:
  FEOtsUDPLCLS2InterfaceConfiguration(void);
  virtual ~FEOtsUDPLCLS2InterfaceConfiguration(void);

  // Methods
  void init(ConfigurationManager *configManager);

  // Getters
  bool getStatus(std::string interfaceID) const;
  bool getChannelStatus(std::string interfaceID, unsigned int channel) const;
  unsigned int getFirmwareVersion(std::string interfaceID) const;
  std::string getIPAddress(std::string interfaceID) const;
  unsigned int getPort(std::string interfaceID) const;
  std::string getInterfaceIPAddress(std::string interfaceID) const;
  unsigned int getInterfacePort(std::string interfaceID) const;
  std::string getStreamingIPAddress(std::string interfaceID) const;
  unsigned int getStreamingPort(std::string interfaceID) const;
  int getNumberOfWords(std::string interfaceID) const;
  unsigned int getDataRate(std::string interfaceID) const;

 private:
  enum {
    InterfaceID,
    Status,
    FirmwareVersion,
    IPAddress,
    Port,
    InterfaceIPAddress,
    InterfacePort,
    StreamingIPAddress,
    StreamingPort,
    NumberOfWords,
    DataRate,
  };
};
}  // namespace ots
#endif
