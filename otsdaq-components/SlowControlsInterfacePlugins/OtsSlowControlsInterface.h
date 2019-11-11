#ifndef _ots_OtsSlowControlsInterface_h
#define _ots_OtsSlowControlsInterface_h

#include <array>
#include <string>

#include "otsdaq/NetworkUtilities/ReceiverSocket.h"  // Make sure this is always first because <sys/types.h> (defined in Socket.h) must be first
#include "otsdaq/SlowControlsCore/SlowControlsVInterface.h"
using namespace ots;
//{

class OtsSlowControlsInterface : public SlowControlsVInterface
{
  public:
	OtsSlowControlsInterface(const std::string&       pluginType,
	                         const std::string&       interfaceUID,
	                         const ConfigurationTree& theXDAQContextConfigTree,
	                         const std::string&       controlsConfigurationPath);
	~OtsSlowControlsInterface();

	void initialize();
	void destroy();

	std::string                                getList(std::string format);
	void                                       subscribe(std::string Name);
	void                                       subscribeJSON(std::string List);
	void                                       unsubscribe(std::string Name);
	std::array<std::string, 4>                 getCurrentValue(std::string Name);
	std::array<std::array<std::string, 5>, 10> getPVHistory(std::string Name);
	std::array<std::string, 9>                 getSettings(std::string Name);
};

//}

#endif
